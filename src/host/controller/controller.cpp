#include "controller.hpp"
#include "invoker.hpp"
#include "loader.hpp"
#include "extensions.hpp"

#include <regex>
#include <chrono>

#ifdef _DEBUG
#define DEBUG_DISPATCH(x, y) { std::string empty; _debug_display->call(x, arguments(y), empty); }
#else
#define DEBUG_DISPATCH(x, y)
#endif

namespace intercept {
    controller::controller() : threaded_dispatcher() {
        _initiated = false;
        add("init"sv, std::bind(&intercept::controller::init, this, std::placeholders::_1, std::placeholders::_2));
        add("reset"sv, std::bind(&intercept::controller::reset, this, std::placeholders::_1, std::placeholders::_2));
        add("ready"sv, std::bind(&intercept::controller::get_ready, this, std::placeholders::_1, std::placeholders::_2));
        add("stop"sv, std::bind(&controller::do_stop, this, std::placeholders::_1, std::placeholders::_2));
        add("export_ptr_list"sv, std::bind(&controller::export_ptr_list, this, std::placeholders::_1, std::placeholders::_2));
        // action results
        add("fetch_result"sv, std::bind(&intercept::controller::fetch_result, this, std::placeholders::_1, std::placeholders::_2));
    }

    bool controller::init(const arguments &, std::string & result_) {
        if (!_initiated) {
            //loader::get().attach_controller(); // no longer needed, as the loader is called directly once.
            invoker::get().attach_controller();
            extensions::get().attach_controller();
            result_ = "1";
            _initiated = true;
        }
        return true;
    }

    bool controller::get_ready(const arguments &, std::string & result_) const {
        result_ = "0";

        if (!_ready)
            result_ = "-1";

        return true;
    }

    bool controller::reset(const arguments &, std::string & ) {
        _ready = false;


        { 
            std::lock_guard<std::mutex> lock_results(_results_lock);

            while (!_results.empty()) {
                _results.pop();
            }

            while (!_messages.empty()) {
                _messages.pop();
            }
        }

        _ready = true;

        return true;
    }

    bool controller::fetch_result(const arguments &, std::string & result_) {
        result_ = "";
        if (!_results.empty()) {
            std::lock_guard<std::mutex> _lock(_results_lock);
            dispatch_result res = _results.front();
            std::stringstream ss;
            ss << "[" << res.id << ",[" << res.message << "]]";
            result_ = ss.str();
            _results.pop();
        }
        return true;
    }

