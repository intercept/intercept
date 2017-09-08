#include "extensions.hpp"
#include "controller.hpp"
#include "export.hpp"
#include "invoker.hpp"
#include "signing.hpp"
#ifdef __linux__
#include <dlfcn.h>
#include <link.h>
#endif

#define PLUGIN_MIN_API_VERSION 1

namespace intercept {

    extensions::extensions() {
        functions.get_type_structure = client_function_defs::get_type_structure;
        functions.get_binary_function = client_function_defs::get_binary_function;
        functions.get_binary_function_typed = client_function_defs::get_binary_function_typed;
        functions.get_nular_function = client_function_defs::get_nular_function;
        functions.get_unary_function = client_function_defs::get_unary_function;
        functions.get_unary_function_typed = client_function_defs::get_unary_function_typed;
        functions.invoke_raw_binary = client_function_defs::invoke_raw_binary_nolock;
        functions.invoke_raw_nular = client_function_defs::invoke_raw_nular_nolock;
        functions.invoke_raw_unary = client_function_defs::invoke_raw_unary_nolock;
        functions.invoker_lock = client_function_defs::invoker_lock;
        functions.invoker_unlock = client_function_defs::invoker_unlock;
        functions.get_engine_allocator = client_function_defs::get_engine_allocator;
        functions.register_sqf_function = client_function_defs::register_sqf_function;
        functions.register_sqf_function_unary = client_function_defs::register_sqf_function_unary;
        functions.register_sqf_function_nular = client_function_defs::register_sqf_function_nular;
        functions.register_sqf_type = client_function_defs::register_sqf_type;
        functions.register_plugin_interface = [](r_string module_name_, std::string_view name_, uint32_t api_version_, void* interface_class_) {
            return extensions::get().register_plugin_interface(module_name_, name_, api_version_, interface_class_);
        };
        functions.list_plugin_interfaces = [](std::string_view name_) {
            return extensions::get().list_plugin_interfaces(name_);
        };
        functions.request_plugin_interface = [](r_string module_name_, std::string_view name_, uint32_t api_version_) {
            return extensions::get().request_plugin_interface(module_name_, name_, api_version_);
        };
        functions.get_pbo_files_list = client_function_defs::get_pbo_files_list;

        std::string arg_line = _searcher.get_command_line();
        std::transform(arg_line.begin(), arg_line.end(), arg_line.begin(), ::tolower);
        if (arg_line.find("-intreloadall"sv) != std::string::npos) {
            do_reload = true;
        } else {
            do_reload = false;
        }
    }

    extensions::~extensions() {
        for (auto& kv : _modules) {
            unload(kv.first);
        }
    }

    void extensions::attach_controller() {
        controller::get().add("list_extensions"sv, std::bind(&extensions::list, this, std::placeholders::_1, std::placeholders::_2));
        controller::get().add("load_extension"sv, [this](const arguments& args_, std::string&) { return load(args_.as_string(0), args_.size() > 1 ? args_.as_string(1) : ""); });
        controller::get().add("unload_extension"sv, [this](const arguments& args_, std::string&) { return unload(args_.as_string(0)); });
    }

    void extensions::reload_all() {
        if (!do_reload)
            return;
        LOG(INFO) << "Doing client DLL reload."sv;
        auto current_modules = _modules;
        for (auto module : current_modules) {
            unload(module.first);
            load(module.first,{});
        }
    }

