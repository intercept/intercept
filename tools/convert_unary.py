import os
import sys
import re

def parse():
    scriptpath = os.path.realpath(__file__)
    projectpath = os.path.dirname(os.path.dirname(scriptpath))
    projectpath = os.path.join(projectpath, "tools")
    declarations_file = os.path.join(projectpath, "unary_definitions.txt")

    converted = []
    functions_converted = []

    with open(declarations_file) as f:
        for line in f:
            m_unary = re.search('(?<=static unary_function )\w+', line)
            if (m_unary): # We have a unary function on this line
                function_name = re.search('(?<=unary__)[a-zA-Z]+', m_unary.group(0)).group(0)
                function_name = re.sub("([a-z])([A-Z])", r"\1_\2", function_name).lower()
                function_output = function_name
                ret_type = 'void'

                if (line.find("ret__scalar") != -1):
                    function_output = "float " + function_output
                    ret_type = "float"

                if (line.find("ret__bool") != -1):
                    function_output = "bool " + function_output
                    ret_type = "bool"

                if (line.find("ret__object") != -1):
                    function_output = "object " + function_output
                    ret_type = "object"

                if (line.find("ret__side") != -1):
                    function_output = "side " + function_output
                    ret_type = "side"

                if (line.find("ret__string") != -1):
                    function_output = "std::string " + function_output
                    ret_type = "std::string"

                if (line.find("ret__display") != -1):
                    function_output = "display " + function_output
                    ret_type = "display"

                if (line.find("ret__control") != -1):
                    function_output = "control " + function_output
                    ret_type = "control"

                if (line.find("ret__nothing") != -1):
                    function_output = "void " + function_output
                    ret_type = "void"

                if (line.find("ret__text") != -1):
                    function_output = "text " + function_output
                    ret_type = "text"

                if (line.find("ret__group") != -1):
                    function_output = "group " + function_output
                    ret_type = "group"

                if (line.find("ret__team_member") != -1):
                    function_output = "team_member " + function_output
                    ret_type = "team_member"

                function_output += "("
                input_type = 'float'
                if (line.find("__scalar__") != -1):
                    function_output += "float value_"
                    input_type = 'float'

                if (line.find("__scalar_nan__") != -1):
                    function_output += "float value_"
                    input_type = 'float'

                if (line.find("__bool__") != -1):
                    function_output += "bool value_"
                    input_type = 'bool'

                if (line.find("__object__") != -1):
                    function_output += "object value_"
                    input_type = 'object'

                if (line.find("__side__") != -1):
                    function_output += "side value_"
                    input_type = 'side'

                if (line.find("__string__") != -1):
                    function_output += "std::string value_"
                    input_type = 'string'

                if (line.find("__display__") != -1):
                    function_output += "display value_"
                    input_type = 'display'

                if (line.find("__control__") != -1):
                    function_output += "control value_"
                    input_type = 'control'

                if (line.find("__text__") != -1):
                    function_output += "text value_"
                    input_type = 'text'

                if (line.find("__group__") != -1):
                    function_output += "group value_"
                    input_type = 'group'

                if (line.find("__array__") != -1):
                    function_output += "array value_"
                    input_type = 'array'
                function_output += ")"

                if (not function_output.startswith(function_name) and not function_output.endswith("()")): # we got a function we can generate with our rules
                    function_implementation = function_output + " {\n    "
                    function_declaration = function_output + ";"

                    # __empty_unary_number(unary_function fnc_, float val_);
                    if (ret_type == 'float'):
                        function_implementation += "return __number_unary_"
                    elif  (ret_type == 'bool'):
                        function_implementation += "return __bool_unary_"
                    elif  (ret_type == 'std::string'):
                        function_implementation += "return __string_unary_"
                    elif  (ret_type == 'object'):
                        function_implementation += "return __object_unary_"
                    elif  (ret_type == 'control'):
                        function_implementation += "return __control_unary_"
                    elif  (ret_type == 'text'):
                        function_implementation += "return __text_unary_"
                    elif  (ret_type == 'display'):
                        function_implementation += "return __display_unary_"
                    elif  (ret_type == 'void'):
                        function_implementation += "__empty_unary_"
                    elif  (ret_type == 'side'):
                        function_implementation += "return __side_unary_"
                    elif  (ret_type == 'group'):
                        function_implementation += "return __group_unary_"

                    if (input_type == 'float'):
                        function_implementation += "number("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'bool'):
                        function_implementation += "bool("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'string'):
                        function_implementation += "string("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'object'):
                        function_implementation += "object("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'control'):
                        function_implementation += "control("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'text'):
                        function_implementation += "text("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'display'):
                        function_implementation += "display("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'side'):
                        function_implementation += "side("+ m_unary.group(0).lower() +", value_);\n"
                    elif  (input_type == 'group'):
                        function_implementation += "group("+ m_unary.group(0).lower() +", value_);\n"

                    function_implementation += "}\n"
                    if input_type != 'array':
                        converted.append(function_declaration)
                        functions_converted.append(function_implementation)

    for output in converted:
        print(output)

    for output in functions_converted:
        print(output)

if __name__ == "__main__":
    parse()
