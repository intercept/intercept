#include "multiplayer.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        game_value remote_exec(sqf_string_const_ref function_name_, sqf_string_const_ref jip_id_) {
            game_value params({function_name_,
                               jip_id_});

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexec__array__ret__string_nothing, params);
        }

        game_value remote_exec(sqf_string_const_ref function_name_, std::variant<int, object, side, group, sqf_string_const_ref_wrapper> target_, sqf_string_const_ref jip_id_) {
            auto_array<game_value> params({function_name_});
            switch (target_.index()) {
                case 0: params.push_back(std::get<0>(target_)); break;
                case 1: params.push_back(std::get<1>(target_)); break;
                case 2: params.push_back(std::get<2>(target_)); break;
                case 3: params.push_back(std::get<3>(target_)); break;
                case 4: params.push_back(std::get<4>(target_).get()); break;
            }
            params.push_back(jip_id_);

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexec__array__ret__string_nothing, std::move(params));
        }

        game_value remote_exec(sqf_string_const_ref function_name_, const game_value &targets_, sqf_string_const_ref jip_id_) {
            game_value params({function_name_,
                               targets_,
                               jip_id_});

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexec__array__ret__string_nothing, params);
        }

        game_value remote_exec_call(sqf_string_const_ref function_name_, sqf_string_const_ref jip_id_) {
            game_value params({function_name_,
                               jip_id_});

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexeccall__array__ret__string_nothing, params);
        }

        game_value remote_exec_call(sqf_string_const_ref function_name_, std::variant<int, object, side, group, sqf_string_const_ref_wrapper> target_, sqf_string_const_ref jip_id_) {
            auto_array<game_value> params({function_name_});
            switch (target_.index()) {
                case 0: params.push_back(std::get<0>(target_)); break;
                case 1: params.push_back(std::get<1>(target_)); break;
                case 2: params.push_back(std::get<2>(target_)); break;
                case 3: params.push_back(std::get<3>(target_)); break;
                case 4: params.push_back(std::get<4>(target_).get()); break;
            }
            params.push_back(jip_id_);

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexeccall__array__ret__string_nothing, std::move(params));
        }

        game_value remote_exec_call(sqf_string_const_ref function_name_, const game_value &targets_, sqf_string_const_ref jip_id_) {
            game_value params({function_name_,
                               targets_,
                               jip_id_});

            return host::functions.invoke_raw_unary(__sqf::unary__remoteexeccall__array__ret__string_nothing, params);
        }

        bool is_multiplayer_solo() {
            return host::functions.invoke_raw_nular(__sqf::nular__ismultiplayersolo__ret__bool);
        }

        bool is_remote_executed() {
            return host::functions.invoke_raw_nular(__sqf::nular__isremoteexecuted__ret__bool);
        }

        bool is_remote_executed_jip() {
            return host::functions.invoke_raw_nular(__sqf::nular__isremoteexecutedjip__ret__bool);
        }

        game_value remote_exec(const game_value &params_, sqf_string_const_ref function_, std::variant<int, object, sqf_string_const_ref_wrapper, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<sqf_string_const_ref_wrapper, bool, object, group>> jip_) {
            game_value targets;
            game_value jip;
            switch (targets_.index()) {
                case 0: targets = static_cast<float>(std::get<int>(targets_)); break;
                case 1: targets = std::get<object>(targets_); break;
                case 2: targets = std::get<2>(targets_).get(); break;
                case 3: targets = std::get<side>(targets_); break;
                case 4: targets = std::get<group>(targets_); break;
                case 5: targets = std::move(auto_array<game_value>({std::get<5>(targets_).get().begin(), std::get<5>(targets_).get().end()})); break;
            }

            if (jip_.has_value()) {
                switch ((*jip_).index()) {
                    case 0: jip = std::get<0>(*jip_).get(); break;
                    case 1: jip = std::get<bool>(*jip_); break;
                    case 2: jip = std::get<object>(*jip_); break;
                    case 3: jip = std::get<group>(*jip_); break;
                }
            }
            game_value params_right = game_value({function_,
                                                  targets,
                                                  jip});

            return host::functions.invoke_raw_binary(__sqf::binary__remoteexec__any__array__ret__string_nothing, params_, params_right);
        }

        game_value remote_exec_call(const game_value &params_, sqf_string_const_ref function_, std::variant<int, object, sqf_string_const_ref_wrapper, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<sqf_string_const_ref_wrapper, bool, object, group>> jip_) {
            game_value targets;
            game_value jip;
            switch (targets_.index()) {
                case 0: targets = static_cast<float>(std::get<int>(targets_)); break;
                case 1: targets = std::get<object>(targets_); break;
                case 2: targets = std::get<2>(targets_).get(); break;
                case 3: targets = std::get<side>(targets_); break;
                case 4: targets = std::get<group>(targets_); break;
                case 5: targets = std::move(auto_array<game_value>({std::get<5>(targets_).get().begin(), std::get<5>(targets_).get().end()})); break;
            }

            if (jip_.has_value()) {
                switch ((*jip_).index()) {
                    case 0: jip = std::get<0>(*jip_).get(); break;
                    case 1: jip = std::get<bool>(*jip_); break;
                    case 2: jip = std::get<object>(*jip_); break;
                    case 3: jip = std::get<group>(*jip_); break;
                }
            }
            game_value params_right = game_value({function_,
                                                  targets,
                                                  jip});

            return host::functions.invoke_raw_binary(__sqf::binary__remoteexeccall__any__array__ret__string_nothing, params_, params_right);
        }

        bool server_command(sqf_string_const_ref command_, sqf_string_const_ref password_) {
            return host::functions.invoke_raw_binary(__sqf::binary__servercommand__string__string__ret__bool, command_, password_);
        }

        bool did_jipowner(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__didjipowner__object__ret__bool, value_);
        }

        void export_jipmessages(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__exportjipmessages__string__ret__nothing, value_);
        }

        bool local(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__local__object__ret__bool, value_);
        }

        bool local(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__local__group__ret__bool, value_);
        }

        bool is_server() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isserver__ret__bool);
        }

        bool is_multiplayer() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__ismultiplayer__ret__bool);
        }

        bool is_dedicated() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__isdedicated__ret__bool);
        }

        bool did_jip() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__didjip__ret__bool);
        }

        bool turret_local(const object &vehicle_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__turretlocal__object__array__ret__bool, vehicle_, std::move(turret_path_));
        }

        int turret_owner(const object &vehicle_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__turretowner__object__array__ret__scalar, vehicle_, std::move(turret_path_));
        }

        float client_owner() {
            return __helpers::__retrieve_nular_number(__sqf::nular__clientowner__ret__scalar);
        }

        float owner(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__owner__object__ret__scalar, value_);
        }

        bool set_owner(const object &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setowner__object__scalar__ret__bool, value0_, value1_);
        }

        void public_variable(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__publicvariable__string__ret__nothing, value_);
        }

        void public_variable_server(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__publicvariableserver__string__ret__nothing, value_);
        }

        void public_variable_client(float value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__publicvariableclient__scalar__string__ret__nothing, value0_, value1_);
        }

        void log_network_terminate(float handle_) {
            host::functions.invoke_raw_unary(__sqf::unary__lognetworkterminate__scalar__ret__nothing, handle_);
        }

        float server_time() {
            return host::functions.invoke_raw_nular(__sqf::nular__servertime__ret__scalar);
        }

        sqf_return_string server_name() {
            return host::functions.invoke_raw_nular(__sqf::nular__servername__ret__string);
        }

        float estimated_end_server_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__estimatedendservertime__ret__scalar);
        }

        bool server_command(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__servercommand__string__ret__bool, value_);
        }

        bool server_command_available(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__servercommandavailable__string__ret__bool, value_);
        }

        bool server_command_executable(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__servercommandexecutable__string__ret__bool, value_);
        }

        float get_client_state_number() {
            return game_value(__helpers::__retrieve_nular_number(__sqf::nular__getclientstatenumber__ret__string));
        }

        sqf_return_string getclientstate() {
            return __helpers::__retrieve_nular_string(__sqf::nular__getclientstate__ret__string);
        }

        bool leaderboard_de_init(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__leaderboarddeinit__string__ret__bool, value_);
        }

        bool leaderboard_init(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__leaderboardinit__string__ret__bool, value_);
        }

        bool leaderboard_request_rows_friends(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__leaderboardrequestrowsfriends__string__ret__bool, value_);
        }

        float leaderboard_state(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__leaderboardstate__string__ret__scalar, value_);
        }

        sqf_return_string net_id(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__netid__object__ret__string, value_);
        }

        sqf_return_string net_id(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__netid__group__ret__string, value_);
        }

        object object_from_net_id(sqf_string_const_ref value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__objectfromnetid__string__ret__object, value_));
        }
        int admin(int owner_id_) {
            return host::functions.invoke_raw_unary(__sqf::unary__admin__scalar__ret__scalar, owner_id_);
        }
        int remote_executed_owner() {
            return host::functions.invoke_raw_nular(__sqf::nular__remoteexecutedowner__ret__scalar);
        }

        bool has_interface() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__hasinterface__ret__bool);
        }

        void connect_to_server(sqf_string_const_ref ip_, float port, sqf_string_const_ref password_) {
            host::functions.invoke_raw_unary(__sqf::unary__connecttoserver__array__ret__nothing, {ip_, port, password_});
        }

        std::vector<float> get_player_scores(const object &player_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__getplayerscores__object__ret__array, player_));
        }

        sqf_return_string_list all_users() {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__allusers__ret__array));
        }

        rv_user_info get_user_info(sqf_string_const_ref id_) {
            return rv_user_info(host::functions.invoke_raw_unary(__sqf::unary__getuserinfo__string__ret__array, id_));
        }
    }  // namespace sqf
}  // namespace intercept
