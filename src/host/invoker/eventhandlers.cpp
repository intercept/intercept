#include "eventhandlers.hpp"
#include "invoker.hpp"
#include "extensions.hpp"
#include "shared/client_types.hpp"

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
            invoker::get().add_eventhandler("pre_start"sv, std::bind(&eventhandlers::pre_start, std::placeholders::_1));
            invoker::get().add_eventhandler("pre_init"sv, std::bind(&eventhandlers::pre_init, std::placeholders::_1));
            invoker::get().add_eventhandler("pre_pre_init"sv, std::bind(&eventhandlers::pre_pre_init, std::placeholders::_1));
            invoker::get().add_eventhandler("post_init"sv, std::bind(&eventhandlers::post_init, std::placeholders::_1));
            invoker::get().add_eventhandler("mission_ended"sv, std::bind(&eventhandlers::mission_ended, std::placeholders::_1));

#define EH_EVENT_DEF(x) invoker::get().add_eventhandler(#x, std::bind(&eventhandlers::x, std::placeholders::_1));

            EH_EVENT_DEF(anim_changed);
            EH_EVENT_DEF(anim_done);
            EH_EVENT_DEF(anim_state_changed);
            EH_EVENT_DEF(container_closed);
            EH_EVENT_DEF(controls_shifted);
            EH_EVENT_DEF(dammaged);
            EH_EVENT_DEF(engine);
            EH_EVENT_DEF(epe_contact);
            EH_EVENT_DEF(epe_contact_end);
            EH_EVENT_DEF(epe_contact_start);
            EH_EVENT_DEF(explosion);
            EH_EVENT_DEF(fired);
            EH_EVENT_DEF(fired_near);
            EH_EVENT_DEF(fuel);
            EH_EVENT_DEF(gear);
            EH_EVENT_DEF(get_in);
            EH_EVENT_DEF(get_out);
            EH_EVENT_DEF(handle_damage);
            EH_EVENT_DEF(handle_heal);
            EH_EVENT_DEF(handle_rating);
            EH_EVENT_DEF(handle_score);
            EH_EVENT_DEF(hit);
            //EH_EVENT_DEF(hit_part);
            EH_EVENT_DEF(init);
            EH_EVENT_DEF(incoming_missile);
            EH_EVENT_DEF(inventory_closed);
            EH_EVENT_DEF(inventory_opened);
            EH_EVENT_DEF(killed);
            EH_EVENT_DEF(landed_touch_down);
            EH_EVENT_DEF(landed_stopped);
            EH_EVENT_DEF(local);
            EH_EVENT_DEF(post_reset);
            EH_EVENT_DEF(put);
            EH_EVENT_DEF(respawn);
            EH_EVENT_DEF(rope_attach);
            EH_EVENT_DEF(rope_break);
            EH_EVENT_DEF(seat_switched);
            EH_EVENT_DEF(sound_played);
            EH_EVENT_DEF(take);
            EH_EVENT_DEF(task_set_as_current);
            EH_EVENT_DEF(weapon_assembled);
            EH_EVENT_DEF(weapon_disassembled);
            EH_EVENT_DEF(weapon_deployed);
            EH_EVENT_DEF(weapon_rested);
            EH_EVENT_DEF(post_start);
            _initialized = true;
        }
    }

    game_value eventhandlers::client_eventhandler(game_value_parameter left_arg, game_value_parameter right_arg) {
        r_string moduleName = left_arg[0];
        const uint8_t ehType = static_cast<int>(left_arg[1]);
        const float uidf = left_arg[2];
        const int32_t uid = static_cast<int32_t>(uidf);
        //uint32_t handle = static_cast<uint32_t>(static_cast<float>(left_arg[3]));

        for (auto& module : extensions::get().modules()) {
            if (module.second.functions.client_eventhandler && module.second.name == static_cast<std::string_view>(moduleName)) {
                game_value ret{};
                module.second.functions.client_eventhandler(ret, ehType, uid, left_arg[3], right_arg[0]);
                return ret;
            }
        }
        return {};
    }

    void eventhandlers::pre_start(game_value_parameter) {
        static bool preStartCalled = false;
        if (preStartCalled) throw std::runtime_error("pre_start called twice");
        get()._ehFunc = sqf_functions::get().register_sqf_function("InterceptClientEvent"sv, "Forwarder used to call functions in Intercept Plugins"sv, userFunctionWrapper<client_eventhandler>, game_data_type::ANY, game_data_type::ARRAY, game_data_type::ARRAY);
        LOG(INFO, "Pre-start");
        for (auto& module : extensions::get().modules()) {
            if (module.second.functions.pre_start) module.second.functions.pre_start();
        }
        preStartCalled = true;
    }
    void eventhandlers::post_start(game_value_parameter) {
        static bool postStartCalled = false;
        if (postStartCalled) throw std::runtime_error("post_start called twice");
        LOG(INFO, "Post-start");
        for (auto& module : extensions::get().modules()) {
            if (module.second.functions.post_start) module.second.functions.post_start();
        }
        postStartCalled = true;
    }
    void eventhandlers::pre_pre_init(game_value_parameter) {
        LOG(INFO, "Pre-pre-init");
        for (auto& module : extensions::get().modules()) {
            module.second.functions.client_eventhandlers_clear(); //Plugin loader enforces this one to be set
            if (module.second.functions.pre_pre_init) module.second.functions.pre_pre_init();
        }
    }
    void eventhandlers::pre_init(game_value_parameter) {
        extensions::get().reload_all();
        LOG(INFO, "Pre-init");
        for (auto& module : extensions::get().modules()) {
            if (module.second.functions.pre_init) module.second.functions.pre_init();
        }
    }
    void eventhandlers::post_init(game_value_parameter) {
        LOG(INFO, "Post-init");
        for (auto& module : extensions::get().modules()) {
            if (module.second.functions.post_init) module.second.functions.post_init();
        }
    }
    void eventhandlers::mission_ended(game_value_parameter) {
        LOG(INFO, "Mission Stopped");
        for (auto& module : extensions::get().modules()) {
            module.second.functions.client_eventhandlers_clear(); //Plugin loader enforces this one to be set
            if (module.second.functions.mission_ended) module.second.functions.mission_ended();
        }
    }
