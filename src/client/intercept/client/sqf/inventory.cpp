#include "inventory.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* potential namespace: items, inventory, campaign */
        void add_item_pool(sqf_string_const_ref item_name_, int item_count_) {
            game_value params({item_name_,
                               static_cast<float>(item_count_)});

            host::functions.invoke_raw_unary(__sqf::unary__additempool__array__ret__nothing, params);
        }

        void add_magazine_pool(sqf_string_const_ref mag_name_, int mag_count_) {
            game_value params({mag_name_,
                               static_cast<float>(mag_count_)});
            host::functions.invoke_raw_unary(__sqf::unary__addmagazinepool__array__ret__nothing, params);
        }

        void add_backpack_cargo(const object &vehicle_, sqf_string_const_ref packClassName_, int count_) {
            game_value args({packClassName_,
                             static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addbackpackcargo__object__array__ret__nothing, vehicle_, args);
        }

        void add_backpack_cargo_global(const object &vehicle_, sqf_string_const_ref packClassName_, int count_) {
            game_value args({packClassName_,
                             static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addbackpackcargoglobal__object__array__ret__nothing, vehicle_, args);
        }

        void add_item_cargo(const object &object_, sqf_string_const_ref item_, int count_) {
            game_value args({item_,
                             static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__additemcargo__object__array__ret__nothing, object_, args);
        }

        void add_item_cargo_global(const object &object_, sqf_string_const_ref item_, int count_) {
            game_value args({item_,
                             static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__additemcargoglobal__object__array__ret__nothing, object_, args);
        }

        void add_magazine(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazine__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_ammo_cargo(const object &obj_, sqf_string_const_ref classname_, int quantity_, int ammocount_) {
            game_value params({classname_,
                               static_cast<float>(quantity_),
                               static_cast<float>(ammocount_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazineammocargo__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_cargo(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazinecargo__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_cargo_global(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazinecargoglobal__object__array__ret__nothing, obj_, params);
        }

        void add_magazines(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazines__object__array__ret__nothing, obj_, params);
        }

        void add_magazine_turret(const object &obj_, sqf_string_const_ref classname_, rv_turret_path turret_path_, int ammocount_) {
            game_value params({classname_,
                               std::move(turret_path_),
                               static_cast<float>(ammocount_)});

            host::functions.invoke_raw_binary(__sqf::binary__addmagazineturret__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_turret(const object &obj_, sqf_string_const_ref classname_, rv_turret_path turret_path_) {
            game_value params({classname_,
                               std::move(turret_path_)});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponturret__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_cargo(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponcargo__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_cargo_global(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponcargoglobal__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_) {
            game_value params({weapon_name_,
                               item_name_});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_, int ammo_count_) {
            game_value params({weapon_name_,
                               game_value({item_name_,
                                           static_cast<float>(ammo_count_)})});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_item(const object &obj_, sqf_string_const_ref weapon_name_, sqf_string_const_ref item_name_, int ammo_count_, sqf_string_const_ref muzzle_name_) {
            game_value params({weapon_name_,
                               game_value({item_name_,
                                           static_cast<float>(ammo_count_),
                                           muzzle_name_})});

            host::functions.invoke_raw_binary(__sqf::binary__addweaponitem__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_with_attachments_cargo(const object &obj_, const rv_weapon_items &weapons_items_, size_t count_) {
            game_value params({
                weapons_items_.operator game_value(),
                count_
            });

            host::functions.invoke_raw_binary(__sqf::binary__addweaponwithattachmentscargo__object__array__ret__nothing, obj_, params);
        }

        void add_weapon_with_attachments_cargo_global(const object &obj_, const rv_weapon_items &weapons_items_, size_t count_) {
            game_value params({
                weapons_items_.operator game_value(),
                count_
            });

            host::functions.invoke_raw_binary(__sqf::binary__addweaponwithattachmentscargoglobal__object__array__ret__nothing, obj_, params);
        }

        sqf_return_string_list magazine_cargo(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazinecargo__object__ret__array, obj_));
        }

        sqf_return_string_list magazines(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazines__object_array__ret__array, obj_));
        }

        std::vector<rv_turret_magazine> magazines_all_turrets(const object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__magazinesallturrets__object_array__ret__array, obj_);
            return __helpers::__convert_to_vector<rv_turret_magazine>(ret);
        }

        std::vector<rv_magazine_ammo> magazines_ammo(const object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__magazinesammo__object_array__ret__array, obj_);
            return __helpers::__convert_to_vector<rv_magazine_ammo>(ret);
        }

        std::vector<rv_magazine_ammo> magazines_ammo_cargo(const object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__magazinesammocargo__object__ret__array, obj_);
            return __helpers::__convert_to_vector<rv_magazine_ammo>(ret);
        }

        std::vector<rv_magazine_ammo_full> magazines_ammo_full(const object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__magazinesammofull__object_array__ret__array, obj_);
            return __helpers::__convert_to_vector<rv_magazine_ammo_full>(ret);
        }

        sqf_return_string_list magazines_detail(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazinesdetail__object_array__ret__array, obj_));
        }

        sqf_return_string_list magazines_detail_backpack(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazinesdetailbackpack__object_array__ret__array, obj_));
        }

        sqf_return_string_list magazines_detail_uniform(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazinesdetailuniform__object_array__ret__array, obj_));
        }

        sqf_return_string_list magazines_detail_vest(const object &obj_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__magazinesdetailvest__object_array__ret__array, obj_));
        }

        sqf_return_string_list backpack_cargo(const object &box_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__backpackcargo__object__ret__array, box_));
        }

        sqf_return_string_list backpack_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__backpackitems__object__ret__array, unit_));
        }

        sqf_return_string_list backpack_magazines(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__backpackmagazines__object__ret__array, unit_));
        }

        bool can_add(const object &obj_, sqf_string_const_ref classname_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadd__object__string_array__ret__bool, obj_, classname_);
        }

        bool can_add(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            return host::functions.invoke_raw_binary(__sqf::binary__canadd__object__string_array__ret__bool, obj_, params);
        }

        bool can_add(sqf_string_const_ref weapon_, sqf_string_const_ref mag_or_item_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadd__string__string_array__ret__bool, weapon_, mag_or_item_);
        }

        bool can_add(sqf_string_const_ref weapon_, sqf_string_const_ref mag_or_item_, sqf_string_const_ref muzzle_or_slot_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadd__string__string_array__ret__bool, weapon_, {mag_or_item_, muzzle_or_slot_});
        }

        bool can_add_item_to_backpack(const object &obj_, sqf_string_const_ref classname_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtobackpack__object__string_array__ret__bool, obj_, classname_);
        }

        bool can_add_item_to_backpack(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtobackpack__object__string_array__ret__bool, obj_, params);
        }

        bool can_add_item_to_uniform(const object &obj_, sqf_string_const_ref classname_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtouniform__object__string_array__ret__bool, obj_, classname_);
        }

        bool can_add_item_to_uniform(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtouniform__object__string_array__ret__bool, obj_, params);
        }

        bool can_add_item_to_vest(const object &obj_, sqf_string_const_ref classname_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtovest__object__string_array__ret__bool, obj_, classname_);
        }

        bool can_add_item_to_vest(const object &obj_, sqf_string_const_ref classname_, int count_) {
            game_value params({classname_,
                               static_cast<float>(count_)});

            return host::functions.invoke_raw_binary(__sqf::binary__canadditemtovest__object__string_array__ret__bool, obj_, params);
        }

        sqf_return_string current_magazine_detail(const object &veh_) {
            return __helpers::__string_unary_object(__sqf::unary__currentmagazinedetail__object__ret__array, veh_);
        }

        void clear_all_items_from_backpack(const object &unit_) {
            __helpers::__empty_unary_object(__sqf::unary__clearallitemsfrombackpack__object__ret__nothing, unit_);
        }

        void clear_backpack_cargo(const object &box_) {
            __helpers::__empty_unary_object(__sqf::unary__clearbackpackcargo__object__ret__nothing, box_);
        }

        void clear_backpack_cargo_global(const object &box_) {
            __helpers::__empty_unary_object(__sqf::unary__clearbackpackcargoglobal__object__ret__nothing, box_);
        }

        void clear_item_cargo(const object &box_) {
            __helpers::__empty_unary_object(__sqf::unary__clearitemcargo__object__ret__nothing, box_);
        }

        void clear_item_cargo_global(const object &box_) {
            __helpers::__empty_unary_object(__sqf::unary__clearitemcargoglobal__object__ret__nothing, box_);
        }

        void clear_magazine_cargo(const object &veh_) {
            __helpers::__empty_unary_object(__sqf::unary__clearmagazinecargo__object__ret__nothing, veh_);
        }

        void clear_magazine_cargo_global(const object &veh_) {
            __helpers::__empty_unary_object(__sqf::unary__clearmagazinecargoglobal__object__ret__nothing, veh_);
        }

        void clear_weapon_cargo(const object &veh_) {
            __helpers::__empty_unary_object(__sqf::unary__clearweaponcargo__object__ret__nothing, veh_);
        }

        void clear_weapon_cargo_global(const object &veh_) {
            __helpers::__empty_unary_object(__sqf::unary__clearweaponcargoglobal__object__ret__nothing, veh_);
        }
        sqf_return_string handgun_magazine(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__handgunmagazine__object__ret__string, value_);
        }

        sqf_return_string handgun_weapon(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__handgunweapon__object__ret__string, value_);
        }
        void remove_all_containers(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallcontainers__object__ret__nothing, value_);
        }

        void remove_all_handgun_items(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallhandgunitems__object__ret__nothing, value_);
        }

        void remove_all_items(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallitems__object__ret__nothing, value_);
        }

        void remove_all_items_with_magazines(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallitemswithmagazines__object__ret__nothing, value_);
        }
        void remove_all_primary_weapon_items(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallprimaryweaponitems__object__ret__nothing, value_);
        }

        void remove_all_weapons(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallweapons__object__ret__nothing, value_);
        }

        void remove_backpack(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removebackpack__object__ret__nothing, value_);
        }

        void remove_backpack_global(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removebackpackglobal__object__ret__nothing, value_);
        }

        void remove_goggles(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removegoggles__object__ret__nothing, value_);
        }

        void remove_headgear(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeheadgear__object__ret__nothing, value_);
        }
        void remove_uniform(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeuniform__object__ret__nothing, value_);
        }

        void remove_vest(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removevest__object__ret__nothing, value_);
        }
        sqf_return_string uniform(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__uniform__object__ret__string, value_);
        }

        object uniform_container(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__uniformcontainer__object__ret__object, value_);
        }

        object unit_backpack(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__unitbackpack__object__ret__object, value_);
        }
        sqf_return_string vest(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__vest__object__ret__string, value_);
        }

        object vest_container(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__vestcontainer__object__ret__object, value_);
        }
        sqf_return_string backpack(const object &unit_) {
            return __helpers::__string_unary_object(__sqf::unary__backpack__object__ret__string, unit_);
        }

        object backpack_container(const object &unit_) {
            return __helpers::__object_unary_object(__sqf::unary__backpackcontainer__object__ret__object, unit_);
        }

        object first_backpack(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__firstbackpack__object__ret__object, value_);
        }

        void add_backpack(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addbackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_backpack_global(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addbackpackglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_goggles(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addgoggles__object__string__ret__nothing, value0_, value1_);
        }

        void add_handgun_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addhandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_headgear(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addheadgear__object__string__ret__nothing, value0_, value1_);
        }

        void add_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__additem__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_backpack(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__additemtobackpack__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_uniform(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__additemtouniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_item_to_vest(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__additemtovest__object__string__ret__nothing, value0_, value1_);
        }

        void add_magazine(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addmagazine__object__string__ret__nothing, value0_, value1_);
        }

        void add_magazine_global(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addmagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void add_primary_weapon_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_secondary_weapon_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addsecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void add_uniform(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__adduniform__object__string__ret__nothing, value0_, value1_);
        }

        void add_vest(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addvest__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addweapon__object__string__ret__nothing, value0_, value1_);
        }

        void add_weapon_global(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addweaponglobal__object__string__ret__nothing, value0_, value1_);
        }

        void assign_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignitem__object__string__ret__nothing, value0_, value1_);
        }
        bool has_weapon(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__hasweapon__object__string__ret__bool, value0_, value1_);
        }
        void link_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__linkitem__object__string__ret__nothing, value0_, value1_);
        }
        bool is_uniform_allowed(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isuniformallowed__object__string__ret__bool, value0_, value1_);
        }
        void remove_handgun_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removehandgunitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_backpack(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeitemfrombackpack__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_uniform(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeitemfromuniform__object__string__ret__nothing, value0_, value1_);
        }

        void remove_item_from_vest(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeitemfromvest__object__string__ret__nothing, value0_, value1_);
        }

        void remove_items(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeitems__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazine_global(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemagazineglobal__object__string__ret__nothing, value0_, value1_);
        }

        void remove_magazines(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemagazines__object__string__ret__nothing, value0_, value1_);
        }

        void remove_primary_weapon_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeprimaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_secondary_weapon_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removesecondaryweaponitem__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeweapon__object__string__ret__nothing, value0_, value1_);
        }

        void remove_weapon_global(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeweaponglobal__object__string__ret__nothing, value0_, value1_);
        }
        void select_weapon(const object &unit_, sqf_string_const_ref muzzle_) {
            host::functions.invoke_raw_binary(__sqf::binary__selectweapon__object__string__ret__nothing, unit_, muzzle_);
        }

        bool select_weapon(const object &unit_, sqf_string_const_ref weapon_, sqf_string_const_ref muzzle_, sqf_string_const_ref mode_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectweapon__object__array__ret__bool_nothing, unit_, {weapon_, muzzle_, mode_});
        }

        void unassign_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__unassignitem__object__string__ret__nothing, value0_, value1_);
        }

        void unlink_item(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__unlinkitem__object__string__ret__nothing, value0_, value1_);
        }
        sqf_return_string_list items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(game_value(host::functions.invoke_raw_unary(__sqf::unary__items__object__ret__array, unit_)));
        }
        rv_throwable current_throwable(const object &unit_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__currentthrowable__object__ret__array, unit_);

            std::vector<float> ids = __helpers::__convert_to_vector<float>(ret[2]);
            return rv_throwable({ret[0], ret[1], ids});
        }
        std::vector<object> every_backpack(const object &container_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__everybackpack__object__ret__array, container_));
        }

        std::vector<rv_container> every_container(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__everycontainer__object__ret__array, container_);

            auto &arr_ret = ret.to_array();

            std::vector<rv_container> containers(arr_ret.begin(), arr_ret.end());
            return containers;
        }

        rv_cargo get_backpack_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getbackpackcargo__object__ret__array, container_);

            //ret is of format [[classnames],[amounts]]

            rv_cargo cargo;

            if (ret.size() == 2) {
                cargo.types = __helpers::__convert_to_vector<sqf_return_string>(ret[0]);
                cargo.amounts = __helpers::__convert_to_vector<float>(ret[1]);
            }

            return cargo;
        }

        rv_cargo get_item_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getitemcargo__object__ret__array, container_);

            //ret is of format [[classnames],[amounts]]

            rv_cargo cargo;

            if (ret.size() == 2) {
                cargo.types = __helpers::__convert_to_vector<sqf_return_string>(ret[0]);
                cargo.amounts = __helpers::__convert_to_vector<float>(ret[1]);
            }

            return cargo;
        }

        rv_cargo get_magazine_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getmagazinecargo__object__ret__array, container_);

            //ret is of format [[classnames],[amounts]]

            rv_cargo cargo;

            if (ret.size() == 2) {
                cargo.types = __helpers::__convert_to_vector<sqf_return_string>(ret[0]);
                cargo.amounts = __helpers::__convert_to_vector<float>(ret[1]);
            }

            return cargo;
        }

        rv_cargo get_weapon_cargo(const object &container_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getweaponcargo__object__ret__array, container_);

            //ret is of format [[classnames],[amounts]]

            rv_cargo cargo;

            if (ret.size() == 2) {
                cargo.types = __helpers::__convert_to_vector<sqf_return_string>(ret[0]);
                cargo.amounts = __helpers::__convert_to_vector<float>(ret[1]);
            }

            return cargo;
        }

        sqf_return_string_list item_cargo(const object &container_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__itemcargo__object__ret__array, container_));
        }

        sqf_return_string_list weapon_cargo(const object &container_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__weaponcargo__object__ret__array, container_));
        }
        sqf_return_string_list weapons(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__weapons__object__ret__array, unit_));
        }
        sqf_return_string_list items_with_magazines(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__itemswithmagazines__object__ret__array, unit_));
        }
        sqf_return_string_list primary_weapon_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__primaryweaponitems__object__ret__array, unit_));
        }

        sqf_return_string_list primary_weapon_magazine(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__primaryweaponmagazine__object__ret__array, unit_));
        }
        sqf_return_string_list secondary_weapon_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__secondaryweaponitems__object__ret__array, unit_));
        }

        sqf_return_string_list secondary_weapon_magazine(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__secondaryweaponmagazine__object__ret__array, unit_));
        }
        std::vector<rv_weapon_items> weapons_items(const object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__weaponsitems__object__ret__array, obj_);
            return __helpers::__convert_to_vector<rv_weapon_items>(ret);
        }

        std::vector<rv_weapon_items> weapons_items_cargo(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__weaponsitemscargo__object__ret__array, veh_);
            return __helpers::__convert_to_vector<rv_weapon_items>(ret);
        }
        rv_handgun_items handgun_items(const object &unit_) {
            return rv_handgun_items(host::functions.invoke_raw_unary(__sqf::unary__handgunitems__object__ret__array, unit_));
        }
        sqf_return_string_list soldier_magazines(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__soldiermagazines__object__ret__array, unit_));
        }
        sqf_return_string_list vest_magazines(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__vestmagazines__object__ret__array, unit_));
        }

        sqf_return_string_list vest_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__vestitems__object__ret__array, unit_));
        }
        sqf_return_string_list uniform_magazines(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__uniformmagazines__object__ret__array, unit_));
        }

        sqf_return_string_list uniform_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__uniformitems__object__ret__array, unit_));
        }
        void remove_all_assigned_items(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__removeallassigneditems__object__ret__nothing, value_);
        }
        sqf_return_string_list assigned_items(const object &unit_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__assigneditems__object__ret__array, unit_));
        }
        sqf_return_string current_magazine(const object &veh_) {
            return __helpers::__string_unary_object(__sqf::unary__currentmagazine__object__ret__string, veh_);
        }

        sqf_return_string current_muzzle(const object &gunner_) {
            return __helpers::__string_unary_object(__sqf::unary__currentmuzzle__object__ret__string, gunner_);
        }
        sqf_return_string current_weapon(const object &veh_) {
            return __helpers::__string_unary_object(__sqf::unary__currentweapon__object__ret__string, veh_);
        }

        sqf_return_string current_weapon_mode(const object &gunner_) {
            return __helpers::__string_unary_object(__sqf::unary__currentweaponmode__object__ret__string, gunner_);
        }
        void load_magazine(const object &obj_, rv_turret_path turret_path_, sqf_string_const_ref weapon_name_, sqf_string_const_ref magazine_name_) {
            game_value params({std::move(turret_path_),
                               weapon_name_,
                               magazine_name_});

            host::functions.invoke_raw_binary(__sqf::binary__loadmagazine__object__array__ret__nothing, obj_, params);
        }

        rv_unit_description get_description(const object &unit_) {
            return rv_unit_description(host::functions.invoke_raw_unary(__sqf::unary__getdescription__object__ret__array, unit_));
        }
        float load(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__load__object__ret__scalar, value_);
        }

        float load_abs(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__loadabs__object__ret__scalar, value_);
        }

        float load_backpack(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__loadbackpack__object__ret__scalar, value_);
        }
        float load_uniform(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__loaduniform__object__ret__scalar, value_);
        }

        float load_vest(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__loadvest__object__ret__scalar, value_);
        }
        sqf_return_string secondary_weapon(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__secondaryweapon__object__ret__string, value_);
        }
        sqf_return_string primary_weapon(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__primaryweapon__object__ret__string, value_);
        }
        void remove_magazine(const object &target_, sqf_string_const_ref magazine_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemagazine__object__string_array__ret__nothing, target_, magazine_);
        }
        void remove_magazines_turret(const object &target_, sqf_string_const_ref magazine_, rv_turret_path turret_path_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemagazinesturret__object__array__ret__nothing, target_, {magazine_, turret_path_ });
        }
        void remove_magazine_turret(const object &target_, sqf_string_const_ref magazine_, rv_turret_path turret_path_) {
            host::functions.invoke_raw_binary(__sqf::binary__removemagazineturret__object__array__ret__nothing, target_, {magazine_, turret_path_ });
        }
        void remove_weapon_attachment_cargo(const object &, const std::vector<game_value> &) {
            //binary__removeweaponattachmentcargo__object__array__ret__nothing
        }
        void remove_weapon_cargo(const object &, const std::vector<game_value> &) {
            //binary__removeweaponcargo__object__array__ret__nothing
        }
        void remove_weapon_turret(const object &target_, sqf_string_const_ref weapon_name_, rv_turret_path turret_path_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeweaponturret__object__array__ret__nothing, target_, {weapon_name_, turret_path_ });
        }
        void set_ammo(const object &target_, sqf_string_const_ref weapon_, int count) {
            host::functions.invoke_raw_binary(__sqf::binary__setammo__object__array__ret__nothing, target_, {weapon_, count});
        }

        game_value get_unit_loadout(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getunitloadout__object_array__ret__array, obj_);
        }
        game_value get_unit_loadout(const config &cfg_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getunitloadout__config__ret__array, cfg_);
        }
        game_value get_unit_loadout(sqf_string_const_ref cfg_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getunitloadout__string__ret__array, cfg_);
        }
        void set_unit_loadout(const object &obj_, const game_value &loadout_, bool rearm_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitloadout__object__array__ret__nothing, obj_, {loadout_, rearm_});
        }
        void set_unit_loadout(const object &obj_, const rv_unit_loadout &loadout_, bool rearm_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitloadout__object__array__ret__nothing, obj_, {static_cast<game_value>(loadout_), rearm_});
        }
        void set_unit_loadout(const object &obj_, const config &cfg_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitloadout__object__config__ret__nothing, obj_, cfg_);
        }
        void set_unit_loadout(const object &obj_, sqf_string_const_ref cfg_) {
            host::functions.invoke_raw_binary(__sqf::binary__setunitloadout__object__string__ret__nothing, obj_, cfg_);
        }
        rv_weapon_accessories weapon_accessories(const object &unit_, sqf_string_const_ref weapon_class_) {
            return rv_weapon_accessories(host::functions.invoke_raw_binary(__sqf::binary__weaponaccessories__object__string__ret__array, unit_, weapon_class_));
        }

        rv_weapon_accessories weapon_accessories_cargo(const object &container_, int weapon_id_, int creator_id_) {
            return rv_weapon_accessories(host::functions.invoke_raw_binary(__sqf::binary__weaponaccessoriescargo__object__array__ret__array, container_, {weapon_id_, creator_id_}));
        }
        sqf_return_string_list magazines_turret(const object &vehicle_, rv_turret_path turret_path_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__magazinesturret__object__array__ret__array, vehicle_, std::move(turret_path_)));
        }

        int magazine_turret_ammo(sqf_string_const_ref magazine_class_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__magazineturretammo__object__array__ret__scalar, magazine_class_, std::move(turret_path_));
        }

        void set_magazine_turret_ammo(const object &vehicle_, sqf_string_const_ref magazine_class_, int ammo_count_, rv_turret_path turret_path_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmagazineturretammo__object__array__ret__nothing, vehicle_, {magazine_class_, ammo_count_, std::move(turret_path_)});
        }
        void set_vehicle_ammo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleammo__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_ammo_def(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleammodef__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_fuel_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfuelcargo__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_repair_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrepaircargo__object__scalar__ret__nothing, value0_, value1_);
        }
        void pick_weapon_pool(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__pickweaponpool__object__ret__nothing, value_);
        }
        void put_weapon_pool(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__putweaponpool__object__ret__nothing, value_);
        }

        float query_items_pool(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__queryitemspool__string__ret__scalar, value_);
        }

        float query_magazine_pool(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__querymagazinepool__string__ret__scalar, value_);
        }

        float query_weapon_pool(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__queryweaponpool__string__ret__scalar, value_);
        }
        float ammo(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ammo__object__string__ret__scalar, value0_, value1_);
        }
        void force_add_uniform(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__forceadduniform__object__string__ret__nothing, value0_, value1_);
        }
        void set_ammo_cargo(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setammocargo__object__scalar__ret__nothing, value0_, value1_);
        }
        void add_weapon_pool(sqf_string_const_ref weapon_name_, int count_) {
            game_value params({weapon_name_,
                               static_cast<float>(count_)});

            host::functions.invoke_raw_unary(__sqf::unary__addweaponpool__array__ret__nothing, params);
        }
        sqf_return_string current_magazine_detail_turret(const object &vehicle_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__currentmagazinedetailturret__object__array__ret__string, vehicle_, std::move(turret_path_));
        }

        sqf_return_string current_magazine_turret(const object &vehicle_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__currentmagazineturret__object__array__ret__string, vehicle_, std::move(turret_path_));
        }

        sqf_return_string current_weapon_turret(const object &vehicle_, rv_turret_path turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__currentweaponturret__object__array__ret__string, vehicle_, std::move(turret_path_));
        }

        sqf_return_string_list get_artillery_ammo(const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getartilleryammo__array__ret__array, std::move(units)));
        }
        void clear_item_pool() {
            __helpers::__empty_nular(__sqf::nular__clearitempool__ret__nothing);
        }

        void clear_magazine_pool() {
            __helpers::__empty_nular(__sqf::nular__clearmagazinepool__ret__nothing);
        }

        void clear_weapon_pool() {
            __helpers::__empty_nular(__sqf::nular__clearweaponpool__ret__nothing);
        }
        sqf_return_string binocular(const object &unit_) {
            return __helpers::__string_unary_object(__sqf::unary__binocular__object__ret__string, unit_);
        }
        float gear_idcammo_count(float value_) {
            return __helpers::__number_unary_number(__sqf::unary__gearidcammocount__scalar__ret__scalar, value_);
        }
        float get_ammo_cargo(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getammocargo__object__ret__scalar, value_);
        }
        float get_fuel_cargo(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getfuelcargo__object__ret__scalar, value_);
        }
        float get_repair_cargo(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getrepaircargo__object__ret__scalar, value_);
        }
        sqf_return_string goggles(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__goggles__object__ret__string, value_);
        }
        sqf_return_string headgear(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__headgear__object__ret__string, value_);
        }
        sqf_return_string hmd(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__hmd__object__ret__string, value_);
        }

        rv_weapon_state weapon_state(const object &unit_) {
            return rv_weapon_state(host::functions.invoke_raw_unary(__sqf::unary__weaponstate__object__ret__array, unit_));
        }

        rv_weapon_state weapon_state(const object &unit_, sqf_string_const_ref muzzle_) {
            return rv_weapon_state(host::functions.invoke_raw_binary(__sqf::binary__weaponstate__object__string__ret__array, unit_, muzzle_));
        }

        rv_weapon_state weapon_state(const object &vehicle_, rv_turret_path turret_path_, std::optional<sqf_return_string> weapon_) {
            auto_array<game_value> params{vehicle_,
                                          std::move(turret_path_)};

            if (weapon_)
                params.push_back(weapon_.value());
            return rv_weapon_state(host::functions.invoke_raw_unary(__sqf::unary__weaponstate__array__ret__array, std::move(params)));
        }

        std::pair<float, float> backpack_space_for(const object &backpack_, sqf_string_const_ref weapon_) {
            auto res = host::functions.invoke_raw_binary(__sqf::binary__backpackspacefor__object__string__ret__array, backpack_, weapon_);
            return  { res[0], res[1] };
        }

        void add_binocular_item(const object &unit_, sqf_string_const_ref classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__addbinocularitem__object__string__ret__nothing, unit_, classname_);
        }

        void remove_binocular_item(const object &unit_, sqf_string_const_ref classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__removebinocularitem__object__string__ret__nothing, unit_, classname_);
        }
        
        void lock_inventory(const object &vehicle_, bool locked_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockinventory__object__bool__ret__nothing, vehicle_, locked_);
        }

        rv_weapon_accessories binocular_items(const object &unit_) {
            return rv_weapon_accessories(host::functions.invoke_raw_unary(__sqf::unary__binocularitems__object__ret__array, unit_));
        }

        sqf_return_string binocular_magazine(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__binocularmagazine__object__ret__string, unit_);
        }

        bool locked_inventory(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__lockedinventory__object__ret__bool, vehicle_);
        }

        void remove_all_binocular_items(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__removeallbinocularitems__object__ret__nothing, unit_);
        }

        void remove_all_secondary_weapon_items(const object &unit_) {
            host::functions.invoke_raw_unary(__sqf::unary__removeallsecondaryweaponitems__object__ret__nothing, unit_);
        }
    }  // namespace sqf
}  // namespace intercept
