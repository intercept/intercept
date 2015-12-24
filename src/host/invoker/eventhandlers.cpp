#include "eventhandlers.hpp"
#include "invoker.hpp"
#include "extensions.hpp"
#include "shared\client_types.hpp"

namespace intercept {
    eventhandlers::eventhandlers() : _initialized(false)
    {
    }
    eventhandlers::~eventhandlers()
    {
    }
    void eventhandlers::initialize()
    {
        if (!_initialized) {
            invoker::get().add_eventhandler("pre_init", std::bind(&eventhandlers::pre_init, this, std::placeholders::_1, std::placeholders::_2));
            invoker::get().add_eventhandler("post_init", std::bind(&eventhandlers::post_init, this, std::placeholders::_1, std::placeholders::_2));
            invoker::get().add_eventhandler("mission_stopped", std::bind(&eventhandlers::mission_stopped, this, std::placeholders::_1, std::placeholders::_2));
            invoker::get().add_eventhandler("fired", std::bind(&eventhandlers::fired, this, std::placeholders::_1, std::placeholders::_2));

            _initialized = true;
        }
    }
    void eventhandlers::pre_init(const std::string & name_, game_value & args_)
    {
        LOG(INFO) << "Pre-init";
        for (auto module : extensions::get().modules()) {
            if (module.second.functions.pre_init) {
                module.second.functions.pre_init();
            }
        }
    }
    void eventhandlers::post_init(const std::string & name_, game_value & args_)
    {
        LOG(INFO) << "Post-init";
        for (auto module : extensions::get().modules()) {
            if (module.second.functions.post_init) {
                module.second.functions.post_init();
            }
        }
    }
    void eventhandlers::mission_stopped(const std::string & name_, game_value & args_)
    {
        LOG(INFO) << "Mission Stopped";
        for (auto module : extensions::get().modules()) {
            if (module.second.functions.mission_stopped) {
                module.second.functions.mission_stopped();
            }
        }
    }
    void eventhandlers::fired(const std::string & name_, game_value & args_)
    {
        object unit = object(args_[0].rv_data);
        std::string weapon = args_[1];
        std::string muzzle = args_[2];
        std::string mode = args_[3];
        std::string ammo = args_[4];
        std::string magazine = args_[5];
        object projectile = object(args_[6].rv_data);

        for (auto module : extensions::get().modules()) {
            if (module.second.functions.fired) {
                module.second.functions.fired(
                    unit,
                    weapon,
                    muzzle,
                    mode,
                    ammo,
                    magazine,
                    projectile
                    );
            }
        }
    }
}