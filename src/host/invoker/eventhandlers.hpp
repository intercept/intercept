/*!
@file
@author Nou (korewananda@gmail.com)

@brief Contains the intercept::invoker class.

https://github.com/NouberNou/intercept
*/
#pragma once

#include "singleton.hpp"
#include "shared/types.hpp"

using namespace intercept::types;

namespace intercept {
    /*!
    @brief Contains all the wrapper functions to calling events from the RV engine
    in client plugins.
    */
    class eventhandlers
        : public singleton<eventhandlers> {
    public:
        eventhandlers();
        ~eventhandlers();

        void initialize();

        static game_value client_eventhandler(game_value_parameter left_arg, game_value_parameter right_arg);

        static void pre_init(game_value_parameter args_);
        static void pre_pre_init(game_value_parameter args_);
        static void pre_start(game_value_parameter args_);
        static void post_start(game_value_parameter args_);
        static void post_init(game_value_parameter args_);
        static void mission_ended(game_value_parameter args_);

#define EH_CLASS_DEF(x) static void x(game_value_parameter args_)

        EH_CLASS_DEF(anim_changed);
        EH_CLASS_DEF(anim_done);
        EH_CLASS_DEF(anim_state_changed);
        EH_CLASS_DEF(container_closed);
        EH_CLASS_DEF(controls_shifted);
        EH_CLASS_DEF(dammaged);
        EH_CLASS_DEF(engine);
        EH_CLASS_DEF(epe_contact);
        EH_CLASS_DEF(epe_contact_end);
        EH_CLASS_DEF(epe_contact_start);
        EH_CLASS_DEF(explosion);
        EH_CLASS_DEF(fired);
        EH_CLASS_DEF(fired_near);
        EH_CLASS_DEF(fuel);
        EH_CLASS_DEF(gear);
        EH_CLASS_DEF(get_in);
        EH_CLASS_DEF(get_out);
        EH_CLASS_DEF(handle_damage);
        EH_CLASS_DEF(handle_heal);
        EH_CLASS_DEF(handle_rating);
        EH_CLASS_DEF(handle_score);
        EH_CLASS_DEF(hit);
        EH_CLASS_DEF(hit_part);
        EH_CLASS_DEF(init);
        EH_CLASS_DEF(incoming_missile);
        EH_CLASS_DEF(inventory_closed);
        EH_CLASS_DEF(inventory_opened);
        EH_CLASS_DEF(killed);
        EH_CLASS_DEF(landed_touch_down);
        EH_CLASS_DEF(landed_stopped);
        EH_CLASS_DEF(local);
        EH_CLASS_DEF(post_reset);
        EH_CLASS_DEF(put);
        EH_CLASS_DEF(respawn);
        EH_CLASS_DEF(rope_attach);
        EH_CLASS_DEF(rope_break);
        EH_CLASS_DEF(seat_switched);
        EH_CLASS_DEF(sound_played);
        EH_CLASS_DEF(take);
        EH_CLASS_DEF(task_set_as_current);
        EH_CLASS_DEF(weapon_assembled);
        EH_CLASS_DEF(weapon_disassembled);
        EH_CLASS_DEF(weapon_deployed);
        EH_CLASS_DEF(weapon_rested);

    protected:
        bool _initialized;
        registered_sqf_function _ehFunc;
    };

}  // namespace intercept
