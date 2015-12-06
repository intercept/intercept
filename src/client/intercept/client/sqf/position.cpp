#include "chat.hpp"
#include "client\pointers.hpp"
#include "position.hpp"

namespace intercept {
    namespace sqf {
		namespace position {
			namespace __helpers {
				vector3 get_pos_obj(unary_function fnc_, object obj_)
				{
					game_value pos = host::functions.invoke_raw_unary(fnc_, *obj_);
					float x = ((game_data_number *)((game_data_array *)pos.data)->data[0].data)->number;
					float y = ((game_data_number *)((game_data_array *)pos.data)->data[1].data)->number;
					float z = ((game_data_number *)((game_data_array *)pos.data)->data[2].data)->number;
					host::functions.free_value(&pos);
					return vector3(x, y, z);
				}
				vector3 get_pos_loc(unary_function fnc_, location loc_)
				{
					game_value pos = host::functions.invoke_raw_unary(fnc_, *loc_);
					float x = ((game_data_number *)((game_data_array *)pos.data)->data[0].data)->number;
					float y = ((game_data_number *)((game_data_array *)pos.data)->data[1].data)->number;
					float z = ((game_data_number *)((game_data_array *)pos.data)->data[2].data)->number;
					host::functions.free_value(&pos);
					return vector3(x, y, z);
				}
			}
			vector3 get_pos(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getpos__object__ret__array, obj_);
			}

			vector3 get_pos(location loc_)
			{
				return __helpers::get_pos_loc(__sqf::unary__getpos__location__ret__array, loc_);
			}

			vector3 get_pos_asl(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposasl__object__ret__array, obj_);
			}

			vector3 get_pos_atl(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposatl__object__ret__array, obj_);
			}

			vector3 get_pos_aslw(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposaslw__object__ret__array, obj_);
			}

			vector3 visible_position(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__visibleposition__object__ret__array, obj_);
			}

			vector3 visible_position_asl(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__visiblepositionasl__object__ret__array, obj_);
			}

			vector3 position(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__position__object__ret__array, obj_);
			}

			vector3 get_pos_visual(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposvisual__object__ret__array, obj_);
			}
			vector3 get_pos_asl_visual(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposaslvisual__object__ret__array, obj_);
			}

			vector3 get_pos_atl_visual(object obj_)
			{
				return __helpers::get_pos_obj(__sqf::unary__getposatlvisual__object__ret__array, obj_);
			}

			void set_pos(object obj_, vector3 pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setpos__object__array__ret__nothing, *obj_, game_value_vector3(pos_));
			}

			void set_pos_asl(object obj_, vector3 pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposasl__object__array__ret__nothing, *obj_, game_value_vector3(pos_));
			}

			void set_pos_asl2(object obj_, vector3 pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposasl2__object__array__ret__nothing, *obj_, game_value_vector3(pos_));
			}

			void set_pos_aslw(object obj_, vector3 pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposaslw__object__array__ret__nothing, *obj_, game_value_vector3(pos_));
			}

			void set_pos_atl(object obj_, vector3 pos_)
			{
				host::functions.invoke_raw_binary(__sqf::binary__setposatl__object__array__ret__nothing, *obj_, game_value_vector3(pos_));
			}
		}
    }
}


