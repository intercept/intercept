#include "sqf_functions.hpp"

using namespace intercept;
using namespace intercept::__internal;
using GameDataType = types::__internal::GameDataType;

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, gsNular* func_) :
    _type(functionType::sqf_nular), _name(func_->_name2),
    _nular(func_), _lArgType(GameDataType::NOTHING), _rArgType(GameDataType::NOTHING), _returnType(return_type_) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, gsFunction* func_) :
    _type(functionType::sqf_function), _name(func_->_name2),
    _func(func_), _lArgType(left_arg_type_), _rArgType(GameDataType::NOTHING), _returnType(return_type_) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, gsOperator* func_) :
    _type(functionType::sqf_operator), _name(func_->_name2),
    _op(func_), _lArgType(left_arg_type_), _rArgType(right_arg_type_), _returnType(return_type_) {}

template <types::__internal::GameDataType returnType>
class unusedSQFFunction {
public:
    static game_value* _cdecl unusedNular(game_value* ret_, uintptr_t gs_) {
        switch (returnType) {
            case GameDataType::SCALAR:
                ::new (ret_) game_value("unimplemented");
                break;
            case GameDataType::BOOL:
                ::new (ret_) game_value(false);
                break;
            case GameDataType::ARRAY:
                ::new (ret_) game_value(std::vector<game_value>());
                break;
            case GameDataType::STRING:
                ::new (ret_) game_value("unimplemented");
                break;
            default:
                ::new (ret_) game_value();
                break;
        }
        return ret_;
    }
    static game_value* _cdecl unusedFunction(game_value* ret_, uintptr_t gs_, uintptr_t larg_) {
        return unusedNular(ret_, gs_);
    }
    static game_value* _cdecl unusedOperator(game_value* ret_, uintptr_t gs_, uintptr_t larg_, uintptr_t rarg_) {
        return unusedNular(ret_, gs_);
    }
};
#define UNUSED_FUNC_SWITCH_FOR_GAMETYPES(ptr,type) \
switch (_returnType) { \
    case GameDataType::SCALAR: \
        *ptr->_operator->procedure_addr = unusedSQFFunction<GameDataType::SCALAR>::type; \
    break; \
    case GameDataType::BOOL: \
        *ptr->_operator->procedure_addr = unusedSQFFunction<GameDataType::BOOL>::type; \
        break; \
    case GameDataType::ARRAY: \
        *ptr->_operator->procedure_addr = unusedSQFFunction<GameDataType::ARRAY>::type; \
        break; \
    case GameDataType::STRING: \
        *ptr->_operator->procedure_addr = unusedSQFFunction<GameDataType::STRING>::type; \
        break; \
    case GameDataType::OBJECT: \
        *ptr->_operator->procedure_addr = unusedSQFFunction<GameDataType::OBJECT>::type; \
        break; \
}

void registered_sqf_func_wrapper::setUnused() {
    switch (_type) {
        case functionType::sqf_nular:
            if (_nular && _nular->_operator)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_nular, unusedNular);
            break;
        case functionType::sqf_function:
            if (_func && _func->_operator)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_func, unusedFunction);
            break;
        case functionType::sqf_operator:
            if (_op && _op->_operator)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_op, unusedOperator);
            break;
    }
}

intercept::registered_sqf_function_impl::registered_sqf_function_impl(std::shared_ptr<registered_sqf_func_wrapper> func_) : _func(func_) {

}
intercept::registered_sqf_function_impl::~registered_sqf_function_impl() {
    if (sqf_functions::get()._canRegister) {
        if (sqf_functions::get().unregisterFunction(_func))
            return;
    }
    _func->setUnused();
}

registered_sqf_function::registered_sqf_function(std::shared_ptr<registered_sqf_function_impl> func_) : _function(func_) {

}

intercept::sqf_functions::sqf_functions() {}


intercept::sqf_functions::~sqf_functions() {}

void intercept::sqf_functions::initialize() {
    _registerFuncs = loader::get().get_register_sqf_info();
    _canRegister = true;
}

