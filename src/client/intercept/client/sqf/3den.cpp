#include "3den.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
			std::string current3denoperation() {
				return __helpers::__retrieve_nular_string(client::__sqf::nular__current3denoperation__ret__string);
			}
			object get3dencamera() {
				return __helpers::__retrieve_nular_object(client::__sqf::nular__get3dencamera__ret__object);
			}

			bool get3deniconsvisible() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3deniconsvisible__ret__bool);
			}

			bool get3denlinesvisible() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3denlinesvisible__ret__bool);
			}

			bool is3den() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3den__ret__bool);
			}

			bool is3denmultiplayer() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3denmultiplayer__ret__bool);
			}
			float get_3den_action_state(const std::string &value_) {
				return __helpers::__number_unary_string(client::__sqf::unary__get3denactionstate__string__ret__scalar, value_);
			}
			void edit_3den_mission_attributes(const std::string &value_) {
				__helpers::__empty_unary_string(client::__sqf::unary__edit3denmissionattributes__string__ret__nothing, value_);
			}
			bool remove_3den_layer(float value_) {
				return __helpers::__bool_unary_number(client::__sqf::unary__remove3denlayer__scalar__ret__bool, value_);
			}

			void remove_all_3den_eventhandlers(const std::string &value_) {
				__helpers::__empty_unary_string(client::__sqf::unary__removeall3deneventhandlers__string__ret__nothing, value_);
			}

			float add_3den_layer(float value0_, const std::string& value1_) {
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__add3denlayer__scalar__string__ret__scalar, value0_, value1_));
			}
    }
}
