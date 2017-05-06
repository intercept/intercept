#include "eden.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* eden */
        std::string current_eden_operation() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__current3denoperation__ret__string);
        }
        object get_eden_camera() {
            return __helpers::__retrieve_nular_object(client::__sqf::nular__get3dencamera__ret__object);
        }

        bool get_eden_icons_visible() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3deniconsvisible__ret__bool);
        }

        bool get_eden_lines_visible() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__get3denlinesvisible__ret__bool);
        }

        bool is_eden() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3den__ret__bool);
        }

        bool is_eden_multiplayer() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__is3denmultiplayer__ret__bool);
        }
        float get_eden_action_state(const std::string &value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__get3denactionstate__string__ret__scalar, value_);
        }
        void edit_eden_mission_attributes(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__edit3denmissionattributes__string__ret__nothing, value_);
        }
        bool remove_eden_layer(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__remove3denlayer__scalar__ret__bool, value_);
        }

        void remove_all_eden_eventhandlers(const std::string &value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__removeall3deneventhandlers__string__ret__nothing, value_);
        }

        float add_eden_layer(int parent_layer_id_, const std::string& name_) {
            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__add3denlayer__scalar__string__ret__scalar, (float) parent_layer_id_, name_));
        }

        float add_eden_event_handler(const std::string &type_, const code &code_) {
            std::vector<game_value> params{
                type_,
                code_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3deneventhandler__array__ret__scalar, params));
        }
        std::vector<object> all_eden_entities() {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__all3denentities__ret__array));
        }
        void do_eden_action(const std::string& value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__do3denaction__string__ret__nothing, value_);
        }
        void get_eden_grid(const std::string& value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__get3dengrid__string__ret__nothing, value_);
        }
        rv_eden_mouse_over get_eden_mouse_over() {
            return rv_eden_mouse_over(host::functions.invoke_raw_nular(client::__sqf::nular__get3denmouseover__ret__array));
        }
        void collect_eden_history(const code &code_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__collect3denhistory__code__ret__nothing, code_);
        }
        float get_eden_entity_id(const object &entity_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__get3denentityid__any__ret__scalar, entity_));
        }

        float get_eden_entity_id(const group &entity_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__get3denentityid__any__ret__scalar, entity_));
        }

        float get_eden_entity_id(const vector3 &entity_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__get3denentityid__any__ret__scalar, entity_));
        }

        float get_eden_entity_id(const marker &entity_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__get3denentityid__any__ret__scalar, entity_));
        }
        void delete_eden_entities(const object &entity_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const group &entity_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const vector3 &entity_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const marker &entity_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }
        bool add_eden_connection(const std::string &type_, const std::vector<object> &from_, const object &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<object> &from_, const group &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<object> &from_, const vector3 &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<object> &from_, const marker &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<group> &from_, const object &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<group> &from_, const group &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<group> &from_, const vector3 &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<group> &from_, const marker &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<vector3> &from_, const object &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<vector3> &from_, const group &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<vector3> &from_, const vector3 &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<vector3> &from_, const marker &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<marker> &from_, const object &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<marker> &from_, const group &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<marker> &from_, const vector3 &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }

        bool add_eden_connection(const std::string &type_, const std::vector<marker> &from_, const marker &to_) {
            std::vector<game_value> from;
            for (auto entity : from_)
                from.push_back(game_value(entity));

            std::vector<game_value> params{
                type_,
                from,
                to_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__add3denconnection__array__ret__nothing, params));
        }
        void move_eden_camera(const vector3 &pos_, const vector3 &offset_) {
            std::vector<game_value> params{
                pos_,
                offset_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__move3dencamera__array__ret__nothing, params);
        }
        void remove_eden_event_handler(const std::string &type_, float id_) {
            std::vector<game_value> params{
                type_,
                id_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__remove3deneventhandler__array__ret__nothing, params);
        }
        void set_eden_grid(const std::string &type_, float increment_) {
            std::vector<game_value> params{
                type_,
                increment_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__set3dengrid__array__ret__nothing, params);
        }

        void set_eden_icons_visible(bool map_, bool scene_) {
            std::vector<game_value> params{
                map_,
                scene_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__set3deniconsvisible__array__ret__nothing, params);
        }

        void set_eden_lines_visible(bool map_, bool scene_) {
            std::vector<game_value> params{
                map_,
                scene_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__set3denlinesvisible__array__ret__nothing, params);
        }

        bool set_eden_mission_attributes(const std::string &section_, const std::string &class_, const game_value &value_) {
            std::vector<game_value> params{
                section_,
                class_,
                value_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__set3denmissionattributes__array__ret__nothing, params));
        }
        std::vector<game_value> create_3den_composition(const config &configPath_, const vector3 &position_) {
            std::vector<game_value> parameters_;
            parameters_.push_back(game_value(configPath_));
            parameters_.push_back(game_value(position_));

            auto eden_entities_ = game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__create3dencomposition__array__ret__array, parameters_));
            std::vector<game_value> output_;
            for (uint32_t i = 0; i < eden_entities_.length(); ++i) {
                output_.push_back(eden_entities_[i]);
            }
            return output_;
        }

        game_value create_3den_entity(const std::string &mode_, const std::string &class_, const vector3 &position_, bool is_empty_) {
            std::vector<game_value> parameters_;
            parameters_.push_back(game_value(mode_));
            parameters_.push_back(game_value(class_));
            parameters_.push_back(game_value(position_));
            parameters_.push_back(game_value(is_empty_));

            return game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__create3denentity__array__ret__any, parameters_));
        }

        std::vector<game_value> create_3den_connections(const game_value &entity_) {
            auto connections_ = game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__get3denconnections__any__ret__array, entity_));
            std::vector<game_value> output_;
            for (uint32_t i = 0; i < connections_.length(); ++i) {
                output_.push_back(connections_[i]);
            }
            return output_;
        }

        game_value get_3den_entity(const float &entity_id_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__get3denentity__scalar__ret__any, entity_id_));
        }

        std::vector<game_value> get_3den_layer_entities(const float &layer_id_) {
            auto entities_ = game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__get3denlayerentities__scalar__ret__array, layer_id_));
            std::vector<game_value> output_;
            for (uint32_t i = 0; i < entities_.length(); ++i) {
                output_.push_back(entities_[i]);
            }
            return output_;
        }

        std::vector<game_value> get_3den_selected(const std::string &type_) {
            auto entities_ = game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__get3denselected__string__ret__array, type_));
            std::vector<game_value> output_;
            for (uint32_t i = 0; i < entities_.length(); ++i) {
                output_.push_back(entities_[i]);
            }
            return output_;
        }

        bool set_3den_attributes(const std::vector<game_value> &entity_attributes_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::__sqf::unary__set3denattributes__array__ret__bool, entity_attributes_));
        }
    }
}
