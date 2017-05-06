#include "inventory.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* potential namespace: items, inventory, campaign */
        void add_item_pool(const std::string &item_name_, int item_count_) {
            std::vector<game_value> params{ item_name_, game_value((float) item_count_) };

            host::functions.invoke_raw_unary(client::__sqf::unary__additempool__array__ret__nothing, params);
        }

        void add_magazine_pool(const std::string &mag_name_, int mag_count_) {
            std::vector<game_value> params{ mag_name_, game_value((float) mag_count_) };
            host::functions.invoke_raw_unary(client::__sqf::unary__addmagazinepool__array__ret__nothing, params);
        }

        void add_backpack_cargo(const object & vehicle_, const std::string & packClassName_, int count_) {
            std::vector<game_value> args{
                packClassName_,
                (float) count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackcargo__object__array__ret__nothing, vehicle_, args);
        }

        void add_backpack_cargo_global(const object & vehicle_, const std::string & packClassName_, int count_) {
            std::vector<game_value> args{
                packClassName_,
                (float) count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackcargoglobal__object__array__ret__nothing, vehicle_, args);
        }

        void add_item_cargo(const object & object_, const std::string & item_, int count_) {
            std::vector<game_value> args{
                item_,
                (float) count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__additemcargo__object__array__ret__nothing, object_, args);
        }

        void add_item_cargo_global(const object & object_, const std::string & item_, int count_) {
            std::vector<game_value> args{
                item_,
                (float) count_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__additemcargoglobal__object__array__ret__nothing, object_, args);
        }

        void add_magazine(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazine__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_ammo_cargo(const object& obj_, const std::string& classname_, int quantity_, int ammocount_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) quantity_),
                game_value((float) ammocount_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazineammocargo__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_cargo(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazinecargo__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_cargo_global(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazinecargoglobal__object__array__ret__nothing, obj_, params);
        }

        void add_magazines(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazines__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_turret(const object& obj_, const std::string& classname_, const std::vector<int>& turretpath_, int ammocount_) {
            std::vector<game_value> path;
            for (int item : turretpath_) {
                path.push_back(game_value((float) item));
            }

            game_value params({
                classname_,
                path,
                (float) ammocount_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazineturret__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_turret(const object& obj_, const std::string& classname_, const std::vector<int>& turretpath_) {
            std::vector<game_value> path;
            for (int item : turretpath_) {
                path.push_back(game_value((float) item));
            }

            game_value params({
                classname_,
                path
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponturret__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_cargo(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponcargo__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_cargo_global(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params = {
                classname_,
                game_value((float) count_)
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponcargoglobal__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_) {
            game_value params({
                weapon_name_,
                item_name_
            });

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_, int ammo_count_) {
            std::vector<game_value> params = {
                weapon_name_,
                std::vector<game_value>({
                item_name_,
                game_value((float) ammo_count_)
            })
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_, int ammo_count_, const std::string& muzzle_name_) {
            std::vector<game_value> params = {
                weapon_name_,
                game_value({
                item_name_,
                game_value((float) ammo_count_),
                muzzle_name_
            })
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        std::vector<std::string> magazine_cargo(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazinecargo__object__ret__array, obj_));
        }

        std::vector<std::string> magazines(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazines__object__ret__array, obj_));
        }

        std::vector<rv_turret_magazine> magazines_all_turrets(const object& obj_) {
            game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__magazinesallturrets__object__ret__array, obj_);

            std::vector<rv_turret_magazine> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                std::vector<int> turret_path = __helpers::__convert_to_integers_vector(input[i][1]);
                output.push_back(rv_turret_magazine({ input[i][0], turret_path, input[i][2], input[i][3], input[i][4] }));
            }

            return output;
        }

        std::vector<rv_magazine_ammo> magazines_ammo(const object& obj_) {
            game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__magazinesammo__object__ret__array, obj_);

            std::vector<rv_magazine_ammo> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(rv_magazine_ammo({ input[i][0], input[i][1], false, -1, "" }));
            }

            return output;
        }

        std::vector<rv_magazine_ammo> magazines_ammo_cargo(const object& obj_) {
            game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__magazinesammocargo__object__ret__array, obj_);

            std::vector<rv_magazine_ammo> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(rv_magazine_ammo({ input[i][0], input[i][1], false, -1, "" }));
            }

            return output;
        }

        std::vector<rv_magazine_ammo> magazines_ammo_full(const object& obj_) {
            game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__magazinesammofull__object__ret__array, obj_);

            std::vector<rv_magazine_ammo> output;
            for (uint32_t i = 0; i < input.length(); ++i) {
                output.push_back(rv_magazine_ammo({ input[i][0], input[i][1], input[i][2], input[i][3], input[i][4] }));
            }

            return output;
        }

        std::vector<std::string> magazines_detail(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazinesdetail__object__ret__array, obj_));
        }

        std::vector<std::string> magazines_detail_backpack(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazinesdetailbackpack__object__ret__array, obj_));
        }

        std::vector<std::string> magazines_detail_uniform(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazinesdetailuniform__object__ret__array, obj_));
        }

        std::vector<std::string> magazines_detail_vest(const object& obj_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__magazinesdetailvest__object__ret__array, obj_));
        }

        std::vector<std::string> backpack_cargo(const object &box_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackcargo__object__ret__array, box_));
        }

        std::vector<std::string> backpack_items(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackitems__object__ret__array, unit_));
        }

        std::vector<std::string> backpack_magazines(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackmagazines__object__ret__array, unit_));
        }

        bool can_add(const object& obj_, const std::string& classname_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadd__object__string_array__ret__bool, obj_, classname_));
        }

        bool can_add(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params{
                classname_,
                (float) count_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadd__object__string_array__ret__bool, obj_, params));
        }

        bool can_add_item_to_backpack(const object& obj_, const std::string& classname_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtobackpack__object__string_array__ret__bool, obj_, classname_));
        }

        bool can_add_item_to_backpack(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params{
                classname_,
                (float) count_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtobackpack__object__string_array__ret__bool, obj_, params));
        }

        bool can_add_item_to_uniform(const object& obj_, const std::string& classname_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtouniform__object__string_array__ret__bool, obj_, classname_));
        }

        bool can_add_item_to_uniform(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params{
                classname_,
                (float) count_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtouniform__object__string_array__ret__bool, obj_, params));
        }

        bool can_add_item_to_vest(const object& obj_, const std::string& classname_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtovest__object__string_array__ret__bool, obj_, classname_));
        }

        bool can_add_item_to_vest(const object& obj_, const std::string& classname_, int count_) {
            std::vector<game_value> params{
                classname_,
                (float) count_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__canadditemtovest__object__string_array__ret__bool, obj_, params));
        }

        std::string current_magazine_detail(const object &veh_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmagazinedetail__object__ret__array, veh_);
        }

        void clear_all_items_from_backpack(const object & unit_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearallitemsfrombackpack__object__ret__nothing, unit_);
        }

        void clear_backpack_cargo(const object & box_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargo__object__ret__nothing, box_);
        }

        void clear_backpack_cargo_global(const object & box_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearbackpackcargoglobal__object__ret__nothing, box_);
        }

        void clear_item_cargo(const object & box_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargo__object__ret__nothing, box_);
        }

        void clear_item_cargo_global(const object & box_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearitemcargoglobal__object__ret__nothing, box_);
        }

        void clear_magazine_cargo(const object & veh_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargo__object__ret__nothing, veh_);
        }

        void clear_magazine_cargo_global(const object & veh_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearmagazinecargoglobal__object__ret__nothing, veh_);
        }

        void clear_weapon_cargo(const object & veh_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargo__object__ret__nothing, veh_);
        }

        void clear_weapon_cargo_global(const object & veh_) {
            __helpers::__empty_unary_object(client::__sqf::unary__clearweaponcargoglobal__object__ret__nothing, veh_);
        }
        std::string handgun_magazine(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunmagazine__object__ret__string, value_);
        }

        std::string handgun_weapon(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__handgunweapon__object__ret__string, value_);
        }
        void remove_all_containers(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallcontainers__object__ret__nothing, value_);
        }

        void remove_all_handgun_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallhandgunitems__object__ret__nothing, value_);
        }

        void remove_all_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitems__object__ret__nothing, value_);
        }

        void remove_all_items_with_magazines(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallitemswithmagazines__object__ret__nothing, value_);
        }
        void remove_all_primary_weapon_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallprimaryweaponitems__object__ret__nothing, value_);
        }

        void remove_all_weapons(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallweapons__object__ret__nothing, value_);
        }

        void remove_backpack(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpack__object__ret__nothing, value_);
        }

        void remove_backpack_global(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removebackpackglobal__object__ret__nothing, value_);
        }

        void remove_goggles(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removegoggles__object__ret__nothing, value_);
        }

        void remove_headgear(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeheadgear__object__ret__nothing, value_);
        }
        void remove_uniform(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeuniform__object__ret__nothing, value_);
        }

        void remove_vest(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removevest__object__ret__nothing, value_);
        }
        std::string uniform(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__uniform__object__ret__string, value_);
        }

        object uniform_container(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__uniformcontainer__object__ret__object, value_);
        }

        object unit_backpack(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__unitbackpack__object__ret__object, value_);
        }
        std::string vest(const object &value_) {
            return __helpers::__string_unary_object(client::__sqf::unary__vest__object__ret__string, value_);
        }

        object vest_container(const object &value_) {
            return __helpers::__object_unary_object(client::__sqf::unary__vestcontainer__object__ret__object, value_);
        }
        void add_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_backpack_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addbackpackglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_goggles(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addgoggles__object__string__ret__nothing, value0_, value1_);
        }

        void add_handgun_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addhandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_headgear(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addheadgear__object__string__ret__nothing, value0_, value1_);
        }

        void add_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additem__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtobackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtouniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__additemtovest__object__string__ret__nothing, value0_, value1_);
        }

        void add_magazine(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazine__object__string__ret__nothing, value0_, value1_);
        }

        void add_magazine_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addmagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_primary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_secondary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addsecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__adduniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addvest__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addweapon__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__addweaponglobal__object__string__ret__nothing, value0_, value1_);
        }

        void assign_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__assignitem__object__string__ret__nothing, value0_, value1_);
        }
        bool has_weapon(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__hasweapon__object__string__ret__bool, value0_, value1_));
        }
        void link_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__linkitem__object__string__ret__nothing, value0_, value1_);
        }
        bool is_uniform_allowed(const object &value0_, const std::string& value1_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__isuniformallowed__object__string__ret__bool, value0_, value1_));
        }
        void remove_handgun_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removehandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_backpack(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfrombackpack__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_uniform(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfromuniform__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_vest(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitemfromvest__object__string__ret__nothing, value0_, value1_);
        }

        void remove_items(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeitems__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazine_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazines(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removemagazines__object__string__ret__nothing, value0_, value1_);
        }


        void remove_primary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_secondary_weapon_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removesecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeweapon__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon_global(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removeweaponglobal__object__string__ret__nothing, value0_, value1_);
        }
        void select_weapon(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__selectweapon__object__string__ret__nothing, value0_, value1_);
        }
        void unassign_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__unassignitem__object__string__ret__nothing, value0_, value1_);
        }

        void unlink_item(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__unlinkitem__object__string__ret__nothing, value0_, value1_);
        }
        std::vector<std::string> items(const object& unit_) {
            return __helpers::__convert_to_strings_vector(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__items__object__ret__array, unit_)));
        }
        rv_throwable current_throwable(const object &unit_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__currentthrowable__object__ret__array, unit_);

            std::vector<float> ids = __helpers::__convert_to_numbers_vector(ret[2]);
            return rv_throwable({ ret[0], ret[1], ids });
        }
        std::vector<object> every_backpack(const object &container_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__everybackpack__object__ret__array, container_));
        }

        std::vector<rv_container> every_container(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__everycontainer__object__ret__array, container_);

            std::vector<rv_container> containers;
            for (uint32_t i = 0; i < ret.length(); ++i) {
                containers.push_back(rv_container({ ret[i][0], ret[i][1] }));
            }

            return containers;
        }

        std::vector<rv_cargo> get_backpack_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__getbackpackcargo__object__ret__array, container_);


            std::vector<rv_cargo> cargo;
            for (uint32_t i = 0; i < ret.length(); ++i) {
                std::vector<std::string> types = __helpers::__convert_to_strings_vector(ret[0][i]);
                std::vector<float> amounts = __helpers::__convert_to_numbers_vector(ret[1][i]);
                cargo.push_back(rv_cargo({ types, amounts }));
            }

            return cargo;
        }

        std::vector<rv_cargo> get_item_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__getitemcargo__object__ret__array, container_);


            std::vector<rv_cargo> cargo;
            for (uint32_t i = 0; i < ret.length(); ++i) {
                std::vector<std::string> types = __helpers::__convert_to_strings_vector(ret[0][i]);
                std::vector<float> amounts = __helpers::__convert_to_numbers_vector(ret[1][i]);
                cargo.push_back(rv_cargo({ types, amounts }));
            }

            return cargo;
        }

        std::vector<rv_cargo> get_magazine_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__getmagazinecargo__object__ret__array, container_);


            std::vector<rv_cargo> cargo;
            for (uint32_t i = 0; i < ret.length(); ++i) {
                std::vector<std::string> types = __helpers::__convert_to_strings_vector(ret[0][i]);
                std::vector<float> amounts = __helpers::__convert_to_numbers_vector(ret[1][i]);
                cargo.push_back(rv_cargo({ types, amounts }));
            }

            return cargo;
        }

        std::vector<rv_cargo> get_weapon_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__getweaponcargo__object__ret__array, container_);


            std::vector<rv_cargo> cargo;
            for (uint32_t i = 0; i < ret.length(); ++i) {
                std::vector<std::string> types = __helpers::__convert_to_strings_vector(ret[0][i]);
                std::vector<float> amounts = __helpers::__convert_to_numbers_vector(ret[1][i]);
                cargo.push_back(rv_cargo({ types, amounts }));
            }

            return cargo;
        }

        std::vector<std::string> item_cargo(const object &container_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__itemcargo__object__ret__array, container_));
        }

        std::vector<std::string> weapon_cargo(const object &container_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__weaponcargo__object__ret__array, container_));
        }
        std::vector<std::string> weapons(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__weapons__object__ret__array, unit_));
        }
        std::vector<std::string> items_with_magazines(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__itemswithmagazines__object__ret__array, unit_));
        }
        std::vector<std::string> primary_weapon_items(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__primaryweaponitems__object__ret__array, unit_));
        }

        std::vector<std::string> primary_weapon_magazine(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__primaryweaponmagazine__object__ret__array, unit_));
        }
        std::vector<std::string> secondary_weapon_items(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__secondaryweaponitems__object__ret__array, unit_));
        }

        std::vector<std::string> secondary_weapon_magazine(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__secondaryweaponmagazine__object__ret__array, unit_));
        }
        std::vector<rv_weapon_items> weapons_items(const object& obj_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__weaponsitems__object__ret__array, obj_);

            if (ret.length() == 0) {
                return {};
            } else {
                std::vector<rv_weapon_items> ret_weapon_items;
                for (uint32_t i = 0; i < ret.length(); ++i)
                    ret_weapon_items.emplace_back(ret[i]);
                return ret_weapon_items;
            }
        }

        std::vector<rv_weapon_items> weapons_items_cargo(const object& veh_) {
            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__weaponsitemscargo__object__ret__array, veh_);

            if (ret.length() == 0) {
                return {};
            } else {
                std::vector<rv_weapon_items> ret_weapon_items;
                for (uint32_t i = 0; i < ret.length(); ++i)
                    ret_weapon_items.emplace_back(ret[i]);
                return ret_weapon_items;
            }
        }
        rv_handgun_items handgun_items(const object& unit_) {
            return rv_handgun_items(host::functions.invoke_raw_unary(client::__sqf::unary__handgunitems__object__ret__array, unit_));
        }
        std::vector<std::string> soldier_magazines(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__soldiermagazines__object__ret__array, unit_));
        }
        std::vector<std::string> vest_magazines(const object& unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__vestmagazines__object__ret__array, unit_));
        }

        std::vector<std::string> vest_items(const object& unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__vestitems__object__ret__array, unit_));
        }
        std::vector<std::string> uniform_magazines(const object& unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__uniformmagazines__object__ret__array, unit_));
        }

        std::vector<std::string> uniform_items(const object& unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__uniformitems__object__ret__array, unit_));
        }
        void remove_all_assigned_items(const object &value_) {
            __helpers::__empty_unary_object(client::__sqf::unary__removeallassigneditems__object__ret__nothing, value_);
        }
        std::vector<std::string> assigned_items(const object &unit_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assigneditems__object__ret__array, unit_));
        }
        std::string current_magazine(const object & veh_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmagazine__object__ret__string, veh_);
        }

        std::string current_muzzle(const object & gunner_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentmuzzle__object__ret__string, gunner_);
        }
        std::string current_weapon(const object & veh_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweapon__object__ret__string, veh_);
        }

        std::string current_weapon_mode(const object & gunner_) {
            return __helpers::__string_unary_object(client::__sqf::unary__currentweaponmode__object__ret__string, gunner_);
        }
        void load_magazine(const object &obj_, const std::vector<int> &turret_path_, const std::string &weapon_name_, const std::string &magazine_name_) {
            std::vector<game_value> turret_path;
            for (int item : turret_path_) {
                turret_path.push_back(game_value((float) item));
            }

            std::vector<game_value> params{
                turret_path,
                weapon_name_,
                magazine_name_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__loadmagazine__object__array__ret__nothing, obj_, params);
        }
        rv_weapon_state weapon_state(const object &unit_) {
            return rv_weapon_state(host::functions.invoke_raw_unary(client::__sqf::unary__weaponstate__object_array__ret__array, unit_));
        }

        rv_weapon_state weapon_state(const object &vehicle_, const std::vector<int> &turret_path_) {
            std::vector<game_value> turret_path;
            for (auto path : turret_path_)
                turret_path.push_back((float) path);

            std::vector<game_value> params{
                vehicle_,
                turret_path
            };

            return rv_weapon_state(host::functions.invoke_raw_unary(client::__sqf::unary__weaponstate__object_array__ret__array, params));
        }
    }
}



