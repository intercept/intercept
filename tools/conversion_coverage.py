import os
import sys
import re

from xml.dom import minidom

def parse():
    scriptpath = os.path.realpath(__file__)
    projectpath = os.path.dirname(os.path.dirname(scriptpath))
    projectpath = os.path.join(projectpath, "src/client/intercept/client")
    projectpath_sqf = os.path.join(projectpath, "sqf")
    
    declarations_file = os.path.join(os.path.dirname(os.path.dirname(scriptpath)), "src/client/headers/client/sqf_pointers_declaration.hpp")

    unary_functions = []
    binary_functions = []
    nular_functions = []

    # Collect the declarations
    with open(declarations_file) as f:
        for line in f:
            m_unary = re.search('(?<=static unary_function )\w+', line)
            m_binary = re.search('(?<=static binary_function )\w+', line)
            m_nular = re.search('(?<=static nular_function )\w+', line)
            if (m_unary):
                unary_functions.append(m_unary.group(0))
            if (m_binary):
                binary_functions.append(m_binary.group(0))
            if (m_nular):
                nular_functions.append(m_nular.group(0))

    # For statistics usage later
    unary_functions_declared = len(unary_functions)
    binary_functions_declared = len(binary_functions)
    nular_functions_declared = len(nular_functions)

    unary_functions_used = []
    binary_functions_used = []
    nular_functions_used = []
    unary_functions_found_at = []
    binary_functions_found_at = []
    nular_functions_found_at = []

    duplicate_unary_functions = []
    duplicate_binary_functions = []
    duplicate_nular_functions = []
    duplicate_unary_functions_loc = []
    duplicate_binary_functions_loc = []
    duplicate_nular_functions_loc = []

    unary_functions_cpy = list(unary_functions)
    binary_functions_cpy = list(binary_functions)
    nular_functions_cpy = list(nular_functions)

    # Walk through our source files and figure out which ones are used in our code
    for file in os.listdir(projectpath_sqf):
        if file.endswith(".cpp"):
            source_file = os.path.join(projectpath_sqf, file) # find our source file contents
            lineN = 0
            with open(source_file) as f:
                for line in f:# fileContent = f.read()
                    lineN += 1
                    for function in unary_functions_cpy: # check if this source file contains any unary functions
                        if line.find(function) != -1 and function not in unary_functions_used:
                            unary_functions.remove(function)
                            unary_functions_used.append(function)
                            unary_functions_found_at.append(["src/client/intercept/client/sqf/" + file, lineN])
                        elif line.find(function) != -1 and function in unary_functions_used:
                            duplicate_unary_functions.append(function)
                            duplicate_unary_functions_loc.append(["src/client/intercept/client/sqf/" + file, lineN])

                    for function in binary_functions_cpy: # check if this source file contains any binary functions
                        if line.find(function) != -1 and function not in binary_functions_used:
                            binary_functions.remove(function)
                            binary_functions_used.append(function)
                            binary_functions_found_at.append(["src/client/intercept/client//sqf/" + file, lineN])
                        elif line.find(function) != -1 and function in binary_functions_used:
                            duplicate_binary_functions.append(function)
                            duplicate_binary_functions_loc.append(["src/client/intercept/client/sqf/" + file, lineN])

                    for function in nular_functions_cpy: # check if this source file contains any nular functions
                        if line.find(function) != -1 and function not in nular_functions_used:
                            nular_functions.remove(function)
                            nular_functions_used.append(function)
                            nular_functions_found_at.append(["src/client/intercept/client/sqf/" + file, lineN])
                        elif line.find(function) != -1 and function in nular_functions_used:
                            duplicate_nular_functions.append(function)
                            duplicate_nular_functions_loc.append(["src/client/intercept/client/sqf/" + file, lineN])

    total_declared = unary_functions_declared + binary_functions_declared + nular_functions_declared
    total_used = len(unary_functions_used) + len(binary_functions_used) + len(nular_functions_used)
    percentage_completed = total_used / total_declared * 100
    print("### PERCENTAGE COMPLETED: {}%\n".format(round(percentage_completed*100)/100))

    print("Unary functions: {}/{}".format(len(unary_functions_used), unary_functions_declared))
    print("Binary functions: {}/{}".format(len(binary_functions_used), binary_functions_declared))
    print("Nular functions: {}/{}".format(len(nular_functions_used), nular_functions_declared))

    print("## TODO:\n-----\n")
    print("### Unary Functions")
    for function in unary_functions: # Output any unary functions yet to be completed
        print("- [ ] {}".format(function))
    print("\n----")

    print("### Binary Functions")
    for function in binary_functions: # Output any binary functions yet to be completed
        print("- [ ] {}".format(function))
    print("\n----")

    print("### Nular Functions")
    for function in nular_functions: # Output any nular functions yet to be completed
        print("- [ ] {}".format(function))
    print("\n----")

    # Output everything already completed
    print("## COMPLETED:\n-----\n")
    print("### Unary Functions")
    index = 0
    for function in unary_functions_used: # Output any unary functions completed
        function_name = re.search('(?<=unary__)[a-zA-Z0-9]+', function).group(0)
        function_name = re.sub("([a-z])([A-Z])", r"\1_\2", function_name).lower()
        print("- [x] {}".format(function_name, unary_functions_found_at[index][0], unary_functions_found_at[index][1]))
        index+=1
    print("\n----")

    print("### Binary Functions")
    index = 0
    for function in binary_functions_used: # Output any binary functions completed
        function_name = re.search('(?<=binary__)[a-zA-Z0-9]+', function).group(0)
        function_name = re.sub("([a-z])([A-Z])", r"\1_\2", function_name).lower()
        print("- [x] {}".format(function_name, binary_functions_found_at[index][0], binary_functions_found_at[index][1]))
        index+=1
    print("\n----")

    print("### Nular Functions")
    index = 0
    for function in nular_functions_used: # Output any nular functions completed
        function_name = re.search('(?<=nular__)[a-zA-Z0-9]+', function).group(0)
        function_name = re.sub("([a-z])([A-Z])", r"\1_\2", function_name).lower()
        print("- [x] {}".format(function_name, nular_functions_found_at[index][0], nular_functions_found_at[index][1]))
        index+=1
    print("\n----")

    return [unary_functions_used, binary_functions_used, nular_functions_used]

if __name__ == "__main__":
    parse()
