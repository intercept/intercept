#include "sqf_functions.hpp"
#include "signing.hpp"

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

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, gsNular* func_, undo_info undo_) :
    _type(functionType::sqf_nular), _name(func_->_name2),
    _nular(func_), _lArgType(GameDataType::NOTHING), _rArgType(GameDataType::NOTHING), _returnType(return_type_), undo(std::make_unique<undo_info>(undo_)) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, gsFunction* func_, undo_info undo_) :
    _type(functionType::sqf_function), _name(func_->_name2),
    _func(func_), _lArgType(left_arg_type_), _rArgType(GameDataType::NOTHING), _returnType(return_type_), undo(std::make_unique<undo_info>(undo_)) {}

registered_sqf_func_wrapper::registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, gsOperator* func_, undo_info undo_) :
    _type(functionType::sqf_operator), _name(func_->_name2),
    _op(func_), _lArgType(left_arg_type_), _rArgType(right_arg_type_), _returnType(return_type_), undo(std::make_unique<undo_info>(undo_)) {}


template <types::game_data_type returnType>
class unusedSQFFunction {
public:
    static game_value* CDECL unusedNular(game_value* ret_, uintptr_t gs_) {
        switch (returnType) {
            case game_data_type::SCALAR:
                ::new (ret_) game_value("unimplemented"sv);
                break;
            case game_data_type::BOOL:
                ::new (ret_) game_value(false);
                break;
            case game_data_type::ARRAY:
                ::new (ret_) game_value(std::vector<game_value>());
                break;
            case game_data_type::STRING:
                ::new (ret_) game_value("unimplemented"sv);
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

void registered_sqf_func_wrapper::setUnused() noexcept {
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

intercept::registered_sqf_function_impl::registered_sqf_function_impl(std::shared_ptr<registered_sqf_func_wrapper> func_) noexcept : _func(func_) {

}
intercept::registered_sqf_function_impl::~registered_sqf_function_impl() {
    if (sqf_functions::get()._canRegister) {
        if (sqf_functions::get().unregister_sqf_function(_func))
            return;
    }
    _func->setUnused();
}

registered_sqf_function::registered_sqf_function(std::shared_ptr<registered_sqf_function_impl> func_) noexcept : _function(func_) {

}

intercept::sqf_functions::sqf_functions() noexcept {}


intercept::sqf_functions::~sqf_functions() {}

void intercept::sqf_functions::initialize() noexcept {
    _registerFuncs = loader::get().get_register_sqf_info();
    _canRegister = true;
}

void sqf_functions::setDisabled() noexcept {
    _canRegister = false;
}

intercept::types::registered_sqf_function intercept::sqf_functions::register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type) {
    //Core plugins can overwrite existing functions. Which is "safe". So they can pass along for now.
    if (!_canRegister && intercept::cert::current_security_class != cert::signing::security_class::core) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::register_sqf_function name can maximum be 256 chars long");

    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };
    sqf_script_type leftType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(left_arg_type)],nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(right_arg_type)],nullptr };


    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    const auto test = findBinary("getvariable", game_data_type::OBJECT, game_data_type::ARRAY);

    auto operators = findOperators(std::string(name));
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);

    if (!operators) {
        auto table = gs->_scriptOperators.get_table_for_key(lowerName.c_str());
        auto found = _keeper.find(reinterpret_cast<uintptr_t>(table->data()));
        if (found == _keeper.end()) {
            //copy array and keep old one active so we never deallocate it and pointers into the old array stay valid
            auto_array<game_operators> backup(table->begin(), table->end());
            _keeper.insert_or_assign(reinterpret_cast<uintptr_t>(table->data()), std::move(*reinterpret_cast<auto_array<char>*>(table)));
            *table = std::move(backup);
        }

        operators = static_cast<game_operators*>(table->push_back(game_operators(r_string(lowerName))));
        operators->copyPH(test);
    } else {  //Name already exists


        if (auto found = findBinary(std::string(name), left_arg_type, right_arg_type); found) {//Function with same arg types already exists
            if (intercept::cert::current_security_class != cert::signing::security_class::core) return registered_sqf_function{ nullptr }; //Core certified plugins have exception for this rule

            //We only manipulate elements that are resolved at runtime.
            //This redirects a normal script command to Intercept. You can still call the original from within Intercept.

            registered_sqf_func_wrapper::undo_info undo;
            undo._procB = found->_operator->procedure_addr;
            found->_operator->procedure_addr = reinterpret_cast<binary_function*>(function_);
        #ifndef __linux__
            undo._description = found->_description;
            found->_description = description;
        #endif

            LOG(INFO, "sqf_functions::register_sqf_function binary OVERRIDE {} {} = {:x} {} = {:x} {} = {:x} @ {:x}", name,
                types::__internal::to_string(return_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),
                types::__internal::to_string(left_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(left_arg_type)]),
                types::__internal::to_string(right_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),
                reinterpret_cast<uintptr_t>(found)
            );
            auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, left_arg_type, right_arg_type, found);

            return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
        }
        if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
    }

    __internal::gsOperator op;
    op._name = name;
    op._name2 = lowerName;
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<binary_operator>::create_single();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<binary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg1_type = leftType;
    op._operator->arg2_type = rightype;

    auto inserted = static_cast<__internal::gsOperator*>(operators->push_back(op));


    //insertBinary(_registerFuncs._gameState, op);

    //auto inserted = findBinary(name, left_arg_type, right_arg_type);
    //std::stringstream stream;
    LOG(INFO, "sqf_functions::register_sqf_function binary {} {} = {:x} {} = {:x} {} = {:x} @ {:x}", name,
        types::__internal::to_string(return_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),
        types::__internal::to_string(left_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(left_arg_type)]),
        types::__internal::to_string(right_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),
        reinterpret_cast<uintptr_t>(inserted)
    );

    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, left_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::game_data_type return_arg_type, types::game_data_type right_arg_type) {
    //Core plugins can overwrite existing functions. Which is "safe". So they can pass along for now.
    if (!_canRegister && intercept::cert::current_security_class != cert::signing::security_class::core) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::register_sqf_function name can maximum be 256 chars long");

    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };
    sqf_script_type rightype{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(right_arg_type)],nullptr };


    const auto test = findUnary("diag_log", game_data_type::ANY);
    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    auto functions = findFunctions(std::string(name));
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);

    if (!functions) {
        if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
        auto table = gs->_scriptFunctions.get_table_for_key(lowerName.c_str());
        auto found = _keeper.find(reinterpret_cast<uintptr_t>(table->data()));
        if (found == _keeper.end()) {
            //copy array and keep old one active so we never deallocate it and pointers into the old array stay valid
            auto_array<game_functions> backup(table->begin(), table->end());
            _keeper.insert_or_assign(reinterpret_cast<uintptr_t>(table->data()), std::move(*reinterpret_cast<auto_array<char>*>(table)));
            *table = std::move(backup);
        }

        functions = static_cast<game_functions*>(table->push_back(game_functions(r_string(lowerName))));
        functions->copyPH(test);
    } else { //Name already exists
        if (auto found = findUnary(std::string(name), right_arg_type); found) {//Function with same arg types already exists
            if (intercept::cert::current_security_class != cert::signing::security_class::core) return registered_sqf_function{ nullptr }; //Core certified plugins have exception for this rule

            //We only manipulate elements that are resolved at runtime.
            //This redirects a normal script command to Intercept. You can still call the original from within Intercept.

            registered_sqf_func_wrapper::undo_info undo;
            undo._procU = found->_operator->procedure_addr;
            found->_operator->procedure_addr = reinterpret_cast<unary_function*>(function_);
#ifndef __linux__
            undo._description = found->_description;
            found->_description = description;
#endif

            LOG(INFO, "sqf_functions::register_sqf_function unary OVERRIDE {} {} = {:x} {} = {:x} @ {:x}", name,
                types::__internal::to_string(return_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),
                types::__internal::to_string(right_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),
                reinterpret_cast<uintptr_t>(found)
            );

            auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, right_arg_type, found, undo);

            return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
        }
        if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");
    }

    __internal::gsFunction op;
    op._name = name;
    op._name2 = lowerName;
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<unary_operator>::create_single();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<unary_function*>(function_);
    op._operator->return_type = retType;
    op._operator->arg_type = rightype;

    auto inserted = static_cast<__internal::gsFunction*>(functions->push_back(op));


    //auto inserted = findUnary(name, right_arg_type); //Could use this to check if == ref returned by push_back.. But I'm just assuming it works right now
    //std::stringstream stream;
    LOG(INFO, "sqf_functions::register_sqf_function unary {} {} = {:x} {} = {:x} @ {:x}", name,
        types::__internal::to_string(return_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]),
        types::__internal::to_string(right_arg_type), reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(right_arg_type)]),
        reinterpret_cast<uintptr_t>(inserted)
    );

    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, right_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

