#include "units.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        void set_user_mfd_value(const object &object_, int index_, float value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setusermfdvalue__object__array__ret__nothing, object_, {index_, value_});
        }

        void forget_target(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__forgettarget__object_group__object__ret__nothing, unit_, target_);
        }

        void forget_target(const group &group_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__forgettarget__object_group__object__ret__nothing, group_, target_);
        }

        void targets(const object &unit_, std::optional<bool> enemy_only_, std::optional<float> max_distance_, std::optional<std::vector<side>> sides_, std::optional<float> max_age_, std::optional<std::variant<std::reference_wrapper<vector2>, std::reference_wrapper<vector3>>> alternate_center_) {
            auto_array<game_value> params_right;

            if (enemy_only_.has_value())
                params_right.push_back(*enemy_only_);
            else
                params_right.push_back(game_value());
            if (max_distance_.has_value())
                params_right.push_back(*max_distance_);
            else
                params_right.push_back(game_value());
            if (sides_.has_value())
                params_right.push_back(auto_array<game_value>((*sides_).begin(), (*sides_).end()));
            else
                params_right.push_back(game_value());
            if (max_age_.has_value())
                params_right.push_back(*max_age_);
            else
                params_right.push_back(game_value());
            if (alternate_center_.has_value()) {
                if ((*alternate_center_).index() == 0)
                    params_right.push_back(std::get<0>(*alternate_center_).get());
                else
                    params_right.push_back(std::get<1>(*alternate_center_).get());
            } else
                params_right.push_back(game_value());

            host::functions.invoke_raw_binary(__sqf::binary__targets__object__array__ret__array, unit_, std::move(params_right));
        }

        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_) {
            game_value params_right({uav_,
                                     check_all_items_});

            return host::functions.invoke_raw_binary(__sqf::binary__isuavconnectable__object__array__ret__bool, unit_, params_right);
        }

        object camera_on() {
            return __helpers::__retrieve_nular_object(__sqf::nular__cameraon__ret__object);
        }

        bool can_unload_in_combat(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canunloadincombat__object__ret__bool, unit_);
        }

        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_) {
            game_value params({wounded_,
                               medic_,
                               medic_can_heal_});

            host::functions.invoke_raw_unary(__sqf::unary__aisfinishheal__array__ret__nothing, params);
        }

        void action(const object &unit_, const std::vector<game_value> &action_array_) {
            host::functions.invoke_raw_binary(__sqf::binary__action__object__array__ret__nothing, unit_, action_array_);
        }

        void action(const std::vector<game_value> &action_array_) {
            host::functions.invoke_raw_unary(__sqf::unary__action__array__ret__nothing, action_array_);
        }

        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_) {
            host::functions.invoke_raw_binary(__sqf::binary__sethidebehind__object__array__ret__nothing, unit_, {object_where_hide_, hide_position_});
        }

        bool in(const object &unit_, const object &vehicle_) {
            return host::functions.invoke_raw_binary(__sqf::binary__in__object__object__ret__bool, unit_, vehicle_);
        }

        rv_target_knowledge target_knowledge(const object &unit_, const object &target_) {
            return rv_target_knowledge(host::functions.invoke_raw_binary(__sqf::binary__targetknowledge__object__object__ret__array, unit_, target_));
        }

        //#TODO: Find out how this function works
        game_value targets_aggregate(const object &speaker_, const side &side_, const object &unit_, const vector3 &place_, float time_, game_value &candidates_) {
            return host::functions.invoke_raw_binary(__sqf::binary__targetsaggregate__array__array__ret__array, {speaker_, side_, unit_, place_, time_}, candidates_);
        }

        rv_query_target targets_query(const object &unit_, const object &target_ignore_, const side &target_side, sqf_string_const_ref target_type_, const vector3 &target_position_, float target_max_age_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__targetsquery__object__array__ret__array, unit_, {target_ignore_, target_side, target_type_, target_position_, target_max_age_});

            return rv_query_target({res[0], res[1], res[2], res[3], res[4], res[5]});
        }

        void create_unit(sqf_string_const_ref type_, const vector3 &pos_, const group &group_, sqf_string_const_ref init_, float skill_, sqf_string_const_ref rank_) {
            game_value args({pos_,
                             group_,
                             init_,
                             skill_,
                             rank_});

            host::functions.invoke_raw_binary(__sqf::binary__createunit__string__array__ret__nothing, type_, args);
        }

        object create_unit(const group &group_, sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, sqf_string_const_ref special_) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({type_,
                             pos_,
                             std::move(markers),
                             placement_,
                             special_});

            return object(host::functions.invoke_raw_binary(__sqf::binary__createunit__group__array__ret__object, group_, args));
        }

        sqf_return_string animation_state(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__animationstate__object__ret__string, unit_);
        }

        sqf_return_string gesture_state(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__gesturestate__object__ret__string, unit_);
        }

        sqf_return_string assigned_team(const object &unit_) {
            return __helpers::__string_unary_object(__sqf::unary__assignedteam__object__ret__string, unit_);
        }

        object assigned_vehicle(const object &unit_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedvehicle__object__ret__object, unit_);
        }

        bool can_fire(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canfire__object__ret__bool, unit_);
        }

        bool can_move(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canmove__object__ret__bool, unit_);
        }

        bool can_stand(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__canstand__object__ret__bool, unit_);
        }

        bool captive(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__captive__object__ret__bool, unit_);
        }

        float captive_num(const object &unit_) {
            return __helpers::__number_unary_object(__sqf::unary__captivenum__object__ret__scalar, unit_);
        }

        sqf_return_string current_command(const object &veh_) {
            return __helpers::__string_unary_object(__sqf::unary__currentcommand__object__ret__string, veh_);
        }

        int current_vision_mode(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__currentvisionmode__object__ret__scalar, unit_);
        }

        rv_vision_mode current_vision_mode_alt(const object &unit_) {
            return rv_vision_mode(host::functions.invoke_raw_unary(__sqf::unary__currentvisionmode__array__ret__array, {unit_}));
        }

        rv_vision_mode current_vision_mode(const object& unit_, sqf_string_const_ref weapon_) {
            return rv_vision_mode(host::functions.invoke_raw_binary(__sqf::binary__currentvisionmode__object__string__ret__array, unit_, weapon_));
        }

        rv_vision_mode current_vision_mode(const object& vehicle_, const rv_turret_path& turret_path_) {
            return rv_vision_mode(host::functions.invoke_raw_binary(__sqf::binary__currentvisionmode__object__array__ret__array, vehicle_, turret_path_));
        }

        float current_zeroing(const object &gunner_) {
            return __helpers::__number_unary_object(__sqf::unary__currentzeroing__object__ret__scalar, gunner_);
        }

        rv_zeroing current_zeroing(const object &vehicle_, sqf_string_const_ref weapon_class_, sqf_string_const_ref muzzle_class_) {
            game_value ret = host::functions.invoke_raw_binary(__sqf::binary__currentzeroing__object__array__ret__array, vehicle_, {weapon_class_, muzzle_class_});
            return rv_zeroing({ret[0], ret[1]});
        }

        sqf_return_string face(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__face__object__ret__string, value_);
        }

        sqf_return_string faction(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__faction__object__ret__string, value_);
        }

        void force_respawn(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__forcerespawn__object__ret__nothing, value_);
        }

        object form_leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__formleader__object__ret__object, value_);
        }

        float formation_direction(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__formationdirection__object__ret__scalar, value_);
        }

        object formation_leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__formationleader__object__ret__object, value_);
        }

        float get_aiming_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getaimingcoef__object__ret__scalar, value_);
        }

        float get_anim_aim_precision(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getanimaimprecision__object__ret__scalar, value_);
        }

        float get_anim_speed_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getanimspeedcoef__object__ret__scalar, value_);
        }

        float get_bleeding_remaining(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getbleedingremaining__object__ret__scalar, value_);
        }

        float get_burning_value(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getburningvalue__object__ret__scalar, value_);
        }

        float get_custom_aim_coef(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getcustomaimcoef__object__ret__scalar, value_);
        }

        float get_fatigue(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getfatigue__object__ret__scalar, value_);
        }

        float get_oxygen_remaining(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getoxygenremaining__object__ret__scalar, value_);
        }

        sqf_return_string get_player_uid(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__getplayeruid__object__ret__string, value_);
        }

        float get_stamina(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getstamina__object__ret__scalar, value_);
        }

        float get_stat_value(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__getstatvalue__string__ret__scalar, value_);
        }

        float get_suppression(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getsuppression__object__ret__scalar, value_);
        }

        float get_weapon_sway(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getweaponsway__object__ret__scalar, value_);
        }

        object gunner(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__gunner__object__ret__object, value_);
        }

        float hands_hit(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__handshit__object__ret__scalar, value_);
        }

        void hide_body(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hidebody__object__ret__nothing, value_);
        }

        sqf_return_string incapacitated_state(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__incapacitatedstate__object__ret__string, value_);
        }

        bool is_able_to_breathe(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isabletobreathe__object__ret__bool, value_);
        }

        bool is_aim_precision_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isaimprecisionenabled__object__ret__bool, value_);
        }

        bool is_bleeding(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isbleeding__object__ret__bool, value_);
        }

        bool is_forced_walk(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isforcedwalk__object__ret__bool, value_);
        }

        bool is_formation_leader(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isformationleader__object__ret__bool, value_);
        }

        bool is_player(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isplayer__object__ret__bool, value_);
        }

        bool is_player(const std::vector<object> &player_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isplayer__array__ret__bool, player_);
        }

        bool is_sprint_allowed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__issprintallowed__object__ret__bool, value_);
        }

        bool is_stamina_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isstaminaenabled__object__ret__bool, value_);
        }

        bool is_turned_out(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isturnedout__object__ret__bool, value_);
        }

        bool is_uavconnected(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isuavconnected__object__ret__bool, value_);
        }

        bool is_walking(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iswalking__object__ret__bool, value_);
        }

        bool is_weapon_deployed(const object &obj_) {
            return __helpers::__bool_unary_object(__sqf::unary__isweapondeployed__object__ret__bool, obj_);
        }

        bool is_weapon_deployed(const object &obj_, bool on_ground_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isweapondeployed__array__ret__bool, {obj_, on_ground_});
        }

        bool can_deploy_weapon(const object& obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__candeployweapon__object__ret__bool, obj_); 
        }

        bool is_weapon_rested(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isweaponrested__object__ret__bool, value_);
        }

        void move(const object &unit_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, unit_, pos_);
        }

        void move(const group &group_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__move__object_group__array__ret__nothing, group_, pos_);
        }

        bool move_in_any(const object &unit_, const object &vehicle_) {
            return host::functions.invoke_raw_binary(__sqf::binary__moveinany__object__object__ret__bool, unit_, vehicle_);
        }

        void move_in_cargo(const object &unit_, const object &vehicle_, int cargo_index_) {
            if (cargo_index_ == -1) {
                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__object__ret__nothing, unit_, vehicle_);
            } else {
                game_value params({vehicle_,
                                   static_cast<float>(cargo_index_)});

                host::functions.invoke_raw_binary(__sqf::binary__moveincargo__object__array__ret__nothing, unit_, params);
            }
        }

        void move_in_commander(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveincommander__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_driver(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveindriver__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_gunner(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveingunner__object__object__ret__nothing, unit_, vehicle_);
        }

        void move_in_turret(const object &unit_, const object &vehicle_, rv_turret_path turret_path_) {
            game_value params({vehicle_,
                               std::move(turret_path_)});

            host::functions.invoke_raw_binary(__sqf::binary__moveinturret__object__array__ret__nothing, unit_, params);
        }

        void remote_control(const object &controller_, const object &controlled_) {
            host::functions.invoke_raw_binary(__sqf::binary__remotecontrol__object__object__ret__nothing, controller_, controlled_);
        }

        rv_vehicle_role assigned_vehicle_role(const object &unit_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__assignedvehiclerole__object__ret__array, unit_);

            if (ret.size() == 0) {
                return rv_vehicle_role({});
            }
            if (ret.size() == 1) {
                return rv_vehicle_role({ret[0]});
            }
            return rv_vehicle_role({ret[0], rv_turret_path(ret[1])});
        }

        group get_group(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__group__object__ret__group, unit_);
        }

        group group_get(const object &unit_) {
            return get_group(unit_);
        }

        std::vector<object> group_selected_units(const object &unit_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__groupselectedunits__object__ret__array, unit_));
        }

        std::pair<sqf_return_string_list, sqf_return_string_list> squad_params(const object &unit_) {
            game_value _engine_result = host::functions.invoke_raw_unary(__sqf::unary__squadparams__object__ret__array, unit_);
            return { std::move(__helpers::__convert_to_vector<sqf_return_string>(_engine_result[0])),std::move(__helpers::__convert_to_vector<sqf_return_string>(_engine_result[1])) };
        }

        bool unit_ready(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__unitready__object_array__ret__bool, unit_);
        }

        sqf_return_string_list unit_addons(sqf_string_const_ref class_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__unitaddons__string__ret__array, class_));
        }

        std::vector<object> get_all_owned_mines(const object &unit_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__getallownedmines__object__ret__array, unit_));
        }

        void remove_all_owned_mines(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__removeallownedmines__object__ret__nothing, unit_);
        }

        bool unit_is_uav(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__unitisuav__object__ret__bool, unit_);
        }

        void add_owned_mine(const object &unit_, const object &mine_) {
            host::functions.invoke_raw_binary(__sqf::binary__addownedmine__object__object__ret__nothing, unit_, mine_);
        }

        void add_player_scores(const object &unit_, int kills_infantry_, int kills_soft_, int kills_armor_, int kills_air_, int killed_) {
            game_value params_right({
                static_cast<float>(kills_infantry_),
                static_cast<float>(kills_soft_),
                static_cast<float>(kills_armor_),
                static_cast<float>(kills_air_),
                static_cast<float>(killed_),
            });

            host::functions.invoke_raw_binary(__sqf::binary__addplayerscores__object__array__ret__nothing, unit_, params_right);
        }

        void assign_as_turret(const object &unit_, const object &vehicle_, rv_turret_path turret_path_) {
            game_value params_right({vehicle_,
                                     std::move(turret_path_)});

            host::functions.invoke_raw_binary(__sqf::binary__assignasturret__object__array__ret__nothing, unit_, params_right);
        }

        bool connect_terminal_to_uav(const object &unit_, const object &uav_) {
            return host::functions.invoke_raw_binary(__sqf::binary__connectterminaltouav__object__object__ret__bool, unit_, uav_);
        }

        void disable_uav_connectability(const object &object_, const object &uav_, bool check_all_items_) {
            game_value params_right({uav_,
                                     check_all_items_});

            host::functions.invoke_raw_binary(__sqf::binary__disableuavconnectability__object__array__ret__nothing, object_, params_right);
        }

        void enable_weapon_disassembly(const object &unit_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableweapondisassembly__object__bool__ret__nothing, unit_, enable_);
        }

        object find_nearest_enemy(const object &unit_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_) {
            if (position_.index() == 0) {
                return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, std::get<0>(position_).get());
            }
            return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, std::get<1>(position_).get());
        }

        object find_nearest_enemy(const object &unit_, const object &object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__findnearestenemy__object__object_array__ret__object, unit_, object_);
        }

        void fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref mode_, sqf_string_const_ref magazine_) {
            game_value params_right({muzzle_,
                                     mode_,
                                     magazine_});

            host::functions.invoke_raw_binary(__sqf::binary__fire__object__array__ret__nothing, unit_, params_right);
        }

        bool fire_at_target(const object &unit_, const object &target_, std::optional<std::string> muzzle_) {
            auto_array<game_value> params_right({target_});

            if (muzzle_.has_value()) {
                params_right.push_back(*muzzle_);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__fireattarget__object__array__ret__bool, unit_, std::move(params_right));
        }

        vector3 get_hide_from(const object &unit_, const object &enemy_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethidefrom__object__object__ret__array, unit_, enemy_);
        }

        std::variant<bool, float> get_unit_trait(const object &unit_, sqf_string_const_ref skill_name_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__getunittrait__object__string__ret__nothing_bool, unit_, skill_name_);

            if (res.type() == game_data_bool::type_def) {
                return static_cast<bool>(res);
            }
            return static_cast<float>(res);
        }

        void set_captive(const object &object_, bool status) {
            host::functions.invoke_raw_binary(__sqf::binary__setcaptive__object__bool_scalar__ret__nothing, object_, status);
        }

        void set_captive(const object &object_, float status) {
            host::functions.invoke_raw_binary(__sqf::binary__setcaptive__object__bool_scalar__ret__nothing, object_, status);
        }

        void set_name(const object &unit_, sqf_string_const_ref name_, sqf_string_const_ref first_name_, sqf_string_const_ref last_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__setname__object__array__ret__nothing, unit_, {name_, first_name_, last_name_});
        }

        void set_unit_trait(const object &unit_, sqf_string_const_ref skill_name_, std::variant<bool, float> value_, bool is_custom_) {
            if (value_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setunittrait__object__array__ret__nothing, unit_, {skill_name_, std::get<0>(value_), is_custom_});
            else
                host::functions.invoke_raw_binary(__sqf::binary__setunittrait__object__array__ret__nothing, unit_, {skill_name_, std::get<1>(value_), is_custom_});
        }

        void leave_vehicle(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__leavevehicle__group__object__ret__nothing, value0_, value1_);
        }

        void leave_vehicle(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__leavevehicle__object__object__ret__nothing, unit_, vehicle_);
        }

        void look_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> units_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_) {
            game_value param_left;
            game_value param_right;

            switch (units_.index()) {
                case 0: param_left = std::get<0>(units_).get(); break;
                case 1: param_left = std::move(auto_array<game_value>({std::get<1>(units_).get().begin(), std::get<1>(units_).get().end()})); break;
            }

            switch (target_.index()) {
                case 0: param_right = std::get<0>(target_).get(); break;
                case 1: param_right = std::get<1>(target_).get(); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__lookat__object_array__object_array__ret__nothing, param_left, param_right);
        }

        void play_action(const object &unit_, sqf_string_const_ref action_) {
            host::functions.invoke_raw_binary(__sqf::binary__playaction__object__string__ret__nothing, unit_, action_);
        }

        void play_action_now(const object &unit_, sqf_string_const_ref action_) {
            host::functions.invoke_raw_binary(__sqf::binary__playactionnow__object__string__ret__nothing, unit_, action_);
        }

        void play_gesture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__playgesture__object__string__ret__nothing, value0_, value1_);
        }

        void play_move(const object &unit_, sqf_string_const_ref anim_) {
            host::functions.invoke_raw_binary(__sqf::binary__playmove__object__string__ret__nothing, unit_, anim_);
        }

        void play_move_now(const object &unit_, sqf_string_const_ref anim_) {
            host::functions.invoke_raw_binary(__sqf::binary__playmovenow__object__string__ret__nothing, unit_, anim_);
        }

        void set_anim_speed_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setanimspeedcoef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_bleeding_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setbleedingremaining__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_custom_aim_coef(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcustomaimcoef__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_face(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setface__object__string__ret__nothing, value0_, value1_);
        }

        void set_faceanimation(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfaceanimation__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_fatigue(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfatigue__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_identity(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setidentity__object__string__ret__nothing, value0_, value1_);
        }

        void set_mimic(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmimic__object__string__ret__nothing, value0_, value1_);
        }

        void set_name(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setname__object__string__ret__nothing, value0_, value1_);
        }

        void set_oxygen_remaining(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setoxygenremaining__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_random_lip(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrandomlip__object__bool__ret__nothing, value0_, value1_);
        }

        void set_rank(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrank__object__string__ret__nothing, value0_, value1_);
        }

        void set_stamina(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setstamina__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_suppression(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsuppression__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_target_age(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settargetage__object__string__ret__nothing, value0_, value1_);
        }

        void set_unconscious(const object &unit_, bool enabled_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunconscious__object__bool__ret__nothing, unit_, enabled_);
        }

        void set_unit_ability(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitability__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_unit_pos(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitpos__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_pos_weak(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitposweak__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_rank(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitrank__object__string__ret__nothing, value0_, value1_);
        }

        void set_unit_recoil_coefficient(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitrecoilcoefficient__object__scalar__ret__nothing, value0_, value1_);
        }

        void switch_action(const object &unit_, sqf_string_const_ref action_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchaction__object__string__ret__nothing, unit_, action_);
        }

        void switch_gesture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchgesture__object__string__ret__nothing, value0_, value1_);
        }

        void switch_move(const object &unit_, sqf_string_const_ref anim_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchmove__object__string__ret__nothing, unit_, anim_);
        }

        object leader(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__leader__object__ret__object, value_);
        }

        sqf_return_string life_state(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__lifestate__object__ret__string, value_);
        }

        bool lock_identity(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__lockidentity__object__ret__bool, value_);
        }

        float morale(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__morale__object__ret__scalar, value_);
        }

        void move_out(const object &unit_) {
            __helpers::__empty_unary_object(__sqf::unary__moveout__object__ret__nothing, unit_);
        }

        void move_out(const object &unit_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveout__object__object__ret__nothing, unit_, vehicle_);
        }

        float move_time(const object &unit_) {
            return __helpers::__number_unary_object(__sqf::unary__movetime__object__ret__scalar, unit_);
        }

        sqf_return_string name(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__name__object__ret__string, value_);
        }

        float need_reload(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__needreload__object__ret__scalar, value_);
        }

        void use_audio_time_for_moves(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__useaudiotimeformoves__object__bool__ret__nothing, value0_, value1_);
        }

        float precision(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__precision__object__ret__scalar, value_);
        }

        sqf_return_string rank(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__rank__object__ret__string, value_);
        }

        float rank_id(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__rankid__object__ret__scalar, value_);
        }

        float rating(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__rating__object__ret__scalar, value_);
        }

        void reload(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__reload__object__ret__nothing, value_);
        }

        bool reload(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref magazine_) {
            return host::functions.invoke_raw_binary(__sqf::binary__reload__object__array__ret__bool, unit_, {muzzle_, magazine_});
        }

        bool reload_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__reloadenabled__object__ret__bool, value_);
        }

        void remove_switchable_unit(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeswitchableunit__object__ret__nothing, value_);
        }

        void reset_subgroup_direction(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__resetsubgroupdirection__object__ret__nothing, value_);
        }

        void select_player(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__selectplayer__object__ret__nothing, value_);
        }

        void set_playable(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__setplayable__object__ret__nothing, value_);
        }

        void set_player_respawn_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setplayerrespawntime__scalar__ret__nothing, value_);
        }

        void set_stamina_scheme(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__setstaminascheme__string__ret__nothing, value_);
        }

        bool some_ammo(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__someammo__object__ret__bool, value_);
        }

        sqf_return_string speaker(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__speaker__object__ret__string, value_);
        }

        sqf_return_string stance(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__stance__object__ret__string, value_);
        }

        bool stopped(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__stopped__object__ret__bool, value_);
        }

        sqf_return_string unit_pos(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__unitpos__object__ret__string, value_);
        }

        float unit_recoil_coefficient(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__unitrecoilcoefficient__object__ret__scalar, value_);
        }

        bool weapon_lowered(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__weaponlowered__object__ret__bool, value_);
        }

        void add_rating(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addrating__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_score(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addscore__object__scalar__ret__nothing, value0_, value1_);
        }

        void allow_sprint(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowsprint__object__bool__ret__nothing, value0_, value1_);
        }

        void assign_team(const object &value0_, team_color team_) {
            game_value team;
            switch (team_) {
                case team_color::MAIN: team = "MAIN"sv; break;
                case team_color::RED: team = "RED"sv; break;
                case team_color::GREEN: team = "GREEN"sv; break;
                case team_color::BLUE: team = "BLUE"sv; break;
                case team_color::YELLOW: team = "YELLOW"sv; break;
                default: return;
            }
            host::functions.invoke_raw_binary(__sqf::binary__assignteam__object__string__ret__nothing, value0_, std::move(team));
        }

        void unassign_team(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__unassignteam__object__ret__nothing, value_);
        }

        float animation_phase(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__animationphase__object__string__ret__scalar, value0_, value1_);
        }

        void disable_conversation(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disableconversation__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_aim_precision(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableaimprecision__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_fatigue(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablefatigue__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_mimics(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablemimics__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_reload(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablereload__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_stamina(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablestamina__object__bool__ret__nothing, value0_, value1_);
        }

        void fire(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__fire__object__string__ret__nothing, value0_, value1_);
        }

        void force_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__forcespeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void force_walk(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__forcewalk__object__bool__ret__nothing, value0_, value1_);
        }

        bool is_flashlight_on(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isflashlighton__object__string__ret__bool, value0_, value1_);
        }

        bool is_irlaser_on(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isirlaseron__object__string__ret__bool, value0_, value1_);
        }

        object get_connected_uav(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__getconnecteduav__object__ret__object, value_);
        }

        void remove_owned_mine(const object &unit_, const object &mine_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeownedmine__object__object__ret__nothing, unit_, mine_);
        }

        void reveal(std::variant<object, group> unit_, const object &target_) {
            game_value param_left;
            switch (unit_.index()) {
                case 0: param_left = std::move(std::get<0>(unit_)); break;
                case 1: param_left = std::move(std::get<1>(unit_)); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__reveal__object_group__object__ret__nothing, param_left, target_);
        }

        void reveal(std::variant<object, group> unit_, const std::vector<object> &targets_) {
            auto_array<game_value> targets({targets_.begin(), targets_.end()});

            game_value param_left;
            switch (unit_.index()) {
                case 0: param_left = std::move(std::get<0>(unit_)); break;
                case 1: param_left = std::move(std::get<1>(unit_)); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__reveal__object_group__array__ret__nothing, param_left, std::move(targets));
        }

        void enable_uav_connect_ability(const object &unit_, const object &uav_, bool check_all_items_) {
            game_value params_right({uav_,
                                     check_all_items_});

            host::functions.invoke_raw_binary(__sqf::binary__enableuavconnectability__object__array__ret__nothing, unit_, params_right);
        }

        void do_stop(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__dostop__object_array__ret__nothing, unit_);
        }

        void do_stop(const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__dostop__object_array__ret__nothing, std::move(units));
        }

        void do_get_out(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__dogetout__object_array__ret__nothing, unit_);
        }

        void do_get_out(const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__dogetout__object_array__ret__nothing, std::move(units));
        }

        void calculate_player_visibility_by_friendly(bool calc_) {
            host::functions.invoke_raw_unary(__sqf::unary__calculateplayervisibilitybyfriendly__bool__ret__nothing, calc_);
        }

        bool get_calculate_player_visibility_by_friendly() {
            return host::functions.invoke_raw_nular(__sqf::nular__getcalculateplayervisibilitybyfriendly__ret__bool);
        }

        bool get_diver_state(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getdiverstate__object__ret__bool, unit_);
        }

        float get_object_fov(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getobjectfov__object__ret__scalar, unit_);
        }

        vector2 weapon_inertia(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__weaponinertia__object__ret__array, unit_);
        }

        object get_connected_uav_unit(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getconnecteduavunit__object__ret__object, unit_);
        }

        sqf_return_string pose(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__pose__object__ret__string, unit_);
        }

        void set_unit_freefall_height(const object &unit_, float height_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitfreefallheight__object__scalar__ret__nothing, unit_, height_);
        }

        rv_freefall_info get_unit_freefall_info(const object &unit_) {
            return rv_freefall_info(host::functions.invoke_raw_unary(__sqf::unary__getunitfreefallinfo__object__ret__array, unit_));
        }

        void set_optics_mode(const object &unit_, sqf_string_const_ref mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setopticsmode__object__array_string__ret__nothing, unit_, mode_);
        }

        void set_optics_mode(const object &unit_, int slot_index_, sqf_string_const_ref mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setopticsmode__object__array_string__ret__nothing, unit_, {slot_index_, mode_});
        }

        void set_optics_mode(const object &unit_, float index_) {
            host::functions.invoke_raw_binary(__sqf::binary__setopticsmode__object__array_string__ret__nothing, unit_, index_);
        }

        void set_optics_mode(const object &unit_, int slot_index_, float mode_index_) {
            host::functions.invoke_raw_binary(__sqf::binary__setopticsmode__object__array_string__ret__nothing, unit_, {slot_index_, mode_index_});
        }

        rv_weapons_info weapons_info(const object &unit_, sqf_string_const_ref wpnOrMuzzle_, bool onlyLoaded_) {
            return rv_weapons_info(host::functions.invoke_raw_binary(__sqf::binary__weaponsinfo__object__array__ret__array, unit_, {wpnOrMuzzle_, onlyLoaded_}));
        }

        sqf_return_string get_optics_mode(const object &unit_, int slot) {
            return host::functions.invoke_raw_binary(__sqf::binary__getopticsmode__object__scalar__ret__string, unit_, slot);
        }

        sqf_return_string_list compatible_magazines(sqf_string_const_ref weapon_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__compatiblemagazines__string_array__ret__array, weapon_));
        }

        sqf_return_string_list compatible_magazines(sqf_string_const_ref weapon_, sqf_string_const_ref muzzle_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__compatiblemagazines__string_array__ret__array, {weapon_, muzzle_}));
        }

        sqf_return_string_list compatible_items(sqf_string_const_ref weapon_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__compatibleitems__string_array__ret__array, weapon_));
        }

        sqf_return_string_list compatible_items(sqf_string_const_ref weapon_, sqf_string_const_ref slot_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__compatibleitems__string_array__ret__array, {weapon_, slot_}));
        }
    }  // namespace sqf
}  // namespace intercept
