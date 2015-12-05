#include "chat.hpp"
#include "client\pointers.hpp"
#include "core.hpp"

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
    }
}
