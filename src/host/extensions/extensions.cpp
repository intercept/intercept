#include "extensions.hpp"
#include "controller.hpp"
#include "export.hpp"
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

        std::string arg_line = _searcher.get_command_line();
        std::transform(arg_line.begin(), arg_line.end(), arg_line.begin(), ::tolower);
        if (arg_line.find("-intreloadall") != std::string::npos) {
            do_reload = true;
        } else {
            do_reload = false;
        }
    }

    extensions::~extensions() {
        for (auto & kv : _modules) {
            arguments temp(kv.first);
            std::string result_temp;
            unload(temp, result_temp);
        }
    }

    void extensions::attach_controller() {
        controller::get().add("list_extensions", std::bind(&extensions::list, this, std::placeholders::_1, std::placeholders::_2));
        controller::get().add("load_extension", std::bind(&extensions::load, this, std::placeholders::_1, std::placeholders::_2));
        controller::get().add("unload_extension", std::bind(&extensions::unload, this, std::placeholders::_1, std::placeholders::_2));
    }

    bool extensions::load(const arguments & args_, std::string &) {
        return do_load(args_.as_string(0));
    }

    void extensions::reload_all() {
        if (!do_reload)
            return;
        LOG(INFO) << "Doing client DLL reload.";
        auto current_modules = _modules;
        for (auto module : current_modules) {
            do_unload(module.first);
            do_load(module.first);
        }
    }

    bool extensions::do_load(const std::string &path_) {
        std::string path = path_;
        LOG(INFO) << "Load requested [" << path_ << "]";

        if (_modules.find(path) != _modules.end()) {
            LOG(ERROR) << "Module already loaded [" << path << "]";
            return true;
        }

        std::string bad_chars = ".\\/:?\"<>|";
        for (auto it = path.begin(); it < path.end(); ++it) {
            bool found = bad_chars.find(*it) != std::string::npos;
            if (found) {
                LOG(ERROR) << "Client plugin: " << path << " contains illegal characters in its name.";
                return false;
            }
        }

        auto full_path = _searcher.find_extension(path);
        if (!full_path)
            return false;

    #ifndef __linux__ //Lazyness
        if (do_reload) {
            LOG(INFO) << "Loading plugin from temp file.";
            char tmpPath[MAX_PATH + 1], buffer[MAX_PATH + 1];

            if (!GetTempPathA(MAX_PATH, tmpPath)) {
                LOG(ERROR) << "GetTempPath() failed, e=" << GetLastError();
                return false;
            }
            if (!GetTempFileNameA(tmpPath, "intercept_temp", 0, buffer)) {
                LOG(ERROR) << "GetTempFileName() failed, e=" << GetLastError();
                return false;
            }
            std::string temp_filename = buffer;
            LOG(INFO) << "Temp file: " << temp_filename;
            if (!CopyFileA(full_path->c_str(), temp_filename.c_str(), FALSE)) {
                DeleteFile(temp_filename.c_str());
                if (!CopyFileA(full_path->c_str(), temp_filename.c_str(), FALSE)) {
                    LOG(ERROR) << "CopyFile() , e=" << GetLastError();
                    return false;
                }
            }
            full_path = temp_filename;
        }
    #endif

    #ifdef __linux__
        auto dllHandle = dlopen(full_path->c_str(), RTLD_NOW | RTLD_GLOBAL);
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e=" << dlerror() << " [" << *full_path << "]";
            return false;
        }
    #else
        auto dllHandle = LoadLibrary(full_path->c_str());
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e=" << GetLastError() << " [" << *full_path << "]";
            return false;
        }
    #endif

        auto new_module = module::entry(*full_path, dllHandle);

    #ifdef __linux__
    #define GET_PROC_ADDR dlsym
    #else
    #define GET_PROC_ADDR GetProcAddress
    #endif

        new_module.functions.api_version = reinterpret_cast<module::api_version_func>(GET_PROC_ADDR(dllHandle, "api_version"));
        new_module.functions.assign_functions = reinterpret_cast<module::assign_functions_func>(GET_PROC_ADDR(dllHandle, "assign_functions"));

        //First verify that this is a valid Plugin before we initialize the rest.

        if (!new_module.functions.api_version) {
            LOG(ERROR) << "Module " << path << " failed to define the api_version function.";
            return false;
        }

        if (new_module.functions.api_version() < PLUGIN_MIN_API_VERSION) {
            LOG(ERROR) << "Module " << path << " has invalid API Version. Has: " << new_module.functions.api_version() << " Need: " << PLUGIN_MIN_API_VERSION;
            return false;
        }

        if (!new_module.functions.assign_functions) {
            LOG(ERROR) << "Module " << path << " failed to define the assign_functions function.";
            return false;
        }

        new_module.functions.handle_unload = reinterpret_cast<module::handle_unload_func>(GET_PROC_ADDR(dllHandle, "handle_unload"));
        new_module.functions.mission_end = reinterpret_cast<module::mission_end_func>(GET_PROC_ADDR(dllHandle, "mission_end"));
        new_module.functions.on_frame = reinterpret_cast<module::on_frame_func>(GET_PROC_ADDR(dllHandle, "on_frame"));
        //new_module.functions.on_signal = (module::on_signal_func)GetProcAddress(dllHandle, "on_signal"); //#TODO why is this disabled?!
        new_module.functions.post_init = reinterpret_cast<module::post_init_func>(GET_PROC_ADDR(dllHandle, "post_init"));
        new_module.functions.pre_init = reinterpret_cast<module::pre_init_func>(GET_PROC_ADDR(dllHandle, "pre_init"));
        new_module.functions.pre_start = reinterpret_cast<module::pre_start_func>(GET_PROC_ADDR(dllHandle, "pre_start"));
        new_module.functions.mission_stopped = reinterpret_cast<module::mission_stopped_func>(GET_PROC_ADDR(dllHandle, "mission_stopped"));

    #define EH_PROC_DEF(x) new_module.eventhandlers.x = (module::x##_func)GET_PROC_ADDR(dllHandle, #x)

        EH_PROC_DEF(anim_changed);
        EH_PROC_DEF(anim_done);
        EH_PROC_DEF(anim_state_changed);
        EH_PROC_DEF(container_closed);
        EH_PROC_DEF(controls_shifted);
        EH_PROC_DEF(dammaged);
        EH_PROC_DEF(engine);
        EH_PROC_DEF(epe_contact);
        EH_PROC_DEF(epe_contact_end);
        EH_PROC_DEF(epe_contact_start);
        EH_PROC_DEF(explosion);
        EH_PROC_DEF(fired);
        EH_PROC_DEF(fired_near);
        EH_PROC_DEF(fuel);
        EH_PROC_DEF(gear);
        EH_PROC_DEF(get_in);
        EH_PROC_DEF(get_out);
        EH_PROC_DEF(handle_damage);
        EH_PROC_DEF(handle_heal);
        EH_PROC_DEF(handle_rating);
        EH_PROC_DEF(handle_score);
        EH_PROC_DEF(hit);
        EH_PROC_DEF(hit_part);
        EH_PROC_DEF(init);
        EH_PROC_DEF(incoming_missile);
        EH_PROC_DEF(inventory_closed);
        EH_PROC_DEF(inventory_opened);
        EH_PROC_DEF(killed);
        EH_PROC_DEF(landed_touch_down);
        EH_PROC_DEF(landed_stopped);
        EH_PROC_DEF(local);
        EH_PROC_DEF(post_reset);
        EH_PROC_DEF(put);
        EH_PROC_DEF(respawn);
        EH_PROC_DEF(rope_attach);
        EH_PROC_DEF(rope_break);
        EH_PROC_DEF(seat_switched);
        EH_PROC_DEF(sound_played);
        EH_PROC_DEF(take);
        EH_PROC_DEF(task_set_as_current);
        EH_PROC_DEF(weapon_assembled);
        EH_PROC_DEF(weapon_disassembled);
        EH_PROC_DEF(weapon_deployed);
        EH_PROC_DEF(weapon_rested);

        new_module.functions.assign_functions(functions);
        new_module.path = *full_path;
        _modules[path] = new_module;
        LOG(INFO) << "Load completed [" << path << "]";
        return false;
}

    bool extensions::unload(const arguments & args_, std::string &) {
        return do_unload(args_.as_string(0));
    }

    bool extensions::do_unload(const std::string &path_) {
        LOG(INFO) << "Unload requested [" << path_ << "]";
        auto module = _modules.find(path_);
        if (module == _modules.end()) {
            LOG(INFO) << "Unload failed, module not loaded [" << path_ << "]";
            return true;
        }

        if (module->second.functions.handle_unload) {
            module->second.functions.handle_unload();
        }

    #ifdef __linux
        if (dlclose(module->second.handle)) {//returms 0 on success
            LOG(INFO) << "dlclose() failed during unload, e=" << dlerror();
        #else
        if (!FreeLibrary(module->second.handle)) {
            LOG(INFO) << "FreeLibrary() failed during unload, e=" << GetLastError();
        #endif
            return false;
        }

        _modules.erase(path_);

        LOG(INFO) << "Unload complete [" << path_ << "]";

        return true;
        }

    bool extensions::list(const arguments &, std::string & result) {

        LOG(INFO) << "Listing loaded modules";
        std::string res;

        for (auto & kv : _modules) {
            res = res + kv.first + ", ";
            LOG(INFO) << "\t" << kv.first;
        }

        result = res;

        return false;
    }

    std::unordered_map<std::string, module::entry>& extensions::modules() {
        return _modules;
    }

    }
