#include "chat.hpp"
#include "client\pointers.hpp"
#include "position.hpp"

namespace intercept {
    namespace sqf {
		namespace position {
			namespace __helpers {
				vector3 get_pos_obj(unary_function fnc_, const object & obj_)
				{
					return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
				}
				vector3 get_pos_loc(unary_function fnc_, const location & loc_)
				{
                    return game_value(host::functions.invoke_raw_unary(fnc_, loc_));
				}
			}

			vector3 get_pos(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getpos__object__ret__array, obj_);
			}

			vector3 get_pos(const location & loc_)
			{
				return __helpers::get_pos_loc(__sqf::unary__getpos__location__ret__array, loc_);
			}

			vector3 get_pos_asl(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposasl__object__ret__array, obj_);
			}

			vector3 get_pos_atl(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposatl__object__ret__array, obj_);
			}

			vector3 get_pos_aslw(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposaslw__object__ret__array, obj_);
			}

			vector3 visible_position(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__visibleposition__object__ret__array, obj_);
			}

			vector3 visible_position_asl(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__visiblepositionasl__object__ret__array, obj_);
			}

			vector3 position(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__position__object__ret__array, obj_);
			}

			vector3 get_pos_visual(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposvisual__object__ret__array, obj_);
			}
			vector3 get_pos_asl_visual(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposaslvisual__object__ret__array, obj_);
			}

			vector3 get_pos_atl_visual(const object & obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposatlvisual__object__ret__array, obj_);
			}

			vector3 aim_pos(const object & obj_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__aimpos__object__ret__array, obj_));
			}

			void set_pos(const object & obj_, const vector3 & pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setpos__object__array__ret__nothing, obj_, pos_);
			}

			void set_pos_asl(const object & obj_, const vector3 & pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposasl__object__array__ret__nothing, obj_, pos_);
			}

			void set_pos_asl2(const object & obj_, const vector3 & pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposasl2__object__array__ret__nothing, obj_, pos_);
			}

			void set_pos_aslw(const object & obj_, const vector3 & pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposaslw__object__array__ret__nothing, obj_, pos_);
			}

			void set_pos_atl(const object & obj_, const vector3 & pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposatl__object__array__ret__nothing, obj_, pos_);
			}
			
			vector3 agl_to_asl(const vector3 & agl_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__agltoasl__array__ret__array, agl_));
			}

			vector3 asl_to_agl(const vector3 & asl_)
			{
                return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__asltoagl__array__ret__array, asl_));
			}

			vector3 atl_to_asl(const vector3 & atl_)
			{
                return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__atltoasl__array__ret__array, atl_));
			}
			vector3 asl_to_atl(const vector3 & asl_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__asltoatl__array__ret__array, asl_));
			}
		}
    }
}


