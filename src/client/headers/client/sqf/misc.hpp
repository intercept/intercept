/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Misc function wrappers.

This is basically stuff that has not been categorized yet. Compared to uncategorized.hpp,
which is functions that lack a clear category.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"
#include <vector>

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        struct rv_artillery_computer_settings {
            std::string name;
            std::string ammo;
            int mode;  //#TODO investigate what this actually is

            rv_artillery_computer_settings(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                  ammo(rv_game_value_[1]),
                  mode(rv_game_value_[2]) {}
        };
        struct rv_credit {
            std::string library_name;
            std::string credits;

            rv_credit(const game_value &rv_game_value_)
                : library_name(rv_game_value_[0]),
                  credits(rv_game_value_[1]) {}
        };
        struct rv_product_version {
            std::string name;
            std::string name_short;
            float version;
            float build;
            std::string branch;
            bool mods;
            std::string platform;

            rv_product_version(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                  name_short(rv_game_value_[1]),
                  version(rv_game_value_[2]),
                  build(rv_game_value_[3]),
                  branch(rv_game_value_[4]),
                  mods(rv_game_value_[5]),
                  platform(rv_game_value_[6]) {}
        };
        //simulation
        //NULAR -- https://github.com/intercept/intercept/issues/13
        bool can_trigger_dynamic_simulation(const object &unit_);
        void enable_simulation(const object &value0_, bool value1_);
        void enable_simulation_global(const object &value0_, bool value1_);
        bool simulation_enabled(const object &value_);
        void trigger_dynamic_simulation(const object &object_, bool trigger_);
        /**
        * \brief
        * \param category_ - one of:

        "Group" - Infantry units. Set to a reasonable distance, player should not see disabled infantry units. Default: 500m
        "Vehicle" - Vehicles with crew. Set to a reasonable distance, player should not see disabled vehicles. Default: 350m
        "EmptyVehicle" - All vehicles without crew. Separated from Props as Empty Vehicles have often more complex damage states and selective destruction. Their activation distance should by larger that the one used for Props. Default: 250m
        "Prop" - Static objects. Anything from a small tin can to a building. Default: 50m

        * \param distance_
        */
        void set_dynamic_simulation_distance(sqf_string_const_ref category_, float distance_);
        //#TODO add BIKI entry and implement
        //void set_dynamic_simulation_distance_coef(sqf_string_const_ref , float); //binary__setdynamicsimulationdistancecoef__string__scalar__ret__nothing
        void enable_dynamic_simulation(const object &object_, bool enable_);
        void enable_dynamic_simulation(const group &group_, bool enable_);
        void diag_dynamic_simulation_end(sqf_string_const_ref type_);
        float dynamic_simulation_distance(sqf_string_const_ref category_);
        float dynamic_simulation_distance_coef(sqf_string_const_ref class_);
        bool dynamic_simulation_enabled(const object &object_);
        bool dynamic_simulation_enabled(const group &group_);
        void enable_dynamic_simulation_system(bool enable_);
        bool dynamic_simulation_system_enabled();
        void set_dynamic_simulation_distance_coef(sqf_string_const_ref class_, float multiplayer_);

        void activate_addons(sqf_string_list_const_ref addons_);
        void enable_saving(bool enable_);
        void enable_saving(bool enable_, bool autosave_);
        std::vector<float> get_dlcs(float filter_);
        float armory_points();
        bool cadet_mode();
        bool cheats_enabled();
        float difficulty();
        float distribution_region();
        void finish_mission_init();
        void force_end();
        bool free_look();
        float get_total_dlc_usage_time();
        bool is_autotest();
        bool is_filepatching_enabled();
        bool is_instructor_figure_enabled();
        bool is_steam_mission();
        bool is_stream_friendly_ui_enabled();

        void load_game();
        void log_entities();
        bool mark_as_finished_on_steam();
        float mission_difficulty();
        void run_init_script();
        bool reversed_mouse_y();
        bool team_switch_enabled();
        void team_switch();
        float system_of_units();
        void select_no_player();
        bool saving_enabled();
        bool difficulty_enabled(sqf_string_const_ref value_);
        void activate_key(sqf_string_const_ref keyname_);
        void de_activate_key(sqf_string_const_ref key_);
        bool is_key_active(sqf_string_const_ref value_);
        void delete_collection(const object &collection_);  //deprecated
        bool delete_identity(sqf_string_const_ref identity_);
        void delete_site(const object &value_);
        bool delete_status(sqf_string_const_ref value_);
        void enable_sentences(bool value_);
        void enable_stress_damage(bool value_);
        void enable_team_switch(bool value_);
        float get_dlcusage_time(float value_);
        void dissolve_team(sqf_string_const_ref value_);
        bool is_dlcavailable(float value_);
        void set_armory_points(float value_);
        void set_system_of_units(float value_);
        bool unlock_achievement(sqf_string_const_ref value_);
        void add_live_stats(const object &value0_, float value1_);  //Xbox stuff
        bool load_identity(const object &value0_, sqf_string_const_ref value1_);
        bool load_status(const object &value0_, sqf_string_const_ref value1_);
        bool save_status(const object &value0_, sqf_string_const_ref value1_);
        void save_game();
        void save_joysticks();
        sqf_return_string role_description(const object &value_);
        bool set_stat_value(sqf_string_const_ref name_, float value_);
        void host_mission(const config &config_, const display &display_);
        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_);
        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_, bool skip_briefing_);
        void play_mission(sqf_string_const_ref campaign_, const config &mission_);
        void play_mission(sqf_string_const_ref campaign_, const config &mission_, bool skip_briefing_);
        void play_scripted_mission(sqf_string_const_ref world_, const code &command_);
        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_);
        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_, bool ignore_child_window_);
        float difficulty_option(sqf_string_const_ref optionname_);
        void enable_weapon_disassembly(bool enable_);
        object create_site(sqf_string_const_ref type_, const vector3 &pos_);
        bool save_identity(const object &value0_, sqf_string_const_ref value1_);

        //TOH traffic - needs to be tested, probably not working
        void set_traffic_density(float density_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_);
        void enable_traffic(bool value_);
        void set_traffic_distance(float value_);

        //A2 artillary - did this ever work?
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, sqf_string_const_ref magazine_type_);
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, sqf_string_const_ref magazine_type_);
        void enable_engine_artillery(bool value_);
        rv_artillery_computer_settings get_artillery_computer_settings();

        sqf_return_string language();
        std::vector<rv_credit> library_credits();
        sqf_return_string_list library_disclaimers();
        rv_product_version product_version();

        //3D stuff
        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_);
        void draw_icon_3d(sqf_string_const_ref texture_, const rv_color &color_, const vector3 &pos_agl_, float width_, float height_, float angle_, sqf_string_const_ref text_ = "", float shadow_ = 1.0f, float text_size_ = 1.0f, sqf_string_const_ref font_ = "TahomaB", sqf_string_const_ref text_align_ = "center", bool draw_offscreen_ = false);

        /* potential namespace: particles */
        void set_particle_params(const object &particle_source_, const rv_particle_array &particle_array_);
        void set_particle_random(const object &particle_source_, const rv_particle_random &particle_random_);
        void set_particle_circle(const object &particle_source_, float radius_, const vector3 &velocity_);
        void set_particle_fire(const object &particle_source_, float core_intensity_, float core_distance_, float damage_time_);
        void set_particle_class(const object &particle_source_, sqf_string_const_ref particle_class_);
        void drop(const rv_particle_array &particle_array_);
        void set_particle_params();
        float particles_quality();
        void set_drop_interval(const object &value0_, float value1_);

        //potential new cat: side
        std::vector<object> detected_mines(const side &side_);
        float count_side(const side &side_, std::vector<object> &objects_);
        void set_airport_side(float value0_, const side &value1_);
        void set_airport_side(const object &target_, const side &value1_);
        void reveal_mine(const side &value0_, const object &value1_);
        bool mine_detected_by(const object &value0_, const side &value1_);
        void add_score_side(const side &value0_, float value1_);
        void airport_side(int id_);
        void airport_side(const object &target_);
        float score_side(const side &value_);
    }  // namespace sqf
}  // namespace intercept
