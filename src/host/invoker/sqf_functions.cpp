#include "sqf_functions.hpp"

using namespace intercept;
using namespace intercept::__internal;

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, gsNular* func_) :
    _type(functionType::sqf_nular), _name(func_->_name2),
    _nular(func_), _lArgType(GameDataType::NOTHING), _rArgType(GameDataType::NOTHING), _returnType(return_type_) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, gsFunction* func_) :
    _type(functionType::sqf_function), _name(func_->_name2),
    _func(func_), _lArgType(left_arg_type_), _rArgType(GameDataType::NOTHING), _returnType(return_type_) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, gsOperator* func_) :
    _type(functionType::sqf_operator), _name(func_->_name2),
    _op(func_), _lArgType(left_arg_type_), _rArgType(right_arg_type_), _returnType(return_type_) {}

template <types::GameDataType returnType>
class unusedSQFFunction {
public:
    static game_value* CDECL unusedNular(game_value* ret_, uintptr_t gs_) {
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
    static game_value* CDECL unusedFunction(game_value* ret_, uintptr_t gs_, uintptr_t larg_) {
        return unusedNular(ret_, gs_);
    }
    static game_value* CDECL unusedOperator(game_value* ret_, uintptr_t gs_, uintptr_t larg_, uintptr_t rarg_) {
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
    return;
    //switch (_type) {
    //    case functionType::sqf_nular:
    //        if (_nular && _nular->_operator)
    //            UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_nular, unusedNular);
    //        break;
    //    case functionType::sqf_function:
    //        if (_func && _func->_operator)
    //            UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_func, unusedFunction);
    //        break;
    //    case functionType::sqf_operator:
    //        if (_op && _op->_operator)
    //            UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_op, unusedOperator);
    //        break;
    //}
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

void sqf_functions::setDisabled() {
    _canRegister = false;
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

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::GameDataType return_arg_type, types::GameDataType left_arg_type, types::GameDataType right_arg_type) {
    if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::registerFunction name can maximum be 256 chars long");
    //typedef int(__thiscall *f_insert_binary)(uintptr_t gameState, const __internal::gsOperator &f);
    //f_insert_binary insertBinary = reinterpret_cast<f_insert_binary>(_registerFuncs._operator_insert);
    //
    //typedef int(__thiscall *f_construct_binary)(__internal::gsOperator* op, const op_script_type_info& returnType, const char* name, int priority, binary_function f, const op_script_type_info& lType, const op_script_type_info& rType,
    //    const char* lArgDesc, const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
    //    uintptr_t jFunc);
    //
    //
    //f_construct_binary constructBinary = reinterpret_cast<f_construct_binary>(_registerFuncs._operator_construct);

    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(left_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };
    sqf_script_type leftType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(left_arg_type)],nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(right_arg_type)],nullptr };


    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    auto test = findBinary("getvariable", GameDataType::OBJECT, GameDataType::ARRAY);

    //__internal::gsOperator op2;
    //constructBinary(&op2, retType, name.c_str(), 4, function_,
    //    leftType, rightype,
    //    "", "", description.c_str(), "", "", "", "", "Intercept", 0);

    auto operators = findOperators(std::string(name));
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    if (!operators) {
        auto table = gs->_scriptOperators.get_table_for_key(lowerName.c_str());
        auto found = _keeper.find(reinterpret_cast<uintptr_t>(table->data()));
        if (found == _keeper.end()) {
            //copy array and keep old one active so we never deallocate it and pointers into the old array stay valid
            auto_array<game_operators> backup(table->begin(), table->end());
            _keeper.insert_or_assign(reinterpret_cast<uintptr_t>(table->data()), std::move(*reinterpret_cast<auto_array<char>*>(table)));
            *table = std::move(backup);
        }

        operators = static_cast<game_operators*>(table->push_back(game_operators(lowerName.c_str())));
        operators->copyPH(test);
    } else {  //Name already exists
        if (findBinary(std::string(name), left_arg_type, right_arg_type)) return registered_sqf_function{ nullptr }; //Function with same arg types already exists
    }