intercept::types::registered_sqf_function intercept::sqf_functions::register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::game_data_type return_arg_type) {
    //Core plugins can overwrite existing functions. Which is "safe". So they can pass along for now.
    if (!_canRegister && intercept::cert::current_security_class != cert::signing::security_class::core) throw std::logic_error("Can only register SQF Commands on preStart");
    if (name.length() > 256) throw std::length_error("intercept::sqf_functions::register_sqf_function name can maximum be 256 chars long");

    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);


    sqf_script_type retType{ _registerFuncs._type_vtable,_registerFuncs._types[static_cast<size_t>(return_arg_type)],nullptr };

    const auto test = findNular("player");
    std::string lowerName(name);
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    const auto alreadyExists = findNular(std::string(name));

    if (alreadyExists) {//Name already exists
        if (intercept::cert::current_security_class != cert::signing::security_class::core) return registered_sqf_function{ nullptr }; //Core certified plugins have exception for this rule
        //We only manipulate elements that are resolved at runtime.
        //This redirects a normal script command to Intercept. You can still call the original from within Intercept.

        registered_sqf_func_wrapper::undo_info undo;
        undo._procN = alreadyExists->_operator->procedure_addr;
        alreadyExists->_operator->procedure_addr = reinterpret_cast<nular_function*>(function_);
#ifndef __linux__
        undo._description = alreadyExists->_description;
        alreadyExists->_description = description;
#endif
        LOG(INFO, "sqf_functions::register_sqf_function nular OVERRIDE {} {} = {:x} @ {:x}", name, types::__internal::to_string(return_arg_type)
            , reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]), reinterpret_cast<uintptr_t>(alreadyExists)
        );
        auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, alreadyExists, undo);

        return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
    }

    if (!_canRegister) throw std::logic_error("Can only register SQF Commands on preStart");

    __internal::gsNular op;
    op._name = name;
    op._name2 = lowerName; //#TODO move this into a constructor. for all types
