#include "rotorlib.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        float get_rotor_brake_rtd(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getrotorbrakertd__object__ret__scalar, value_);
        }
        float get_wings_orientation_rtd(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getwingsorientationrtd__object__ret__scalar, value_);
        }

        float get_wings_position_rtd(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getwingspositionrtd__object__ret__scalar, value_);
        }
        bool is_auto_trim_on_rtd(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isautotrimonrtd__object__ret__bool, value_);
        }
        bool is_object_rtd(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isobjectrtd__object__ret__bool, value_);
        }
        float number_of_engines_rtd(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__numberofenginesrtd__object__ret__scalar, value_);
        }
        void stop_engine_rtd(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__stopenginertd__object__ret__nothing, value_);
        }
        void enable_auto_start_up_rtd(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableautostartuprtd__object__bool__ret__nothing, value0_, value1_);
        }

        bool enable_auto_trim_rtd(const object &value0_, bool value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__enableautotrimrtd__object__bool__ret__bool, value0_, value1_);
        }
        std::vector<bool> engines_is_on_rtd(const object &heli_) {
            return __helpers::__convert_to_vector<bool>(host::functions.invoke_raw_unary(__sqf::unary__enginesisonrtd__object__ret__array, heli_));
        }

        std::vector<float> engines_rpm_rtd(const object &heli_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__enginesrpmrtd__object__ret__array, heli_));
        }

        std::vector<float> engines_torque_rtd(const object &heli_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__enginestorquertd__object__ret__array, heli_));
        }
        void set_rotor_brake_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrotorbrakertd__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_actual_collective_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setactualcollectivertd__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_custom_weight_rtd(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcustomweightrtd__object__scalar__ret__nothing, value0_, value1_);
        }
        std::vector<rv_forces_rtd> rotors_forces_rtd(const object &heli_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__rotorsforcesrtd__object__ret__array, heli_);
            return __helpers::__convert_to_vector<rv_forces_rtd>(ret);
        }

        std::vector<rv_forces_rtd> wings_forces_rtd(const object &heli_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__wingsforcesrtd__object__ret__array, heli_);
            return __helpers::__convert_to_vector<rv_forces_rtd>(ret);
        }
        std::vector<float> rotors_rpm_rtd(const object &heli_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__rotorsrpmrtd__object__ret__array, heli_));
        }

        rv_weight_rtd weight_rtd(const object &heli_) {
            return rv_weight_rtd::from_vector(__helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__weightrtd__object__ret__array, heli_)));
        }
        void set_brakes_rtd(const object &heli_, float amount_, int wheel_index_) {
            game_value params({amount_,
                               static_cast<float>(wheel_index_)});

            host::functions.invoke_raw_binary(__sqf::binary__setbrakesrtd__object__array__ret__nothing, heli_, params);
        }

        void set_engine_rpm_rtd(const object &heli_, float rpms_, int engine_index_) {
            game_value params({rpms_,
                               static_cast<float>(engine_index_)});

            host::functions.invoke_raw_binary(__sqf::binary__setenginerpmrtd__object__array__ret__nothing, heli_, params);
        }

        void set_wanted_rpm_rtd(const object &heli_, float rpms_, float time_, int engine_index_) {
            game_value params({rpms_,
                               time_,
                               static_cast<float>(engine_index_)});

            host::functions.invoke_raw_binary(__sqf::binary__setwantedrpmrtd__object__array__ret__nothing, heli_, params);
        }
        bool difficulty_enabled_rtd() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__difficultyenabledrtd__ret__bool);
        }
        void clear_forces_rtd() {
            __helpers::__empty_nular(__sqf::nular__clearforcesrtd__ret__nothing);
        }
        float air_density_rtd(float altitude_) {
            return __helpers::__number_unary_number(__sqf::unary__airdensityrtd__scalar__ret__scalar, altitude_);
        }
        float collective_rtd(const object &helicopter_) {
            return __helpers::__number_unary_object(__sqf::unary__collectivertd__object__ret__scalar, helicopter_);
        }
        bool is_stress_damage_enabled() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isstressdamageenabled__ret__bool);
        }
    }  // namespace sqf
}  // namespace intercept
