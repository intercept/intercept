#include "extensions.hpp"
#include "controller.hpp"

namespace intercept {

    extensions::extensions() {
    
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

#ifdef _WINDOWS
        // Make a copy of the file to temp, and load it from there, referencing the current path name
        char tmpPath[MAX_PATH + 1], buffer[MAX_PATH + 1];

        if (!GetTempPathA(MAX_PATH, tmpPath)) {
            LOG(ERROR) << "GetTempPath() failed, e=" << GetLastError();
            return false;
        }
        if (!GetTempFileNameA(tmpPath, "intercept_dynload", TRUE, buffer)) {
            LOG(ERROR) << "GetTempFileName() failed, e=" << GetLastError();
            return false;
        }
        std::string temp_filename = buffer;
        if (!CopyFileA(args_.as_string(0).c_str(), temp_filename.c_str(), FALSE)) {
            DeleteFile(temp_filename.c_str());
            if (!CopyFileA(args_.as_string(0).c_str(), temp_filename.c_str(), FALSE)) {
                LOG(ERROR) << "CopyFile() , e=" << GetLastError();
                return false;
            }
        }
#else
        std::string temp_filename = args_.as_string(0);
#endif

        dllHandle = LoadLibrary(temp_filename.c_str());
        if (!dllHandle) {
            LOG(ERROR) << "LoadLibrary() failed, e=" << GetLastError() << " [" << args_.as_string(0) << "]";
            return false;
        }
        /*
        if (!function) {
            LOG(ERROR) << "GetProcAddress() failed, e=" << GetLastError() << " [" << args_.as_string(0) << "]";
            FreeLibrary(dllHandle);
            return false;
        }
        */
        LOG(INFO) << "Load completed [" << args_.as_string(0) << "]";

        //_modules[args_.as_string(0)] = module(args_.as_string(0), dllHandle, function, temp_filename);

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
        //if (!DeleteFileA(_modules[args_.as_string(0)].temp_filename.c_str())) {
        //    LOG(INFO) << "DeleteFile() failed during unload, e=" << GetLastError();
        //    return false;
        //}

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
#ifdef _DEBUG
        //if (args_.as_string(0) != "fetch_result" && args_.as_string(0) != "ready") {
        //    LOG(INFO) << "Called [" << args_.as_string(0) << "], with {" << function_str << "} result={" << result << "}";
        //}
#endif
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

}