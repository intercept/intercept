#include "sqf_functions.hpp"

using namespace intercept;
using namespace intercept::__internal;
using GameDataType = types::__internal::GameDataType;
registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, gsNular* func_) :
    _returnType(return_type_), _type(functionType::sqf_nular), _nular(func_), _lArgType(GameDataType::NOTHING), _rArgType(types::__internal::GameDataType::NOTHING) {

}

template <types::__internal::GameDataType returnType>
class unusedSQFFunction {
public:
    static uintptr_t _cdecl unusedNular(char* ret_, uintptr_t gs_) {
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
            case GameDataType::OBJECT:
                //#TODO figure out how to create null object I guess...
                break;
        }
        return (uintptr_t)ret_;
    }
    static uintptr_t _cdecl unusedFunction(char* ret_, uintptr_t gs_, uintptr_t larg_) {
        return unusedNular(ret_, gs_);
    }
    static uintptr_t _cdecl unusedOperator(char* ret_, uintptr_t gs_, uintptr_t larg_, uintptr_t rarg_) {
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
            if (_nular)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_nular, unusedNular);
            break;
        case functionType::sqf_function:
            if (_func)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_func, unusedFunction);
            break;
        case functionType::sqf_operator:
            if (_op)
                UNUSED_FUNC_SWITCH_FOR_GAMETYPES(_op, unusedOperator);
            break;
    }
}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, gsFunction* func_) :
    _returnType(return_type_), _type(functionType::sqf_function), _func(func_), _lArgType(left_arg_type_), _rArgType(GameDataType::NOTHING) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, gsOperator* func_) :
    _returnType(return_type_), _type(functionType::sqf_operator), _op(func_), _lArgType(left_arg_type_), _rArgType(right_arg_type_) {}

intercept::registered_sqf_function_impl::registered_sqf_function_impl(std::shared_ptr<registered_sqf_func_wrapper> func_) : _func(func_) {

}
intercept::registered_sqf_function_impl::~registered_sqf_function_impl() {
    _func->setUnused();
}

registered_sqf_function::registered_sqf_function(std::shared_ptr<registered_sqf_function_impl> func_) : _function(func_) {

}

intercept::sqf_functions::sqf_functions() {}


intercept::sqf_functions::~sqf_functions() {}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string name, std::string description, WrapperFunctionBinary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType left_arg_type, types::__internal::GameDataType right_arg_type) {
    //#TODO max length of name is 22 chars... Somehow.. Need to investigate why
    //#TODO check if name already exists. If we assigned that overwrite it except it has a Final flag (Add Final flag)
    typedef int(__thiscall *f_insert_binary)(uintptr_t gameState, const __internal::gsOperator &f);
    f_insert_binary insertBinary = reinterpret_cast<f_insert_binary>(_registerFuncs._operator_insert);

    typedef int(__thiscall *f_construct_binary)(__internal::gsOperator* op, uintptr_t returnType, const char* name, int priority, binary_function f, uintptr_t lType, uintptr_t rType,
        const char* lArgDesc, const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
        uintptr_t jFunc);
    __internal::gsOperator op;

    f_construct_binary constructBinary = reinterpret_cast<f_construct_binary>(_registerFuncs._operator_construct);

    if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak(); //#TODO remove when registerFunction with unsupported type throws compiler error
    if (_registerFuncs._types[static_cast<size_t>(left_arg_type)] == 0) __debugbreak();   //and all supported types are implemented
    if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    constructBinary(&op, _registerFuncs._types[(size_t) return_arg_type], name.c_str(), 4, function_,
        _registerFuncs._types[(size_t) left_arg_type], _registerFuncs._types[(size_t) right_arg_type],
        "", "", "", "", "", "", "", "Intercept", 0);
    insertBinary(_registerFuncs._gameState, op);

    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, left_arg_type, right_arg_type, nullptr); //#TODO lookup inserted record and give that instead of nullptr

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::registerFunction(std::string name, std::string description, WrapperFunctionUnary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType right_arg_type) {
    typedef int(__thiscall *f_insert_unary)(uintptr_t gameState, const __internal::gsFunction &f);
    f_insert_unary insertBinary = reinterpret_cast<f_insert_unary>(_registerFuncs._unary_insert);

    typedef int(__thiscall *f_construct_unary)(__internal::gsFunction* op, uintptr_t returnType, const char* name, unary_function f, uintptr_t rType,
        const char* rArgDesc, const char* desc, const char* example, const char* exampleReturn, const char* unk1, const char* unk2, const char* def,
        uintptr_t jFunc);
    __internal::gsFunction op;

    f_construct_unary constructUnary = reinterpret_cast<f_construct_unary>(_registerFuncs._unary_construct);

    if (_registerFuncs._types[static_cast<size_t>(return_arg_type)] == 0) __debugbreak(); //#TODO remove when registerFunction with unsupported type throws compiler error
    if (_registerFuncs._types[static_cast<size_t>(right_arg_type)] == 0) __debugbreak();

    constructUnary(&op, _registerFuncs._types[static_cast<size_t>(return_arg_type)], name.c_str(), function_,
        _registerFuncs._types[static_cast<size_t>(right_arg_type)],
        "", "", "", "", "", "", "Intercept", 0);
    insertBinary(_registerFuncs._gameState, op);

    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, right_arg_type, nullptr); //#TODO lookup inserted record and give that instead of nullptr

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

void intercept::sqf_functions::initialize() {
    //#TODO _initialized variable
    _registerFuncs = loader::get().get_register_sqf_info();
}