#ifndef __linux__
    op._description = description;
#endif
    op.copyPH(test);
    op._operator = rv_allocator<nular_operator>::create_single();
    op._operator->_vtable = test->_operator->_vtable;
    op._operator->procedure_addr = reinterpret_cast<nular_function*>(function_);
    op._operator->return_type = retType;
#ifndef __linux__
    op._category = "intercept"sv;
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
    LOG(INFO, "sqf_functions::register_sqf_function nular {} {} = {:x} @ {:x}", name, types::__internal::to_string(return_arg_type)
        , reinterpret_cast<uintptr_t>(_registerFuncs._types[static_cast<size_t>(return_arg_type)]), reinterpret_cast<uintptr_t>(inserted)
    );
    auto wrapper = std::make_shared<registered_sqf_func_wrapper>(return_arg_type, inserted);

    return registered_sqf_function(std::make_shared<registered_sqf_function_impl>(wrapper));
}

bool sqf_functions::unregister_sqf_function(const std::shared_ptr<registered_sqf_func_wrapper>& shared) {
    //Undoing a override is "safe"
    if (!_canRegister && !shared->undo) throw std::runtime_error("Can only unregister SQF Commands on preStart");

    //Handle undo's
    if (shared->undo) {
        switch (shared->_type) {
        case functionType::sqf_nular:
            shared->_nular->_operator->procedure_addr = shared->undo->_procN;
#ifndef __linux__
            shared->_nular->_description = shared->undo->_description;
#endif
            return true;
        case functionType::sqf_function:
            shared->_func->_operator->procedure_addr = shared->undo->_procU;
#ifndef __linux__
            shared->_func->_description = shared->undo->_description;
#endif
            return true;
        case functionType::sqf_operator:
            shared->_op->_operator->procedure_addr = shared->undo->_procB;
#ifndef __linux__
            shared->_op->_description = shared->undo->_description;
#endif
            return true;
        }
        return false;
    }

    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);
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