#define EH_START(x) void eventhandlers::x(game_value_parameter args_) {\
        for (auto& module : extensions::get().modules()) {\
            if (module.second.eventhandlers.x) module.second.eventhandlers.x

#define EH_END ;\
        }\
    }

    
    EH_START(anim_changed)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]))EH_END
    EH_START(anim_done)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]))EH_END
    EH_START(anim_state_changed)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]))EH_END
    EH_START(container_closed)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(controls_shifted)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(dammaged)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<float>(args_[2]))EH_END
    EH_START(engine)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    EH_START(epe_contact)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<r_string>(args_[2]), static_cast<r_string>(args_[3]), static_cast<float>(args_[4]))EH_END
    EH_START(epe_contact_end)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<r_string>(args_[2]), static_cast<r_string>(args_[3]), static_cast<float>(args_[4]))EH_END
    EH_START(epe_contact_start)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<r_string>(args_[2]), static_cast<r_string>(args_[3]), static_cast<float>(args_[4]))EH_END
    EH_START(explosion)(static_cast<object &>(args_[0]), static_cast<float>(args_[1]))EH_END
    
    EH_START(fired)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<r_string>(args_[2]), static_cast<r_string>(args_[3]), static_cast<r_string>(args_[4]), static_cast<r_string>(args_[5]), static_cast<object &>(args_[6]))EH_END
    
    EH_START(fired_near)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<float>(args_[2]), static_cast<r_string>(args_[3]), static_cast<r_string>(args_[4]), static_cast<r_string>(args_[5]), static_cast<r_string>(args_[6]))EH_END
    EH_START(fuel)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    EH_START(gear)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    //EH_START(get_in)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<object &>(args_[2]), rv_turret_path turret_path)EH_END

    void eventhandlers::get_in(game_value_parameter args_) {
        for (auto& module : extensions::get().modules()) {
            if (module.second.eventhandlers.get_in) {
                module.second.eventhandlers.get_in(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<object &>(args_[2]), rv_turret_path(args_[3]));
            }
        }
    }

    //EH_START(get_out)(static_cast<object &>(args_[0]), static_cast<rv_string>(args_[REPLACE_ME]), static_cast<object &>(args_[REPLACE_ME]), rv_turret_path turret_path)EH_END

    void eventhandlers::get_out(game_value_parameter args_) {
        for (auto& module : extensions::get().modules()) {
            if (module.second.eventhandlers.get_out) {
                module.second.eventhandlers.get_out(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<object &>(args_[2]), rv_turret_path(args_[3]));
            }
        }
    }

    EH_START(handle_damage)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<float>(args_[2]), static_cast<object &>(args_[3]), static_cast<r_string>(args_[4]), static_cast<int>(args_[5]))EH_END
    EH_START(handle_heal)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<bool>(args_[2]))EH_END
    EH_START(handle_rating)(static_cast<object &>(args_[0]), static_cast<float>(args_[1]))EH_END
    EH_START(handle_score)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<float>(args_[2]))EH_END
    EH_START(hit)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<float>(args_[2]))EH_END
    //EH_START(hit_part)(std::vector<hit_part_data> data_)EH_END
    EH_START(init)(static_cast<object &>(args_[0]))EH_END
    EH_START(incoming_missile)(static_cast<object &>(args_[0]), static_cast<r_string>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(inventory_closed)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(inventory_opened)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(killed)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(landed_touch_down)(static_cast<object &>(args_[0]), static_cast<int>(args_[1]))EH_END
    EH_START(landed_stopped)(static_cast<object &>(args_[0]), static_cast<int>(args_[1]))EH_END
    EH_START(local)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    EH_START(post_reset)()EH_END
    EH_START(put)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<r_string>(args_[2]))EH_END
    EH_START(respawn)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(rope_attach)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(rope_break)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(seat_switched)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(sound_played)(static_cast<object &>(args_[0]), static_cast<int>(args_[1]))EH_END
    EH_START(take)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<r_string>(args_[2]))EH_END
    EH_START(task_set_as_current)(static_cast<object &>(args_[0]), static_cast<task &>(args_[1]))EH_END
    EH_START(weapon_assembled)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]))EH_END
    EH_START(weapon_disassembled)(static_cast<object &>(args_[0]), static_cast<object &>(args_[1]), static_cast<object &>(args_[2]))EH_END
    EH_START(weapon_deployed)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    EH_START(weapon_rested)(static_cast<object &>(args_[0]), static_cast<bool>(args_[1]))EH_END
    
}
