#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include "intercept.hpp"
#include "logging.hpp"
#include <sstream>
#include "client\client.hpp"
#include "client\pointers.hpp"
#include <atomic>
INITIALIZE_EASYLOGGINGPP

std::thread test_thread;
std::atomic<bool> stop_thread;

int __cdecl intercept::api_version() {
    return 1;
}

std::list<object> bullets;

void __cdecl intercept::on_frame() {
    /*
    std::stringstream side_chat_msg;
    
    object player = intercept::sqf::player();
    {
        object another_player = player;
    }
    vector3 pos = intercept::sqf::get_pos_asl(player);
    float world_size = intercept::sqf::safe_zone_w();
    side_chat_msg << "Player Pos: [" << pos.x << "," << pos.y << "," << pos.z << "] World Size: " << world_size;
    //object test = intercept::sqf::core::create_vehicle("Bo_Mk82", pos, { }, 100.0f, "NONE");
    intercept::sqf::side_chat(player, side_chat_msg.str());
    //intercept::sqf::position::set_pos_asl(test, pos);
    */
    auto it = bullets.begin();
    while (it != bullets.end()) {
        uintptr_t data = (uintptr_t)(it->rv_data.data);
        uintptr_t data_1 = data + 12;
        uintptr_t data_2 = *(uintptr_t *)data_1;
        if (data_2) {
            uintptr_t data_3 = data_2 + 4;
            uintptr_t val = *(uintptr_t *)data_3;
            if (!val) {
                bullets.erase(it++);
                LOG(DEBUG) << "Null Bullet!";
            }
            else {
                LOG(DEBUG) << "Bullet Fly!";
                ++it;
            }
        }
        else {
            bullets.erase(it++);
            LOG(DEBUG) << "Null Bullet!";
        }
    }
}

void test_thread_func() {
    LOG(DEBUG) << "START TEST THREAD";
    while (!stop_thread) {
        std::stringstream side_chat_msg;

        object player = intercept::sqf::player();
        {
            object another_player = player;
        }
        vector3 pos = intercept::sqf::get_pos_asl(player);
        float world_size = intercept::sqf::safe_zone_w();
        side_chat_msg << "Player Pos: [" << pos.x << "," << pos.y << "," << pos.z << "] World Size: " << world_size;
        //object test = intercept::sqf::core::create_vehicle("Bo_Mk82", pos, { }, 100.0f, "NONE");
        //intercept::sqf::side_chat(player, side_chat_msg.str());
        //intercept::sqf::position::set_pos_asl(test, pos);
        sleep(10);
    }
    LOG(DEBUG) << "SHUT DOWN TEST THREAD";
}

void __cdecl intercept::post_init() {
    stop_thread = false;
    test_thread = std::thread(&test_thread_func);
}

void __cdecl intercept::mission_stopped() {
    stop_thread = true;
    test_thread.join();
}




void __cdecl intercept::fired(
    object unit_,
    std::string weapon_,
    std::string muzzle_,
    std::string mode_,
    std::string ammo_,
    std::string magazine,
    object projectile_) {
    //float speed = intercept::sqf::speed(projectile_);
    bullets.push_back(projectile_);
    //LOG(DEBUG) << weapon_ << "," << ammo_ << " kph: " << speed;
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
