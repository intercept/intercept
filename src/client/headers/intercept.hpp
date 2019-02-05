#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "client/eventhandlers.hpp"
#include "shared/functions.hpp"
#ifndef INTERCEPT_NO_SQF
#include "client/sqf/sqf.hpp"
#endif
#include "shared/client_types.hpp"

namespace intercept {
    extern "C" {
        DLLEXPORT int  CDECL api_version();
        /// @brief before initFunctions. Actually a prePreStart
        DLLEXPORT void CDECL pre_start();
        /// @brief CBA XEH_preStart
        DLLEXPORT void CDECL post_start();
        DLLEXPORT void CDECL pre_init();
        DLLEXPORT void CDECL pre_pre_init();
        DLLEXPORT void CDECL post_init();
        DLLEXPORT void CDECL mission_ended();
        DLLEXPORT void CDECL on_frame();
        DLLEXPORT void CDECL on_signal(std::string &signal_name_, game_value& value1_);  //#TODO no C ABI here! use r_string
        DLLEXPORT void CDECL on_interface_unload(r_string name_);
        DLLEXPORT void CDECL register_interfaces();
        DLLEXPORT void CDECL handle_unload();
        DLLEXPORT bool CDECL is_signed();

#define EH(x) DLLEXPORT void CDECL x

        EH(anim_changed)(object &unit_, r_string anim_name_);
        EH(anim_done)(object &unit_, r_string anim_name_);
        EH(anim_state_changed)(object &unit_, r_string anim_name_);
        EH(container_closed)(object &container_, object &player_);
        EH(controls_shifted)(object &vehicle_, object &new_controller_, object &old_controller_);
        EH(dammaged)(object &unit_, r_string &selection_name_, float damage_);
        EH(engine)(object &vehicle_, bool engine_state_);
        EH(epe_contact)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(epe_contact_end)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(epe_contact_start)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(explosion)(object &vehicle_, float damage_);
        EH(fired)(object &unit_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_, r_string magazine, object &projectile_);
        EH(fired_near)(object &unit_, object &firer_, float distance_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_);
        EH(fuel)(object &vehicle_, bool fuel_state_);
        EH(gear)(object &vehicle_, bool gear_state_);
        EH(get_in)(object &vehicle_, r_string position_, object &unit_, rv_turret_path turret_path);
        EH(get_out)(object &vehicle_, r_string position_, object &unit_, rv_turret_path turret_path);
        EH(handle_damage)(object &unit_, r_string selection_name_, float damage_, object &source_, r_string projectile_, int hit_part_index_);
        EH(handle_heal)(object &unit_, object &healder_, bool healer_can_heal_);
        EH(handle_rating)(object &unit_, float rating_);
        EH(handle_score)(object &unit_, object &object_, float score_);
        EH(hit)(object &unit_, object &caused_by_, float damage_);
        EH(hit_part)(std::vector<hit_part_data> &data_);
        EH(init)(object &unit_);
        EH(incoming_missile)(object &unit_, r_string ammo_, object &firer_);
        EH(inventory_closed)(object &object_, object &container_);
        EH(inventory_opened)(object &object_, object &container_);
        EH(killed)(object &unit_, object &killer_);
        EH(landed_touch_down)(object &plane_, int airport_id_);
        EH(landed_stopped)(object &plane_, int airport_id_);
        EH(local)(object &object_, bool local_);
        EH(post_reset)();
        EH(put)(object &unit_, object &container_, r_string item_);
        EH(respawn)(object &unit_, object &corpse_);
        EH(rope_attach)(object &object1, object &rope_, object &object2_);
        EH(rope_break)(object &object1, object &rope_, object &object2_);
        EH(seat_switched)(object &vehicle_, object &unit1_, object &unit2_);
        EH(sound_played)(object &unit_, int sound_code_);
        EH(take)(object &unit_, object &container_, r_string item_);
        EH(task_set_as_current)(object &unit_, task &task_);
        EH(weapon_assembled)(object &unit_, object &weapon_);
        EH(weapon_disassembled)(object &unit_, object &primary_bag_, object &secondary_bag_);
        EH(weapon_deployed)(object &unit_, bool is_deployed_);
        EH(weapon_rested)(object &unit_, bool is_rested_);
    }
}
