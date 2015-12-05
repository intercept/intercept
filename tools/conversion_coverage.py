import os
import sys
import re

from xml.dom import minidom

def parse():
    scriptpath = os.path.realpath(__file__)
    projectpath = os.path.dirname(os.path.dirname(scriptpath))
    projectpath = os.path.join(projectpath, "src\\client\\intercept\\client")
    projectpath_sqf = os.path.join(projectpath, "sqf")

    declarations_file = os.path.join(projectpath, "sqf_pointers_declaration.hpp")

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

    # Walk through our source files and figure out which ones are used in our code
    for file in os.listdir(projectpath_sqf):
        if file.endswith(".cpp"):
            source_file = os.path.join(projectpath_sqf, file) # find our source file contents
            with open(source_file) as f:
                fileContent = f.read()

                for function in unary_functions: # check if this source file contains any unary functions
                    if fileContent.find(function) != -1:
                        unary_functions.remove(function)
                        unary_functions_used.append(function)

                for function in binary_functions: # check if this source file contains any binary functions
                    if fileContent.find(function) != -1:
                        binary_functions.remove(function)
                        binary_functions_used.append(function)

                for function in nular_functions: # check if this source file contains any nular functions
                    if fileContent.find(function) != -1:
                        nular_functions.remove(function)
                        nular_functions_used.append(function)

    percentage_completed = ((unary_functions_declared + binary_functions_declared + nular_functions_declared) / (len(unary_functions_used) + len(binary_functions_used) + len(nular_functions_used))) / 100
    print("### PERCENTAGE COMPLETED: {}%\n".format(round(percentage_completed)))

    print("Unary functions declared: {}".format(unary_functions_declared))
    print("Binary functions declared: {}".format(binary_functions_declared))
    print("Nular functions declared: {}".format(nular_functions_declared))
    print("Unary functions used: {}".format(len(unary_functions_used)))
    print("Binary functions used: {}".format(len(binary_functions_used)))
    print("Nular functions used: {}".format(len(nular_functions_used)))

    print("### Unary Functions")
    for function in unary_functions: # Output any unary functions yet to be completed
        print("- [ ] {}".format(function))
    for function in unary_functions_used: # Output any unary functions completed
        print("- [x] {}".format(function))
    print("\n----")

    print("### Binary Functions")
    for function in binary_functions: # Output any binary functions yet to be completed
        print("- [ ] {}".format(function))
    for function in binary_functions_used: # Output any binary functions completed
        print("- [x] {}".format(function))
    print("\n----")

    print("### Nular Functions")
    for function in nular_functions: # Output any nular functions yet to be completed
        print("- [ ] {}".format(function))
    for function in nular_functions_used: # Output any nular functions completed
        print("- [x] {}".format(function))
    print("\n----")



if __name__ == "__main__":
    parse()
