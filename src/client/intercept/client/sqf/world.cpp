#include "world.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* World */

        float world_size() {
            return sqf::__helpers::__retrieve_nular_number(__sqf::nular__worldsize__ret__scalar);
        }

        sqf_return_string world_name() {
            return host::functions.invoke_raw_nular(__sqf::nular__worldname__ret__string);
        }

        float wind_str() {
            return __helpers::__retrieve_nular_number(__sqf::nular__windstr__ret__scalar);
        }

        float wind_dir() {
            return __helpers::__retrieve_nular_number(__sqf::nular__winddir__ret__scalar);
        }
        void set_wind(float x_, float y_) {
            game_value params({x_, y_});

            host::functions.invoke_raw_unary(__sqf::unary__setwind__array__ret__nothing, params);
        }

        void set_wind(float x_, float y_, bool force_) {
            game_value params({x_, y_, force_});

            host::functions.invoke_raw_unary(__sqf::unary__setwind__array__ret__nothing, params);
        }
        vector3 wind() {
            return __helpers::__retrieve_nular_vector3(__sqf::nular__wind__ret__array);
        }

        float gusts() {
            return __helpers::__retrieve_nular_number(__sqf::nular__gusts__ret__scalar);
        }

        float humidity() {
            return __helpers::__retrieve_nular_number(__sqf::nular__humidity__ret__scalar);
        }

        float waves() {
            return __helpers::__retrieve_nular_number(__sqf::nular__waves__ret__scalar);
        }

        float lightnings() {
            return __helpers::__retrieve_nular_number(__sqf::nular__lightnings__ret__scalar);
        }

        float moon_intensity() {
            return __helpers::__retrieve_nular_number(__sqf::nular__moonintensity__ret__scalar);
        }

        float next_weather_change() {
            return __helpers::__retrieve_nular_number(__sqf::nular__nextweatherchange__ret__scalar);
        }

        float overcast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__overcast__ret__scalar);
        }

        float overcast_forecast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__overcastforecast__ret__scalar);
        }

        float rain() {
            return __helpers::__retrieve_nular_number(__sqf::nular__rain__ret__scalar);
        }

        float rainbow() {
            return __helpers::__retrieve_nular_number(__sqf::nular__rainbow__ret__scalar);
        }

        float sun_or_moon() {
            return __helpers::__retrieve_nular_number(__sqf::nular__sunormoon__ret__scalar);
        }

        bool fog() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__fog__ret__scalar);
        }

        float fog_forecast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__fogforecast__ret__scalar);
        }

        float time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__time__ret__scalar);
        }

        float time_multiplier() {
            return __helpers::__retrieve_nular_number(__sqf::nular__timemultiplier__ret__scalar);
        }

        float date_to_number(int year_, int month_, int day_, int hour_, float minute_) {
            game_value date({static_cast<float>(year_),
                             static_cast<float>(month_),
                             static_cast<float>(day_),
                             static_cast<float>(hour_),
                             minute_});

            return host::functions.invoke_raw_unary(__sqf::unary__datetonumber__array__ret__scalar, date);
        }

        rv_date number_to_date(int year_, float time_) {
            game_value params({static_cast<float>(year_),
                               time_});

            return rv_date::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__numbertodate__array__ret__array, params)));
        }
        rv_date date() {
            return rv_date::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__date__ret__array)));
        }
        rv_date mission_start() {
            return rv_date::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__missionstart__ret__array)));
        }

        rv_fog_parameters fog_params() {
            return rv_fog_parameters::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__fogparams__ret__array)));
        }

        rv_rendering_distances get_object_view_distance() {
            return rv_rendering_distances::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__getobjectviewdistance__ret__array)));
        }
        void set_date(int year_, int month_, int day_, int hour_, float minute_) {
            game_value date({static_cast<float>(year_),
                             static_cast<float>(month_),
                             static_cast<float>(day_),
                             static_cast<float>(hour_),
                             minute_});

            host::functions.invoke_raw_unary(__sqf::unary__setdate__array__ret__nothing, date);
        }

        std::vector<object> entities(sqf_string_list_const_ref typesinclude_, sqf_string_list_const_ref typesexclude_, bool includeCrews_, bool excludeDead_) {
            auto_array<game_value> typesinclude(typesinclude_.begin(), typesinclude_.end());
            auto_array<game_value> typesexclude(typesexclude_.begin(), typesexclude_.end());

            game_value params({std::move(typesinclude),
                               std::move(typesexclude),
                               includeCrews_,
                               excludeDead_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__entities__array__ret__array, params));
        }

        void set_horizon_parallax_coef(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__sethorizonparallaxcoef__scalar__ret__nothing, value_);
        }

        void set_detail_map_blend_pars(float full_detail_, float no_detail_) {
            game_value params({full_detail_,
                               no_detail_});

            host::functions.invoke_raw_unary(__sqf::unary__setdetailmapblendpars__array__ret__nothing, params);
        }

        void simul_cloud_density(const vector3 &pos_) {
            host::functions.invoke_raw_unary(__sqf::unary__simulclouddensity__array__ret__scalar, pos_);
        }

        void simul_cloud_occlusion(const vector3 &pos1_, const vector3 &pos2_) {
            game_value params({pos1_,
                               pos2_});

            host::functions.invoke_raw_unary(__sqf::unary__simulcloudocclusion__array__ret__scalar, params);
        }

        bool simul_in_clouds(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__simulinclouds__array__ret__bool, pos_);
        }

        void set_fog(float time_, float fog_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, fog_);
        }

        void set_fog(float time_, float fog_value_, float fog_decay_, float fog_base_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, {fog_value_, fog_decay_, fog_base_});
        }

        void set_gusts(float time_, float gusts_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setgusts__scalar__scalar__ret__nothing, time_, gusts_value_);
        }

        void set_rain(float time_, float rain_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrain__scalar__scalar__ret__nothing, time_, rain_value_);
        }

        void set_rain(const config &cfg_) {
            host::functions.invoke_raw_unary(__sqf::unary__setrain__config__ret__nothing, cfg_);
        }

        void set_rain(const rv_rain_parameters &rain_params_) {
            host::functions.invoke_raw_unary(__sqf::unary__setrain__array__ret__nothing, (game_value)rain_params_);
        }

        void set_rainbow(float time_, float rainbow_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrainbow__scalar__scalar__ret__nothing, time_, rainbow_value_);
        }

        void set_overcast(float time_, float overcast_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setovercast__scalar__scalar__ret__nothing, time_, overcast_value_);
        }

        void set_wind_dir(float time_, float wind_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwinddir__scalar__scalar__ret__nothing, time_, wind_value_);
        }

        void set_wind_force(float time_, float force_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwindforce__scalar__scalar__ret__nothing, time_, force_value_);
        }

        void set_wind_str(float time_, float strength_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwindstr__scalar__scalar__ret__nothing, time_, strength_value_);
        }

        void set_acc_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setacctime__scalar__ret__nothing, value_);
        }

        void set_object_view_distance(float distance_) {
            __helpers::__empty_unary_number(__sqf::unary__setobjectviewdistance__scalar__ret__nothing, distance_);
        }

        void set_object_view_distance(float object_distance_, float shadow_distance_) {
            game_value params({object_distance_,
                               shadow_distance_});

            host::functions.invoke_raw_unary(__sqf::unary__setobjectviewdistance__array__ret__nothing, params);
        }

        void set_shadow_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setshadowdistance__scalar__ret__nothing, value_);
        }

        void set_simul_weather_layers(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setsimulweatherlayers__scalar__ret__nothing, value_);
        }

        void set_terrain_grid(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setterraingrid__scalar__ret__nothing, value_);
        }

        void set_time_multiplier(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__settimemultiplier__scalar__ret__nothing, value_);
        }

        void set_view_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setviewdistance__scalar__ret__nothing, value_);
        }

        void set_pip_view_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setpipviewdistance__scalar__ret__nothing, value_);
        }

        void skip_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__skiptime__scalar__ret__nothing, value_);
        }

        void enable_environment(bool ambient_life_, bool ambient_sound_) {
            host::functions.invoke_raw_unary(__sqf::unary__enableenvironment__bool_array__ret__nothing, {ambient_life_, ambient_sound_});
        }

        void enable_sat_normal_on_detail(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enablesatnormalondetail__bool__ret__nothing, value_);
        }

        float acc_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__acctime__ret__scalar);
        }

        float daytime() {
            return __helpers::__retrieve_nular_number(__sqf::nular__daytime__ret__scalar);
        }

        void force_weather_change() {
            __helpers::__empty_nular(__sqf::nular__forceweatherchange__ret__nothing);
        }

        float get_shadow_distance() {
            return __helpers::__retrieve_nular_number(__sqf::nular__getshadowdistance__ret__scalar);
        }

        void init_ambient_life() {
            __helpers::__empty_nular(__sqf::nular__initambientlife__ret__nothing);
        }

        void simul_weather_sync() {
            __helpers::__empty_nular(__sqf::nular__simulweathersync__ret__nothing);
        }

        std::pair<bool, bool> environment_enabled() {
            game_value res = host::functions.invoke_raw_nular(__sqf::nular__environmentenabled__ret__array);

            return std::pair<bool, bool>({res[0], res[1]});
        }

        float moon_phase(int year_, int month_, int day_, int hour_, float minute_) {
            game_value date({static_cast<float>(year_),
                             static_cast<float>(month_),
                             static_cast<float>(day_),
                             static_cast<float>(hour_),
                             minute_});

            return host::functions.invoke_raw_unary(__sqf::unary__moonphase__array__ret__scalar, date);
        }

        void set_waves(float time_, float waves_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaves__scalar__scalar__ret__nothing, time_, waves_value_);
        }

        void set_fog(float &time_, float &fog_value_, std::optional<float> fog_decay_, std::optional<float> fog_base_) {
            if (fog_decay_.has_value() && fog_base_.has_value())
                host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, {fog_value_, *fog_decay_, *fog_base_});
            host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, fog_value_);
        }

        int get_terrain_grid() {
            return static_cast<int>(host::functions.invoke_raw_nular(__sqf::nular__getterraingrid__ret__scalar));
        }

        float view_distance() {
            return __helpers::__retrieve_nular_number(__sqf::nular__viewdistance__ret__scalar);
        }

        float get_pip_view_distance() {
            return __helpers::__retrieve_nular_number(__sqf::nular__getpipviewdistance__ret__scalar);
        }

        void enable_caustics(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enablecaustics__bool__ret__nothing, value_);
        }

        void set_lightnings(float time_, float lightnings_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightnings__scalar__scalar__ret__nothing, time_, lightnings_value_);
        }

        std::vector<object> near_objects(const vector3 &pos_, float radius_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, pos_, radius_));
        }

        std::vector<object> near_objects(const object &object_, float radius_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, object_, radius_));
        }

        std::vector<object> near_objects(const vector3 &pos_, sqf_string_const_ref type_, float radius_) {
            game_value args({type_,
                             radius_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, pos_, args));
        }

        std::vector<object> near_objects(const object &object_, sqf_string_const_ref type_, float radius_) {
            game_value args({type_,
                             radius_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearobjects__object_array__scalar_array__ret__array, object_, args));
        }

        bool near_objects_ready(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_) {
            game_value param_left;
            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__nearobjectsready__object_array__scalar__ret__bool, param_left, radius_);
        }

        std::vector<object> near_roads(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_) {
            game_value param_left;
            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearroads__object_array__scalar__ret__array, param_left, radius_));
        }

        std::vector<object> near_supplies(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_) {
            game_value param_left;
            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearsupplies__object_array__scalar_array__ret__array, param_left, radius_));
        }

        std::vector<rv_target> near_targets(const object &unit_, float radius_) {
            game_value ret = host::functions.invoke_raw_binary(__sqf::binary__neartargets__object__scalar__ret__array, unit_, radius_);
            return __helpers::__convert_to_vector<rv_target>(ret);
        }

        object nearest_object(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__nearestobject__array__ret__object, pos_);
        }

        object nearest_object(const vector3 &pos_, sqf_string_const_ref type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nearestobject__array__string__ret__object, pos_, type_);
        }

        object nearest_object(const object &obj_, sqf_string_const_ref type_) {
            game_value params({obj_,
                               type_});

            return host::functions.invoke_raw_unary(__sqf::unary__nearestobject__array__ret__object, params);
            // Same as: position nearObjects filter (where position is vector3 and filter is string) - binary__nearestobject__array__string__ret__object
        }

        object nearest_object(const vector3 &pos_, float id_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nearestobject__array__scalar__ret__object, pos_, id_);
        }

        sqf_return_string get_object_id(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getobjectid__object__ret__string, obj_);
        }

        std::vector<object> nearest_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value params({pos_,
                               std::move(types),
                               radius_,
                               mode_2d_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestobjects__array__ret__array, std::move(params)));
        }

        std::vector<object> nearest_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value params({obj_,
                               std::move(types),
                               radius_,
                               mode_2d_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestobjects__array__ret__array, std::move(params)));
        }

        std::vector<object> nearest_terrain_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value params({pos_,
                               std::move(types),
                               radius_,
                               sort_,
                               mode_2d_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestterrainobjects__array__ret__array, std::move(params)));
        }

        std::vector<object> nearest_terrain_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_, bool sort_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value params({obj_,
                               std::move(types),
                               radius_,
                               sort_,
                               mode_2d_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestterrainobjects__array__ret__array, std::move(params)));
        }

        std::vector<object> units_below_height(const group &group_, float height_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__unitsbelowheight__group__scalar__ret__array, group_, height_));
        }

        std::vector<object> units_below_height(const std::vector<object> &units_, float height_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__unitsbelowheight__array__scalar__ret__array, std::move(auto_array<game_value>(units_.begin(), units_.end())), height_));
        }

        bool surface_is_water(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfaceiswater__array__ret__bool, pos_);
        }

        bool surface_is_water(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfaceiswater__array__ret__bool, pos_);
        }

        vector3 surface_normal(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfacenormal__array__ret__array, pos_);
        }

        vector3 surface_normal(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfacenormal__array__ret__array, pos_);
        }

        sqf_return_string surface_type(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfacetype__array__ret__string, pos_);
        }

        std::vector<rv_best_place> select_best_places(const object &obj_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_) {
            game_value params({obj_,
                               radius_,
                               expression_,
                               precision_,
                               max_results_});

            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__selectbestplaces__array__ret__array, std::move(params));

            return __helpers::__convert_to_vector<rv_best_place>(ret);
        }

        std::vector<rv_best_place> select_best_places(const vector3 &pos_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_) {
            game_value params({pos_,
                               radius_,
                               expression_,
                               precision_,
                               max_results_});

            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__selectbestplaces__array__ret__array, std::move(params));

            return __helpers::__convert_to_vector<rv_best_place>(ret);
        }

        bool is_on_road(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isonroad__object_array__ret__bool, object_);
        }

        bool is_on_road(const vector3 &position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isonroad__object_array__ret__bool, position_);
        }

        float get_friend(const side &side1_, const side &side2_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getfriend__side__side__ret__scalar, side1_, side2_);
        }

        void set_friend(const side &side1_, const side &side2_, float value_) {
            game_value args({side2_,
                             value_});

            host::functions.invoke_raw_binary(__sqf::binary__setfriend__side__array__ret__nothing, side1_, args);
        }

        std::vector<object> entities(sqf_string_const_ref type_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__entities__string__ret__array, type_));
        }

        std::vector<object> units(const object &unit_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__units__object__ret__array, unit_));
        }

        object nearest_building(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__nearestbuilding__object__ret__object, value_);
        }

        object nearest_building(const vector3 &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__nearestbuilding__array__ret__object, value_));
        }

        bool preload_object(float distance_, const object &object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__preloadobject__scalar__object_string__ret__bool, distance_, object_);
        }

        bool preload_object(float distance_, sqf_string_const_ref class_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__preloadobject__scalar__object_string__ret__bool, distance_, class_name_);
        }

        object road_at(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__roadat__object_array__ret__object, object_);
        }

        object road_at(const vector3 &position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__roadat__object_array__ret__object, position_);
        }

        bool get_remote_sensors_disabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__getremotesensorsdisabled__ret__bool);
        }

        void disable_remote_sensors(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__disableremotesensors__bool__ret__nothing, value_);
        }

        bool underwater(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__underwater__object__ret__bool, value_);
        }

        std::vector<object> vehicles() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__vehicles__ret__array));
        }

        void set_local_wind_params(float strength_, float diameter_) {
            game_value params({strength_,
                               diameter_});

            host::functions.invoke_raw_unary(__sqf::unary__setlocalwindparams__array__ret__nothing, params);
        }

        float getelevationoffset() {
            return __helpers::__retrieve_nular_number(__sqf::nular__getelevationoffset__ret__scalar);
        }

        float get_object_scale(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getobjectscale__object__ret__scalar, obj_);
        }

        void set_object_scale(const object &obj_, float scale_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectscale__object__scalar__ret__nothing, obj_, scale_);
        }

        rv_world_airports all_airports() {
            return rv_world_airports(host::functions.invoke_raw_nular(__sqf::nular__allairports__ret__array));
        }

        rv_world_lighting get_lighting() {
            return rv_world_lighting(host::functions.invoke_raw_nular(__sqf::nular__getlighting__ret__array));
        }

        rv_object_lighting get_lighting_at(const object &obj_) {
            return rv_object_lighting(host::functions.invoke_raw_unary(__sqf::unary__getlightingat__object__ret__array, obj_));
        }

        rv_road_info get_road_info(const object &road_obj_) {
            return rv_road_info(host::functions.invoke_raw_unary(__sqf::unary__getroadinfo__object__ret__array, road_obj_));
        }

        void set_wind_dir(const vector2 &dir_) {
            host::functions.invoke_raw_unary(__sqf::unary__setwinddir__array__ret__nothing, dir_);
        }

        sqf_return_string surface_texture(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__surfacetexture__array__ret__string, pos_);
        }

        rv_ambient_temperature ambient_temperature() {
            return rv_ambient_temperature(host::functions.invoke_raw_nular(__sqf::nular__ambienttemperature__ret__array));
        }

        void set_humidity(float value_) {
            host::functions.invoke_raw_unary(__sqf::unary__sethumidity__scalar__ret__nothing, value_);
        }

        rv_rain_parameters rain_params() {
            return rv_rain_parameters(host::functions.invoke_raw_nular(__sqf::nular__rainparams__ret__array));
        }

        std::vector<object> all_objects(int obj_type_, object_simulation_kind simulation_kind_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__allobjects__scalar__scalar__ret__array, obj_type_, (int)simulation_kind_));
        }

        std::vector<object> all_objects(int obj_type_, int simulation_kind_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__allobjects__scalar__scalar__ret__array, obj_type_, simulation_kind_));
        }

        std::vector<object> nearest_mines(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestmines__array__ret__array, {pos_, std::move(types), radius_, sort_, mode_2d_}));
        }

        std::vector<object> nearest_mines(const vector2 &pos_, sqf_string_list_const_ref types_, float radius_, bool sort_, bool mode_2d_) {
            auto_array<game_value> types(types_.begin(), types_.end());
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__nearestmines__array__ret__array, {pos_, std::move(types), radius_, sort_, mode_2d_}));
        }

        rv_terrain_info get_terrain_info() {
            return rv_terrain_info(host::functions.invoke_raw_nular(__sqf::nular__getterraininfo__ret__array));
        }

        float get_tide() {
            auto ret = host::functions.invoke_raw_nular(__sqf::nular__getterraininfo__ret__array);
            return ret[4];
        }

        float get_terrain_height(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getterrainheight__array__ret__scalar, pos_);
        }

        void set_terrain_height(const std::vector<vector3> &positions_, bool adjust_objs_) {
            host::functions.invoke_raw_unary(__sqf::unary__setterrainheight__array__ret__nothing, {positions_, adjust_objs_});
        }
    }  // namespace sqf
}  // namespace intercept
