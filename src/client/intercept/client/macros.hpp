#pragma once

#define STACK_GAMEVALUE(var_name) game_value var_name;\
var_name.__vptr = 

#define STACK_SCALAR(var_name, val)  game_value var_name;\
game_data_number var_name##_data;\
var_name.data = &var_name##_data;\
((game_data_number *)var_name##.data)->number = val

#define STACK_SCALAR_EL(tmp_name, var_name, val) game_data_number tmp_name;\
var_name##.data = &tmp_name;\
((game_data_number *)var_name##.data)->number = val

#define STACK_3DARRAY(var_name, input_vector) game_value var_name;\
game_data_array_stack var_name##_data;\
var_name.data = &var_name##_data;\
game_value var_name##_array_data[3];\
((game_data_array_stack *)var_name##.data)->length = 3;\
((game_data_array_stack *)var_name##.data)->max_size = 3;\
((game_data_array_stack *)var_name##.data)->data = var_name##_array_data;\
STACK_SCALAR_EL(var_name##_x, var_name##_array_data[0], input_vector##.x);\
STACK_SCALAR_EL(var_name##_y, var_name##_array_data[1], input_vector##.y);\
STACK_SCALAR_EL(var_name##_z, var_name##_array_data[2], input_vector##.z)