    bool controller::export_ptr_list(const arguments &args_, std::string &) const {
        std::ofstream pointers("sqf_pointers_declaration.hpp");
        std::ofstream pointers_def("sqf_pointers_definitions.hpp");

        std::ofstream assignments("sqf_assignments.hpp");
        pointers << "//Exported Pointer Definitions For: "sv << args_.as_string(0) << "\n\n";
        assignments << "//Exported Pointer Assignments For: "sv << args_.as_string(0) << "\n\n";

        pointers << "\n// Unary Functions\n"sv;
        pointers_def << "\n// Unary Functions\n"sv;

        assignments << "\n// Unary Functions\n"sv;

        auto unary_list = loader::get().unary();
        std::vector<r_string> sorted_unary_list;//#TODO just keep iterators and only sort the iterators. That way we don't need map lookups later
        sorted_unary_list.reserve(unary_list.size());
        for (const auto &unary : unary_list) {
            sorted_unary_list.push_back(unary.first);
        }
        std::sort(sorted_unary_list.begin(), sorted_unary_list.end());

        for (const auto &op_name : sorted_unary_list) {
            std::regex name_test = std::regex("[a-z]+?.*");
            if (std::regex_match(static_cast<std::string>(op_name), name_test)) {
                for (auto op : unary_list[op_name]) {
                    auto arg_types = op.op->arg_type.type_str();
                    arg_types.to_lower();
                    auto return_type = op.op->return_type.type_str();
                    return_type.to_lower();
                    auto first_arg_type = *op.op->arg_type.type().begin();
                    auto pointer_name = "unary__" + op_name + "__" + arg_types + "__ret__" + return_type;
                    pointers_def << "unary_function __sqf::"sv << pointer_name << ";\n";
                    pointers << "static unary_function "sv << pointer_name << ";\n";
                    //__sqf::unary_random_scalar_raw = (unary_function)functions.get_unary_function_typed("random", "SCALAR");
                    assignments << "__sqf::"sv << pointer_name << " = " << "(unary_function)host::functions.get_unary_function_typed(\""sv << op_name << "\"sv, \"" << first_arg_type << "\"sv);\n"sv;
                }
            }
        }

        pointers << "\n// Binary Functions\n"sv;
        pointers_def << "\n// Binary Functions\n"sv;

        assignments << "\n// Binary Functions\n"sv;

        auto binary_list = loader::get().binary();
        std::vector<r_string> sorted_binary_list;
        sorted_binary_list.reserve(binary_list.size());
        for (const auto &binary : binary_list) {
            sorted_binary_list.push_back(binary.first);
        }
        std::sort(sorted_binary_list.begin(), sorted_binary_list.end());

        for (auto& op_name : sorted_binary_list) {
            std::regex name_test = std::regex("[a-z]+?.*");
            if (std::regex_match(static_cast<std::string>(op_name), name_test)) {
                for (auto op : binary_list[op_name]) {
                    auto arg1_types = op.op->arg1_type.type_str();
                    arg1_types.to_lower();
                    auto arg2_types = op.op->arg2_type.type_str();
                    arg2_types.to_lower();

                    auto return_type = op.op->return_type.type_str();
                    return_type.to_lower();

                    auto first_arg1_type = *op.op->arg1_type.type().begin();
                    auto first_arg2_type = *op.op->arg2_type.type().begin();

                    auto pointer_name = "binary__" + op_name + "__" + arg1_types + "__" + arg2_types + "__ret__" + return_type;
                    pointers_def << "binary_function __sqf::"sv << pointer_name << ";\n"sv;
                    pointers << "static binary_function "sv << pointer_name << ";\n"sv;

                    assignments << "__sqf::"sv << pointer_name << " = " << "(binary_function)host::functions.get_binary_function_typed(\""sv << op_name << 
                        "\"sv, \"" << first_arg1_type << "\"sv, \"" << first_arg2_type << "\"sv);\n"sv;
                }
            }
        }

        pointers << "\n// Nular Functions\n";
        pointers_def << "\n// Nular Functions\n";

        assignments << "\n// Nular Functions\n";

        auto nular_list = loader::get().nular();
        std::vector<r_string> sorted_nular_list;
        sorted_nular_list.reserve(nular_list.size());
        for (const auto &nular : nular_list) {
            sorted_nular_list.push_back(nular.first);
        }
        std::sort(sorted_nular_list.begin(), sorted_nular_list.end());

        for (auto op_name : sorted_nular_list) {
            std::regex name_test = std::regex("[a-z]+?.*");
            if (std::regex_match(static_cast<std::string>(op_name), name_test)) {
                for (auto op : nular_list[op_name]) {
                    auto return_type = op.op->return_type.type_str();
                    return_type.to_lower();
                    auto pointer_name = "nular__" + op_name + "__ret__" + return_type;
                    pointers_def << "nular_function __sqf::"sv << pointer_name << ";\n";
                    pointers << "static nular_function "sv << pointer_name << ";\n";

                    //__sqf::unary_random_scalar_raw = (unary_function)functions.get_unary_function_typed("random", "SCALAR");
                    assignments << "__sqf::"sv << pointer_name << " = " << "(nular_function)host::functions.get_nular_function(\""sv << op_name << "\"sv);\n"sv;
                }
            }
        }

        return true;
    }
}

