#include "misc.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include <memory>

namespace intercept {
    namespace sqf {




        //simulation
        void enable_dynamic_simulation(const object &object_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enabledynamicsimulation__object__bool__ret__nothing, object_, enable_);
        }

        void enable_dynamic_simulation(const group &group_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enabledynamicsimulation__group__bool__ret__nothing, group_, enable_);
        }

        void set_dynamic_simulation_distance(sqf_string_const_ref category_, float distance_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdynamicsimulationdistance__string__scalar__ret__nothing, category_, distance_);
        }

        void trigger_dynamic_simulation(const object &object_, bool trigger_) {
            host::functions.invoke_raw_binary(__sqf::binary__triggerdynamicsimulation__object__bool__ret__nothing, object_, trigger_);
        }

        bool simulation_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__simulationenabled__object__ret__bool, value_);
        }

        void enable_simulation(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablesimulation__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_simulation_global(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablesimulationglobal__object__bool__ret__nothing, value0_, value1_);
        }

        bool can_trigger_dynamic_simulation(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__cantriggerdynamicsimulation__object__ret__bool, unit_);
        }

        void diag_dynamic_simulation_end(sqf_string_const_ref type_) {
            host::functions.invoke_raw_unary(__sqf::unary__diag_dynamicsimulationend__string__ret__nothing, type_);
        }

        float dynamic_simulation_distance(sqf_string_const_ref category_) {
            return host::functions.invoke_raw_unary(__sqf::unary__dynamicsimulationdistance__string__ret__scalar, category_);
        }

        float dynamic_simulation_distance_coef(sqf_string_const_ref class_) {
            return host::functions.invoke_raw_unary(__sqf::unary__dynamicsimulationdistancecoef__string__ret__scalar, class_);
        }

        bool dynamic_simulation_enabled(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__dynamicsimulationenabled__object__ret__bool, object_);
        }

        bool dynamic_simulation_enabled(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__dynamicsimulationenabled__group__ret__bool, group_);
        }

        void enable_dynamic_simulation_system(bool enable_) {
            host::functions.invoke_raw_unary(__sqf::unary__enabledynamicsimulationsystem__bool__ret__nothing, enable_);
        }
        //NULAR -- https://github.com/intercept/intercept/issues/13
        bool dynamic_simulation_system_enabled() {
            return host::functions.invoke_raw_nular(__sqf::nular__dynamicsimulationsystemenabled__ret__bool);
        }

        void set_dynamic_simulation_distance_coef(sqf_string_const_ref class_, float multiplayer_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdynamicsimulationdistancecoef__string__scalar__ret__nothing, class_, multiplayer_);
        }

        void set_traffic_density(float density_, float x_min_, float x_max_, float z_min_, float z_max_) {
            game_value params({
                density_,
                x_min_,
                x_max_,
                z_min_,
                z_max_
            });

            host::functions.invoke_raw_unary(__sqf::unary__settrafficdensity__array__ret__nothing, params);
        }

        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_) {
            game_value params({
                gap_,
                x_min_,
                x_max_,
                z_min_,
                z_max_
            });

            host::functions.invoke_raw_unary(__sqf::unary__settrafficgap__array__ret__nothing, params);
        }

        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_) {
            game_value params({
                speed_,
                x_min_,
                x_max_,
                z_min_,
                z_max_
            });

            host::functions.invoke_raw_unary(__sqf::unary__settrafficspeed__array__ret__nothing, params);
        }

        void enable_traffic(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enabletraffic__bool__ret__nothing, value_);
        }
        void set_traffic_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__settrafficdistance__scalar__ret__nothing, value_);
        }
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, sqf_string_const_ref magazine_type_) {
            auto_array<game_value> units({ units_.begin(), units_.end() });

            game_value params_right({
                std::move(units),
                magazine_type_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__inrangeofartillery__array__array__ret__bool, position_, params_right);
        }
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, sqf_string_const_ref magazine_type_) {
            game_value params_right({
                target_position_,
                magazine_type_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getartilleryeta__object__array__ret__scalar, unit_, params_right);
        }
        void enable_engine_artillery(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enableengineartillery__bool__ret__nothing, value_);
        }

        rv_artillery_computer_settings get_artillery_computer_settings() {
            return rv_artillery_computer_settings(host::functions.invoke_raw_nular(__sqf::nular__getartillerycomputersettings__ret__array));
        }

        sqf_return_string language() {
            return __helpers::__retrieve_nular_string(__sqf::nular__language__ret__string);
        }

        std::vector<rv_credit> library_credits() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__librarycredits__ret__array);

            std::vector<rv_credit> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(input[i]);
            }
            return output;
        }

        sqf_return_string_list library_disclaimers() {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_nular(__sqf::nular__librarydisclaimers__ret__array));
        }
        rv_product_version product_version() {
            return rv_product_version(host::functions.invoke_raw_nular(__sqf::nular__productversion__ret__array));
        }

        void activate_addons(sqf_string_list_const_ref addons_) {
            auto_array<game_value> addons(addons_.begin(), addons_.end());

            host::functions.invoke_raw_unary(__sqf::unary__activateaddons__array__ret__nothing, std::move(addons));
        }

        void enable_saving(bool enable_) {
            enable_saving(enable_, !enable_);
        }

        void enable_saving(bool enable_, bool autosave_) {
            game_value args({
                enable_,
                autosave_
            });

            host::functions.invoke_raw_unary(__sqf::unary__enablesaving__bool_array__ret__nothing, args);
        }

        std::vector<float> get_dlcs(float filter_) {
            return __helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(__sqf::unary__getdlcs__scalar__ret__array, filter_));
        }

        float armory_points() {
            return __helpers::__retrieve_nular_number(__sqf::nular__armorypoints__ret__scalar);
        }

        bool cadet_mode() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__cadetmode__ret__bool);
        }

        bool cheats_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__cheatsenabled__ret__bool);
        }

        float difficulty() {
            return __helpers::__retrieve_nular_number(__sqf::nular__difficulty__ret__scalar);
        }

        float distribution_region() {
            return __helpers::__retrieve_nular_number(__sqf::nular__distributionregion__ret__scalar);
        }

        void finish_mission_init() {
            __helpers::__empty_nular(__sqf::nular__finishmissioninit__ret__nothing);
        }

        void force_end() {
            __helpers::__empty_nular(__sqf::nular__forceend__ret__nothing);
        }

        bool free_look() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__freelook__ret__bool);
        }

        float get_total_dlc_usage_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__gettotaldlcusagetime__ret__scalar);
        }

        bool is_autotest() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isautotest__ret__bool);
        }

        bool is_filepatching_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isfilepatchingenabled__ret__bool);
        }

        bool is_instructor_figure_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isinstructorfigureenabled__ret__bool);
        }

        bool is_steam_mission() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__issteammission__ret__bool);
        }

        bool is_stream_friendly_ui_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isstreamfriendlyuienabled__ret__bool);
        }

        void load_game() {
            __helpers::__empty_nular(__sqf::nular__loadgame__ret__nothing);
        }

        void log_entities() {
            __helpers::__empty_nular(__sqf::nular__logentities__ret__nothing);
        }

        bool mark_as_finished_on_steam() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__markasfinishedonsteam__ret__bool);
        }

        float mission_difficulty() {
            return __helpers::__retrieve_nular_number(__sqf::nular__missiondifficulty__ret__scalar);
        }

        void run_init_script() {
            __helpers::__empty_nular(__sqf::nular__runinitscript__ret__nothing);
        }

        bool team_switch_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__teamswitchenabled__ret__bool);
        }

        void team_switch() {
            __helpers::__empty_nular(__sqf::nular__teamswitch__ret__nothing);
        }

        float system_of_units() {
            return __helpers::__retrieve_nular_number(__sqf::nular__systemofunits__ret__scalar);
        }

        void select_no_player() {
            __helpers::__empty_nular(__sqf::nular__selectnoplayer__ret__nothing);
        }

        bool saving_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__savingenabled__ret__bool);
        }

        void activate_key(sqf_string_const_ref keyname_) {
            __helpers::__empty_unary_string(__sqf::unary__activatekey__string__ret__nothing, keyname_);
        }

        void add_switchable_unit(const object & unit_) {
            __helpers::__empty_unary_object(__sqf::unary__addswitchableunit__object__ret__nothing, unit_);
        }

        bool difficulty_enabled(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__difficultyenabled__string__ret__bool, value_);
        }

        void enable_sentences(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enablesentences__bool__ret__nothing, value_);
        }

        void enable_stress_damage(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enablestressdamage__bool__ret__nothing, value_);
        }

        void enable_team_switch(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enableteamswitch__bool__ret__nothing, value_);
        }

        float get_dlcusage_time(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__getdlcusagetime__scalar__ret__scalar, value_);
        }

        void de_activate_key(sqf_string_const_ref key_) {
            __helpers::__empty_unary_string(__sqf::unary__deactivatekey__string__ret__nothing, key_);
        }

        void delete_collection(const object & collection_) {
            __helpers::__empty_unary_object(__sqf::unary__deletecollection__object__ret__nothing, collection_);
        }

        bool delete_identity(sqf_string_const_ref identity_) {
            return __helpers::__bool_unary_string(__sqf::unary__deleteidentity__string__ret__bool, identity_);
        }

        void delete_site(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__deletesite__object__ret__nothing, value_);
        }

        bool delete_status(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__deletestatus__string__ret__bool, value_);
        }

        void dissolve_team(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__dissolveteam__string__ret__nothing, value_);
        }

        bool is_dlcavailable(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__isdlcavailable__scalar__ret__bool, value_);
        }

        void set_armory_points(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setarmorypoints__scalar__ret__nothing, value_);
        }

        void set_system_of_units(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setsystemofunits__scalar__ret__nothing, value_);
        }

        bool unlock_achievement(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__unlockachievement__string__ret__bool, value_);
        }

        void add_live_stats(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addlivestats__object__scalar__ret__nothing, value0_, value1_);
        }

        bool load_identity(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__loadidentity__object__string__ret__bool, value0_, value1_);
        }

        bool load_status(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__loadstatus__object__string__ret__bool, value0_, value1_);
        }

        bool save_identity(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__saveidentity__object__string__ret__bool, value0_, value1_);
        }

        bool save_status(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__savestatus__object__string__ret__bool, value0_, value1_);
        }

        void save_game() {
            host::functions.invoke_raw_nular(__sqf::nular__savegame__ret__nothing);
        }

        void save_joysticks() {
            host::functions.invoke_raw_nular(__sqf::nular__savejoysticks__ret__nothing);
        }

        sqf_return_string role_description(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__roledescription__object__ret__string, value_);
        }

        bool set_stat_value(sqf_string_const_ref name_, float value_) {
            game_value params({
                name_,
                value_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__setstatvalue__array__ret__bool, params);
        }

        void host_mission(const config &config_, const display &display_) {
            game_value params({
                config_,
                display_
            });

            host::functions.invoke_raw_unary(__sqf::unary__hostmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_) {
            game_value params({
                campaign_,
                mission_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_, bool skip_briefing_) {
            game_value params({
                campaign_,
                mission_,
                skip_briefing_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, const config &mission_) {
            game_value params({
                campaign_,
                mission_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, const config &mission_, bool skip_briefing_) {
            game_value params({
                campaign_,
                mission_,
                skip_briefing_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_) {
            game_value params({
                world_,
                command_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playscriptedmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_) {
            game_value params({
                world_,
                command_,
                config_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playscriptedmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_, bool ignore_child_window_) {
            game_value params({
                world_,
                command_,
                config_,
                ignore_child_window_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playscriptedmission__array__ret__nothing, params);
        }

        float difficulty_option(sqf_string_const_ref optionname_) {
            return host::functions.invoke_raw_unary(__sqf::unary__difficultyoption__string__ret__scalar, optionname_);
        }

        void enable_weapon_disassembly(bool enable_) {
            host::functions.invoke_raw_unary(__sqf::unary__enableweapondisassembly__bool__ret__nothing, enable_);
        }

        object create_site(sqf_string_const_ref type_, const vector3 &pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__createsite__string__array__ret__object, type_, pos_);
        }
    }
}
