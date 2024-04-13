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
        struct rv_user_info {
            sqf_string player_id;           // 0 - user DirectPlay ID (see getPlayerID, PlayerConnected);
            sqf_string player_uid;          // 2 - player UID (see getPlayerUID);
            sqf_string soldier_name;        // 3 - player name (see profileName);
            sqf_string display_name;        // 4 - player name including squad (see name, squadParams);
            sqf_string steam_profile_name;  // 5 - steam profile name (see profileNameSteam);
            object player_object;           // 10 - user player entity (see player, selectPlayer);
            float owner;                    // 1 - user owner (see owner);
            float client_state;             // 6 -  : String user client state (see getClientStateNumber);
            float admin_state;              // 8 - admin status of the user (see admin);
            float avg_ping;                 // 9 - 0
            float avg_bandwidth;            // 9 - 1
            float desync;                   // 9 - 2
            bool is_headless;               // 7 - whether or not this is a headless client (see hasInterface, isServer)
            explicit rv_user_info(const game_value &gv_) : player_id{gv_[0]},
                                                           player_uid{gv_[2]},
                                                           soldier_name{gv_[3]},
                                                           display_name{gv_[4]},
                                                           steam_profile_name{gv_[5]},
                                                           player_object{gv_[10]},
                                                           owner{gv_[1]},
                                                           client_state{gv_[6]},
                                                           admin_state{gv_[8]},
                                                           avg_ping{gv_[9][0]},
                                                           avg_bandwidth{gv_[9][1]},
                                                           desync{gv_[9][2]},
                                                           is_headless{gv_[7]} {}
        };

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

        void connect_to_server(sqf_string_const_ref ip_, float port, sqf_string_const_ref password_);
        std::vector<float> get_player_scores(const object &player_);

        sqf_return_string_list all_users();

        rv_user_info get_user_info(sqf_string_const_ref id_);
        game_value get_user_info(sqf_string_const_ref id_, int index_);
    }  // namespace sqf
}  // namespace intercept
