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
        struct rv_road_info {
            sqf_string mapType;            // - road segment type, could be "ROAD", "MAIN ROAD", "TRACK", "TRAIL" (see nearestTerrainObjects)
            sqf_string texture;            // - road segment surface texture
            sqf_string textureEnd;         // - road segment surface texture
            sqf_string material;           // - road segment surface material
            vector3 begPos;                // - start of the road segment in ASL
            vector3 endPos;                // - finish of the road segment in ASL
            float width;                   // - road segment width
            float aiPathOffset;            // - config value of `AIpathOffset`
            bool isPedestrian;             // - when true road is for pedestrian use only
            bool isBridge;                 // - when true road segment is a bridge
            explicit rv_road_info(const game_value &gv_)
                : mapType(gv_[0]),
                  width(gv_[1]),
                  isPedestrian(gv_[2]),
                  texture(gv_[3]),
                  textureEnd(gv_[4]),
                  material(gv_[5]),
                  begPos(gv_[6]),
                  endPos(gv_[7]),
                  isBridge(gv_[8]),
                  aiPathOffset(gv_[9]) {}
        };

        struct rv_world_airports {
            std::vector<float> static_airports;
            std::vector<object> dynamic_airports;
            explicit rv_world_airports(const game_value &gv_) {
                auto &arr_pair = gv_.to_array();
                auto &arr_1 = arr_pair[0].to_array();
                auto &arr_2 = arr_pair[1].to_array();
                static_airports = std::move(std::vector<float>(arr_1.begin(), arr_1.end()));
                dynamic_airports = std::move(std::vector<object>(arr_2.begin(), arr_2.end()));
            }
        };

        struct rv_color_rgb {
            float red{};
            float green{};
            float blue{};
            explicit rv_color_rgb(const game_value &ret_game_value_) : red(ret_game_value_[0]),
                                                                   green(ret_game_value_[1]),
                                                                   blue(ret_game_value_[2]) {}
        };

        struct rv_world_lighting {
            rv_color_rgb light;
            vector3 direction;
            float brightness;
            float starts_visibility;
            explicit rv_world_lighting(const game_value &gv_)
                : light(gv_[0]),
                  brightness(gv_[1]),
                  direction(gv_[2]),
                  starts_visibility(gv_[3]) {}
        };

        struct rv_object_lighting {
            rv_color_rgb ambient_light;
            rv_color_rgb dynamic_light;
            float ambient_brightness;
            float dynamic_brightness;
            explicit rv_object_lighting(const game_value &gv_)
                : ambient_light(gv_[0]),
                  ambient_brightness(gv_[1]),
                  dynamic_light(gv_[2]),
                  dynamic_brightness(gv_[3]) {}
        };

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

        struct rv_rain_parameters {
            sqf_string rainDropTexture{"a3\\data_f\\rainnormal_ca.paa"};
            float texDropCount = 1.f;
            float minRainDensity = 0.01f;
            float effectRadius = 15.f;
            float windCoef = 0.1f;
            float dropSpeed = 2.f;
            float rndSpeed = 0.5f;
            float rndDir = 0.5f;
            float dropWidth = 0.02f;
            float dropHeight = 0.02f;
            rv_color dropColor{0.1f, 0.1f, 0.1f, 1.f};
            float lumSunFront = 0.1f;
            float lumSunBack = 0.1f;
            float refractCoef = 5.5f;
            float refractSaturation = 0.3f;
            bool snow = false;
            bool dropColorStrong = false;
            rv_rain_parameters() = default;
            explicit rv_rain_parameters(const game_value &gv_)
                : rainDropTexture(gv_[0]),
                  texDropCount(gv_[1]),
                  minRainDensity(gv_[2]),
                  effectRadius(gv_[3]),
                  windCoef(gv_[4]),
                  dropSpeed(gv_[5]),
                  rndSpeed(gv_[6]),
                  rndDir(gv_[7]),
                  dropWidth(gv_[8]),
                  dropHeight(gv_[9]),
                  dropColor(gv_[10]),
                  lumSunFront(gv_[11]),
                  lumSunBack(gv_[12]),
                  refractCoef(gv_[13]),
                  refractSaturation(gv_[14]),
                  snow(gv_[15]),
                  dropColorStrong(gv_[16])
            {
            }
            rv_rain_parameters(
                std::string_view rainDropTexture_,
                float texDropCount_,
                float minRainDensity_,
                float effectRadius_,
                float windCoef_,
                float dropSpeed_,
                float rndSpeed_,
                float rndDir_,
                float dropWidth_,
                float dropHeight_,
                const rv_color& dropColor_,
                float lumSunFront_,
                float lumSunBack_,
                float refractCoef_,
                float refractSaturation_,
                bool snow_,
                bool dropColorStrong_) : rainDropTexture(rainDropTexture_),
                                         texDropCount(texDropCount_),
                                         minRainDensity(minRainDensity_),
                                         effectRadius(effectRadius_),
                                         windCoef(windCoef_),
                                         dropSpeed(dropSpeed_),
                                         rndSpeed(rndSpeed_),
                                         rndDir(rndDir_),
                                         dropWidth(dropWidth_),
                                         dropHeight(dropHeight_),
                                         dropColor(dropColor_),
                                         lumSunFront(lumSunFront_),
                                         lumSunBack(lumSunBack_),
                                         refractCoef(refractCoef_),
                                         refractSaturation(refractSaturation_),
                                         snow(snow_),
                                         dropColorStrong(dropColorStrong_)
            {
            }

            explicit operator game_value() const {
                return {
                    rainDropTexture,
                    texDropCount,
                    minRainDensity,
                    effectRadius,
                    windCoef,
                    dropSpeed,
                    rndSpeed,
                    rndDir,
                    dropWidth,
                    dropHeight,
                    dropColor,
                    lumSunFront,
                    lumSunBack,
                    refractCoef,
                    refractSaturation,
                    snow,
                    dropColorStrong
                };
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
        void set_rain(const config &cfg_);
        void set_rain(const rv_rain_parameters &rain_params_);
        void set_humidity(float value_);
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
        void set_pip_view_distance(float value_);
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
        float get_pip_view_distance();
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
        sqf_return_string get_object_id(const object &obj_);
        std::vector<object> nearest_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool mode_2d_ = false);
        std::vector<object> nearest_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_, bool mode_2d_ = false);
        std::vector<object> nearest_terrain_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_ = true, bool mode_2d_ = false);
        std::vector<object> nearest_terrain_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_, bool sort_ = true, bool mode_2d_ = false);
        std::vector<object> units_below_height(const group &group_, float height_);
        std::vector<object> units_below_height(const std::vector<object> &units_, float height_);
        bool surface_is_water(const vector2 &pos_);
        bool surface_is_water(const vector3 &pos_);
        vector3 surface_normal(const vector2 &pos_);
        vector3 surface_normal(const vector3 &pos_);
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
        float get_object_scale(const object &obj_);
        void set_object_scale(const object &obj_, float scale_);
        float getelevationoffset();
        rv_world_airports all_airports();
        rv_world_lighting get_lighting();
        rv_object_lighting get_lighting_at(const object &obj_);
        rv_road_info get_road_info(const object &road_obj_);
        void set_wind_dir(const vector2 &dir_);
        sqf_return_string surface_texture(const vector2 &pos_, bool accurate_ = false);
        sqf_return_string surface_type(const vector2 &pos_, bool accurate_ = false);

        struct rv_ambient_temperature {
            float air_temp;
            float black_surf_temp;
            float white_surf_temp;
            explicit rv_ambient_temperature(const game_value &gv_)
                : air_temp(gv_[0]),
                  black_surf_temp(gv_[1]),
                  white_surf_temp(gv_[2]) {}
        };

        rv_rain_parameters rain_params();
        rv_ambient_temperature ambient_temperature();

        std::vector<object> all_objects(int obj_type_, object_simulation_kind simulation_kind_);
        std::vector<object> all_objects(sqf_string_const_ref obj_type_, object_simulation_kind simulation_kind_);
        std::vector<object> all_objects(int obj_type_, int simulation_kind_);
        std::vector<object> all_objects(sqf_string_const_ref obj_type_, int simulation_kind_);

        std::vector<object> nearest_mines(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_ = true, bool mode_2d_ = false);
        std::vector<object> nearest_mines(const vector2 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_ = true, bool mode_2d_ = false);

        struct rv_terrain_info {
            float land_grid_width;
            int land_grid_size;
            float terrain_grid_width;
            int terrain_grid_size;
            float sea_level;
            explicit rv_terrain_info(const game_value &gv_)
                : land_grid_width(gv_[0]),
                  land_grid_size(gv_[1]),
                  terrain_grid_width(gv_[2]),
                  terrain_grid_size(gv_[3]),
                  sea_level(gv_[4]) {}
        };

        rv_terrain_info get_terrain_info();
        float get_tide();
        float get_terrain_height(const vector2 &pos_);
        void set_terrain_height(const std::vector<vector3> &positions_, bool adjust_objs_);

        rv_hashmap get_mission_options();
        void set_mission_options(const rv_hashmap &options_);

        struct rv_camera_info {
            struct r2t {
                sqf_string r2t_name;         // the camera's RTT name (see cameraEffect);
                sqf_string r2t_effect_name;  // see cameraEffect for possible values;
                sqf_string pp_effect_type;   // one of Normal, NightVision, Thermal, Colors, Mirror, ChromAber or FilmGrain;
                float ti_index;               // see setCamUseTI for possible values;
                explicit r2t(const game_value &gv_) : r2t_name{gv_[0]},
                                                      r2t_effect_name{gv_[1]},
                                                      pp_effect_type{gv_[2]},
                    ti_index{gv_[3]} {}
            };
            object camera;              // the camera itself (see camCreate);
            std::vector<r2t> r2t_infos;  // [r2tName, r2tEffectName, ppEffectType, TIindex]
            sqf_string effect_name;     // (Optional, only available if isPrimary is true) see cameraEffect for possible values;
            float view_mode;            // (Optional, only available if isPrimary is true) 0 = normal, 1 = NVG, 2 = TI, 3 = NVG + TI;
            float ti_index;              // (Optional, only available if isPrimary is true) see setCamUseTI for possible values;
            bool is_primary;            // whether or not this camera is the current main one
            explicit rv_camera_info(const game_value &gv_);
        };

        std::vector<rv_camera_info> all_cameras();
    }  // namespace sqf
}  // namespace intercept
