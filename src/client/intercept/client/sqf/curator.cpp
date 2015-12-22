#include "curator.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		object curatorcamera() {
			return __helpers::__retrieve_nular_object(client::__sqf::nular__curatorcamera__ret__object);
		}

		object curatormouseover() {
			return __helpers::__retrieve_nular_object(client::__sqf::nular__curatormouseover__ret__object);
		}

		std::vector<object> curatorselected() {
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__curatorselected__ret__array));
		}

		void opencuratorinterface() {
			__helpers::__empty_nular(client::__sqf::nular__opencuratorinterface__ret__nothing);
		}

		bool shown_curatorcompass() {
			return __helpers::__retrieve_nular_bool(client::__sqf::nular__showncuratorcompass__ret__bool);
		}

		float curator_camera_area_ceiling(const object &value_) {
			return __helpers::__number_unary_object(client::__sqf::unary__curatorcameraareaceiling__object__ret__scalar, value_);
		}

		bool curator_editing_area_type(const object &value_) {
			return __helpers::__bool_unary_object(client::__sqf::unary__curatoreditingareatype__object__ret__bool, value_);
		}

		float curator_points(const object &value_) {
			return __helpers::__number_unary_object(client::__sqf::unary__curatorpoints__object__ret__scalar, value_);
		}

		float curator_waypoint_cost(const object &value_) {
			return __helpers::__number_unary_object(client::__sqf::unary__curatorwaypointcost__object__ret__scalar, value_);
		}

		object get_assigned_curator_logic(const object &value_) {
			return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorlogic__object__ret__object, value_);
		}

		object get_assigned_curator_unit(const object &value_) {
			return __helpers::__object_unary_object(client::__sqf::unary__getassignedcuratorunit__object__ret__object, value_);
		}

		void remove_all_curator_addons(const object &value_) {
			__helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoraddons__object__ret__nothing, value_);
		}

		void remove_all_curator_camera_areas(const object &value_) {
			__helpers::__empty_unary_object(client::__sqf::unary__removeallcuratorcameraareas__object__ret__nothing, value_);
		}

		void remove_all_curator_editing_areas(const object &value_) {
			__helpers::__empty_unary_object(client::__sqf::unary__removeallcuratoreditingareas__object__ret__nothing, value_);
		}

		void show_curator_compass(bool value_) {
			__helpers::__empty_unary_bool(client::__sqf::unary__showcuratorcompass__bool__ret__nothing, value_);
		}

		void unassign_curator(const object &value_) {
			__helpers::__empty_unary_object(client::__sqf::unary__unassigncurator__object__ret__nothing, value_);
		}

		void add_curator_points(const object &value1_, float value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__addcuratorpoints__object__scalar__ret__nothing, value0_, value1_);
		}

		void allow_curator_logic_ignore_areas(const object &value1_, bool value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__allowcuratorlogicignoreareas__object__bool__ret__nothing, value0_, value1_);
		}
		float curator_coef(const object &value0_, const std::string &value1_) {
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__curatorcoef__object__string__ret__scalar, value0_, value1_));
		}

		void remove_curator_camera_area(const object &value1_, float value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__removecuratorcameraarea__object__scalar__ret__nothing, value0_, value1_);
		}

		void remove_curator_editing_area(const object &value1_, float value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__removecuratoreditingarea__object__scalar__ret__nothing, value0_, value1_);
		}

		void set_curator_camera_area_ceiling(const object &value1_, float value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__setcuratorcameraareaceiling__object__scalar__ret__nothing, value0_, value1_);
		}

		void set_curator_editing_area_type(const object &value1_, bool value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__setcuratoreditingareatype__object__bool__ret__nothing, value0_, value1_);
		}

		void set_curator_waypoint_cost(const object &value1_, float value0_) {
			host::functions.invoke_raw_binary(client::__sqf::binary__setcuratorwaypointcost__object__scalar__ret__nothing, value0_, value1_);
		}

		std::vector<std::string> curator_addons(const object &curator_module_)
		{
			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__curatoraddons__object__ret__array, curator_module_));
		}

		std::vector<object> curator_editable_objects(const object &curator_module_)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__curatoreditableobjects__object__ret__array, curator_module_));
		}
    }
}
