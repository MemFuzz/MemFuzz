#!/usr/bin/python3
import os
import sys
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
from elftools.dwarf.descriptions import describe_form_class

def extract_function_names_dynamic(elf_filename):
    function_names = set()
    with open(elf_filename, 'rb') as elf_file:
        elf = ELFFile(elf_file)

        # Find the DWARF information section.
        dwarf_info = elf.get_dwarf_info()

        # Iterate through the compilation units (CUs).
        for cu in dwarf_info.iter_CUs():
            for die in cu.iter_DIEs():
                if die.tag == 'DW_TAG_subprogram':
                    # Get the function name from the DIE.
                    attr = die.attributes.get('DW_AT_name')
                    func_name = attr.value if attr else None
                    if func_name:
                        function_names.add(func_name.decode('utf-8'))
    # for item in function_names:
    #     print(item)
    return function_names

def extract_function_name_for_cpp(code):
    index = code.find('(')
    if code[index] == '(':
        code = code[:index]
    else:
        return code
    i = len(code) - 1
    while i > 0:
        if code[i] == ' ' or code[i] == ':':
            break
        i -= 1
    if i >= 0 and (code[i] == ':' or code[i] == ' '):
        return code[i+1: ]
    return code[i: ]

def extract_function_names_static(path_to_ctags, target_dir):
    cmd = path_to_ctags + ' -R --c++-kinds=f --c-kinds=f ' + target_dir
    os.system(cmd)
    def extract_function_names(tags_file):
        function_names = []
        with open(tags_file, 'r') as f:
            for line in f:
                parts = line.split('\t')
                # print(parts)
                if len(parts) >= 1:
                    tag_name = parts[0]
                    if not tag_name.startswith('!'):
                        function_names.append(tag_name)
        return function_names
    tags_file = 'tags' 
    function_names = extract_function_names(tags_file)
    return function_names

def gen_call_stack(valgrind_info_filename):
    read_functions = ['read', 'fread', 'fscanf', 'fgetc', 'fgets', 'pread']
    marked_read_functions = set()
    s = []
    res = []
    depth = 0
    main_found = False
    exit_found = False
    with open(valgrind_info_filename,'r') as f:
        for lineno, line in enumerate(f):
            if not main_found:
                if line.startswith("function entered: main"):
                    main_found = True
            if not exit_found:
                if line.startswith("function left: main"):
                    exit_found = True
                    break
            if main_found and not exit_found:
                #print(line) #debug 
                if line.startswith("function entered: "):
                    function_name = line[17:].strip()
                    if function_name in read_functions:
                        for item in s:
                            marked_read_functions.add(extract_function_name_for_cpp(item))
                    s.append(function_name)
                    depth += 1
                    res.append([extract_function_name_for_cpp(function_name), depth])
                    
                elif line.startswith("function left: "):
                    function_name = line[15:].strip()
                    if function_name == s[-1]:
                        s.pop()
                    else:
                        print("enter and exit does not match! line number is " + str(lineno) + "\n")
                        print(line)
                        print("Last call is " + res[-1][0])
                        sys.exit(1)
                    depth -= 1
                # Some program's output may mix match our information, we probably need to use regex to extract...
                else:
                     index = line.find("function left: ")
                     if index != -1:
                        trunc_line = line[index:]
                        function_name = trunc_line[15:].strip()
                        if function_name == s[-1]:
                            s.pop()
                        else:
                            print("enter and exit does not match! line number is " + str(lineno) + "\n")
                            print(line)
                            print("Last call is " + res[-1][0])
                            sys.exit(1)

                    
            
    # print("Call stack:")
    # for item in res:
    #     print(item)
    # print("----------------------------------------")
    # print("Read functions:")
    # for item in marked_read_functions:
    #     print(item)
    if "main" in marked_read_functions:
        marked_read_functions.remove("main")
    return res, marked_read_functions

def load_APIs(filename):
    res = set()
    with open(filename, "r") as f:
        for line in f:
            if line[0] != '#':
                res.add(line.strip())
    if "main" in res:
        res.remove("main")
    return res

# handle both C/C++
def gen_simplify_stack(call_stk, APIs):
    new_stk = []
    found_API = False
    found_depth = 0
    for call in call_stk:
        function_name = call[0]
        depth = call[1]
        if found_API:
            if depth > found_depth:
                continue
            else:
                found_API = False
                found_depth = 0
        if function_name in APIs:
            found_API = True
            found_depth = depth
            new_stk.append(function_name)
            
    return new_stk



if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("./analyze.py target")
        sys.exit(1)
    # res = extract_function_names_dynamic(sys.argv[1])
    target = sys.argv[1]
    APIs = load_APIs('./APIs/' + target + "_dynamic")
    call_stk, read_function_set = gen_call_stack('./valid/' + target)
    simple_stack = gen_simplify_stack(call_stk, APIs)
    read_APIs = APIs.intersection(read_function_set)
    seen_functions = set()
    # for i in read_function_set:
    #     print(i)
    # for i in read_APIs:
    #     print(i)
    # for i in simple_stack:
    #     print(i)
    for i in simple_stack:
        if i in read_APIs and i not in seen_functions:
            seen_functions.add(i)
            print(i)
