/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Wrappers for the 3den 3D editor functions.

These are wrappers for the 3den 3D editor that will be released in the next major
Arma 3 release.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/types.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* eden */
        sqf_return_string current_eden_operation();
        object get_eden_camera();
        // [showScene,showMap]
        std::pair<bool, bool> get_eden_icons_visible();
        // [showScene,showMap]
        std::pair<bool, bool> get_eden_lines_visible();
        bool is_eden();
        bool is_eden_multiplayer();
        float get_eden_action_state(sqf_string_const_ref value_);
        void edit_eden_mission_attributes(sqf_string_const_ref value_);
        float add_eden_layer(int parent_layer_id_, sqf_string_const_ref name_);
        bool remove_eden_layer(float value_);
        void remove_all_eden_eventhandlers(sqf_string_const_ref value_);
        float add_eden_event_handler(sqf_string_const_ref type_, const code &code_);
        std::vector<game_value> create_3den_composition(const config &config_path_, const vector3 &position_);                             //#TODO add Eden Entity type
        game_value create_3den_entity(sqf_string_const_ref mode_, sqf_string_const_ref class_, const vector3 &position_, bool is_empty_);  //#TODO array[] of array[string,Eden entity] and mode can only be  "Object", "Trigger", "Logic", "Waypoint" or "Marker"
        std::vector<game_value> create_3den_connections(const game_value &entity_);
        game_value get_3den_entity(const float &entity_id_);
        std::vector<game_value> get_3den_layer_entities(const float &layer_id_);
        std::vector<game_value> get_3den_selected(sqf_string_const_ref type_);
        bool set_3den_attributes(const std::vector<game_value> &entity_attributes_);
        std::vector<object> all_eden_entities();
        void do_eden_action(sqf_string_const_ref value_);
        void get_eden_grid(sqf_string_const_ref value_);
        struct rv_eden_mouse_over {
            std::string type;
            game_value entity;//#TODO make enum "Object", "Group", "Trigger", "Logic", "Waypoint" or "Marker"

            explicit rv_eden_mouse_over(const game_value &rv_game_value_)
                : type(rv_game_value_[0]),
                  entity(rv_game_value_[1]) {}
        };
        rv_eden_mouse_over get_eden_mouse_over();
        void collect_eden_history(const code &code_);
        void collect_eden_history(sqf_string_const_ref text_, sqf_string_const_ref tooltip_, sqf_string_const_ref icon_, const code &code_);
        float get_eden_entity_id(const object &entity_);
        float get_eden_entity_id(const group &entity_);
        float get_eden_entity_id(const vector3 &entity_);
        float get_eden_entity_id(const marker &entity_);
        void delete_eden_entities(const object &entity_);
        void delete_eden_entities(const group &entity_);
        void delete_eden_entities(const vector3 &entity_);
        void delete_eden_entities(const marker &entity_);

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const object &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const group &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const vector3 &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const marker &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const object &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const group &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const vector3 &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const marker &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const object &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const group &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const vector3 &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const marker &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const object &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const group &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const vector3 &to_);
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const marker &to_);

        void set_eden_grid(sqf_string_const_ref type_, float increment_);
        void set_eden_icons_visible(bool map_, bool scene_);
        void set_eden_lines_visible(bool map_, bool scene_);
        bool set_eden_mission_attributes(sqf_string_const_ref section_, sqf_string_const_ref class_, const game_value &value_);

        void remove_eden_event_handler(sqf_string_const_ref type_, float id_);
        void move_eden_camera(const vector3 &pos_, const vector3 &offset_);

        using eden_entity = game_value;
        bool remove_3den_connection(sqf_string_const_ref type_, eden_entity from_, eden_entity to_);
        //#undocumented
        bool clear_3den_attribute(const game_value &unknown_, sqf_string_const_ref attribute_);
        eden_entity create_3den_entity(const group &group_, sqf_string_const_ref mode_, sqf_string_const_ref class_, const vector3 &position_, bool is_empty = false);
        //Not fully implemented
        std::vector<game_value> get_3den_attribute(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>, sqf_string_const_ref_wrapper, std::reference_wrapper<float>> entity_, sqf_string_const_ref attribute_);
        std::vector<game_value> get_3den_attributes(const object& obj_, sqf_string_const_ref category_);
        game_value get_3den_mission_attribute(sqf_string_const_ref section_, sqf_string_const_ref class_);
        game_value get_3den_mission_attributes(sqf_string_const_ref section_, sqf_string_const_ref category_);

        bool set_3den_mission_attribute(sqf_string_const_ref section_, sqf_string_const_ref attribute_class_, game_value _attribute_value);

        //#TODO use eden_entity typedef for all https://community.bistudio.com/wiki/Special:WhatLinksHere/Eden_Entity
        bool set_3den_attribute(eden_entity entity_, sqf_string_const_ref attribute_class_, game_value _attribute_value);
        bool set_3den_layer(eden_entity entity_, float layer_);
        void set_3den_object_type(const std::vector<object> &objects_, sqf_string_const_ref classname_);

        void set_3den_selected(const std::vector<object> &entites_);

        sqf_return_string_list get_mission_layers();
        void set_3den_logic_type(const std::vector<object> &objects_, sqf_string_const_ref class_name_);
        sqf_return_string_list get_mission_layer_entities(sqf_string_const_ref layername_);

        int get_3den_layer(const object &obj_);
        object get_3den_parent(const object &obj_);

        void ignore_3den_history(const code &code_);
        bool load_3den_scenario(sqf_string_const_ref scenario_or_world_);

        bool save_3den_preferences();

        void set_3den_attached_cursor_entity(const rv_hashmap& values_);
    }  // namespace sqf
}  // namespace intercept