    __internal::gsOperator op;
    op._name = name;
    op._name2 = lowerName;
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<binary_operator>::createSingle();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<binary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg1_type = leftType;
    op._operator->arg2_type = rightype;

    auto inserted = static_cast<__internal::gsOperator*>(operators->push_back(op));


    //insertBinary(_registerFuncs._gameState, op);

    //auto inserted = findBinary(name, left_arg_type, right_arg_type);
    //std::stringstream stream;
    LOG(INFO) << "sqf_functions::registerFunction binary " << name << " " << types::__internal::to_string(return_arg_type)
        << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
        << types::__internal::to_string(right_arg_type) << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(right_arg_type)] << " @ " << inserted << "\n";
#ifndef __linux__
   // OutputDebugStringA(stream.str().c_str());
#endif
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, left_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::GameDataType return_arg_type, types::GameDataType right_arg_type) {
    if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::registerFunction name can maximum be 256 chars long");
    //typedef int(__thiscall *f_insert_unary)(uintptr_t gameState, const __internal::gsFunction &f);
    //f_insert_unary insertUnary = reinterpret_cast<f_insert_unary>(_registerFuncs._unary_insert);
    //
    //typedef int(__thiscall *f_construct_unary)(__internal::gsFunction* op, const op_script_type_info& returnType, const char* name, unary_function f, const op_script_type_info& rType,
    //    const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
    //    uintptr_t jFunc);
    //
    //
    //
    //f_construct_unary constructUnary = reinterpret_cast<f_construct_unary>(_registerFuncs._unary_construct);

    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();
    //if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(right_arg_type)],nullptr };

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


    auto functions = findFunctions(std::string(name));
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    if (!functions) {
        auto table = gs->_scriptFunctions.get_table_for_key(lowerName.c_str());
        auto found = _keeper.find(reinterpret_cast<uintptr_t>(table->data()));
        if (found == _keeper.end()) {
            //copy array and keep old one active so we never deallocate it and pointers into the old array stay valid
            auto_array<game_functions> backup(table->begin(), table->end());
            _keeper.insert_or_assign(reinterpret_cast<uintptr_t>(table->data()), std::move(*reinterpret_cast<auto_array<char>*>(table)));
            *table = std::move(backup);
        }

        functions = static_cast<game_functions*>(table->push_back(game_functions(lowerName.c_str())));
        functions->copyPH(test);
    } else { //Name already exists
        if (findUnary(std::string(name), right_arg_type)) return registered_sqf_function{ nullptr }; //Function with same arg types already exists
    }

    __internal::gsFunction op;
    op._name = name;
    op._name2 = lowerName;
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<unary_operator>::createSingle();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<unary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg_type = rightype;

    auto inserted = static_cast<__internal::gsFunction*>(functions->push_back(op));


    //auto inserted = findUnary(name, right_arg_type); //Could use this to check if == ref returned by push_back.. But I'm just assuming it works right now
    //std::stringstream stream;
    LOG(INFO) << "sqf_functions::registerFunction unary " << name << " " << types::__internal::to_string(return_arg_type)
        << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
        << types::__internal::to_string(right_arg_type) << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(right_arg_type)] << " @ " << inserted << "\n";
#ifndef __linux__
    //OutputDebugStringA(stream.str().c_str());
#endif
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::GameDataType return_arg_type) {
    if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::registerFunction name can maximum be 256 chars long");
    //if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak();
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);


    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };

    auto test = findNular("player");
    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto alreadyExists = findNular(std::string(name));

    if (alreadyExists) {//Name already exists
        return registered_sqf_function{ nullptr };
    }

    __internal::gsNular op;
    op._name = name;
    op._name2 = lowerName; //#TODO move this into a constructor. for all types
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<nular_operator>::createSingle();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<nular_function*>(function_);
    op._operator->return_type = retType;
