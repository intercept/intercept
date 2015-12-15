#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "shared.hpp"
#include "controller.hpp"
#include "logging.hpp"
#include "invoker.hpp"
#include "export.hpp"
#include "client\client.hpp"
#include "extensions.hpp"
#include "shared\functions.hpp"

INITIALIZE_EASYLOGGINGPP

extern "C"
{
    __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};



static char version[] = "1.0";

std::string get_command(const std::string & input) {
    size_t cmd_end;
    std::string command;

    cmd_end = input.find(':');
    if (cmd_end < 1) {
        return "";
    }

    return input.substr(0, cmd_end);
}

std::atomic_bool _threaded = false;

void __stdcall RVExtension(char *output, int outputSize, const char *function) {
    ZERO_OUTPUT();

    // Get the command, then the command args
    std::string input = function;

    std::string command = get_command(input);
    bool block_execute = false;

    std::string argument_str;
    if (command.length() > 1 && input.length() > command.length() + 1) {
        argument_str = input.substr(command.length() + 1, (input.length() + 1 - command.length()));
    }
    intercept::arguments _args(argument_str);

    std::string result = "-1";
    _threaded = false;
    if (command.size() < 1) {
        output[0] = 0x00;
        return;
    }
    if (command == "version") {
        result = version;
    }
    else if (command == "echo") {
        result = function;
    }
    else if (command == "async") {
        _threaded = true;
        result = "0";
    }
    else if (command == "stop") {
        _threaded = false;
    }

    if (command == "block_execute") {
        block_execute = true;
        command = _args.as_string(0);
        _threaded = false;
    }
    if (block_execute) {
        intercept::invoker::get().allow_access();
    }
    intercept::controller::get().call(command, _args, result, _threaded);
    if (block_execute) {
        intercept::invoker::get().deny_access();
    }
    if (result.length() > 0) {
        sprintf_s(output, outputSize, "%s", result.c_str());
    }
    EXTENSION_RETURN();
}




intercept::client_functions intercept::client::host::functions;


void Init(void) {
    intercept::client::host::functions = intercept::extensions::get().functions;
    el::Configurations conf;

    conf.setGlobally(el::ConfigurationType::Filename, "logs/intercept_dll.log");
    conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "10240");
#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    conf.setGlobally(el::ConfigurationType::PerformanceTracking, "true");
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif
    el::Loggers::setDefaultConfigurations(conf, true);

    LOG(INFO) << "Intercept DLL Loaded";
}

void Cleanup(void) {

}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        Cleanup();
        break;
    }
    return TRUE;
}
