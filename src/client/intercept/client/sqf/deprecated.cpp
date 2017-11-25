#include "deprecated.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        void delete_editor_object(const control &map_, sqf_string_const_ref object_) {
            host::functions.invoke_raw_binary(__sqf::binary__deleteeditorobject__control__string__ret__any, map_, object_);
        }

        void editor_set_event_handler(const control &map_, sqf_string_const_ref event_type_, sqf_string_const_ref event_function_) {
            game_value params_right({event_type_,
                                     event_function_});

            host::functions.invoke_raw_binary(__sqf::binary__editorseteventhandler__control__array__ret__nothing, map_, params_right);
        }

        game_value eval_object_argument(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref argument_) {
            return host::functions.invoke_raw_binary(__sqf::binary__evalobjectargument__control__array__ret__any, map_, {object_, argument_});
        }

        game_value exec_editor_script(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref script_) {
            game_value params_right({object_,
                                     script_});

            return host::functions.invoke_raw_binary(__sqf::binary__execeditorscript__control__array__ret__any, map_, params_right);
        }

        /*
        #TODO: Find out about the usage of this command
        binary__findeditorobject__control__array__ret__string
        binary__findeditorobject__control__any__ret__string

        sqf_return_string find_editor_object(const control &map_, const ) {
        return host::functions.invoke_raw_binary(__sqf::binary__findeditorobject__control__array__ret__string, object_, std::move(params_right));
        }
        */

        sqf_return_string insert_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &value_, sqf_string_list_const_ref values_, sqf_string_const_ref sub_type_) {
            game_value params_right({type_,
                                     value_,
                                     std::move(auto_array<game_value>({values_.begin(), values_.end()})),
                                     sub_type_});

            return host::functions.invoke_raw_binary(__sqf::binary__inserteditorobject__control__array__ret__string, map_, params_right);
        }

        game_value select_editor_object(const control &map_, sqf_string_const_ref object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selecteditorobject__control__string__ret__any, map_, object_);
        }

        void set_editor_object_scope(const control &map_, sqf_string_list_const_ref objects_, sqf_string_const_ref editor_type_, sqf_string_const_ref condition_, sqf_string_const_ref scope_, bool sub_ordinates_also_) {
            game_value params_right({std::move(auto_array<game_value>(objects_.begin(), objects_.end())),
                                     editor_type_,
                                     condition_,
                                     scope_,
                                     sub_ordinates_also_});

            host::functions.invoke_raw_binary(__sqf::binary__seteditorobjectscope__control__array__ret__nothing, map_, params_right);
        }

        void set_visible_if_tree_collapsed(const control &map_, sqf_string_const_ref object_, bool visible_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvisibleiftreecollapsed__control__array__ret__nothing, map_, {object_, visible_});
        }

        //#TODO: Find out which params are to the right
        game_value shown_editor_object(const control &map_, const game_value &params_right_) {
            return host::functions.invoke_raw_binary(__sqf::binary__showneweditorobject__control__array__ret__any, map_, params_right_);
        }

        sqf_return_string add_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &values_, sqf_string_const_ref subtype_class_) {
            game_value params_right({type_,
                                     values_,
                                     subtype_class_});

            return host::functions.invoke_raw_binary(__sqf::binary__addeditorobject__control__array__ret__string, map_, params_right);
        }

        int add_menu(const control &map_, sqf_string_const_ref text_, float priority_) {
            game_value params_right({text_,
                                     priority_});

            return host::functions.invoke_raw_binary(__sqf::binary__addmenu__control__array__ret__scalar, map_, params_right);
        }

        int add_menu_item(const control &map_, sqf_string_const_ref menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_) {
            game_value params_right({menu_,
                                     text_,
                                     command_,
                                     priority_});

            return host::functions.invoke_raw_binary(__sqf::binary__addmenuitem__control__array__ret__scalar, map_, params_right);
        }

        int add_menu_item(const control &map_, int menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_) {
            game_value params_right({static_cast<float>(menu_),
                                     text_,
                                     command_,
                                     priority_});

            return host::functions.invoke_raw_binary(__sqf::binary__addmenuitem__control__array__ret__scalar, map_, params_right);
        }

        int nmenu_items(const control &map_, sqf_string_const_ref menu_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nmenuitems__control__string_scalar__ret__scalar, map_, menu_name_);
        }

        int nmenu_items(const control &map_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__nmenuitems__control__string_scalar__ret__scalar, map_, index_);
        }

        void update_menu_item(const control &map_, int menu_item_index_, sqf_string_const_ref text_, sqf_string_const_ref command_) {
            host::functions.invoke_raw_binary(__sqf::binary__updatemenuitem__control__array__ret__nothing, map_, {menu_item_index_, text_, command_});
        }

        game_value edit_object(const control &map_, sqf_string_const_ref object_) {
            return host::functions.invoke_raw_binary(__sqf::binary__editobject__control__string__ret__any, map_, object_);
        }

        //#TODO: Find out if the return type is correct
        sqf_return_string_list list_objects(const control &map_, sqf_string_const_ref type_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__listobjects__control__string__ret__array, map_, type_));
        }

        game_value set_object_arguments(const control &map_, sqf_string_const_ref object_, sqf_string_list_const_ref values_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setobjectarguments__control__array__ret__any, map_, {object_, std::move(auto_array<game_value>(values_.begin(), values_.end()))});
        }

        void set_object_proxy(const control &map_, sqf_string_const_ref object_, const object &proxy_object_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectproxy__control__array__ret__any, map_, {object_, proxy_object_});
        }

        sqf_return_string get_object_argument(const control &map_, const object &object_, sqf_string_const_ref argument_) {
            game_value params_right({object_,
                                     argument_});

            return host::functions.invoke_raw_binary(__sqf::binary__getobjectargument__control__array__ret__string, map_, params_right);
        }

        sqf_return_string_list get_object_children(const control &map_, sqf_string_const_ref object_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__getobjectchildren__control__string__ret__array, map_, object_));
        }

        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, sqf_string_const_ref_wrapper>>> &attributes_) {
            auto_array<game_value> attributes;

            for (auto &it : attributes_) {
                attributes.push_back(it.first);
                if (it.second.index() == 0)
                    attributes.push_back(std::get<0>(it.second));
                else
                    attributes.push_back(std::get<1>(it.second).get());
            }

            return host::functions.invoke_raw_binary(__sqf::binary__setattributes__text_string__array__ret__text, text_, std::move(attributes));
        }

        void buldozer_enable_road_diag(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__buldozer_enableroaddiag__bool__ret__nothing, value_);
        }

        bool buldozer_load_new_roads(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__buldozer_loadnewroads__string__ret__bool, value_);
        }

        bool buldozer_is_enabled_road_diag() {
            return host::functions.invoke_raw_nular(__sqf::nular__buldozer_isenabledroaddiag__ret__bool);
        }

        void buldozer_reload_oper_map() {
            host::functions.invoke_raw_nular(__sqf::nular__buldozer_reloadopermap__ret__nothing);
        }

    }  // namespace sqf
}  // namespace intercept
