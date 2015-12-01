#include "extensions.hpp"
#include "controller.hpp"
#include "export.hpp"

namespace intercept {

    extensions::extensions() {
        _functions.new_string = client_function_defs::new_string;
        _functions.new_scalar = client_function_defs::new_scalar;
        _functions.free_value = client_function_defs::free_value;
        _functions.get_binary_function = client_function_defs::get_binary_function;
        _functions.get_binary_function_typed = client_function_defs::get_binary_function_typed;
        _functions.get_nular_function = client_function_defs::get_nular_function;
        _functions.get_unary_function = client_function_defs::get_unary_function;
        _functions.get_unary_function_typed = client_function_defs::get_unary_function_typed;
        _functions.invoke_raw_binary = client_function_defs::invoke_raw_binary;
        _functions.invoke_raw_nular = client_function_defs::invoke_raw_nular;
        _functions.invoke_raw_unary = client_function_defs::invoke_raw_unary;
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

        LOG(INFO) << "Load requested [" << args_.as_string(0) << "]";

        if (_modules.find(args_.as_string(0)) != _modules.end()) {
            LOG(ERROR) << "Module already loaded [" << args_.as_string(0) << "]";
            return true;
        }

        dllHandle = LoadLibrary(args_.as_string(0).c_str());
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e=" << GetLastError() << " [" << args_.as_string(0) << "]";
            return false;
        }

        
        auto new_module = module::entry(args_.as_string(0), dllHandle);

        new_module.functions.api_version = (module::api_version_func)GetProcAddress(dllHandle, "api_version");
        new_module.functions.assign_functions = (module::assign_functions_func)GetProcAddress(dllHandle, "assign_functions");
        new_module.functions.mission_end = (module::mission_end_func)GetProcAddress(dllHandle, "mission_end");
        new_module.functions.on_frame = (module::on_frame_func)GetProcAddress(dllHandle, "on_frame");
        new_module.functions.post_init = (module::post_init_func)GetProcAddress(dllHandle, "post_init");
        new_module.functions.pre_init = (module::pre_init_func)GetProcAddress(dllHandle, "pre_init");

        if (!new_module.functions.api_version) {
            LOG(ERROR) << "Module " << args_.as_string(0) << " failed to define the api_version function.";
            return false;
        }

        if (!new_module.functions.assign_functions) {
            LOG(ERROR) << "Module " << args_.as_string(0) << " failed to define the assign_functions function.";
            return false;
        }

        new_module.functions.assign_functions(_functions);

        _modules[args_.as_string(0)] = new_module;
        LOG(INFO) << "Load completed [" << args_.as_string(0) << "]";
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

    bool extensions::call(const arguments & args_, std::string & result) {
        //LOG(INFO) << "Calling [" << args_.as_string(0) << "]";

        if (_modules.find(args_.as_string(0)) == _modules.end()) {
            return false;
        }

        result = "";
        result.resize(4096);

        std::string function_str;
        std::vector<std::string> temp = intercept::split(args_.get(), ',');

        if (temp.size() < 3) {
            function_str = temp[1];
        }
        else {
            for (int x = 1; x < temp.size(); x++)
                function_str = function_str + temp[x] + ",";
        }
        //_modules[args_.as_string(0)].function((char *)result.c_str(), 4096, (const char *)function_str.c_str());

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

    const std::unordered_map<std::string, module::entry>& extensions::modules()
    {
        return _modules;
    }

}