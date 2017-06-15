#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "client/client.hpp"
#include "controller.hpp"
#include "export.hpp"
#include "extensions.hpp"
#include "invoker.hpp"
#include "logging.hpp"
#include "shared.hpp"
#include "shared/functions.hpp"

INITIALIZE_EASYLOGGINGPP

#ifndef __linux__
extern "C" DLLEXPORT void __stdcall RVExtension(char *output, int outputSize, const char *function);
#endif

static char version[] = "1.0";

std::string get_command(const std::string &input) {
    std::string command;

    size_t cmd_end = input.find(':');
    if (cmd_end < 1) {
        return "";
    }

    return input.substr(0, cmd_end);
}

std::atomic_bool _threaded(false);
#ifdef __linux__
extern "C" void RVExtension(char *output, int outputSize, const char *function) {
#else
void __stdcall RVExtension(char *output, int outputSize, const char *function) {
#endif
    ZERO_OUTPUT();

    // Get the command, then the command args
    std::string input = function;

    std::string command = get_command(input);

    std::string argument_str;
    if (command.length() > 1 && input.length() > command.length() + 1) {
        argument_str = input.substr(command.length() + 1, input.length() + 1 - command.length());
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
    } else if (command == "echo") {
        result = function;
    } else if (command == "async") {
        _threaded = true;
        result = "0";
    } else if (command == "stop") {
        _threaded = false;
    }

    if (command == "init_patch") {
#if _WIN64 || __X86_64__
        uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(reinterpret_cast<uintptr_t>(output) + outputSize + 0x2970 - 0x2800);
#else
#if __linux__
        uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(reinterpret_cast<uintptr_t>(output) + outputSize + 0x264);
#else
        uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(reinterpret_cast<uintptr_t>(output) + outputSize + 8);
#endif
#endif
        //std::cout << "gameState " << std::hex << game_state_addr << "\n";
        intercept::loader::get().do_function_walk(game_state_addr);
        return;
    }

    intercept::controller::get().call(command, _args, result, _threaded);

    if (result.length() > 0) {
        snprintf(output, outputSize, "%s", result.c_str());
    }
    EXTENSION_RETURN();
}

intercept::client_functions intercept::client::host::functions;

void Init() {
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

void Cleanup() {
}

#ifndef __linux__
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
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
#endif
