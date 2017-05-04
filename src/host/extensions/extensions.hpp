/*!
@file
@author Nou (korewananda@gmail.com)

@brief Handles loading and unloading client plugins.

This contains the functionality for loading and unload client plugin modules.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "shared\functions.hpp"
#include "shared\client_types.hpp"

#include "search.hpp"

namespace intercept {
    /*!
    @namespace
    @brief Contains the module entry definitions and classes.
    */
    namespace module {
        /*!
        @name Plugin Exported Function Definitions
        */
        /*!@{
        @brief Function definitions.
        */
        typedef int(__cdecl *api_version_func)();
        typedef void(__cdecl *assign_functions_func)(const struct intercept::client_functions funcs);
        typedef void(__cdecl *handle_unload_func)();
        typedef void(__cdecl *pre_start_func)();
        typedef void(__cdecl *pre_init_func)();
        typedef void(__cdecl *post_init_func)();
        typedef void(__cdecl *mission_end_func)();
        typedef void(__cdecl *mission_stopped_func)();
        typedef void(__cdecl *on_frame_func)();
        typedef void(__cdecl *on_signal_func)(game_value &this_);

        //!@}

        /*!
        @brief Holds the addresses of exported functions from client plugins.
        */
        struct functions {
            /*!@{
            @brief Addresses of exported functions.
            */
            api_version_func api_version;
            assign_functions_func assign_functions;
            handle_unload_func handle_unload;
            pre_start_func pre_start;
            pre_init_func pre_init;
            post_init_func post_init;
            mission_end_func mission_end;
            mission_stopped_func mission_stopped;
            on_frame_func on_frame;
            on_signal_func on_signal;
            //!@}
        };



#define EH(x) typedef void(__cdecl *x##_func)
        //#TODO might want r_string& here
        EH(anim_changed)(object &unit_, r_string anim_name_);
        EH(anim_done)(object &unit_, r_string anim_name_);
        EH(anim_state_changed)(object &unit_, r_string anim_name_);
        EH(container_closed)(object &container_, object &player_);
        EH(controls_shifted)(object &vehicle_, object &new_controller_, object &old_controller_);
        EH(dammaged)(object &unit_, r_string selection_name_, float damage_);
        EH(engine)(object &vehicle_, bool engine_state_);
        EH(epe_contact)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(epe_contact_end)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(epe_contact_start)(object &object1_, object &object2_, r_string selection1_, r_string selection2_, float force_);
        EH(explosion)(object &vehicle_, float damage_);
        EH(fired)(object &unit_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_, r_string magazine, object &projectile_);
        EH(fired_near)(object &unit_, object &firer_, float distance_, r_string weapon_, r_string muzzle_, r_string mode_, r_string ammo_);
        EH(fuel)(object &vehicle_, bool fuel_state_);
        EH(gear)(object &vehicle_, bool gear_state_);
        EH(get_in)(object &vehicle_, r_string position_, object &unit_, rv_list<int> &turret_path);
        EH(get_out)(object &vehicle_, r_string position_, object &unit_, rv_list<int> &turret_path);
        EH(handle_damage)(object &unit_, r_string selection_name_, float damage_, object &source_, r_string projectile_, int hit_part_index_);
        EH(handle_heal)(object &unit_, object &healder_, bool healer_can_heal_);
        EH(handle_rating)(object &unit_, float rating_);
        EH(handle_score)(object &unit_, object &object_, float score_);
        EH(hit)(object &unit_, object &caused_by_, float damage_);
        EH(hit_part)(rv_list<hit_part_data> &data_);
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

#define EH_STRUCT_DEF(x) x##_func x

        struct eventhandlers {
            EH_STRUCT_DEF(anim_changed);
            EH_STRUCT_DEF(anim_done);
            EH_STRUCT_DEF(anim_state_changed);
            EH_STRUCT_DEF(container_closed);
            EH_STRUCT_DEF(controls_shifted);
            EH_STRUCT_DEF(dammaged);
            EH_STRUCT_DEF(engine);
            EH_STRUCT_DEF(epe_contact);
            EH_STRUCT_DEF(epe_contact_end);
            EH_STRUCT_DEF(epe_contact_start);
            EH_STRUCT_DEF(explosion);
            EH_STRUCT_DEF(fired);
            EH_STRUCT_DEF(fired_near);
            EH_STRUCT_DEF(fuel);
            EH_STRUCT_DEF(gear);
            EH_STRUCT_DEF(get_in);
            EH_STRUCT_DEF(get_out);
            EH_STRUCT_DEF(handle_damage);
            EH_STRUCT_DEF(handle_heal);
            EH_STRUCT_DEF(handle_rating);
            EH_STRUCT_DEF(handle_score);
            EH_STRUCT_DEF(hit);
            EH_STRUCT_DEF(hit_part);
            EH_STRUCT_DEF(init);
            EH_STRUCT_DEF(incoming_missile);
            EH_STRUCT_DEF(inventory_closed);
            EH_STRUCT_DEF(inventory_opened);
            EH_STRUCT_DEF(killed);
            EH_STRUCT_DEF(landed_touch_down);
            EH_STRUCT_DEF(landed_stopped);
            EH_STRUCT_DEF(local);
            EH_STRUCT_DEF(post_reset);
            EH_STRUCT_DEF(put);
            EH_STRUCT_DEF(respawn);
            EH_STRUCT_DEF(rope_attach);
            EH_STRUCT_DEF(rope_break);
            EH_STRUCT_DEF(seat_switched);
            EH_STRUCT_DEF(sound_played);
            EH_STRUCT_DEF(take);
            EH_STRUCT_DEF(task_set_as_current);
            EH_STRUCT_DEF(weapon_assembled);
            EH_STRUCT_DEF(weapon_disassembled);
            EH_STRUCT_DEF(weapon_deployed);
            EH_STRUCT_DEF(weapon_rested);
        };

        /*!
        @brief A client entry. Stores, name handles, function pointers, etc.
        */
        class entry {
        public:
            entry() : handle(nullptr), name("") {}
            entry(const std::string & name_, HMODULE handle_) : handle(handle_), name(name_) {}
            /*!
            @brief The name of the module
            */
            std::string name;

            /*!
            @brief The path of the loaded module
            */
            std::string path;

            /*!
            @brief A intercept::module::functions struct containing pointers to
            plugin exported functions.
            */
            functions functions;

            /*!
            @brief A intercept::module::eventhandlers struct containing pointers to
            plugin exported event handler functions.
            */
            eventhandlers eventhandlers;

            /*!
            @brief A list of exported functions called by the signal ability.
            */
            std::unordered_map<std::string, on_signal_func> signal_funcs;

            /*!
            @brief A handle to the plugin dynamic library.
            */
            HMODULE     handle;
        };
    }

    /*!
    @brief Extension controller module.

    This controller module handles loading and unloading client plugins.
    */
    class extensions : public singleton<extensions> {
    public:
        extensions();
        ~extensions();

        /*!
        @brief Attaches the controller functions to the main controllers.
        */
        void attach_controller();
        /*!
        @name Controller Functions
        */
        //!@{
        /*!
        @brief Loads a client plugin.

        This handles all the initialization of a client plugin, and storing the
        results in the map of loaded clients.
        */
        bool load(const arguments & args_, std::string & result);

        void reload_all();

        bool do_load(const std::string & path_);



        /*!
        @brief Unloads a client plugin.

        Unloads and removes a client plugin.
        */
        bool unload(const arguments & args_, std::string & result);

        bool do_unload(const std::string & path_);

        /*!
        @brief Returns a list of all loaded modules to SQF.
        */
        bool list(const arguments & args_, std::string & result);
        //!@}

        /*!
        @brief Returns the map of all loaded modules.
        */
        std::unordered_map<std::string, module::entry>& modules();

        /*!
        @brief The struct that contains the functions exported to client plugins.
        */
        client_functions functions;

        bool do_reload;
    protected:
        /*!
        @brief The map of all loaded modules.
        */
        std::unordered_map<std::string, module::entry> _modules;

        intercept::pbo::search _searcher;

        std::list<std::string> _mod_folders;
    };
    
};
