/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief World information functions.

Get information about the game world, wind, waves, date/time, etc.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;
namespace intercept {
    namespace sqf {
        /* World */

        struct rv_date {
            float year;
            float month;
            float day;
            float hour;
            float minute;

            rv_date(float year_, float month_, float day_, float hour_, float minute_) {
                year = year_;
                month = month_;
                day = day_;
                hour = hour_;
                minute = minute_;
            }

            static rv_date from_vector(const std::vector<float> &date_vector_) {
                return rv_date(date_vector_[0], date_vector_[1], date_vector_[2], date_vector_[3], date_vector_[4]);
            }

            operator game_value() {
                return game_value(std::vector<game_value>({year,
                                                           month,
                                                           day,
                                                           hour,
                                                           minute}));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({year,
                                                           month,
                                                           day,
                                                           hour,
                                                           minute}));
            }

            std::vector<float> to_vector() const {
                std::vector<float> ret_val{year, month, day, hour, minute};
                return ret_val;
            }
        };

        float world_size();
        sqf_return_string world_name();
        float wind_str();
        float wind_dir();
        void set_wind(float x_, float y_);
        void set_wind(float x_, float y_, bool force_);
        vector3 wind();
        float gusts();
        float humidity();
        float waves();

        float lightnings();

        float moon_intensity();
        float next_weather_change();
        float overcast();
        float overcast_forecast();
        float rain();
        float rainbow();
        float sun_or_moon();  // BUT WHICH ONE IS IT!?!?!??!!?
        bool fog();
        float fog_forecast();

        float time();

        float time_multiplier();

        float date_to_number(int year_, int month_, int day_, int hour_, float minute_);
        rv_date number_to_date(int year_, float time_);
        rv_date date();
        rv_date mission_start();

        struct rv_fog_parameters {
            float value;
            float decay;
            float base;

            rv_fog_parameters(float value_, float decay_, float base_) {
                value = value_;
                decay = decay_;
                base = base_;
            }

            static rv_fog_parameters from_vector(const std::vector<float> &fog_params_vector_) {
                return rv_fog_parameters(fog_params_vector_[0], fog_params_vector_[1], fog_params_vector_[2]);
            }

            std::vector<float> to_vector() const {
                std::vector<float> ret_val{value, decay, base};
                return ret_val;
            }
        };

        rv_fog_parameters fog_params();

        struct rv_rendering_distances {
            float object_distance;
            float shadow_distance;

            rv_rendering_distances(float object_distance_, float shadow_distance_) {
                object_distance = object_distance_;
                shadow_distance = shadow_distance_;
            }

            static rv_rendering_distances from_vector(const std::vector<float> &rendering_distances_vector_) {
                return rv_rendering_distances(rendering_distances_vector_[0], rendering_distances_vector_[1]);
            }

            std::vector<float> to_vector() const {
                std::vector<float> ret_val{object_distance, shadow_distance};
                return ret_val;
            }
        };

        rv_rendering_distances get_object_view_distance();

        void set_date(int year_, int month_, int day_, int hour_, float minute_);

        std::vector<object> entities(sqf_string_list_const_ref typesinclude_, sqf_string_list_const_ref typesexclude_, bool includeCrews_, bool excludeDead_);

        void set_horizon_parallax_coef(float value_);
        void set_detail_map_blend_pars(float full_detail_, float no_detail_);
        void simul_cloud_density(const vector3 &pos_);
        void simul_cloud_occlusion(const vector3 &pos1_, const vector3 &pos2_);
        bool simul_in_clouds(const vector3 &pos_);
        void set_fog(float &time_, float &fog_value_, std::optional<float> fog_decay_, std::optional<float> fog_base_);
        void set_gusts(float time_, float gusts_value_);
        void set_rain(float time_, float rain_value_);
        void set_rainbow(float time_, float rainbow_value_);
        void set_overcast(float time_, float overcast_value_);
        void set_wind_dir(float time_, float wind_value_);
        void set_wind_force(float time_, float force_value_);
        void set_wind_str(float time_, float strength_value_);
        void set_acc_time(float value_);
        void set_object_view_distance(float distance_);
        void set_object_view_distance(float object_distance_, float shadow_distance_);
        void set_shadow_distance(float value_);
        void set_simul_weather_layers(float value_);
        void set_terrain_grid(float value_);
        void set_time_multiplier(float value_);
        void set_view_distance(float value_);
        void skip_time(float value_);

        void enable_environment(bool ambient_life_, bool ambient_sound_ = true);
        void enable_sat_normal_on_detail(bool value_);
        float acc_time();
        float daytime();
        void force_weather_change();
        float get_shadow_distance();
        void init_ambient_life();
        void simul_weather_sync();

        std::pair<bool, bool> environment_enabled();

        float moon_phase(int year_, int month_, int day_, int hour_, float minute_);
        void set_waves(float time_, float waves_value_);
        void set_fog(float time_, float fog_);
        void set_fog(float time_, float fog_value_, float fog_decay_, float fog_base_);
        int get_terrain_grid();
        float view_distance();
        void enable_caustics(bool value_);
        void set_lightnings(float time_, float lightnings_value_);
        bool near_objects_ready(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_roads(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_supplies(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<rv_target> near_targets(const object &unit_, float radius_);
        object nearest_object(const vector3 &pos_);
        object nearest_object(const vector3 &pos_, sqf_string_const_ref type_);
        object nearest_object(const object &obj_, sqf_string_const_ref type_);
        object nearest_object(const vector3 &pos_, float id_);
        std::vector<object> nearest_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_terrain_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_terrain_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> units_below_height(const group &group_, float height_);
        std::vector<object> units_below_height(const std::vector<object> &units_, float height_);
        bool surface_is_water(const vector3 &pos_);
        vector3 surface_normal(const vector3 &pos_);
        sqf_return_string surface_type(const vector3 &pos_);
        std::vector<rv_best_place> select_best_places(const object &obj_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_);
        std::vector<rv_best_place> select_best_places(const vector3 &pos_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_);
        bool is_on_road(const object &object_);
        bool is_on_road(const vector3 &position_);
        float get_friend(const side &side1_, const side &side2_);
        void set_friend(const side &side1_, const side &side2_, float value_);
        std::vector<object> near_objects(const vector3 &pos_, float radius_);
        std::vector<object> near_objects(const object &object_, float radius_);
        std::vector<object> near_objects(const vector3 &pos_, sqf_string_const_ref type_, float radius_);
        std::vector<object> near_objects(const object &object_, sqf_string_const_ref type_, float radius_);
        object nearest_building(const object &value_);
        object nearest_building(const vector3 &value_);

        std::vector<object> entities(sqf_string_const_ref type_);
        std::vector<object> units(const object &unit_);
        bool preload_object(float distance_, const object &object_);
        bool preload_object(float distance_, sqf_string_const_ref class_name_);
        object road_at(const object &object_);
        object road_at(const vector3 &position_);
        bool get_remote_sensors_disabled();
        void disable_remote_sensors(bool value_);
        bool underwater(const object &value_);
        std::vector<object> vehicles();
        void set_local_wind_params(float strength_, float diameter_);

        float getelevationoffset();
    }  // namespace sqf
}  // namespace intercept
