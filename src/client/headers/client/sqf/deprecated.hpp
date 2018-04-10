/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Deprecated Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        // TODO void edit(sqf_string_const_ref value_); // Are we sure this is a valid sqf script command?

        //2d editor commands (probably unneeded)
        //#TODO check them
        void delete_editor_object(const control &map_, sqf_string_const_ref object_);
        sqf_return_string add_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &values_, sqf_string_const_ref subtype_class_);
        game_value shown_editor_object(const control &map_, const game_value &params_right_);
        void editor_set_event_handler(const control &map_, sqf_string_const_ref event_type_, sqf_string_const_ref event_function_);
        game_value eval_object_argument(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref argument_);
        game_value exec_editor_script(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref script_);
        sqf_return_string get_object_argument(const control &map_, const object &object_, sqf_string_const_ref argument_);
        sqf_return_string_list get_object_children(const control &map_, sqf_string_const_ref object_);
        sqf_return_string insert_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &value_, sqf_string_list_const_ref values_, sqf_string_const_ref sub_type_);
        game_value select_editor_object(const control &map_, sqf_string_const_ref object_);
        void set_editor_object_scope(const control &map_, sqf_string_list_const_ref objects_, sqf_string_const_ref editor_type_, sqf_string_const_ref condition_, sqf_string_const_ref scope_, bool sub_ordinates_also_);
        void set_visible_if_tree_collapsed(const control &map_, sqf_string_const_ref object_, bool visible_);
        int add_menu(const control &map_, sqf_string_const_ref text_, float priority_);
        int add_menu_item(const control &map_, sqf_string_const_ref menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_);
        int add_menu_item(const control &map_, int menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_);
        int nmenu_items(const control &map_, sqf_string_const_ref menu_name_);
        int nmenu_items(const control &map_, int index_);
        void update_menu_item(const control &map_, int menu_item_index_, sqf_string_const_ref text_, sqf_string_const_ref command_);
        game_value edit_object(const control &map_, sqf_string_const_ref object_);
        sqf_return_string_list list_objects(const control &map_, sqf_string_const_ref type_);
        game_value set_object_arguments(const control &map_, sqf_string_const_ref object_, sqf_string_list_const_ref values_);
        void set_object_proxy(const control &map_, sqf_string_const_ref object_, const object &proxy_object_);

        //doesn't work in A3 (comment from KK) - Should probably check if that's true tho
        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, sqf_string_const_ref_wrapper>>> &attributes_);
        //buldozer
        bool buldozer_is_enabled_road_diag();
        void buldozer_reload_oper_map();
        void buldozer_enable_road_diag(bool value_);
        bool buldozer_load_new_roads(sqf_string_const_ref value_);
    }  // namespace sqf
}  // namespace intercept
