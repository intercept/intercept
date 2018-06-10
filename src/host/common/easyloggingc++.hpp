#pragma once
#include <sstream>
#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#ifdef _DEBUG
#define SPDLOG_TRACE_ON
#endif
#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING

#define TRACE(...) SPDLOG_TRACE(logging::logfile, __VA_ARGS__)
#define TRACE_IF(flag, ...) SPDLOG_TRACE(logging::logfile, flag, __VA_ARGS__))

#define INFO logging::logfile->info
#define DEBUG logging::logfile->debug
#define WARNING logging::logfile->warn
#ifdef ERROR
#undef ERROR
#endif
#define ERROR logging::logfile->error

#define LOG(LEVEL, ...) LEVEL(__VA_ARGS__)

#define INITIALIZE_EASYLOGGINGPP std::shared_ptr<spdlog::logger> logging::logfile{};
//#define SPDLOG_FMT_PRINTF


namespace logging {
    extern std::shared_ptr<spdlog::logger> logfile;
}




