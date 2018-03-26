/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief High command related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* HC */
        struct rv_hc_group_params {
            std::string string;
            float f1;
            float f2;
            float f3;
            float f4;
        };

        std::vector<group> hc_selected(const object &unit_);
        std::vector<group> hc_all_groups(const object &unit_);
        void hc_remove_group(const object &value0_, const group &value1_);
        rv_hc_group_params hc_group_params(const object &unit_, const group &group_);
        void hc_select_group(const object &unit, const std::vector<game_value> &array_);
        void hc_set_group(const object &unit_, const group &group_, std::optional<std::string> group_name_, std::optional<game_value> team_);
        object hc_leader(const group &value_);
        void hc_remove_all_groups(const object &value_);
    }  // namespace sqf
}  // namespace intercept
