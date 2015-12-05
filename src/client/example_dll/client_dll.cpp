#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include "intercept.hpp"
#include "logging.hpp"
#include <sstream>

INITIALIZE_EASYLOGGINGPP



int __cdecl intercept::api_version() {
    return 1;
}

void __cdecl intercept::on_frame() {
    float rand_val = intercept::sqf::random(100.0f);
    std::stringstream side_chat_msg;
    side_chat_msg << "Hello Arma World, here is some randomness: " << rand_val;
    intercept::sqf::custom_chat(intercept::sqf::player(), 1, side_chat_msg.str());
}




void Init(void) {
    el::Configurations conf;

    conf.setGlobally(el::ConfigurationType::Filename, "logs/intercept_example_dll.log");
    conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "10240");
#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    conf.setGlobally(el::ConfigurationType::PerformanceTracking, "true");
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif
    el::Loggers::setDefaultConfigurations(conf, true);

    LOG(INFO) << "Intercept Example DLL Loaded";
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
