#include <stdio.h>
#include <filesystem>
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

std::optional<std::string_view> get_command(std::string_view input) {
    size_t cmd_end = input.find(':');
    if (cmd_end < 1) {
        return {};
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
    std::string_view input = function;

    std::optional<std::string_view> cmd = get_command(input);
    if (!cmd) {
        output[0] = 0x00;
        return;
    }

    std::string_view command = cmd.value();

    std::string argument_str;
    if (command.length() > 1 && input.length() > command.length() + 1) {
        argument_str = input.substr(command.length() + 1, input.length() + 1 - command.length());
    }
    intercept::arguments _args(argument_str);

    std::string result = "-1";
    _threaded = false;

    if (command == "version"sv) {
        result = version;
    } else if (command == "echo"sv) {
        result = function;
    } else if (command == "async"sv) {
        _threaded = true;
        result = "0";
    } else if (command == "stop"sv) {
        _threaded = false;
    }

    if (command == "init_patch"sv) {
        uintptr_t game_state_addr = intercept::loader::find_game_state(reinterpret_cast<uintptr_t>(output) + outputSize);

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

void 
#ifdef __linux__
__attribute__((constructor))
#endif
    InitLogging() {
    intercept::client::host::functions = intercept::extensions::get().functions;
    auto arg_line = intercept::search::plugin_searcher::get_command_line();
    std::transform(arg_line.begin(), arg_line.end(), arg_line.begin(), ::tolower);
    
    
    if (arg_line.find("-interceptdebuglog"sv) != std::string::npos) {
        spdlog::set_level(spdlog::level::debug);
    } else {
        spdlog::set_level(spdlog::level::info);
    }


    spdlog::set_pattern("[%H:%M:%S]-{%l}- %v");
    try {
        auto logfile_it_ = arg_line.find("-interceptlogfile"sv);
        if (logfile_it_ != std::string::npos) {
            auto path_start_ = logfile_it_ + 17; // skip -interceptlogfile

            //trim left
            path_start_ = arg_line.find_first_not_of(" \t\"", path_start_);

            //trim right
            size_t path_end_ = arg_line.find("\"", path_start_); // find ending quotationmark

            if (path_start_ == std::string::npos) {
                if (std::filesystem::is_directory("logs")) {
                    logging::logfile = spdlog::rotating_logger_mt("logfile", "logs/intercept_dll.log", 1024000, 3);
                } else {
                    logging::logfile = spdlog::stdout_logger_mt("Intercept Core");
                }
            } else {
                std::string _path = arg_line.substr(path_start_, path_end_ - path_start_);
                logging::logfile = spdlog::rotating_logger_mt("logfile", _path, 1024000, 3);
            }
        } else if (std::filesystem::is_directory("logs")) {
            logging::logfile = spdlog::rotating_logger_mt("logfile", "logs/intercept_dll.log", 1024000, 3);
        } else {
            spdlog::set_level(spdlog::level::off);
            logging::logfile = spdlog::stdout_logger_mt("Intercept Core");
        }

        logging::logfile->flush_on(spdlog::level::debug);
    } catch (const spdlog::spdlog_ex&) {
        spdlog::set_level(spdlog::level::off);
        logging::logfile = spdlog::stdout_logger_mt("Intercept Core");
    }

    LOG(INFO, "Intercept DLL Loaded");
}

void
#ifdef __linux__
__attribute__((destructor))
#endif
CleanupLogging() {
    if (logging::logfile)
        logging::logfile->flush();
    spdlog::drop_all();
}

#ifndef __linux__
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            InitLogging();
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            CleanupLogging();
            break;
    }
    return TRUE;
}
#endif
