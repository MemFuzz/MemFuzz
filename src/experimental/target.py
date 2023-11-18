#!/usr/bin/env python
import os
import sys
import re

class ctag_info:
    def __init__(self, ctag_line):
        l = ctag_line.split()
        if l[0] != 'operator':
            self.name = l[0] # function name
            self.type = l[1] # we only use ctag to find prototype
            self.lineno = l[2] # line no of prototype
            self.filename = l[3] # filename of the prototype
            self.content = " ".join(l[4:]) #prototype content
        else:
            self.name = 'operator'  
            self.type = l[2]
            self.lineno = l[3]
            self.filename = l[4]
            self.content = " ".join(l[5:])
    
    def __str__(self):
        return self.name + " " + self.type + " " + self.lineno + " " +  self.filename + " " + self.content


def find_cpp_files(dirpath):
    l = []
    for root, dirs, files in os.walk(dirpath):
        for file in files:
            if file.endswith('.c') or file.endswith('.cpp') or file.endswith('.h') or file.endswith('.hpp') or file.endswith('.cc') or file.endswith('.cxx') or file.endswith('.C') or file.endswith('.c++'):
                l.append(os.path.join(root, file))
        for dir in dirs:
            l += find_cpp_files(os.path.join(root, dir))
    return l


def extract_prototype(filepath):
    #cmd = 'ctags -x --c++-kinds=p --language-force=c++ ' # we need only prototype
    cmd = 'ctags -x --c++-kinds=p --language-force=c++ ' # we need only prototype
    cmd += filepath
    cmd += '> /tmp/ctag_info'
    os.system(cmd)
    l = []
    if not os.path.exists('/tmp/ctag_info'):
        return l

    with open('/tmp/ctag_info') as f:
        for line in f:
            l.append(line)
    os.remove('/tmp/ctag_info')
    tags = []
    with open(filepath) as f:
        lines = f.readlines()
        total_lines = len(lines)
        for sym in l:
            a_tag = ctag_info(sym)
            i = 0
            proto = ""
            try:
                base_line = int(a_tag.lineno)
            except ValueError:
                os.write(2, "Error: " + str(a_tag) + "\n")
                continue
            while base_line - 1 + i < len(lines):
                tmp = lines[base_line - 1 + i].strip()
                id = tmp.find(";")
                if id == -1:
                    proto += tmp
                else:
                    proto += tmp[: id] + ";"
                    break
                i += 1
            a_tag.content= proto
            tags.append(a_tag)
            
    return tags


def find_elf_files(dirpath):
    l = []
    for root, dirs, files in os.walk(dirpath):
        for file in files:
            abs_path = os.path.join(root, file)
            if file.endswith('.o') or file.endswith('.so') or file.endswith('.a') or file.endswith('.la'):
                l.append(abs_path)
            elif os.access(abs_path, os.X_OK):
                with open(abs_path, "rb") as f:
                    magic = f.read(4)
                    if magic == "\x7fELF":
                        l.append(abs_path)
        for dir in dirs:
            l += find_elf_files(os.path.join(root, dir))
    return l


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Need directory")
        sys.exit(1)

    c_keywords = ['size_t', 'ssize_t', 'float', 'double', 'int',  'void', "bool", 'char', '_Bool'
    , 'operator', 'std', 'class', 'virtual', 'class', 'template', 'string', 'this', 'restrict',
    'const', 'long', 'short', 'auto', 'signed', 'unsigned', 'static', 'extern', 'struct', 'union', 'inline']

    regex = re.compile("[a-zA-Z_][a-zA-Z0-9_]*")

    elf_files = find_elf_files(sys.argv[1])
    prototypes = set()
    for fileidx, file in enumerate(elf_files):
        os.write(2, "Parse " + str(fileidx) + "/" + str(len(elf_files)) + ": " + file + "\n")
        cmd = "/home/youwei/pahole/pahole/pfunct -P --no_parm_names " + file + "> /tmp/pfunct"
        os.system(cmd)
        with open("/tmp/pfunct", "r") as f:
            for line in f:
                prototypes.add(line)

    use_count = {}
    for prototype in prototypes:
        objs = re.findall(regex, prototype)
        for sym in objs:
            if sym not in c_keywords:
                if sym not in use_count:
                    use_count[sym] = 1
                else:
                    use_count[sym] += 1
        # print(prototype)
    
    for name, count in sorted(use_count.items(), key=lambda item: -item[1]):
        print(name)
        print(count)


    sys.exit(0)
    
    cfiles = find_cpp_files(sys.argv[1])
    name_type = {} # map a function name to its arguement type(only class, struct, union)
    regex = re.compile("[a-zA-Z_][a-zA-Z0-9_]*")
    all_tags = []
    for fileidx, file in enumerate(cfiles):
        os.write(2, "Parse " + str(fileidx) + "/" + str(len(cfiles)) + ": " + file + "\n")
        tags = extract_prototype(file)
        all_tags += tags
        for tag in tags:
            name_type[tag.name] = []
            # bilist = tag.content.split(tag.name)
            # print(bilist)
            # if len(bilist) < 2:
            #     os.write(2, tag.content)
            #     sys.exit(1)
            # start_pos = bilist[1].find('(')
            # end_pos = bilist[1].find(')')
            # parameter_string = bilist[1][start_pos + 1: end_pos]
            # parameter_list = parameter_string.split(',')
            # for a_parameter in parameter_list:
            #     a_parameter_ = a_parameter.strip()
            #     objs = re.findall(regex, a_parameter_)
            #     objs = objs[:-1] # remove the arguement name
            #     for word in objs:
            #         if word not in c_keywords:
            #             name_type[tag.name].append(word)
                        # print(word)
                        # break

            # We extract all possible symbols, including the argument name
            objs = re.findall(regex, tag.content)
            for sym in objs:
                if sym not in c_keywords and sym != tag.name:
                    name_type[tag.name].append(sym)

    use_count = {}
    for name in name_type:
        for a_type  in name_type[name]:
            if a_type not in use_count:
                use_count[a_type] = 1
            else:
                use_count[a_type] += 1
    
    # symbol frequency
    for name, count in sorted(use_count.items(), key=lambda item: -item[1]):
        print(name)
        print(count)
        # find whether this structure has 
        # for tag in all_tags:
        