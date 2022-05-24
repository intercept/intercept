#include "actions.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        std::vector<float> action_ids(const object &entity_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__actionids__object__ret__array, entity_));
        }

        rv_action_params action_params(const object &entity_, int id_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__actionparams__object__scalar__ret__array, entity_, static_cast<float>(id_));

            return rv_action_params({res[0],
                                     res[1],
                                     res[2],
                                     res[3],
                                     res[4],
                                     res[5],
                                     res[6],
                                     res[7],
                                     res[8],
                                     res[9],
                                     res[10],
                                     res[11],
                                     res[12]});
        }

        void set_user_action_text(const object &object_, int action_index_, std::variant<std::string, rv_text> text_menu_, std::variant<std::string, rv_text> text_window_background_, std::variant<std::string, rv_text> text_window_foreground_) {
            auto_array<game_value> params_right({action_index_});

            if (text_menu_.index() == 0) {
                params_right.push_back(std::get<0>(text_menu_));
            } else {
                params_right.push_back(std::get<1>(text_menu_));
            }

            if (text_window_background_.index() == 0) {
                params_right.push_back(std::get<0>(text_window_background_));
            } else {
                params_right.push_back(std::get<1>(text_window_background_));
            }

            if (text_window_foreground_.index() == 0) {
                params_right.push_back(std::get<0>(text_window_foreground_));
            } else {
                params_right.push_back(std::get<1>(text_window_foreground_));
            }

            host::functions.invoke_raw_binary(__sqf::binary__setuseractiontext__object__array__ret__nothing, object_, std::move(params_right));
        }

        sqf_return_string_list action_keys(sqf_string_const_ref user_action_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__actionkeys__array__ret__array, {user_action_}));
        }

        std::vector<rv_action_key_details> action_keys_ex(sqf_string_const_ref user_action_) {
            return __helpers::__convert_to_vector<rv_action_key_details>(host::functions.invoke_raw_unary(__sqf::unary__actionkeysex__string__ret__array, user_action_));
        }

        rv_text action_keys_images(sqf_string_const_ref user_action_) {
            return rv_text(host::functions.invoke_raw_unary(__sqf::unary__actionkeysimages__string_array__ret__text, user_action_));
        }

        sqf_return_string action_keys_names(sqf_string_const_ref user_action_) {
            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, user_action_);
        }

        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_) {
            game_value params({user_action_, static_cast<float>(max_keys_)});
            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, params);
        }
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_) {
            game_value params({user_action_,
                               static_cast<float>(max_keys_),
                               input_device_priority_});

            return host::functions.invoke_raw_unary(__sqf::unary__actionkeysnames__string_array__ret__string, params);
        }

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_) {
            game_value act_keys = host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, user_action_);
            sqf_return_string_list r_arr = __helpers::__convert_to_vector<sqf_return_string>(act_keys);

            return r_arr;
        }

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_) {
            game_value params({user_action_, static_cast<float>(max_keys_)});

            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_) {
            game_value params({user_action_,
                               static_cast<float>(max_keys_),
                               input_device_priority_});

            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
        }

        float add_action(const object &object_, sqf_string_const_ref title_, sqf_string_const_ref script_, game_value arguments_, float priority_, bool show_window_, bool hide_on_use_, sqf_string_const_ref shortcut_, sqf_string_const_ref condition_) {
            game_value args({title_,
                             script_,
                             arguments_,
                             priority_,
                             show_window_,
                             hide_on_use_,
                             shortcut_,
                             condition_});

            return host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args);
        }

        float add_action(const object &object_, sqf_string_const_ref title_, const code &script_, game_value arguments_, float priority_, bool show_window_, bool hide_on_use_, sqf_string_const_ref shortcut_, sqf_string_const_ref condition_) {
            game_value args({title_,
                             script_,
                             arguments_,
                             priority_,
                             show_window_,
                             hide_on_use_,
                             shortcut_,
                             condition_});

            return host::functions.invoke_raw_binary(__sqf::binary__addaction__object__array__ret__nothing_scalar, object_, args);
        }

        sqf_return_string action_name(sqf_string_const_ref action_) {
            return __helpers::__string_unary_string(__sqf::unary__actionname__string__ret__string, action_);
        }

        float input_action(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__inputaction__string__ret__scalar, value_);
        }

        void remove_all_actions(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallactions__object__ret__nothing, value_);
        }

        void remove_action(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeaction__object__scalar__ret__nothing, value0_, value1_);
        }

        sqf_return_string key_image(float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__keyimage__string_scalar__ret__text, value_);
        }

        sqf_return_string key_name(float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__keyname__string_scalar__ret__string, value_);
        }

        sqf_return_string commanding_menu() {
            return __helpers::__retrieve_nular_string(__sqf::nular__commandingmenu__ret__string);
        }

        float input_controller(float input_) {
            return host::functions.invoke_raw_unary(__sqf::unary__inputcontroller__scalar__ret__scalar, input_);
        }

        float input_mouse(float button_) {
            return host::functions.invoke_raw_unary(__sqf::unary__inputmouse__scalar__ret__scalar, button_);
        }

        bool input_mouse(sqf_string_const_ref combo_code_) {
            return host::functions.invoke_raw_unary(__sqf::unary__inputmouse__string__ret__bool, combo_code_);
        }

    }  // namespace sqf
}  // namespace intercept
