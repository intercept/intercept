#include "chat.hpp"
#include "client\pointers.hpp"
#include "core.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        object player() {
            game_value player_obj = host::functions.invoke_raw_nular(client::__sqf::nular__player__ret__object);
            return std::make_shared<object_ptr>(player_obj);
        }

        object create_vehicle(std::string type_, vector3 pos_)
        {
            game_value type = host::functions.new_string(type_.c_str());
            game_value obj = host::functions.invoke_raw_binary(__sqf::binary__createvehicle__string__array__ret__object, &type, game_value_vector3(pos_));
            host::functions.free_value(&type);
            return std::make_shared<object_ptr>(obj);
        }

        object create_vehicle(std::string type_, vector3 pos_, std::vector<marker> markers_ = {}, float placement_ = 0.0f, std::string special_ = "NONE")
        {
            game_value_array<5> args({
                game_value_string(type_),
                game_value_vector3(pos_),
                game_value_array_dynamic<marker, game_value_string>(markers_),
                game_value_number(placement_),
                game_value_string(special_)
            });

            return std::make_shared<object_ptr>(host::functions.invoke_raw_unary(__sqf::unary__createvehicle__array__ret__object, args));
        }

        void delete_vehicle(object obj_)
        {
            host::functions.invoke_raw_unary(__sqf::unary__deletevehicle__object__ret__nothing, *obj_);
        }

        std::vector<object>& all_3den_entities() {
            return __helpers::all_objects(client::__sqf::nular__all3denentities__ret__array);
        }

        std::vector<object>& all_curators() {
            return __helpers::all_objects(client::__sqf::nular__all3denentities__ret__array);
        }

        std::vector<object>& all_dead() {
            return __helpers::all_objects(client::__sqf::nular__alldead__ret__array);
        }

        std::vector<object>& all_deadmen() {
            return __helpers::all_objects(client::__sqf::nular__alldeadmen__ret__array);
        }

        std::vector<display>& all_displays() {
            return __helpers::all_displays(client::__sqf::nular__alldisplays__ret__array);
        }

        std::vector<group>& all_groups() {
            return __helpers::all_groups(client::__sqf::nular__allgroups__ret__array);
        }

        std::vector<marker>& all_map_markers() {
            return __helpers::all_map_markers(client::__sqf::nular__allmapmarkers__ret__array);
        }

        std::vector<object>& all_mines() {
            return __helpers::all_objects(client::__sqf::nular__allmines__ret__array);
        }

        std::vector<object>& all_players() {
            return __helpers::all_objects(client::__sqf::nular__allplayers__ret__array);
        }

        std::vector<object>& all_units() {
            return __helpers::all_objects(client::__sqf::nular__allunits__ret__array);
        }

        std::vector<object>& all_units_uav() {
            return __helpers::all_objects(client::__sqf::nular__allunitsuav__ret__array);
        }

		float server_time()
        {
			return __helpers::__retrieve_nular_number(client::__sqf::nular__servertime__ret__scalar);
        }

		std::string server_name()
        {
			return __helpers::__retrieve_nular_string(client::__sqf::nular__servername__ret__string);
        }
    }
}
