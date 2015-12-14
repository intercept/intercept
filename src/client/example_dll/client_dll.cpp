#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include "intercept.hpp"
#include "logging.hpp"
#include <sstream>
#include "client\client.hpp"
#include "client\pointers.hpp"
INITIALIZE_EASYLOGGINGPP



int __cdecl intercept::api_version() {
    return 1;
}

void __cdecl intercept::on_frame() {
    std::stringstream side_chat_msg;
    
    object player = intercept::sqf::core::player();
    vector3 pos = intercept::sqf::position::get_pos_asl(player);

    side_chat_msg << "Player Pos: [" << pos.x << "," << pos.y << "," << pos.z << "]";
    //object test = intercept::sqf::core::create_vehicle("Bo_Mk82", pos, { }, 100.0f, "NONE");
    intercept::sqf::chat::side_chat(player, side_chat_msg.str());
    //intercept::sqf::position::set_pos_asl(player, pos);
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
