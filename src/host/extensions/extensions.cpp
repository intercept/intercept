#include "extensions.hpp"
#include "controller.hpp"
#include "export.hpp"


namespace intercept {

    extensions::extensions() {
        functions.get_type_structure = client_function_defs::get_type_structure;
        functions.free_value = client_function_defs::free_value;
        functions.allocate_string = client_function_defs::allocate_string;
        functions.free_string = client_function_defs::free_string;
        functions.get_binary_function = client_function_defs::get_binary_function;
        functions.get_binary_function_typed = client_function_defs::get_binary_function_typed;
        functions.get_nular_function = client_function_defs::get_nular_function;
        functions.get_unary_function = client_function_defs::get_unary_function;
        functions.get_unary_function_typed = client_function_defs::get_unary_function_typed;
        functions.invoke_raw_binary = client_function_defs::invoke_raw_binary;
        functions.invoke_raw_binary_nolock = client_function_defs::invoke_raw_binary_nolock;
        functions.invoke_raw_nular = client_function_defs::invoke_raw_nular;
        functions.invoke_raw_nular_nolock = client_function_defs::invoke_raw_nular_nolock;
        functions.invoke_raw_unary = client_function_defs::invoke_raw_unary;
        functions.invoke_raw_unary_nolock = client_function_defs::invoke_raw_unary_nolock;
        functions.invoker_lock = client_function_defs::invoker_lock;
        functions.invoker_unlock = client_function_defs::invoker_unlock;
        for (auto file : _searcher.active_pbo_list()) {
            size_t last_index = file.find_last_of("\\/");
            std::string path = file.substr(0, last_index);
            last_index = path.find_last_of("\\/");
            path = path.substr(0, last_index);
            _mod_folders.push_back(path);
        }
        _mod_folders.unique();
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

    bool extensions::load(const arguments & args_, std::string & result) {
        HMODULE dllHandle;
        std::string path = args_.as_string(0);
        LOG(INFO) << "Load requested [" << args_.as_string(0) << "]";

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

        std::string full_path = "";

        for (auto folder : _mod_folders) {
            std::string test_path = folder + "\\intercept\\" + path + ".dll";
            LOG(DEBUG) << "Mod: " << test_path;
            std::ifstream check_file(test_path);
            if (check_file.good()) {
                full_path = test_path;
                break;
            }
        }
        if (full_path == "") {
            LOG(ERROR) << "Client plugin: " << path << " was not found.";
            return false;
        }



        dllHandle = LoadLibrary(full_path.c_str());
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e=" << GetLastError() << " [" << full_path << "]";
            return false;
        }


        auto new_module = module::entry(full_path, dllHandle);

        new_module.functions.api_version = (module::api_version_func)GetProcAddress(dllHandle, "api_version");
        new_module.functions.assign_functions = (module::assign_functions_func)GetProcAddress(dllHandle, "assign_functions");
        new_module.functions.mission_end = (module::mission_end_func)GetProcAddress(dllHandle, "mission_end");
        new_module.functions.on_frame = (module::on_frame_func)GetProcAddress(dllHandle, "on_frame");
        //new_module.functions.on_signal = (module::on_signal_func)GetProcAddress(dllHandle, "on_signal");
        new_module.functions.post_init = (module::post_init_func)GetProcAddress(dllHandle, "post_init");
        new_module.functions.pre_init = (module::pre_init_func)GetProcAddress(dllHandle, "pre_init");
        new_module.functions.mission_stopped = (module::mission_stopped_func)GetProcAddress(dllHandle, "mission_stopped");

#define EH_PROC_DEF(x) new_module.eventhandlers.##x = (module::##x##_func)GetProcAddress(dllHandle, #x)

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


        if (!new_module.functions.api_version) {
            LOG(ERROR) << "Module " << path << " failed to define the api_version function.";
            return false;
        }

        if (!new_module.functions.assign_functions) {
            LOG(ERROR) << "Module " << path << " failed to define the assign_functions function.";
            return false;
        }

        new_module.functions.assign_functions(functions);

        _modules[path] = new_module;
        LOG(INFO) << "Load completed [" << path << "]";
        return false;
    }

    bool extensions::unload(const arguments & args_, std::string & result) {

        LOG(INFO) << "Unload requested [" << args_.as_string(0) << "]";

        if (_modules.find(args_.as_string(0)) == _modules.end()) {
            LOG(INFO) << "Unload failed, module not loaded [" << args_.as_string(0) << "]";
            return true;
        }

        if (!FreeLibrary(_modules[args_.as_string(0)].handle)) {
            LOG(INFO) << "FreeLibrary() failed during unload, e=" << GetLastError();
            return false;
        }

        _modules.erase(args_.as_string(0));

        LOG(INFO) << "Unload complete [" << args_.as_string(0) << "]";

        return true;
    }

    bool extensions::list(const arguments & args_, std::string & result) {

        LOG(INFO) << "Listing loaded modules";
        std::string res;

        for (auto & kv : _modules) {
            res = res + kv.first + ", ";
            LOG(INFO) << "\t" << kv.first;
        }

        result = res;

        return false;
    }

    std::unordered_map<std::string, module::entry>& extensions::modules()
    {
        return _modules;
    }

}
