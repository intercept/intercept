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




    }
}
