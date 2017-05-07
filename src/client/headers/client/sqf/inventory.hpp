/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)

@brief Inventory functions.

These are used to Manipulate Player or Vehicle Inventories.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {


        struct rv_magazine_ammo {
            std::string name;
            int count;
            bool loaded;
            int type;
            std::string location;
        };

        struct rv_turret_magazine {
            std::string name;
            std::vector<int> turret_path;
            int count;
            int id;
            object creator; // player
        };
        struct rv_container {
            std::string type;
            object container;
        };

        /* potential namespace: items, inventory, campaign */
        void add_item_pool(const std::string &item_name_, int item_count_);
        void add_magazine_pool(const std::string &mag_name_, int mag_count_);
        void add_backpack_cargo(const object &vehicle_, const std::string &packClassName_, int count_);
        void add_backpack_cargo_global(const object &vehicle_, const std::string &packClassName_, int count_);
        void add_item_cargo(const object &object_, const std::string &item_, int count_);
        void add_item_cargo_global(const object &object_, const std::string &item_, int count_);
        void add_magazine(const object& obj_, const std::string& classname_, int count_);
        void add_magazine_ammo_cargo(const object& obj_, const std::string& classname_, int quantity_, int ammocount_);
        void add_magazine_cargo(const object& obj_, const std::string& classname_, int count_);
        void add_magazine_cargo_global(const object& obj_, const std::string& classname_, int count_);
        void add_magazines(const object& obj_, const std::string& classname_, int count_);
        void add_magazine_turret(const object& obj_, const std::string& classname_, const std::vector<int>& turretpath_, int ammocount_);
        void add_weapon_turret(const object& obj_, const std::string& classname_, const std::vector<int>& turretpath_);
        void add_weapon_cargo(const object& obj_, const std::string& classname_, int count_);
        void add_weapon_cargo_global(const object& obj_, const std::string& classname_, int count_);
        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_);
        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_, int ammo_count_);
        void add_weapon_item(const object& obj_, const std::string& weapon_name_, const std::string& item_name_, int ammo_count_, const std::string& muzzle_name_);
        std::vector<std::string> magazine_cargo(const object& obj_);
        std::vector<std::string> magazines(const object& obj_);
        std::vector<rv_turret_magazine> magazines_all_turrets(const object& obj_);
        std::vector<rv_magazine_ammo> magazines_ammo(const object& obj_);
        std::vector<rv_magazine_ammo> magazines_ammo_cargo(const object& obj_);
        std::vector<rv_magazine_ammo> magazines_ammo_full(const object& obj_);
        std::vector<std::string> magazines_detail(const object& obj_);
        std::vector<std::string> magazines_detail_backpack(const object& obj_);
        std::vector<std::string> magazines_detail_uniform(const object& obj_);
        std::vector<std::string> magazines_detail_vest(const object& obj_);


        std::vector<std::string> backpack_cargo(const object &box_);
        std::vector<std::string> backpack_items(const object &unit_);
        std::vector<std::string> backpack_magazines(const object &unit_);
        bool can_add(const object& obj_, const std::string& classname_);
        bool can_add(const object& obj_, const std::string& classname_, int count_);
        bool can_add_item_to_backpack(const object& obj_, const std::string& classname_);
        bool can_add_item_to_backpack(const object& obj_, const std::string& classname_, int count_);
        bool can_add_item_to_uniform(const object& obj_, const std::string& classname_);
        bool can_add_item_to_uniform(const object& obj_, const std::string& classname_, int count_);
        bool can_add_item_to_vest(const object& obj_, const std::string& classname_);
        bool can_add_item_to_vest(const object& obj_, const std::string& classname_, int count_);
        /* potential namespace: magazine, items, inventory */
        std::string current_magazine_detail(const object &veh_);


        void clear_all_items_from_backpack(const object & unit_);
        void clear_backpack_cargo(const object & box_);
        void clear_backpack_cargo_global(const object & box_);
        void clear_item_cargo(const object & box_);
        void clear_item_cargo_global(const object & box_);
        void clear_magazine_cargo(const object & veh_);
        void clear_magazine_cargo_global(const object & veh_);
        void clear_weapon_cargo(const object & veh_);
        void clear_weapon_cargo_global(const object & veh_);


        std::string handgun_magazine(const object &value_);
        std::string handgun_weapon(const object &value_);

        void remove_all_containers(const object &value_);
        void remove_all_handgun_items(const object &value_);
        void remove_all_items(const object &value_);
        void remove_all_items_with_magazines(const object &value_);
        void remove_all_primary_weapon_items(const object &value_);
        void remove_all_weapons(const object &value_);
        void remove_backpack(const object &value_);
        void remove_backpack_global(const object &value_);
        void remove_goggles(const object &value_);
        void remove_headgear(const object &value_);
        void remove_uniform(const object &value_);
        void remove_vest(const object &value_);

        std::string uniform(const object &value_);
        object uniform_container(const object &value_);
        object unit_backpack(const object &value_);
        std::string vest(const object &value_);
        object vest_container(const object &value_); //#TODO return rv_container class.. I think.
        std::string backpack(const object & unit_);
        object backpack_container(const object & unit_);

        void add_backpack(const object &value0_, const std::string& value1_);
        void add_backpack_global(const object &value0_, const std::string& value1_);
        void add_goggles(const object &value0_, const std::string& value1_);
        void add_handgun_item(const object &value0_, const std::string& value1_);
        void add_headgear(const object &value0_, const std::string& value1_);
        void add_item(const object &value0_, const std::string& value1_);
        void add_item_to_backpack(const object &value0_, const std::string& value1_);
        void add_item_to_uniform(const object &value0_, const std::string& value1_);
        void add_item_to_vest(const object &value0_, const std::string& value1_);
        void add_magazine(const object &value0_, const std::string& value1_);
        void add_magazine_global(const object &value0_, const std::string& value1_);
        void add_primary_weapon_item(const object &value0_, const std::string& value1_);
        void add_secondary_weapon_item(const object &value0_, const std::string& value1_);
        void add_uniform(const object &value0_, const std::string& value1_);
        void add_vest(const object &value0_, const std::string& value1_);
        void add_weapon(const object &value0_, const std::string& value1_);
        void add_weapon_global(const object &value0_, const std::string& value1_);

        void assign_item(const object &value0_, const std::string& value1_);
        bool has_weapon(const object &value0_, const std::string& value1_);
        void link_item(const object &value0_, const std::string& value1_);
        bool is_uniform_allowed(const object &value0_, const std::string& value1_);


        void remove_handgun_item(const object &value0_, const std::string& value1_);
        void remove_item(const object &value0_, const std::string& value1_);
        void remove_item_from_backpack(const object &value0_, const std::string& value1_);
        void remove_item_from_uniform(const object &value0_, const std::string& value1_);
        void remove_item_from_vest(const object &value0_, const std::string& value1_);
        void remove_items(const object &value0_, const std::string& value1_);
        void remove_magazine_global(const object &value0_, const std::string& value1_);
        void remove_magazines(const object &value0_, const std::string& value1_);

        void remove_primary_weapon_item(const object &value0_, const std::string& value1_);
        void remove_secondary_weapon_item(const object &value0_, const std::string& value1_);
        void remove_weapon(const object &value0_, const std::string& value1_);
        void remove_weapon_global(const object &value0_, const std::string& value1_);
        void select_weapon(const object &value0_, const std::string& value1_);
        void unassign_item(const object &value0_, const std::string& value1_);
        void unlink_item(const object &value0_, const std::string& value1_);
        std::vector<std::string> items(const object& unit_);

        struct rv_throwable {
            std::string magazine_class_name;
            std::string muzzle_class_name;
            std::vector<float> ids;
        };

        rv_throwable current_throwable(const object &unit_);



        std::vector<object> every_backpack(const object &container_);

        std::vector<rv_container> every_container(const object &container_);

        struct rv_cargo {
            std::vector<std::string> types;
            std::vector<float> amounts;
        };

        std::vector<rv_cargo> get_backpack_cargo(const object &container_);
        std::vector<rv_cargo> get_item_cargo(const object &container_);
        std::vector<rv_cargo> get_magazine_cargo(const object &container_);
        std::vector<rv_cargo> get_weapon_cargo(const object &container_);
        std::vector<std::string> item_cargo(const object &container_);
        std::vector<std::string> weapon_cargo(const object &container_);
        std::vector<std::string> weapons(const object &unit_);
        std::vector<std::string> items_with_magazines(const object &unit_);
        std::vector<std::string> primary_weapon_items(const object &unit_);
        std::vector<std::string> primary_weapon_magazine(const object &unit_);
        std::vector<std::string> secondary_weapon_items(const object &unit_);
        std::vector<std::string> secondary_weapon_magazine(const object &unit_);



        struct rv_magazine {
            std::string name;
            int ammo;

            rv_magazine(const game_value &ret_game_value_) :
                name(ret_game_value_[0]),
                ammo(ret_game_value_[1]) {}
        };

        struct rv_weapon_items {
            std::string weapon;
            std::string muzzle;
            std::string laser;
            std::string optics;
            rv_magazine magazine; //#TODO there might be two of these if grenade launcher is loaded - jonpas  | std::optional? - dedmen
            std::string bipod;

            rv_weapon_items(const game_value &ret_game_value_) :
                weapon(ret_game_value_[0]),
                muzzle(ret_game_value_[1]),
                laser(ret_game_value_[2]),
                optics(ret_game_value_[3]),
                magazine(ret_game_value_[4]),
                bipod(ret_game_value_[5]) {}
        };

        std::vector<rv_weapon_items> weapons_items(const object& obj_);
        std::vector<rv_weapon_items> weapons_items_cargo(const object& veh_);
        struct rv_handgun_items {
            std::string silencer;
            std::string laser;
            std::string optics;

            rv_handgun_items(const game_value &ret_game_value_) :
                silencer(ret_game_value_[0]),
                laser(ret_game_value_[1]),
                optics(ret_game_value_[2]) {}
        };

        rv_handgun_items handgun_items(const object& unit_);
        std::vector<std::string> soldier_magazines(const object& unit_);
        std::vector<std::string> vest_magazines(const object& unit_);
        std::vector<std::string> vest_items(const object& unit_);
        std::vector<std::string> uniform_magazines(const object& unit_);
        std::vector<std::string> uniform_items(const object& unit_);

        void remove_all_assigned_items(const object &value_);
        std::vector<std::string> assigned_items(const object &unit_);
        std::string current_magazine(const object & veh_);
        std::string current_muzzle(const object & gunner_);
        std::string current_weapon(const object & veh_);
        std::string current_weapon_mode(const object & gunner_);

        void load_magazine(const object &obj_, const std::vector<int> &turret_path_, const std::string &weapon_name_, const std::string &magazine_name_);

        struct rv_weapon_state {
            std::string weapon;
            std::string muzzle;
            std::string mode;
            std::string magazine;
            float ammo_count;

            rv_weapon_state(const game_value &ret_game_value_) :
                weapon(ret_game_value_[0]),
                muzzle(ret_game_value_[1]),
                mode(ret_game_value_[2]),
                magazine(ret_game_value_[3]),
                ammo_count(ret_game_value_[4]) {}
        };

        rv_weapon_state weapon_state(const object &unit_);
        rv_weapon_state weapon_state(const object &vehicle_, const std::vector<int> &turret_path_);

    }
}
