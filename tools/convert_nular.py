import os
import sys
import re
import conversion_coverage as coverage

def parse():
    scriptpath = os.path.realpath(__file__)
    projectpath = os.path.dirname(os.path.dirname(scriptpath))
    projectpath = os.path.join(projectpath, "tools")
    declarations_file = os.path.join(projectpath, "unary_definitions.txt")

    used_functions = coverage.parse()
    unary_functions = used_functions[0]
    binary_functions = used_functions[1]
    nular_functions = used_functions[2]

    converted = []
    functions_converted = []
    helper_methods = {}
    with open(declarations_file) as f:
        for line in f:
            m_unary = re.search('(?<=static nular_function )\w+', line)
            if (m_unary): # We have a unary function on this line
                skip_generation = m_unary.group(0).lower() in nular_functions # check if we can skip auto generation for this - it's already done somewhere in our source files
                function_name = re.search('(?<=nular__)[a-zA-Z0-9]+', m_unary.group(0)).group(0)
                function_name = re.sub("([a-z])([A-Z])", r"\1_\2", function_name).lower()
                function_output = function_name
                ret_type = 'void'

                part = line

                if (part.find("ret__scalar") != -1):
                    function_output = "float " + function_output
                    ret_type = "float"
                if (part.find("ret__script") != -1):
                    function_output = "script " + function_output
                    ret_type = "script"
                if (part.find("ret__bool") != -1):
                    function_output = "bool " + function_output
                    ret_type = "bool"
                if (part.find("ret__object") != -1):
                    function_output = "object " + function_output
                    ret_type = "object"
                if (part.find("ret__side") != -1):
                    function_output = "side " + function_output
                    ret_type = "side"
                if (part.find("ret__string") != -1):
                    function_output = "std::string " + function_output
                    ret_type = "std::string"
                if (part.find("ret__display") != -1):
                    function_output = "display " + function_output
                    ret_type = "display"
                if (part.find("ret__control") != -1):
                    function_output = "control " + function_output
                    ret_type = "control"
                if (part.find("ret__nothing") != -1):
                    function_output = "void " + function_output
                    ret_type = "void"
                if (part.find("ret__text") != -1):
                    function_output = "text " + function_output
                    ret_type = "text"
                if (part.find("ret__group") != -1):
                    function_output = "group " + function_output
                    ret_type = "group"
                if (part.find("ret__namespace") != -1):
                    function_output = "rv_namespace " + function_output
                    ret_type = "rv_namespace"
                if (part.find("ret__any") != -1):
                    function_output = "rv_any " + function_output
                    ret_type = "rv_any"
                if (part.find("ret__task") != -1):
                    function_output = "task " + function_output
                    ret_type = "task"
                if (part.find("ret__team_member") != -1):
                    function_output = "team_member " + function_output
                    ret_type = "team_member"
                if (part.find("ret__array") != -1):
                    function_output = "std::vector<?> " + function_output
                    ret_type = "array"

                function_output += "()"

                if (not function_output.startswith(function_name)): # we got a function we can generate with our rules
                    function_implementation = function_output + " {\n    "
                    function_declaration = function_output + ";"

                    helper_method = ""
                    # __empty_unary_number(unary_function fnc_, float val_);
                    if (ret_type == 'float'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'bool'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'std::string'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'object'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'control'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'text'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'script'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'task'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'rv_namespace'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'display'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'void'):
                        helper_method += ""
                    elif  (ret_type == 'side'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'group'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'team_member'):
                        helper_method += "game_value ret_value = "
                    elif  (ret_type == 'array'):
                        helper_method += "game_value input__ = "
                    elif  (ret_type == 'rv_any'):
                        helper_method += "game_value input__ = "

                    helper_method += "host::functions.invoke_raw_nular"
                    function_implementation += helper_method + "(client::__sqf::"+ m_unary.group(0).lower() + ");\n"

                    # handle return value
                    return_conversion = ""
                    if (ret_type == 'float'):
                        return_conversion += "    float rv = ((game_data_number *)ret_value.data)->number;\n    host::functions.free_value(&ret_value);\n    return rv;\n"
                    elif  (ret_type == 'bool'):
                        return_conversion += "    bool rv = ((game_data_bool *)ret_value.data)->value;\n    host::functions.free_value(&ret_value);\n    return rv;\n"
                    elif  (ret_type == 'std::string'):
                        return_conversion += "    std::string rv = ((game_data_string *)ret_value.data)->get_string();\n    host::functions.free_value(&ret_value);\n    return rv;\n"
                    elif  (ret_type == 'object'):
                        return_conversion += "    return object(ret_value);\n"
                    elif  (ret_type == 'control'):
                        return_conversion += "    return control(ret_value);\n"
                    elif  (ret_type == 'script'):
                        return_conversion += "    return script(ret_value);\n"
                    elif  (ret_type == 'task'):
                        return_conversion += "    return task(ret_value);\n"
                    elif  (ret_type == 'rv_namespace'):
                        return_conversion += "    return rv_namespace(ret_value);\n"
                    elif  (ret_type == 'text'):
                        return_conversion += "    std::string rv = ((game_data_string *)ret_value.data)->get_string();\n    host::functions.free_value(&ret_value);\n    return rv;\n"
                    elif  (ret_type == 'display'):
                        return_conversion += "    return display(ret_value);\n"
                    elif  (ret_type == 'side'):
                        return_conversion += "    return side(ret_value);\n"
                    elif  (ret_type == 'group'):
                        return_conversion += "    return group(ret_value);\n"
                    elif  (ret_type == 'team_member'):
                        return_conversion += "    return team_member(ret_value);\n"
                    elif  (ret_type == 'rv_any'):
                        return_conversion += "    return rv_any(ret_value);\n"
                    elif  (ret_type == 'array'):
                        return_conversion += "    game_data_array* array_value = ((game_data_array *)input__.data);\n"
                        return_conversion += "    std::vector<?> output;\n"
                        return_conversion += "    for (int i = 0; i < array_value->length; ++i) {\n"
                        return_conversion += "        output.push_back(?(array_value->data[i])); // TODO Conversion\n"
                        return_conversion += "    }\n    host::functions.free_value(&input__);\n    return output;\n"

                    function_implementation += return_conversion + "}\n" # close function definition

                    if not skip_generation:
                        converted.append(function_declaration)
                        functions_converted.append(function_implementation)
                    if helper_method in helper_methods.keys():
                        helper_methods[helper_method] +=1
                    else:
                        helper_methods[helper_method] = 1

    #orig_stdout = sys.stdout
    #f = file('out.txt', 'w')
    #sys.stdout = f

    for output in converted:
        print(output)

    for output in functions_converted:
        print(output)
    #for helper in helper_methods.keys():
    #    print("{}: {}".format(helper, helper_methods[helper]))

if __name__ == "__main__":
    parse()
