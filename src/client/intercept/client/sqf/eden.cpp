#include "eden.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* eden */
        sqf_return_string current_eden_operation() {
            return __helpers::__retrieve_nular_string(__sqf::nular__current3denoperation__ret__string);
        }
        object get_eden_camera() {
            return __helpers::__retrieve_nular_object(__sqf::nular__get3dencamera__ret__object);
        }

        std::pair<bool, bool> get_eden_icons_visible() {
            //#TODO build a wrapper for these bool array returns
            auto ret = host::functions.invoke_raw_nular(__sqf::nular__get3deniconsvisible__ret__array);
            return {ret[0], ret[1]};
        }

        std::pair<bool, bool> get_eden_lines_visible() {
            auto ret = host::functions.invoke_raw_nular(__sqf::nular__get3denlinesvisible__ret__array);
            return {ret[0], ret[1]};
        }

        bool is_eden() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__is3den__ret__bool);
        }

        bool is_eden_multiplayer() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__is3denmultiplayer__ret__bool);
        }
        float get_eden_action_state(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__get3denactionstate__string__ret__scalar, value_);
        }
        void edit_eden_mission_attributes(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__edit3denmissionattributes__string__ret__nothing, value_);
        }
        bool remove_eden_layer(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__remove3denlayer__scalar__ret__bool, value_);
        }

        void remove_all_eden_eventhandlers(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__removeall3deneventhandlers__string__ret__nothing, value_);
        }

        float add_eden_layer(int parent_layer_id_, sqf_string_const_ref name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__add3denlayer__scalar__string__ret__scalar, static_cast<float>(parent_layer_id_), name_);
        }

        float add_eden_event_handler(sqf_string_const_ref type_, const code &code_) {
            std::vector<game_value> params{
                type_,
                code_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3deneventhandler__array__ret__scalar, params);
        }
        std::vector<object> all_eden_entities() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__all3denentities__ret__array));
        }
        void do_eden_action(sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__do3denaction__string__ret__nothing, value_);
        }
        void get_eden_grid(sqf_string_const_ref value_) {
            host::functions.invoke_raw_unary(__sqf::unary__get3dengrid__string__ret__nothing, value_);
        }
        rv_eden_mouse_over get_eden_mouse_over() {
            return rv_eden_mouse_over(host::functions.invoke_raw_nular(__sqf::nular__get3denmouseover__ret__array));
        }
        void collect_eden_history(const code &code_) {
            host::functions.invoke_raw_unary(__sqf::unary__collect3denhistory__code__ret__nothing, code_);
        }

        void collect_eden_history(sqf_string_const_ref text_, sqf_string_const_ref tooltip_, sqf_string_const_ref icon_, const code& code_) {
            host::functions.invoke_raw_binary(__sqf::binary__collect3denhistory__array__code__ret__nothing, {text_, tooltip_, icon_}, code_);
        }

        float get_eden_entity_id(const object &entity_) {
            return host::functions.invoke_raw_unary(__sqf::unary__get3denentityid__any__ret__scalar, entity_);
        }

        float get_eden_entity_id(const group &entity_) {
            return host::functions.invoke_raw_unary(__sqf::unary__get3denentityid__any__ret__scalar, entity_);
        }

        float get_eden_entity_id(const vector3 &entity_) {
            return host::functions.invoke_raw_unary(__sqf::unary__get3denentityid__any__ret__scalar, entity_);
        }

        float get_eden_entity_id(const marker &entity_) {
            return host::functions.invoke_raw_unary(__sqf::unary__get3denentityid__any__ret__scalar, entity_);
        }
        void delete_eden_entities(const object &entity_) {
            host::functions.invoke_raw_unary(__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const group &entity_) {
            host::functions.invoke_raw_unary(__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const vector3 &entity_) {
            host::functions.invoke_raw_unary(__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }

        void delete_eden_entities(const marker &entity_) {
            host::functions.invoke_raw_unary(__sqf::unary__delete3denentities__array__ret__nothing, entity_);
        }
        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const object &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const group &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const vector3 &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<object> &from_, const marker &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const object &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const group &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const vector3 &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<group> &from_, const marker &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const object &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const group &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const vector3 &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<vector3> &from_, const marker &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const object &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const group &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const vector3 &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }

        bool add_eden_connection(sqf_string_const_ref type_, const std::vector<marker> &from_, const marker &to_) {
            auto_array<game_value> from(from_.begin(), from_.end());

            std::vector<game_value> params{
                type_,
                std::move(from),
                to_};

            return host::functions.invoke_raw_unary(__sqf::unary__add3denconnection__array__ret__nothing, params);
        }
        void move_eden_camera(const vector3 &pos_, const vector3 &offset_) {
            std::vector<game_value> params{
                pos_,
                offset_};

            host::functions.invoke_raw_unary(__sqf::unary__move3dencamera__array__ret__nothing, params);
        }
        void remove_eden_event_handler(sqf_string_const_ref type_, float id_) {
            std::vector<game_value> params{
                type_,
                id_};

            host::functions.invoke_raw_unary(__sqf::unary__remove3deneventhandler__array__ret__nothing, params);
        }
        void set_eden_grid(sqf_string_const_ref type_, float increment_) {
            std::vector<game_value> params{
                type_,
                increment_};

            host::functions.invoke_raw_unary(__sqf::unary__set3dengrid__array__ret__nothing, params);
        }

        void set_eden_icons_visible(bool map_, bool scene_) {
            std::vector<game_value> params{
                map_,
                scene_};

            host::functions.invoke_raw_unary(__sqf::unary__set3deniconsvisible__array__ret__nothing, params);
        }

        void set_eden_lines_visible(bool map_, bool scene_) {
            std::vector<game_value> params{
                map_,
                scene_};

            host::functions.invoke_raw_unary(__sqf::unary__set3denlinesvisible__array__ret__nothing, params);
        }

        bool set_eden_mission_attributes(sqf_string_const_ref section_, sqf_string_const_ref class_, const game_value &value_) {
            std::vector<game_value> params{
                section_,
                class_,
                value_};

            return host::functions.invoke_raw_unary(__sqf::unary__set3denmissionattributes__array__ret__nothing, params);
        }
        std::vector<game_value> create_3den_composition(const config &configPath_, const vector3 &position_) {
            game_value parameters_({configPath_,
                                    position_});

            auto ret = host::functions.invoke_raw_unary(__sqf::unary__create3dencomposition__array__ret__array, parameters_);
            return __helpers::__convert_to_vector<game_value>(ret);
        }

        game_value create_3den_entity(sqf_string_const_ref mode_, sqf_string_const_ref class_, const vector3 &position_, bool is_empty_) {
            game_value parameters_({mode_,
                                    class_,
                                    position_,
                                    is_empty_});

            return host::functions.invoke_raw_unary(__sqf::unary__create3denentity__array__ret__any, parameters_);
        }

        std::vector<game_value> create_3den_connections(const game_value &entity_) {
            auto ret = game_value(host::functions.invoke_raw_unary(__sqf::unary__get3denconnections__any__ret__array, entity_));
            return __helpers::__convert_to_vector<game_value>(ret);
        }

        game_value get_3den_entity(const float &entity_id_) {
            return host::functions.invoke_raw_unary(__sqf::unary__get3denentity__scalar__ret__any, entity_id_);
        }

        std::vector<game_value> get_3den_layer_entities(const float &layer_id_) {
            auto ret = game_value(host::functions.invoke_raw_unary(__sqf::unary__get3denlayerentities__scalar__ret__array, layer_id_));
            return __helpers::__convert_to_vector<game_value>(ret);
        }

        std::vector<game_value> get_3den_selected(sqf_string_const_ref type_) {
            auto ret = game_value(host::functions.invoke_raw_unary(__sqf::unary__get3denselected__string__ret__array, type_));
            return __helpers::__convert_to_vector<game_value>(ret);
        }

        bool set_3den_attributes(const std::vector<game_value> &entity_attributes_) {
            return host::functions.invoke_raw_unary(__sqf::unary__set3denattributes__array__ret__bool, entity_attributes_);
        }

        bool remove_3den_connection(sqf_string_const_ref type_, eden_entity from_, eden_entity to_) {
            game_value params({type_,
                               from_,
                               to_});

            return host::functions.invoke_raw_unary(__sqf::unary__remove3denconnection__array__ret__nothing, params);
        }

        void set_3den_selected(const std::vector<object> &entites_) {
            auto_array<game_value> entities(entites_.begin(), entites_.end());

            host::functions.invoke_raw_unary(__sqf::unary__set3denselected__array__ret__nothing, std::move(entities));
        }

        void clear_3den_attribute(const game_value &unknown_, sqf_string_const_ref attribute_) {
            host::functions.invoke_raw_binary(__sqf::binary__clear3denattribute__any__string__ret__nothing, unknown_, attribute_);
        }

        eden_entity create_3den_entity(const group &group_, sqf_string_const_ref mode_, sqf_string_const_ref class_, const vector3 &position_, bool is_empty) {
            game_value params_right({mode_,
                                     class_,
                                     position_,
                                     is_empty});

            return host::functions.invoke_raw_binary(__sqf::binary__create3denentity__group__array__ret__any, group_, params_right);
        }

        std::vector<game_value> get_3den_attribute(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>, sqf_string_const_ref_wrapper, std::reference_wrapper<float>> entity_, sqf_string_const_ref attribute_) {
            switch (entity_.index()) {
                case 0: return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__get3denattribute__object__string__ret__array, std::get<0>(entity_).get(), attribute_));
                case 1: return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__get3denattribute__group__string__ret__array, std::get<1>(entity_).get(), attribute_));
                case 2: return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__get3denattribute__string__string__ret__array, std::get<2>(entity_).get(), attribute_));
                case 3: return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__get3denattribute__scalar__string__ret__array, std::get<3>(entity_).get(), attribute_));
            }
            return std::vector<game_value>();
            //#TODO: add binary__get3denattribute__array__string__ret__array
        }

        game_value get_3den_mission_attribute(sqf_string_const_ref section_, sqf_string_const_ref class_) {
            return host::functions.invoke_raw_binary(__sqf::binary__get3denmissionattribute__string__string__ret__any, section_, class_);
        }

        bool set_3den_mission_attribute(sqf_string_const_ref section_, sqf_string_const_ref attribute_class_, game_value _attribute_value) {
            return host::functions.invoke_raw_binary(__sqf::binary__set3denmissionattribute__string__array__ret__nothing, section_, {attribute_class_, std::move(_attribute_value)});
        }
        bool set_3den_attribute(eden_entity entity_, sqf_string_const_ref attribute_class_, game_value _attribute_value) {
            return host::functions.invoke_raw_binary(__sqf::binary__set3denattribute__any__array__ret__bool, entity_, {attribute_class_, std::move(_attribute_value)});
        }

        bool set_3den_layer(eden_entity entity_, float layer_) {
            return host::functions.invoke_raw_binary(__sqf::binary__set3denlayer__any__scalar__ret__bool, entity_, layer_);
        }

        void set_3den_object_type(const std::vector<object> &objects_, sqf_string_const_ref classname_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());
            host::functions.invoke_raw_binary(__sqf::binary__set3denobjecttype__array__string__ret__nothing, std::move(objects), classname_);
        }

        sqf_return_string_list get_mission_layer_entities(sqf_string_const_ref layername_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getmissionlayerentities__string_scalar__ret__array, layername_));
        }

        sqf_return_string_list get_mission_layers() {  //#TODO: Find out if this really returns sqf_return_string_list
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__getmissionlayers__ret__array));
        }

        void set_3den_logic_type(const std::vector<object> &objects_, sqf_string_const_ref class_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__set3denlogictype__array__string__ret__nothing, auto_array<game_value>(objects_.begin(), objects_.end()), class_name_);
        }
    }  // namespace sqf
}  // namespace intercept