    bool extensions::load(const std::string& path_, std::optional<std::string> certPath) {

    #ifndef __linux__
        using string_type = std::wstring;
        using string_view_type = std::wstring_view;
        string_view_type bad_chars = L".\\/:?\"<>|"sv;
        int length = MultiByteToWideChar(CP_UTF8, 0, path_.data(), path_.length(), 0, 0);
        string_type path;
        path.resize(length);
        MultiByteToWideChar(CP_UTF8, 0, path_.data(), path_.length(), path.data(), length);
    #else
        using string_type = std::string;
        using string_view_type = std::string_view;
        string_type path = path_;
        string_view_type bad_chars = ".\\/:?\"<>|"sv;
    #endif

        LOG(INFO) << "Load requested ["sv << path_ << "]"sv;

        if (_modules.find(path_) != _modules.end()) {
            LOG(ERROR) << "Module already loaded ["sv << path << "]"sv;
            return true;
        }

        //Filter out bad chars
        for (auto it = path.begin(); it < path.end(); ++it) {
            bool found = bad_chars.find(*it) != std::string::npos;
            if (found) {
                LOG(ERROR) << "Client plugin: "sv << path << " contains illegal characters in its name."sv;
                return false;
            }
        }

        auto full_path = _searcher.find_extension(path);
        if (!full_path)
            return false;

    #ifndef __linux__
        //certificate check
        if (certPath && certPath->length() != 0) {
            r_string certData = invoker::get().invoke_raw("loadfile", *certPath);
            if (certData.capacity() != 0) {
                cert::signing sign_checker(*full_path, certData);
                if (!sign_checker.verify()) {
                    LOG(ERROR) << "PluginLoad failed, code signing certificate invalid "sv << " [" << *full_path << "]";
                }
            }
        }
    #endif









#ifndef __linux__  //Lazyness
        if (do_reload) {
            LOG(INFO) << "Loading plugin from temp file."sv;
            wchar_t tmpPath[MAX_PATH + 1], buffer[MAX_PATH + 1];

            if (!GetTempPathW(MAX_PATH, tmpPath)) {
                LOG(ERROR) << "GetTempPath() failed, e="sv << GetLastError();
                return false;
            }
            if (!GetTempFileNameW(tmpPath, L"intercept_temp", 0, buffer)) {
                LOG(ERROR) << "GetTempFileName() failed, e="sv << GetLastError();
                return false;
            }
            std::wstring temp_filename = buffer;
            LOG(INFO) << "Temp file: "sv << temp_filename;
            if (!CopyFileW(full_path->c_str(), temp_filename.c_str(), FALSE)) {
                DeleteFileW(temp_filename.c_str());
                if (!CopyFileW(full_path->c_str(), temp_filename.c_str(), FALSE)) {
                    LOG(ERROR) << "CopyFile() , e="sv << GetLastError();
                    return false;
                }
            }
            full_path = temp_filename;
        }
#endif

#ifdef __linux__
        auto dllHandle = dlopen(full_path->c_str(), RTLD_NOW | RTLD_GLOBAL);
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e="sv << dlerror() << " [" << *full_path << "]";
            return false;
        }
#else
        auto dllHandle = LoadLibraryW(full_path->c_str());
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e="sv << GetLastError() << " [" << *full_path << "]";
            return false;
        }
#endif

    #ifndef __linux__
        length = WideCharToMultiByte(CP_UTF8, 0, (*full_path).data(), (*full_path).length(), nullptr, 0, nullptr, nullptr);
        std::string utf8_name;
        utf8_name.resize(length);
        WideCharToMultiByte(CP_UTF8, 0, (*full_path).data(), (*full_path).length(), utf8_name.data(), length, nullptr, nullptr);
    #else
        string_type utf8_name = *full_path;
    #endif

        auto new_module = module::entry(utf8_name, dllHandle);

#ifdef __linux__
#define GET_PROC_ADDR dlsym
#else
#define GET_PROC_ADDR GetProcAddress
#endif

        new_module.functions.api_version = reinterpret_cast<module::api_version_func>(GET_PROC_ADDR(dllHandle, "api_version"));
        new_module.functions.assign_functions = reinterpret_cast<module::assign_functions_func>(GET_PROC_ADDR(dllHandle, "assign_functions"));

        //First verify that this is a valid Plugin before we initialize the rest.

        if (!new_module.functions.api_version) {
            LOG(ERROR) << "Module "sv << path << " failed to define the api_version function."sv;
            return false;
        }

        if (new_module.functions.api_version() < PLUGIN_MIN_API_VERSION) {
            LOG(ERROR) << "Module "sv << path << " has invalid API Version. Has: "sv << new_module.functions.api_version() << " Need: "sv << PLUGIN_MIN_API_VERSION;
            return false;
        }

        if (!new_module.functions.assign_functions) {
            LOG(ERROR) << "Module "sv << path << " failed to define the assign_functions function."sv;
            return false;
        }

        new_module.functions.handle_unload = reinterpret_cast<module::handle_unload_func>(GET_PROC_ADDR(dllHandle, "handle_unload"));
        new_module.functions.handle_unload_internal = reinterpret_cast<module::handle_unload_func>(GET_PROC_ADDR(dllHandle, "handle_unload_internal"));
        new_module.functions.mission_end = reinterpret_cast<module::mission_end_func>(GET_PROC_ADDR(dllHandle, "mission_end"));
        new_module.functions.on_frame = reinterpret_cast<module::on_frame_func>(GET_PROC_ADDR(dllHandle, "on_frame"));
        //new_module.functions.on_signal = (module::on_signal_func)GetProcAddress(dllHandle, "on_signal"); //#TODO why is this disabled?!
        new_module.functions.post_init = reinterpret_cast<module::post_init_func>(GET_PROC_ADDR(dllHandle, "post_init"));
        new_module.functions.pre_init = reinterpret_cast<module::pre_init_func>(GET_PROC_ADDR(dllHandle, "pre_init"));
        new_module.functions.pre_start = reinterpret_cast<module::pre_start_func>(GET_PROC_ADDR(dllHandle, "pre_start"));
        new_module.functions.register_interfaces = reinterpret_cast<module::register_interfaces_func>(GET_PROC_ADDR(dllHandle, "register_interfaces"));
        new_module.functions.client_eventhandler = reinterpret_cast<module::client_eventhandler_func>(GET_PROC_ADDR(dllHandle, "client_eventhandler"));
        new_module.functions.mission_stopped = reinterpret_cast<module::mission_stopped_func>(GET_PROC_ADDR(dllHandle, "mission_stopped"));

