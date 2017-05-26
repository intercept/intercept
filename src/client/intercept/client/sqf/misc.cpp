#include "chat.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include <memory>

namespace intercept {
    namespace sqf {
        float diag_fps() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_fps__ret__scalar);
        }
        float diag_fpsmin() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_fpsmin__ret__scalar);
        }
        float diag_frameno() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_frameno__ret__scalar);
        }
        float diag_ticktime() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_ticktime__ret__scalar);
        }
        std::vector<script> diag_active_mission_fsms() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activemissionfsms__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }

        std::vector<script> diag_active_sqf_scripts() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqfscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }

        std::vector<script> diag_active_sqs_scripts() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqsscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }




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


    }
}
