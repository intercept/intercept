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
            game_value params({density_,
                               x_min_,
                               x_max_,
                               z_min_,
                               z_max_});

            host::functions.invoke_raw_unary(__sqf::unary__settrafficdensity__array__ret__nothing, params);
        }

        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_) {
            game_value params({gap_,
                               x_min_,
                               x_max_,
                               z_min_,
                               z_max_});

            host::functions.invoke_raw_unary(__sqf::unary__settrafficgap__array__ret__nothing, params);
        }

        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_) {
            game_value params({speed_,
                               x_min_,
                               x_max_,
                               z_min_,
                               z_max_});

            host::functions.invoke_raw_unary(__sqf::unary__settrafficspeed__array__ret__nothing, params);
        }

        void enable_traffic(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enabletraffic__bool__ret__nothing, value_);
        }
        void set_traffic_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__settrafficdistance__scalar__ret__nothing, value_);
        }
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, sqf_string_const_ref magazine_type_) {
            auto_array<game_value> units({units_.begin(), units_.end()});

            game_value params_right({std::move(units),
                                     magazine_type_});

            return host::functions.invoke_raw_binary(__sqf::binary__inrangeofartillery__array__array__ret__bool, position_, params_right);
        }
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, sqf_string_const_ref magazine_type_) {
            game_value params_right({target_position_,
                                     magazine_type_});

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
            game_value ret = host::functions.invoke_raw_nular(__sqf::nular__librarycredits__ret__array);
            return __helpers::__convert_to_vector<rv_credit>(ret);
        }

        sqf_return_string_list library_disclaimers() {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__librarydisclaimers__ret__array));
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
            game_value args({enable_,
                             autosave_});

            host::functions.invoke_raw_unary(__sqf::unary__enablesaving__bool_array__ret__nothing, args);
        }

        std::vector<float> get_dlcs(float filter_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__getdlcs__scalar__ret__array, filter_));
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

        void delete_collection(const object &collection_) {
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
            game_value params({name_,
                               value_});

            return host::functions.invoke_raw_unary(__sqf::unary__setstatvalue__array__ret__bool, params);
        }

        void host_mission(const config &config_, const display &display_) {
            game_value params({config_,
                               display_});

            host::functions.invoke_raw_unary(__sqf::unary__hostmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_) {
            game_value params({campaign_,
                               mission_});

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_, bool skip_briefing_) {
            game_value params({campaign_,
                               mission_,
                               skip_briefing_});

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, const config &mission_) {
            game_value params({campaign_,
                               mission_});

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_mission(sqf_string_const_ref campaign_, const config &mission_, bool skip_briefing_) {
            game_value params({campaign_,
                               mission_,
                               skip_briefing_});

            host::functions.invoke_raw_unary(__sqf::unary__playmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_) {
            game_value params({world_,
                               command_});

            host::functions.invoke_raw_unary(__sqf::unary__playscriptedmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_) {
            game_value params({world_,
                               command_,
                               config_});

            host::functions.invoke_raw_unary(__sqf::unary__playscriptedmission__array__ret__nothing, params);
        }

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_, bool ignore_child_window_) {
            game_value params({world_,
                               command_,
                               config_,
                               ignore_child_window_});

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

        //3d Stuff
        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_) {
            game_value args({pos1_,
                             pos2_,
                             color_});
            host::functions.invoke_raw_unary(__sqf::unary__drawline3d__array__ret__nothing, args);
        }

        void draw_icon_3d(sqf_string_const_ref texture_, const rv_color & color_, const vector3 & pos_agl_, float width_, float height_, float angle_, sqf_string_const_ref text_, float shadow_, float text_size_, sqf_string_const_ref font_, sqf_string_const_ref text_align_, bool draw_offscreen_) {
            game_value args({
                texture_,
                color_,
                pos_agl_,
                width_,
                height_,
                angle_,
                text_,
                shadow_,
                text_size_,
                font_,
                text_align_,
                draw_offscreen_
            });

            host::functions.invoke_raw_unary(__sqf::unary__drawicon3d__array__ret__nothing, args);
        }

        void draw_laser(const vector3& pos_asl_, const vector3& dir_, const rv_color& beam_color_, const rv_color& dot_color_, float dot_size_, float beam_thickness_, float max_beam_length_, bool is_IR) {
            game_value args({
                pos_asl_,
                dir_,
                beam_color_,
                dot_color_,
                dot_size_,
                beam_thickness_,
                max_beam_length_,
                is_IR
            });

            host::functions.invoke_raw_unary(__sqf::unary__drawlaser__array__ret__nothing, args);
        }

        //particles
        float particles_quality() {
            return __helpers::__retrieve_nular_number(__sqf::nular__particlesquality__ret__scalar);
        }

        void set_particle_params(const object &particle_source_, const rv_particle_array &particle_array_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticleparams__object__array__ret__nothing, particle_source_, particle_array_);
        }

        void set_particle_random(const object &particle_source_, const rv_particle_random &particle_random_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticlerandom__object__array__ret__nothing, particle_source_, particle_random_);
        }

        void set_particle_circle(const object &particle_source_, float radius_, const vector3 &velocity_) {
            game_value args({radius_,
                             velocity_});
            host::functions.invoke_raw_binary(__sqf::binary__setparticlecircle__object__array__ret__nothing, particle_source_, args);
        }

        void set_particle_fire(const object &particle_source_, float core_intensity_, float core_distance_, float damage_time_) {
            game_value args({core_intensity_,
                             core_distance_,
                             damage_time_});
            host::functions.invoke_raw_binary(__sqf::binary__setparticlefire__object__array__ret__nothing, particle_source_, args);
        }

        void drop(const rv_particle_array &particle_array_) {
            host::functions.invoke_raw_unary(__sqf::unary__drop__array__ret__nothing, particle_array_);
        }

        void set_particle_class(const object &particle_source_, sqf_string_const_ref particle_class_) {
            host::functions.invoke_raw_binary(__sqf::binary__setparticleclass__object__string__ret__nothing, particle_source_, particle_class_);
        }

        //#TODO: Implement with this massive amount of params
        void set_particle_params() {
            //host::functions.invoke_raw_binary(__sqf::binary__setparticleparams__object__array__ret__nothing, time_, overcast_value_);
        }

        void set_drop_interval(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdropinterval__object__scalar__ret__nothing, value0_, value1_);
        }

        //side

        std::vector<object> detected_mines(const side &side_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__detectedmines__side__ret__array, side_));
        }

        float count_side(const side &side_, std::vector<object> &objects_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countside__side__array__ret__scalar, side_, std::move(objects));
        }

        void reveal_mine(const side &value0_, const object &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__revealmine__side__object__ret__nothing, value0_, value1_);
        }

        void set_airport_side(float value0_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairportside__object_scalar__side__ret__nothing, value0_, value1_);
        }

        void set_airport_side(const object &target_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairportside__object_scalar__side__ret__nothing, target_, value1_);
        }

        bool mine_detected_by(const object &value0_, const side &value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__minedetectedby__object__side__ret__bool, value0_, value1_);
        }

        void add_score_side(const side &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addscoreside__side__scalar__ret__nothing, value0_, value1_);
        }

        side airport_side(int id_) {
            return host::functions.invoke_raw_unary(__sqf::unary__airportside__object_scalar__ret__side, static_cast<float>(id_));
        }
        side airport_side(const object &target_) {
            return host::functions.invoke_raw_unary(__sqf::unary__airportside__object_scalar__ret__side, target_);
        }

        float score_side(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__scoreside__side__ret__scalar, value_);
        }


        bool is_key_active(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__iskeyactive__string__ret__bool, value_);
        }

        bool reversed_mouse_y() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__reversedmousey__ret__bool);
        }


        //From contact DLC
        std::vector<float> decay_graph_values(const std::vector<float>& lower_bound_values_, const std::vector<float>& graph_values_, float coef_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__decaygraphvalues__array__ret__array, {lower_bound_values_, graph_values_, coef_}));
        }

        game_value get_graph_values(const rv_graph_value_par &graph_val_par, const std::vector<float> &xy_) {
            auto_array<game_value> parameter;
            parameter.reserve(xy_.size()+1);
            parameter.push_back({
                    graph_val_par.graph_min_x,
                    graph_val_par.graph_min_y,
                    graph_val_par.graph_max_x,
                    graph_val_par.graph_max_y,
                    graph_val_par.valueCount,
                    graph_val_par.randomOffset,
                });
            parameter.insert(parameter.end(), xy_.begin(), xy_.end());

            return host::functions.invoke_raw_unary(__sqf::unary__getgraphvalues__array__ret__array,parameter);
        }

        std::vector<float> get_person_used_dlcs(const object& unit_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__getpersonuseddlcs__object__ret__array, unit_));
        }

    }  // namespace sqf
}  // namespace intercept