#define EH_PROC_DEF(name, ...) new_module.eventhandlers.name = (module::name##_func)GET_PROC_ADDR(dllHandle, #name);
        EH_LIST(EH_PROC_DEF)


        new_module.functions.assign_functions(functions, r_string(new_module.name));
        new_module.path = *full_path;
        _modules[path_] = new_module;

        if (new_module.functions.register_interfaces)
            new_module.functions.register_interfaces();

        LOG(INFO) << "Load completed ["sv << path << "]"sv;
        return false;
    }

    bool extensions::unload(std::string path_) {
        LOG(INFO) << "Unload requested ["sv << path_ << "]"sv;
        auto module = _modules.find(path_);
        if (module == _modules.end()) {
            LOG(INFO) << "Unload failed, module not loaded ["sv << path_ << "]"sv;
            return true;
        }

        std::map<r_string, std::vector<r_string>> interfaces_to_unload;
        for (auto& iface : module->second.exported_interfaces) {
            auto found = exported_interfaces.find(iface);
            if (found != exported_interfaces.end())
                interfaces_to_unload.insert({iface.name, found->second.modules_using_interface});
        }

        for (auto& entry : interfaces_to_unload) {
            auto& iface_name = entry.first;
            auto& module_list = entry.second;
            for (auto& plugin : _modules) {
                if (!plugin.second.functions.on_interface_unload) continue;
                auto found = std::find(module_list.begin(), module_list.end(), plugin.first);
                if (found != module_list.end()) {
                    plugin.second.functions.on_interface_unload(iface_name);
                }
            }
        }

        if (module->second.functions.handle_unload) {
            module->second.functions.handle_unload();
        }

        if (module->second.functions.handle_unload_internal) {
            module->second.functions.handle_unload_internal();
        }

#ifdef __linux
        if (dlclose(module->second.handle)) {  //returms 0 on success
            LOG(INFO) << "dlclose() failed during unload, e="sv << dlerror();
#else
        if (!FreeLibrary(module->second.handle)) {
            LOG(INFO) << "FreeLibrary() failed during unload, e="sv << GetLastError();
#endif
            return false;
        }

        LOG(INFO) << "Unload complete ["sv << path_ << "]"sv; //path_ sometimes becomes corrupted if placed after the erase

        _modules.erase(path_);

        return true;
    }

    bool extensions::list(const arguments&, std::string& result) {
        LOG(INFO) << "Listing loaded modules"sv;
        std::string res;

        for (auto& kv : _modules) {
            res = res + kv.first + ", ";
            LOG(INFO) << "\t" << kv.first;
        }

        result = res;

        return false;
    }

    register_plugin_interface_result extensions::register_plugin_interface(r_string module_name_, std::string_view name_, uint32_t api_version_, void* interface_class_) {
        module::plugin_interface_identifier ident{name_, module_name_, api_version_};
        if (exported_interfaces.find(ident) != exported_interfaces.end())
            return register_plugin_interface_result::interface_already_registered;

        auto module_with_same_name = std::find_if(exported_interfaces.begin(), exported_interfaces.end(),
                                                  [&name_](const std::pair<module::plugin_interface_identifier, module::plugin_interface>& item) {
                                                      return item.first.name == name_;
                                                  });

        if (module_with_same_name != exported_interfaces.end() &&     //Already one interface with same name registered
            module_with_same_name->first.module_name != module_name_  //But by a different plugin!
        )
            return register_plugin_interface_result::interface_name_occupied_by_other_module;

        //No duplicates and module owns that interface so.. Insert it
        exported_interfaces.insert({ident, {ident, interface_class_}});

        return register_plugin_interface_result::success;
    }

    std::pair<r_string, auto_array<uint32_t>> extensions::list_plugin_interfaces(std::string_view name_) {
        auto_array<uint32_t> ret;
        r_string owning_module;
        for (auto& module : exported_interfaces) {
            if (module.first.name == name_) {
                ret.push_back(module.first.api_version);
                owning_module = module.first.module_name;
            }
        }
        return {owning_module, std::move(ret)};
    }

    void* extensions::request_plugin_interface(r_string module_name_, std::string_view name_, uint32_t api_version_) {
        //#TODO store name as hash for faster lookups
        auto iface = std::find_if(exported_interfaces.begin(), exported_interfaces.end(),
                                  [&name_, &api_version_](const std::pair<module::plugin_interface_identifier, module::plugin_interface>& item) {
                                      return item.first.api_version == api_version_ && item.first.name == name_;  //compare cheaper stuff first
                                  });
        if (iface != exported_interfaces.end()) {
            iface->second.modules_using_interface.push_back(module_name_);
            return ((*iface).second.interface_class);
        }
        return nullptr;
    }

    std::unordered_map<std::string, module::entry>& extensions::modules() {
        return _modules;
    }

}  // namespace intercept
