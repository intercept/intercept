/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Debug/Diagnose commands

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        enum class debug_toggles {
            AIAiming,            //shows vectors (lines) of AI aiming at known target
            AIBrain,             //general informations about AI brain, combat mode and fsm state
            AIDynamicError,      //shows value of dynamically calculated AI aiming error
            AISkill,             //shows value of skill, plus global coefficients, as set by difficulty mode
            AISuppression,       //shows value of suppression
            AIDriving,           //Shows various information about AI driving and path in real time.
            DynSimEntities,      //Displays the map overlay with yellow coloured activation boxes around each dynamically simulated (empty) object.
            DynSimGrid,          //Displays the map overlay with the most detailed Dynamic Simulation grid.
            DynSimGroups,        //Displays the map overlay with side coloured activation boxes around each dynamically simulated group.
            Animation,           //displays current animation state, actions being used and target animation states depending on the actions
            AnimSrcTarget,       //displays all animation sources and their values for the model under the cursor
            AnimSrcUnit,         //displays all animation sources and their values for the player's vehicle (or his gun in case of a soldier)
            EPEVehicle,          //displays gearbox, friction, thrust, brake and various parameters of a PhysX vehicle
            EPEForce,            //displays PhysX forces applied on the vehicle
            Force,               //displays some other forces with their names
            Suspension,          //displays status of suspension for each wheel of a PhysX vehicle
            HitPoints,           //displays status of hit points of the player's vehicle and vehicle under the cursor
            Mines,               //displays nearby mines, their properties and radius
            Particles,           //displays what particles are used in scene and their count
            ParticleNames,       //attaches a name to each particle effect used so that it may be identified
            Shots,               //visualizes projectiles and their paths, hits and ricochets, guidance, seek radius and laser and artillery targets; shows details about hit contacts, penetration, projectile speed, guidance and missile phases
            SurfaceUnder,        //displays the per-foot surface information on which a unit is standing
            CursorTargetObject,  //Shows name of cursor object and it is distance to the player. Max distance in 50 meters
        };
        enum class debug_draw_modes {
            Normal,
            Roadway,
            Geometry,
            ViewGeometry,
            FireGeometry,
            Paths,
            ShadowVolume,
            ShadowBuffer,
            Buoyancy
        };
        float diag_fps();
        float diag_fpsmin();
        float diag_frameno();
        float diag_ticktime();

        std::vector<script> diag_active_mission_fsms();
        std::vector<script> diag_active_sqf_scripts();
        std::vector<script> diag_active_sqs_scripts();
        std::vector<float> diag_active_scripts();
        auto_array<game_value> diag_all_mission_eventhandlers();
        float diag_delta_time();

        //diag
        void diag_capture_frame(float frame_);
        void diag_capture_frame_to_file(float frame_);
        void diag_capture_slow_frame(sqf_string_const_ref section_, float threshold_);
        void diag_code_performance(const code &code_, const game_value &arguments_, float cycles_);
        void diag_log(game_value text_);
        void diag_log_slow_frame(sqf_string_const_ref section_, float threshold_);

        void enable_diag_legend(bool value_);
        void halt();  //only in dev version - at least wiki says so
        void throw_exception(game_value exception_);
        void diag_enable(debug_toggles mode_, bool enable_);
        bool diag_enabled(sqf_string_const_ref mode_);
        auto_array<game_value> diag_dump_terrain_synth();
        void diag_reset_fsm();
        void diag_reset_shapes();
        void diag_reset_anims();
        void diag_draw_mode(debug_draw_modes mode_); //diag-exe only
        vector2 diag_get_terrain_segment_offset(const vector2 &pos_);
        void diag_light_new_load(sqf_string_const_ref path_);
        sqf_return_string_list diag_list(sqf_string_const_ref name_);
        sqf_return_string_list diag_localized(sqf_string_const_ref stringtable_);
        void diag_merge_config_file(sqf_string_const_ref path_, bool is_user_path_ = false);
        void diag_set_light_new(sqf_string_const_ref str_config_);
        void diag_toggle(debug_toggles mode_);
        auto_array<game_value> diag_remains_collector(float value_);
        void diag_sqfc_debug_dump(sqf_string_const_ref source_, sqf_string_const_ref target_);
    }  // namespace sqf
}  // namespace intercept