std::pair<types::game_data_type, sqf_script_type>  intercept::sqf_functions::register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
    if (!_canRegister) throw std::runtime_error("Can only register SQF Types on preStart");
    if (name.length() > 128) throw std::length_error("intercept::sqf_functions::register_sqf_type name can maximum be 128 chars long");
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);

    auto newType = rv_allocator<script_type_info>::create_single(
    #ifdef __linux__
        name,cf,localizedName,localizedName
    #else
        name,cf,localizedName,localizedName,description,r_string("intercept"sv),typeName
    #endif
    );
    gs->_scriptTypes.emplace_back(newType);
    const auto newIndex = _registerFuncs._types.size();
    _registerFuncs._types.emplace_back(newType);
    LOG(INFO, "sqf_functions::register_sqf_type {} {} {} ", name, localizedName, description, typeName);
    types::__internal::add_game_datatype(name, static_cast<types::game_data_type>(newIndex));
    return { static_cast<types::game_data_type>(newIndex),{ _registerFuncs._type_vtable,newType,nullptr } };
}

sqf_script_type sqf_functions::register_compound_sqf_type(auto_array<types::game_data_type> types) {
    if (!_canRegister) throw std::runtime_error("Can only register SQF Types on preStart");
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);

    auto_array<const script_type_info*> resolvedTypes;

    for (auto& it : types) {
        auto argTypeString = types::__internal::to_string(it);
        for (auto& type : gs->get_script_types()) {
            if (type->_name == argTypeString)
                resolvedTypes.emplace_back(type);
        }
    }

    auto newType = rv_allocator<compound_script_type_info>::create_single(
        resolvedTypes
    );

    LOG(INFO, "sqf_functions::register_compound_sqf_type");
    return {_registerFuncs._type_vtable, nullptr, newType};
}

intercept::__internal::gsNular* intercept::sqf_functions::findNular(std::string name) const {
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptNulars.get(name.c_str());
    if (gs->_scriptNulars.is_null(found)) return nullptr;
    return &found;
}

intercept::__internal::gsFunction* intercept::sqf_functions::findUnary(std::string name, game_data_type argument_type) const {
    //gs->_scriptFunctions.get_table_for_key(name.c_str())->for_each([](const game_functions& it) {
    //    OutputDebugStringA(it._name.c_str());
    //    OutputDebugStringA("\n");
    //});
    auto funcs = findFunctions(name);
    if (!funcs) return nullptr;
    auto argTypeString = types::__internal::to_string(argument_type);
    for (auto& it : *funcs) {
        auto types = it._operator->arg_type.type();
        if (types.find(argTypeString) != types.end()) {
            return &it;
        }
    }
    return nullptr;
}

intercept::__internal::gsOperator* intercept::sqf_functions::findBinary(std::string name, types::game_data_type left_argument_type, types::game_data_type right_argument_type) const {
    //gs->_scriptOperators.get_table_for_key(name.c_str())->for_each([](const game_operators& it) {
    //    OutputDebugStringA(it._name.c_str());
    //    OutputDebugStringA("\n");
    //});

    auto operators = findOperators(name);
    if (!operators) return nullptr;
    auto left_argTypeString = types::__internal::to_string(left_argument_type);
    auto right_argTypeString = types::__internal::to_string(right_argument_type);
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
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptOperators.get(name.c_str());
    if (gs->_scriptOperators.is_null(found)) return nullptr;
    return &found;
}

intercept::__internal::game_functions* intercept::sqf_functions::findFunctions(std::string name) const {
    auto gs = reinterpret_cast<game_state*>(_registerFuncs._gameState);
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    auto& found = gs->_scriptFunctions.get(name.c_str());
    if (gs->_scriptFunctions.is_null(found)) return nullptr;
    return &found;
}