/*
 Dedmen
 Our Problem with registering SQF functions is that we are reallocating the Array that contains the function.
 Every compiled script compiles into Instructions. And the Instructions that call the actual engine functions keep pointers to the function
 which is inside said Array. Meaning by reallocating that Array we invalidate each pointer into it from any function that was compiled before we
 inserted our Function.

 Current workaround is by just registering our stuff before any function is compiled by overwriting
 CfgFunctions >> init
 to point to our script.

 Alternative workaround is to never deallocate the old Array and just keep it dangling.
 That way pointers into that still stay valid.
 This means however that we cannot use the Engines "InsertFunctionIntoFunctionMap" function but we don't want to use that anyway.

*/

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string name, std::string description, WrapperFunctionBinary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType left_arg_type, types::__internal::GameDataType right_arg_type) {
    //typedef int(__thiscall *f_insert_binary)(uintptr_t gameState, const __internal::gsOperator &f);
    //f_insert_binary insertBinary = reinterpret_cast<f_insert_binary>(_registerFuncs._operator_insert);
    //
    //typedef int(__thiscall *f_construct_binary)(__internal::gsOperator* op, const op_value_entry& returnType, const char* name, int priority, binary_function f, const op_value_entry& lType, const op_value_entry& rType,
    //    const char* lArgDesc, const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
    //    uintptr_t jFunc);
    //
    //
    //f_construct_binary constructBinary = reinterpret_cast<f_construct_binary>(_registerFuncs._operator_construct);

    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(left_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    sqf_script_type retType{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),nullptr };
    sqf_script_type leftType{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(left_arg_type)]),nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),nullptr };


    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    auto test = findBinary("getvariable", GameDataType::OBJECT, GameDataType::ARRAY);

    //__internal::gsOperator op2;
    //constructBinary(&op2, retType, name.c_str(), 4, function_,
    //    leftType, rightype,
    //    "", "", description.c_str(), "", "", "", "", "Intercept", 0);

    auto operators = findOperators(name);
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    if (!operators) {//Name already exists
        operators = &gs->_scriptOperators.get_table_for_key(lowerName.c_str())->push_back(game_operators(lowerName.c_str()));
        operators->copyPH(test);
    } else {
        if (findBinary(name, left_arg_type, right_arg_type)) return registered_sqf_function{ nullptr }; //Function with same arg types already exists
    }

    __internal::gsOperator op;
    op._name = name;
    op._name2 = lowerName;
    op._description = description;
    op.copyPH(test);
    op._operator = rv_allocator<binary_operator>::createSingle();
    op._operator->v_table = test->_operator->v_table;
    op._operator->ref_count = 1;
    op._operator->procedure_addr = reinterpret_cast<binary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg1_type = leftType;
    op._operator->arg2_type = rightype;

    auto inserted = &operators->push_back(op);


    //insertBinary(_registerFuncs._gameState, op);

    //auto inserted = findBinary(name, left_arg_type, right_arg_type);
    //std::stringstream stream;
    //stream << "sqf_functions::registerFunction binary " << name << " " << to_string(return_arg_type)
    //    << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
    //    << to_string(right_arg_type) << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(right_arg_type)] << " @ " << inserted << "\n";
    //OutputDebugStringA(stream.str().c_str());
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, left_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string name, std::string description, WrapperFunctionUnary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType right_arg_type) {
    //typedef int(__thiscall *f_insert_unary)(uintptr_t gameState, const __internal::gsFunction &f);
    //f_insert_unary insertUnary = reinterpret_cast<f_insert_unary>(_registerFuncs._unary_insert);
    //
    //typedef int(__thiscall *f_construct_unary)(__internal::gsFunction* op, const op_value_entry& returnType, const char* name, unary_function f, const op_value_entry& rType,
    //    const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
    //    uintptr_t jFunc);
    //
    //
    //
    //f_construct_unary constructUnary = reinterpret_cast<f_construct_unary>(_registerFuncs._unary_construct);

    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    sqf_script_type retType{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),nullptr };

    //constructUnary(&op, retType, name.c_str(), function_,
    //    rightype,
    //    "", description.c_str(), "", "", "", "", "Intercept", 0);

    auto test = findUnary("diag_log", GameDataType::ANY);
    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    //auto gs = (__internal::game_state*) _registerFuncs._gameState;
    //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    //gs->_scriptFunctions.get_table_for_key(name.c_str())->push_back(game_functions(name)).push_back(op);


    //auto tbl = gs->_scriptFunctions.get_table_for_key(name);
    //auto& funcs = gs->_scriptFunctions.get_table_for_key(lowerName.c_str())->push_back(game_functions(lowerName.c_str()));
    //funcs.push_back(op);
    //funcs.copyPH(test);
    //gs->_scriptFunctions.get_table_for_key(lowerName.c_str())->shrink_to_fit();
    //auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);
    //insertUnary(_registerFuncs._gameState, op);


    auto functions = findFunctions(name);
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    if (!functions) {
        functions = &gs->_scriptFunctions.get_table_for_key(lowerName.c_str())->push_back(game_functions(lowerName.c_str()));
        functions->copyPH(test);
    } else { //Name already exists
        if (findUnary(name, right_arg_type)) return registered_sqf_function{ nullptr }; //Function with same arg types already exists
    }

    __internal::gsFunction op;
    op._name = name;
    op._name2 = lowerName;
    op._description = description;
    op.copyPH(test);
    op._operator = rv_allocator<unary_operator>::createSingle();
    op._operator->v_table = test->_operator->v_table;
    op._operator->ref_count = 1;
    op._operator->procedure_addr = reinterpret_cast<unary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg_type = rightype;

    auto inserted = &functions->push_back(op);


    //auto inserted = findUnary(name, right_arg_type); //Could use this to check if == ref returned by push_back.. But I'm just assuming it works right now
    std::stringstream stream;
    stream << "sqf_functions::registerFunction unary " << name << " " << to_string(return_arg_type)
        << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
        << to_string(right_arg_type) << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(right_arg_type)] << " @ " << inserted << "\n";
    OutputDebugStringA(stream.str().c_str());
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string name, std::string description, WrapperFunctionNular function_, types::__internal::GameDataType return_arg_type) {

    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();

    sqf_script_type retType{ _registerFuncs._type_vtable,reinterpret_cast<value_entry*>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),nullptr };

    auto test = findNular("player");
    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto alreadyExists = findNular(name);
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    if (alreadyExists) {//Name already exists
        return registered_sqf_function{ nullptr };
    }

    __internal::gsNular op;
    op._name = name;
    op._name2 = lowerName;
    op._description = description;
    op.copyPH(test);
    op._operator = rv_allocator<nular_operator>::createSingle();
    op._operator->v_table = test->_operator->v_table;
    op._operator->ref_count = 1;
    op._operator->procedure_addr = reinterpret_cast<nular_function*>(function_);
    op._operator->return_type = retType;
    op._category = "intercept";

    auto inserted = &gs->_scriptNulars.get_table_for_key(lowerName.c_str())->push_back(op);


    //auto inserted = findNular(name);  Could use this to confirm that inserted points to correct value
    std::stringstream stream;
    stream << "sqf_functions::registerFunction nular " << name << " " << to_string(return_arg_type)
        << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
        << " @ " << inserted << "\n";
    OutputDebugStringA(stream.str().c_str());
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

