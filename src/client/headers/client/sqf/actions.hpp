/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Action Menu related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct rv_action_key_details {
            sqf_string main_device;
            sqf_string combo_device;
            float main_dik_code = -1;
            float combo_dik_code = -1;
            float device_id = -1;
            bool is_double_tap = false;
            explicit rv_action_key_details(const game_value &gv_) {
                auto ret_array = gv_.to_array();
                if (ret_array.empty())
                    return;

                auto main_array = ret_array[0].to_array();
                if (main_array.empty())
                    return;

                is_double_tap = ret_array[2];
                main_dik_code = main_array[0];
                main_device = sqf_string(main_array[1]);
                if (main_array.size() > 1)
                    device_id = main_array[2];

                auto combo_array = ret_array[1].to_array();
                if (combo_array.empty())
                    return;

                combo_dik_code = combo_array[0];
                combo_device = sqf_string(combo_array[1]);
            }
        };

        sqf_return_string_list action_keys(sqf_string_const_ref user_action_);
        std::vector<rv_action_key_details> action_keys_ex(sqf_string_const_ref user_action_);

        std::vector<float> action_ids(const object &entity_);
        float input_action(sqf_string_const_ref value_);

        rv_text action_keys_images(sqf_string_const_ref user_action_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_);

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_);
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_);
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_);

        float add_action(const object &object_, sqf_string_const_ref title_, sqf_string_const_ref script_, game_value arguments_ = game_value(), float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, sqf_string_const_ref shortcut_ = "", sqf_string_const_ref condition_ = "true");
        float add_action(const object &object_, sqf_string_const_ref title_, const code &script_, game_value arguments_ = game_value(), float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, sqf_string_const_ref shortcut_ = "", sqf_string_const_ref condition_ = "true");

        sqf_return_string commanding_menu();
        sqf_return_string action_name(sqf_string_const_ref action_);
        sqf_return_string key_image(float value_);
        sqf_return_string key_name(float value_);
        void remove_all_actions(const object &value_);
        void remove_action(const object &value0_, float value1_);
        rv_action_params action_params(const object &entity_, int id_);
        void set_user_action_text(const object &object_, int action_index_, std::variant<std::string, rv_text> text_menu_, std::variant<std::string, rv_text> text_window_background_, std::variant<std::string, rv_text> text_window_foreground_);

        float input_controller(float input_);
        float input_mouse(float button_);
        bool input_mouse(sqf_string_const_ref combo_code_);


    }  // namespace sqf
}  // namespace intercept
