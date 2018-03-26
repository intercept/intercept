/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Rotorlib Advanced flightmodel commands

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct rv_forces_rtd {
            explicit rv_forces_rtd(game_value gv_) : roll(gv_[0]), pitch(gv_[1]), collective(gv_[2]) {}
            float roll;
            float pitch;
            float collective;
        };
        struct rv_weight_rtd {
            float fuselage;
            float crew;
            float fuel;
            float custom;
            float weapons;

            rv_weight_rtd(float fuselage_, float crew_, float fuel_, float custom_, float weapons_) {
                fuselage = fuselage_;
                crew = crew_;
                fuel = fuel_;
                custom = custom_;
                weapons = weapons_;
            }

            static rv_weight_rtd from_vector(const std::vector<float> &weight_vector_) {
                return rv_weight_rtd(weight_vector_[0], weight_vector_[1], weight_vector_[2], weight_vector_[3], weight_vector_[4]);
            }
        };

        //rtd simulation from take on helicopters
        float get_rotor_brake_rtd(const object &value_);
        float get_wings_orientation_rtd(const object &value_);
        float get_wings_position_rtd(const object &value_);
        bool is_auto_trim_on_rtd(const object &value_);
        bool is_object_rtd(const object &value_);
        float number_of_engines_rtd(const object &value_);
        void stop_engine_rtd(const object &value_);
        void enable_auto_start_up_rtd(const object &value0_, bool value1_);
        bool enable_auto_trim_rtd(const object &value0_, bool value1_);
        std::vector<bool> engines_is_on_rtd(const object &heli_);
        std::vector<float> engines_rpm_rtd(const object &heli_);
        std::vector<float> engines_torque_rtd(const object &heli_);
        void set_rotor_brake_rtd(const object &value0_, float value1_);
        void set_actual_collective_rtd(const object &value0_, float value1_);
        void set_custom_weight_rtd(const object &value0_, float value1_);
        std::vector<rv_forces_rtd> rotors_forces_rtd(const object &heli_);
        std::vector<rv_forces_rtd> wings_forces_rtd(const object &heli_);
        std::vector<float> rotors_rpm_rtd(const object &heli_);
        rv_weight_rtd weight_rtd(const object &heli_);
        void set_brakes_rtd(const object &heli_, float amount_, int wheel_index_);
        void set_engine_rpm_rtd(const object &heli_, float rpms_, int engine_index_);
        void set_wanted_rpm_rtd(const object &heli_, float rpms_, float time_, int engine_index_);
        bool difficulty_enabled_rtd();
        void clear_forces_rtd();
        float air_density_rtd(float altitude_);
        float collective_rtd(const object &helicopter_);
        bool is_stress_damage_enabled();

    }  // namespace sqf
}  // namespace intercept