bool sqf_functions::unregisterFunction(const std::shared_ptr<registered_sqf_func_wrapper>& shared) {
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);
    switch (shared->_type) {

        case functionType::sqf_nular: {
            auto table = gs->_scriptNulars.get_table_for_key(shared->_name.c_str());
            auto found = std::find_if(table->begin(), table->end(), [name = shared->_name](const gsNular& fnc)
            {
                return fnc._name2 == name;
            });
            if (found != table->end()) {
                table->erase(found);
                return true;
            }
            return false;
        }break;
        case functionType::sqf_function: {
            auto& table = gs->_scriptFunctions.get(shared->_name.c_str());
            auto found = std::find_if(table.begin(), table.end(), [name = shared->_name](const gsFunction& fnc)
            {
                return fnc._name2 == name;
            });
            if (found != table.end()) {
                table.erase(found); //#TODO remove table if empty now
                return true;
            }
            return false;
        }break;
        case functionType::sqf_operator: {
            auto& table = gs->_scriptOperators.get(shared->_name.c_str());
            auto found = std::find_if(table.begin(), table.end(), [name = shared->_name](const gsOperator& fnc)
            {
                return fnc._name2 == name;
            });
            if (found != table.end()) {
                table.erase(found); //#TODO remove table if empty now
                return true;
            }
            return false;
        }break;
    }
    return false;
}

intercept::__internal::gsNular* intercept::sqf_functions::findNular(std::string name) const {
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptNulars.get(name.c_str());
    if (gs->_scriptNulars.is_null(found)) return nullptr;
    return &found;
}

intercept::__internal::gsFunction* intercept::sqf_functions::findUnary(std::string name, GameDataType argument_type) const {
    //gs->_scriptFunctions.get_table_for_key(name.c_str())->for_each([](const game_functions& it) {
    //    OutputDebugStringA(it._name.c_str());
    //    OutputDebugStringA("\n");
    //});
    auto funcs = findFunctions(name);
    if (!funcs) return nullptr;
    std::string argTypeString = to_string(argument_type);
    for (auto& it : *funcs) {
        auto types = it._operator->arg_type.type();
        if (types.find(argTypeString) != types.end()) {
            return &it;
        }
    }
    return nullptr;
}

intercept::__internal::gsOperator* intercept::sqf_functions::findBinary(std::string name, types::__internal::GameDataType left_argument_type, types::__internal::GameDataType right_argument_type) const {
    //gs->_scriptOperators.get_table_for_key(name.c_str())->for_each([](const game_operators& it) {
    //    OutputDebugStringA(it._name.c_str());
    //    OutputDebugStringA("\n");
    //});

    auto operators = findOperators(name);
    if (!operators) return nullptr;
    std::string left_argTypeString = to_string(left_argument_type);
    std::string right_argTypeString = to_string(right_argument_type);
    for (auto& it : *operators) {
        auto left_types = it._operator->arg1_type.type();
        if (left_types.find(left_argTypeString) != left_types.end()) {
            auto right_types = it._operator->arg1_type.type();
            if (right_types.find(left_argTypeString) != right_types.end()) {
                return &it;
            }
        }
    }
    return nullptr;
}

intercept::__internal::game_operators* intercept::sqf_functions::findOperators(std::string name) const {
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptOperators.get(name.c_str());
    if (gs->_scriptOperators.is_null(found)) return nullptr;
    return &found;
}

intercept::__internal::game_functions* intercept::sqf_functions::findFunctions(std::string name) const {
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptFunctions.get(name.c_str());
    if (gs->_scriptFunctions.is_null(found)) return nullptr;
    return &found;
}