#ifndef __linux__
    op._category = "intercept";
#endif

    auto table = gs->_scriptNulars.get_table_for_key(lowerName.c_str());
    auto found = _keeper.find(reinterpret_cast<uintptr_t>(table->data()));
    if (found == _keeper.end()) {
        //copy array and keep old one active so we never deallocate it and pointers into the old array stay valid
        auto_array<gsNular> backup(table->begin(), table->end());
        _keeper.insert_or_assign(reinterpret_cast<uintptr_t>(table->data()), std::move(*reinterpret_cast<auto_array<char>*>(table)));
        *table = std::move(backup);
    }

    auto inserted = static_cast<__internal::gsNular*>(table->push_back(op));


    //auto inserted = findNular(name);  Could use this to confirm that inserted points to correct value
    //std::stringstream stream;
    LOG(INFO) << "sqf_functions::registerFunction nular " << name << " " << types::__internal::to_string(return_arg_type)
        << "=" << std::hex << _registerFuncs._types[static_cast<size_t>(return_arg_type)] << " "
        << " @ " << inserted << "\n";
#ifndef __linux__
    //OutputDebugStringA(stream.str().c_str());
#endif
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

bool sqf_functions::unregisterFunction(const std::shared_ptr<registered_sqf_func_wrapper>& shared) {
    if (!_canRegister) throw std::runtime_error("Can only unregister SQF Commands on preStart");
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
                table.erase(found);
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
                table.erase(found);
                return true;
            }
            return false;
        }break;
    }
    return false;
}


std::pair<types::GameDataType, sqf_script_type>  intercept::sqf_functions::registerType(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
    if (!_canRegister) throw std::runtime_error("Can only register SQF Types on preStart");
    if (name.length() > 128) throw std::length_error("intercept::sqf_functions::registerType name can maximum be 128 chars long");
    auto gs = reinterpret_cast<__internal::game_state*>(_registerFuncs._gameState);

    auto newType = rv_allocator<script_type_info>::createSingle(
    #ifdef __linux__
        name,cf,localizedName,localizedName
    #else
        name,cf,localizedName,localizedName,description,r_string("intercept"),typeName
    #endif
    );
    gs->_scriptTypes.emplace_back(newType);
    auto newIndex = _registerFuncs._types.size();
    _registerFuncs._types.emplace_back(newType);
    LOG(INFO) << "sqf_functions::registerType " << name << localizedName << description << typeName;
    types::__internal::add_game_datatype(name, static_cast<types::GameDataType>(newIndex));
    return { static_cast<types::GameDataType>(newIndex),{ _registerFuncs._type_vtable,newType,nullptr } };
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
    std::string argTypeString = types::__internal::to_string(argument_type);
    for (auto& it : *funcs) {
        auto types = it._operator->arg_type.type();
        if (types.find(argTypeString) != types.end()) {
            return &it;
        }
    }
    return nullptr;
}

intercept::__internal::gsOperator* intercept::sqf_functions::findBinary(std::string name, types::GameDataType left_argument_type, types::GameDataType right_argument_type) const {
    //gs->_scriptOperators.get_table_for_key(name.c_str())->for_each([](const game_operators& it) {
    //    OutputDebugStringA(it._name.c_str());
    //    OutputDebugStringA("\n");
    //});

    auto operators = findOperators(name);
    if (!operators) return nullptr;
    std::string left_argTypeString = types::__internal::to_string(left_argument_type);
    std::string right_argTypeString = types::__internal::to_string(right_argument_type);
    for (auto& it : *operators) {
        auto left_types = it._operator->arg1_type.type();
        if (left_types.find(left_argTypeString) != left_types.end()) {
            auto right_types = it._operator->arg2_type.type();
            if (right_types.find(right_argTypeString) != right_types.end()) {
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

