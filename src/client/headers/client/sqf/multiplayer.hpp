/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Multiplayer commands.

Check the locality and other multiplayer related facets of objects and the environment.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        game_value remote_exec(sqf_string_const_ref function_name_, sqf_string_const_ref jip_id_);
        game_value remote_exec(sqf_string_const_ref function_name_, std::variant<int, object, side, group, sqf_string_const_ref_wrapper> target_, sqf_string_const_ref jip_id_);
        game_value remote_exec(sqf_string_const_ref function_name_, const game_value &targets_, sqf_string_const_ref jip_id_);
        game_value remote_exec_call(sqf_string_const_ref function_name_, sqf_string_const_ref jip_id_);
        game_value remote_exec_call(sqf_string_const_ref function_name_, std::variant<int, object, side, group, sqf_string_const_ref_wrapper> target_, sqf_string_const_ref jip_id_);
        game_value remote_exec_call(sqf_string_const_ref function_name_, const game_value &targets_, sqf_string_const_ref jip_id_);

        void log_network_terminate(float handle_);

        float server_time();
        sqf_return_string server_name();

        bool local(const object &value_);
        bool local(const group &value_);
        bool is_server();
        bool is_multiplayer();
        bool is_dedicated();
        bool did_jip();
        float client_owner();
        float estimated_end_server_time();
        sqf_return_string getclientstate();

        bool has_interface();
        bool did_jipowner(const object &value_);
        void export_jipmessages(sqf_string_const_ref value_);
        bool leaderboard_de_init(sqf_string_const_ref value_);
        bool leaderboard_init(sqf_string_const_ref value_);
        bool leaderboard_request_rows_friends(sqf_string_const_ref value_);
        float leaderboard_state(sqf_string_const_ref value_);
        sqf_return_string net_id(const object &value_);
        sqf_return_string net_id(const group &value_);
        object object_from_net_id(sqf_string_const_ref value_);
        float owner(const object &value_);
        void public_variable(sqf_string_const_ref value_);
        void public_variable_server(sqf_string_const_ref value_);
        void public_variable_client(float value0_, sqf_string_const_ref value1_);

        bool server_command(sqf_string_const_ref value_);
        bool server_command(sqf_string_const_ref command_, sqf_string_const_ref password_);

        bool server_command_available(sqf_string_const_ref value_);
        bool server_command_executable(sqf_string_const_ref value_);

        float get_client_state_number();
        bool set_owner(const object &value0_, float value1_);

        bool is_multiplayer_solo();
        bool is_remote_executed();
        bool is_remote_executed_jip();

        game_value remote_exec(const game_value &params_, sqf_string_const_ref function_, std::variant<int, object, sqf_string_const_ref_wrapper, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<sqf_string_const_ref_wrapper, bool, object, group>> jip_);
        game_value remote_exec_call(const game_value &params_, sqf_string_const_ref function_, std::variant<int, object, sqf_string_const_ref_wrapper, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<sqf_string_const_ref_wrapper, bool, object, group>> jip_);

        bool turret_local(const object &vehicle_, rv_turret_path turret_path_);
        int turret_owner(const object &vehicle_, rv_turret_path turret_path_);
        //mp
        int admin(int owner_id_);
        int remote_executed_owner();

    }  // namespace sqf
}  // namespace intercept
