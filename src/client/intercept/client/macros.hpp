#pragma once

/**
 *
 *
 *
 */
#define STACK_BOOL(var_name, val)  game_value var_name;\
game_data_bool var_name##_data;\
var_name.data = &var_name##_data;\
((game_data_bool *)var_name##.data)->value = val

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


#define SIMPLE_UNARY_FUNC_ANY_ANY(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_ANY_CODE(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_ANY_SCALAR(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_BOOL(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_CONFIG(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_CONTROL(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_DISPLAY(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_GROUP(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_LOCATION(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_NetObject(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_OBJECT(ptr, fnc, var)
#define SIMPLE_UNARY_FUNC_BOOL_SCALAR(ptr, fnc, var)