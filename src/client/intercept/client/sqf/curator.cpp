#include "curator.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* Curator */
        object curator_camera() {
            return __helpers::__retrieve_nular_object(__sqf::nular__curatorcamera__ret__object);
        }

        object curator_mouse_over() {
            return __helpers::__retrieve_nular_object(__sqf::nular__curatormouseover__ret__object);
        }

        curator_selected_return curator_selected() {
            game_value selected = host::functions.invoke_raw_nular(__sqf::nular__curatorselected__ret__array);

            curator_selected_return _return = curator_selected_return(
                __helpers::__convert_to_vector<object>(selected[0]),
                __helpers::__convert_to_vector<group>(selected[1]),
                __helpers::__convert_to_vector<waypoint>(selected[2]),
                __helpers::__convert_to_vector<marker>(selected[3])
            );
            return  _return;
        }

        void open_curator_interface() {
            __helpers::__empty_nular(__sqf::nular__opencuratorinterface__ret__nothing);
        }

        bool shown_curatorcompass() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__showncuratorcompass__ret__bool);
        }

        std::vector<rv_curator_cam_area> curator_camera_area(const object &curator_) {
            return __helpers::__convert_to_vector<rv_curator_cam_area>(host::functions.invoke_raw_unary(__sqf::unary__curatorcameraarea__object__ret__array, curator_));
        }

        rv_curator_cam_area curator_editing_area(const object &curator_) {
            return rv_curator_cam_area(host::functions.invoke_raw_unary(__sqf::unary__curatoreditingarea__object__ret__array, curator_));
        }

        float curator_camera_area_ceiling(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__curatorcameraareaceiling__object__ret__scalar, value_);
        }

        bool curator_editing_area_type(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__curatoreditingareatype__object__ret__bool, value_);
        }

        float curator_points(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__curatorpoints__object__ret__scalar, value_);
        }

        float curator_waypoint_cost(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__curatorwaypointcost__object__ret__scalar, value_);
        }

        object get_assigned_curator_logic(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__getassignedcuratorlogic__object__ret__object, value_);
        }

        object get_assigned_curator_unit(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__getassignedcuratorunit__object__ret__object, value_);
        }

        void remove_all_curator_addons(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallcuratoraddons__object__ret__nothing, value_);
        }

        void remove_all_curator_camera_areas(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallcuratorcameraareas__object__ret__nothing, value_);
        }

        void remove_all_curator_editing_areas(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallcuratoreditingareas__object__ret__nothing, value_);
        }

        void show_curator_compass(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showcuratorcompass__bool__ret__nothing, value_);
        }

        void unassign_curator(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__unassigncurator__object__ret__nothing, value_);
        }

        void add_curator_points(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__addcuratorpoints__object__scalar__ret__nothing, value0_, value1_);
        }

        void allow_curator_logic_ignore_areas(const object &value1_, bool value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowcuratorlogicignoreareas__object__bool__ret__nothing, value0_, value1_);
        }
        float curator_coef(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__curatorcoef__object__string__ret__scalar, value0_, value1_);
        }

        void remove_curator_camera_area(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__removecuratorcameraarea__object__scalar__ret__nothing, value0_, value1_);
        }

        void remove_curator_editing_area(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__removecuratoreditingarea__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_curator_camera_area_ceiling(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcuratorcameraareaceiling__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_curator_editing_area_type(const object &value1_, bool value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcuratoreditingareatype__object__bool__ret__nothing, value0_, value1_);
        }

        void set_curator_waypoint_cost(const object &value1_, float value0_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcuratorwaypointcost__object__scalar__ret__nothing, value0_, value1_);
        }

        void add_curator_addons(const object &curator_object_, sqf_string_list_const_ref addons_) {
            auto_array<game_value> addons(addons_.begin(), addons_.end());

            host::functions.invoke_raw_binary(__sqf::binary__addcuratoraddons__object__array__ret__nothing, curator_object_, std::move(addons));
        }

        void add_curator_camera_area(const object &curator_object_, int camera_area_id_, const vector2 &position_, float radius_) {
            game_value args({static_cast<float>(camera_area_id_),
                             position_,
                             radius_});

            host::functions.invoke_raw_binary(__sqf::binary__addcuratorcameraarea__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_camera_area(const object &curator_object_, int camera_area_id_, const vector3 &position_, float radius_) {
            game_value args({static_cast<float>(camera_area_id_),
                             position_,
                             radius_});

            host::functions.invoke_raw_binary(__sqf::binary__addcuratorcameraarea__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_editable_objects(const object &curator_object_, const std::vector<object> &objects_, bool add_crew_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());

            game_value args({std::move(objects),
                             add_crew_});

            host::functions.invoke_raw_binary(__sqf::binary__addcuratoreditableobjects__object__array__ret__nothing, curator_object_, args);
        }

        void add_curator_editing_area(const object &curator_object_, int edit_area_id_, const vector2 &position_, float radius_) {
            game_value args({static_cast<float>(edit_area_id_),
                             position_,
                             radius_});

            host::functions.invoke_raw_binary(__sqf::binary__addcuratoreditingarea__object__array__ret__nothing, curator_object_, args);
        }

        sqf_return_string_list curator_addons(const object &curator_module_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__curatoraddons__object__ret__array, curator_module_));
        }

        std::vector<object> curator_editable_objects(const object &curator_module_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__curatoreditableobjects__object__ret__array, curator_module_));
        }

        std::vector<object> curator_registered_objects(const object &curator_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__curatorregisteredobjects__object__ret__array, curator_));
        }
        std::vector<object> object_curators(const object &obj_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__objectcurators__object__ret__array, obj_));
        }

        void remove_curator_addons(const object &curator_module_, sqf_string_list_const_ref addons_) {
            auto_array<game_value> addons(addons_.begin(), addons_.end());

            host::functions.invoke_raw_binary(__sqf::binary__removecuratoraddons__object__array__ret__nothing, curator_module_, std::move(addons));
        }

        void remove_curator_editable_objects(const object &curator_module_, const std::vector<object> &objects_, bool &remove_crew_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());
            game_value params_right({std::move(objects),
                                     remove_crew_});

            host::functions.invoke_raw_binary(__sqf::binary__removecuratoreditableobjects__object__array__ret__nothing, curator_module_, params_right);
        }

        void set_curator_coef(const object &curator_, sqf_string_const_ref action_, std::variant<float, bool> coef_) {
            if (coef_.index() == 0)
                host::functions.invoke_raw_binary(__sqf::binary__setcuratorcoef__object__array__ret__nothing, curator_, {action_, std::get<bool>(coef_)});
            else
                host::functions.invoke_raw_binary(__sqf::binary__setcuratorcoef__object__array__ret__nothing, curator_, {action_, std::get<float>(coef_)});
        }

        void assign_curator(const object &player_, const object &curator_module_) {
            host::functions.invoke_raw_binary(__sqf::binary__assigncurator__object__object__ret__nothing, player_, curator_module_);
        }

    }  // namespace sqf
}  // namespace intercept
