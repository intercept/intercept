#include "hc.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        rv_hc_group_params hc_group_params(const object &unit_, const group &group_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__hcgroupparams__object__group__ret__array, unit_, group_);

            return rv_hc_group_params({res[0], res[1][0], res[1][1], res[1][2], res[1][3]});
        }

        //#TODO: Find out about the second argument
        void hc_select_group(const object &unit, const std::vector<game_value> &array_) {
            auto_array<game_value> params_right({array_.begin(), array_.end()});

            host::functions.invoke_raw_binary(__sqf::binary__hcselectgroup__object__array__ret__nothing, unit, std::move(params_right));
        }

        //#TODO: Find out about what exactly is team_
        void hc_set_group(const object &unit_, const group &group_, std::optional<std::string> group_name_, std::optional<game_value> team_) {
            auto_array<game_value> params_right({group_});
            if (group_name_.has_value()) params_right.push_back(*group_name_);
            if (team_.has_value()) params_right.push_back(*team_);

            host::functions.invoke_raw_binary(__sqf::binary__hcsetgroup__object__array__ret__nothing, unit_, std::move(params_right));
        }

        void hc_remove_all_groups(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hcremoveallgroups__object__ret__nothing, value_);
        }

        void hc_remove_group(const object &value0_, const group &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hcremovegroup__object__group__ret__nothing, value0_, value1_);
        }

        object hc_leader(const group &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__hcleader__group__ret__object, value_));
        }

        std::vector<group> hc_selected(const object &unit_) {
            return __helpers::__convert_to_vector<group>(host::functions.invoke_raw_unary(__sqf::unary__hcselected__object__ret__array, unit_));
        }

        std::vector<group> hc_all_groups(const object &unit_) {
            return __helpers::__convert_to_vector<group>(host::functions.invoke_raw_unary(__sqf::unary__hcallgroups__object__ret__array, unit_));
        }
    }  // namespace sqf
}  // namespace intercept
