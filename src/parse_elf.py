#!/usr/bin/env python
import re
import sys
import os


# determine if it is a local struct in target
def query(struct_name, target):
    #path = "./third/src/pahole"
    path = "./pahole"
    if os.path.exists("./memfuzz_enum.h"):
        os.system("rm ./memfuzz_enum.h")
    cmd = path + " --classes_as_structs -M -I -q -a --class_name=" + struct_name + " " + target + " > /tmp/one_class"
    msg = os.system(cmd)
    assert(msg == 0)
    enum = ""
    if os.path.exists("./memfuzz_enum.h"):
        with open("./memfuzz_enum.h", "r") as f:
            enum = f.read()
    with open("/tmp/one_class", "r") as f:
        content = f.read()
        lines = content.split("\n")
        assert(len(lines) >= 2)
        obj = re.findall("home", lines[1])
        if obj:
            return True, content, enum
        else:
            return False, content, enum
        

class Values:
    Interesting_8 = ["-128","-1","0","1","16","32","64","100","127"]
    Interesting_16 = ['-32768', '-129', '128', '255', '256', '512', '1000', '1024', '4096', '32767']
    Interesting_32 = ['-2147483648', '-100663046', '-32769', '32768', '65535', '65536', '100663045', '2147483647']
    Interesting_64 = [str(1<<63)+'LL', '2147483647', '-2147483648']
    Double_ = Float_ = ['0.00001', '0.0000000001', '2147483647.0', '0.0','0.1', '1.0', '-0.1', '-1.0']
    
    base_type_name_to_size_table = \
    {
        "unsigned": 32,
        "signed int": 32,
        "unsigned int": 32,
        "int": 32,
        "short unsigned int": 16,
        "signed short": 16,
        "unsigned short": 16,
        "short int": 16,
        "short": 16,
        "char": 8,
        "signed char": 8,
        "unsigned char": 8,
        "signed long": 64, #long may be 32 or 64, in this machine, we take 64
        "long int": 64,
        "unsigned long": 64,
        "long unsigned int": 64,
        "bool": 8,
        "_Bool": 8,
        "long long unsigned int": 64,
        "long long int": 64,
        "long long": 64,
        "signed long long": 64,
        "unsigned long long": 64,
        "double": 64,
        "double double": 64,
        "single float": 32,
        "float": 32,
        "long double": 128,
        "long double long double": 128,
        "__int128": 128,
        "unsigned __int128": 128,
        "__int128 unsigned": 128,
        "_Float128": 128
    }

    float_value_name_table = ["double", "double double", "single float", "float", "long double", "long double long double", "__Float_128"]
    
    @staticmethod
    def Int8():
        return Values.Interesting_8

    @staticmethod
    def Int16():
        return set(Values.Interesting_16 + Values.Interesting_8)

    @staticmethod
    def Int32():
        return set(Values.Interesting_32 + Values.Interesting_16 + Values.Interesting_8)

    @staticmethod
    def Int64():
        return set(Values.Interesting_64 + Values.Interesting_32 + Values.Interesting_16 + Values.Interesting_8)

    @staticmethod
    def Float():
        return Values.Float_

    @staticmethod
    def Double():
        return Values.Double_
    
    @staticmethod
    def is_float(base_type):
        if base_type in Values.float_value_name_table:
            return True
        return False

    @staticmethod
    def get_values(base_type):
        base_type = base_type.strip(" ")
        if base_type in Values.float_value_name_table:
            if base_type == "double" or base_type == "double double" or base_type == "long double long double":
                return "double"
            else:
                return "float"
        else:
            if base_type not in Values.base_type_name_to_size_table:
                print(base_type + " is not in base_type!")
                sys.exit(1)
            else:
                bits = Values.base_type_name_to_size_table[base_type]
                if bits == 8:
                    return "int8_t"
                elif bits == 16:
                    return "int16_t"
                elif bits == 32:
                    return "int32_t"
                elif bits == 64:
                    return "int64_t"
        
'''
DW_TAG_unknown
DW_TAG_pointer_type
DW_TAG_typedef
DW_TAG_subroutine_type
DW_TAG_const_type
DW_TAG_array_type
DW_TAG_string_type
DW_TAG_structure_type
DW_TAG_class_type
DW_TAG_union_type
DW_TAG_enumeration_type
DW_TAG_base_type
DW_TAG_bitfield          # it is not in DWARF's DW_TAG
'''
class Tag:
    def __init__(self, tag, extra=None):
        self.tag = tag
        self.extra = extra
   
    '''
    array_type: a[1][2][3] -> [1, 2, 3]
    structure_type: struct st{int a; char b;}; -> {("st", {"a": "int", "b" : "char"})}
    class_type: ...
    union_type: ...
    enumeration_type: {x, y, z} -> 3
    base_type: char x -> "char"
    bitfield: bitfield_size
    '''
    def __str__(self):
        return self.tag

class Member:
    def __init__(self, name, tags):
        self.name = name
        new_tags = []
        for i in tags:
            if i.tag == "DW_TAG_typedef":
                continue
            new_tags.append(i)
        self.tags = new_tags

    def is_base(self):
        for i in self.tags:
            if i.tag == "DW_TAG_base_type":
                return True
        return False

    def is_structure(self):
        for i in self.tags:
            if i.tag == "DW_TAG_structure_type" or i.tag == "DW_TAG_class_type" or i.tag == "DW_TAG_union_type":
                return True
        return False

    def is_enumerate(self):
        for i in self.tags:
            if i.tag == "DW_TAG_enumeration_type":
                return True
        return False

    def is_array(self):
        for i in self.tags:
            if i.tag == "DW_TAG_array_type":
                return True
        return False

    def is_pointer(self):
        for i in self.tags:
            if i.tag == "DW_TAG_pointer_type":
                return True
        return False
    
    def is_bitfield(self):
        for i in self.tags:
            if i.tag == "DW_TAG_bitfield":
                return True
        return False

    def is_const(self):
        for i in self.tags:
            if i.tag == "DW_TAG_const_type":
                return True
        return False
        
    def get_pointer_level(self):
        num = 0
        for i in self.tags:
            if i.tag == "DW_TAG_pointer_type":
                num += 1
        return num

    def get_array_dimension(self):
        for i in self.tags:
            if i.tag == "DW_TAG_array_type":
                return i.extra
        return None

    def get_base_type(self):
        for i in self.tags:
            if i.tag == "DW_TAG_base_type":
                return i.extra
        return None
    
    def get_enum_num(self):
        for i in self.tags:
            if i.tag == "DW_TAG_enumeration_type":
                return i.extra
        return None

    def get_struct_type(self):
        for i in self.tags:
            if i.tag == "DW_TAG_structure_type" or i.tag == "DW_TAG_class_type" or i.tag == "DW_TAG_union_type":
                return i.extra
        return None

    def __str__(self):
        pre = ""
        post = ""
        tags = self.tags
        for t in tags:
            if t.tag == "DW_TAG_unknown":
                return "unknown " + self.name
            elif t.tag == "DW_TAG_pointer_type":
                pre += "*"
            elif t.tag == "DW_TAG_subroutine_type":
                return "function " + self.name
            elif t.tag == "DW_TAG_const_type": 
                pre = "const " + pre
            elif t.tag == "DW_TAG_string_type":
                return "string " + self.name
            elif t.tag == "DW_TAG_array_type":
                for i in t.extra:
                    post += "[" + str(i) + "]"
            elif t.tag == "DW_TAG_structure_type":
                if t.extra[0] is not None:
                    pre = "struct " + t.extra[0] + " " + pre
                else: 
                    pre = "struct anonymous " + pre
                    pre += "{"
                    for a_member in t.extra[1]:
                        pre += str(a_member) + "; "
                    pre += "} "
            elif t.tag == "DW_TAG_class_type":
                if t.extra[0] is not None:
                    pre = t.extra[0] + " " + pre
                else:
                    pre = "calss anonymous " + pre
                    pre += "{"
                    for a_member in t.extra[1]:
                        pre += str(a_member) + "; "
                    pre += "} "
            elif t.tag == "DW_TAG_union_type":
                if t.extra[0] is not None:
                    pre = "union " + t.extra[0] + " " + pre
                else:
                    pre = "union anonymous " + pre
                    pre += "{"
                    for a_member in t.extra[1]:
                        pre += str(a_member) + "; "
                    pre += "} "
            elif t.tag == "DW_TAG_enumeration_type":
                pre = "enum " + pre
            elif t.tag == "DW_TAG_base_type":
                pre = t.extra + " " + pre
            elif t.tag == "DW_TAG_bitfield":
                post += ":" + str(t.extra)
        return pre + self.name + post

# TODO: create a set for anonymous struct and when parsing them, add to the set
class AnonymousStruct:
    def __init__(self, name_, members_, type_):
        self.name = name_ # name of the class, string
        self.members = members_ # a list of Member
        self.type = type_ # class struct union, string

    def __str__(self):
        return self.type + " " + self.name

class Struct:
    def __init__(self, name_, members_, type_):
        self.name = name_ # name of the class, string
        self.members = members_ # a list of Member
        self.type = type_ # class struct union, string

    def __str__(self):
        return self.type + " " + self.name

class Enum:
    # name=None means it is anonymous enum, values is a map whose key is enum identifier(string) and value is a num(int)
    def __init__(self, name, values):
        self.name = name #(string or None)
        self.values = values #(map)

    def __eq__(self, other):
        return self.values == other.values

    def __hash__(self):
        return hash(tuple(sorted(self.values)))

    def __str__(self):
        s = "enum "
        if self.name != None:
            s += self.name
        s += "{\n"
        for i in self.values:
            s += "\t" + i + " = " + str(self.values[i]) + ",\n"
        s += "};\n"
        return s

def rename_anonymous(class_map):
    new_class_map = {}
    default_name = "memfuzz_anonymous_struct_"
    anonymous_struct_cnt = 0
    # for a_class in class_map:
        

# return the index of next token in buf and the content of next token
# It seems the member name may include $ in C++ dumped by pahole so we do special check
def next_token(buf):
    token = ""
    index = 0
    length = len(buf)
    while index < length and (buf[index] == ' ' or buf[index] == '\n' or buf[index] == '\r'):
        index += 1
    buf = buf[index:]
    if len(buf) == 0:
        return index, None
    if buf[0] == '(' or buf[0] == ')' or buf[0] == '{' or buf[0] == '}' or buf[0] == '[' or buf[0] == ']':
        return index + 1, buf[0]
    template_cnt = 0
    for i in range(len(buf)):
        if template_cnt > 0:
            if buf[i] == '<':
                template_cnt += 1
            elif buf[i] == '>':
                template_cnt -= 1
            token += buf[i]
            index += 1
        else:
            # $ : . are soeciall for handling class in C++
            if buf[i] == '_' or buf[i].isalpha() or buf[i].isdigit() or buf[i] == '$' or buf[i] == ':' or buf[i] == '.':
                token += buf[i]
                index += 1
            # handle template
            elif buf[i] == '<':
                template_cnt += 1
                token += buf[i]
                index += 1
            else:
                return index, token


def parse_1(line):
    # parse class name
    if line.startswith('ClassName'):
        class_type = 'class'
        index = 9
    elif line.startswith('StructName'):
        class_type = 'struct'
        index = 10
    elif line.startswith('UnionName'):
        class_type = 'union'
        index = 9
    else:
        print('Head parse Error!\n')
        sys.exit(1)
    class_name = line[index + 1: -2]
    if class_name == "(null)":
        try:
            parse_1.anonymous_struct_cnt += 1
        except AttributeError:
            parse_1.anonymous_struct_cnt = 0
        class_name = "memfuzz_anonymous_struct_" + str(parse_1.anonymous_struct_cnt)
    return class_type, class_name


def find_balanced_curly_brackets(buf):
    cnt = 0
    for i in range(len(buf)):
        if buf[i] == '{':
            cnt += 1
        elif buf[i] == '}':
            cnt -= 1
            if cnt == -1:
                return i
    return -1

# Parse and return a list of class members
def parse_2(line, level=0):

    class_members = []
    square_bracket = 0
    member_name = None
    member_tags = []
    saved_line = line
    while next_token(line)[1] != None:
        index, token = next_token(line)
        line = line[index: ]
        one_tag = None
        if token == '[':
            square_bracket += 1
        elif token == ']':
            square_bracket -= 1
            if square_bracket < 0:
                print('Level ' + str(level) + ': Format error, extra ]!\n')
                print(line)
                sys.exit(1)
            if square_bracket == 0:
                member_tags_1 = []
                for tag in member_tags:
                    if tag != None:
                        member_tags_1.append(tag)
                one_member = Member(member_name, member_tags_1)
                class_members.append(one_member)
                member_name = None
                member_tags = []
        #parse name
        elif token == 'MemberName':
            index, token = next_token(line)
            line = line[index:]
            index, token = next_token(line)
            member_name = token
            line = line[index:]
            index, token = next_token(line)
            line = line[index:]
            #print(member_name)
        #parse tags
        #DW_TAG_unknown(%s) or DW_TAG_unknown
        elif token == 'DW_TAG_unknown':
            index, token = next_token(line)
            if token == '(':
                line = line[index:]
                index, token = next_token(line)
                
                one_tag = Tag('DW_TAG_unknown', token)
                line = line[index:]
                index, token = next_token(line)
                line = line[index:]
            else: 
                one_tag = Tag('DW_TAG_unknown')

        elif token == 'DW_TAG_pointer_type':
            pass
            one_tag = Tag('DW_TAG_pointer_type')
        
        elif token == 'DW_TAG_typedef':
            pass
            one_tag = Tag('DW_TAG_typedef')
        
        elif token == 'DW_TAG_subroutine_type':
            pass
            one_tag = Tag('DW_TAG_subroutine_type')
        
        elif token == 'DW_TAG_const_type':
            pass
            one_tag = Tag('DW_TAG_const_type')
        
        #DW_TAG_array_type(dimension, ...)
        elif token == 'DW_TAG_array_type':
            #parse the dimension first
            index, token = next_token(line)
            line = line[index:]
            index, token = next_token(line)
            line = line[index:]
            dimensions = int(token)
            d_list = []
            for i in range(dimensions):
                index, token = next_token(line)
                line = line[index:]
                d_list.append(int(token))
            index, token = next_token(line)
            line = line[index:]
            one_tag = Tag('DW_TAG_array_type', d_list)
                        
        elif token == 'DW_TAG_string_type':
            pass
            one_tag = Tag('DW_TAG_string_type')
        
        #DW_TAG_array_type(name){...}
        elif token == 'DW_TAG_class_type' or token == 'DW_TAG_structure_type':
            class_or_structure = token
            index, token = next_token(line)
            a_name = None
            extra = None
            # The class name
            if token == '(':
                line = line[index:]
                            
                index, token = next_token(line)
                a_name = token
                line = line[index:]
                            
                index, token = next_token(line)
                line = line[index:]
                            
                index, token = next_token(line)
            if token == '{':
                line = line[index:]
                #recursively parse class
                # buggy here, what if {{}}
                index_1 = find_balanced_curly_brackets(line)
                #index_1 = line.find('}')
                extra = parse_2(line[:index_1], level+1) #members
                line = line[index_1 + 1:]
            one_tag = Tag(class_or_structure, (a_name, extra))

        elif token == 'DW_TAG_union_type':
            index, token = next_token(line)
            a_name = None
            extra = None
            if token == '(':
                line = line[index:]

                index, token = next_token(line)
                a_name = token
                line = line[index:]

                index, token = next_token(line)
                line = line[index:]

                index, token = next_token(line)
            if token == '{':
                line = line[index:]
                # buggy
                index_1 = find_balanced_curly_brackets(line)
                #index_1 = line.find('}')
                extra = parse_2(line[:index_1], level+1) #members
                line = line[index_1 + 1:]
            one_tag = Tag('DW_TAG_union_type', (a_name, extra))

        #DW_TAG_enumeration_type(num)
        elif token == 'DW_TAG_enumeration_type':
            index, token = next_token(line)
            line = line[index:]
            index, token = next_token(line)
            line = line[index:]
            enum_num = int(token)
            one_tag = Tag('DW_TAG_enumeration_type', enum_num)
            index, token = next_token(line)
            line = line[index:]
        
        #DW_TAG_base_type(base_type)
        elif token == 'DW_TAG_base_type':
            index, token = next_token(line)
            line = line[index:]
            base_type = ""
            while next_token(line)[1] != ')':
                index, token = next_token(line)
                line = line[index:]
                base_type += token
                base_type += " "
            one_tag = Tag('DW_TAG_base_type', base_type)
            index, token = next_token(line)
            line = line[index:]

        elif token == 'DW_TAG_bitfield':
            index, token = next_token(line) #get (
            line = line[index:]
            
            index, token = next_token(line) # get bitfield_size
            line = line[index:]
            one_tag = Tag('DW_TAG_bitfield', int(token))

            index, token = next_token(line) #get )
            line = line[index:]
        else:
            print('Unknown tag when parsing tags!(' + token + ')')
            print('Bug line:' + saved_line)
            sys.exit(1)
        member_tags.append(one_tag)
    if square_bracket > 0:
        print('Level ' + str(level) + ': Unbalanced [ and ]\n')
        print(saved_line)
        sys.exit(1)
    return class_members

# parser class_info and generate a map from struct name to to struct class
def parse(filename):
    class_map = {}
    with open(filename, 'r') as f:
        parse_phase = 0
        class_name = ""
        class_members = []
        class_type = ""
        for line in f:
            # parse class name
            if parse_phase % 3 == 0:
                class_type, class_name = parse_1(line)
            #parse class member
            elif parse_phase % 3 == 1:
                #if class_name == 'opj_codec_private':
                    #print('!!opj_codec_private', line)
                class_members = parse_2(line)
            #parse trailer, ending with ;            
            else: 
                if(line.startswith(';')):
                    one_class = Struct(class_name, class_members, class_type)
                    class_map[class_name] = one_class
                    #print(class_name, class_members)
                else:
                    print('Trailer parse Error!\n')
                    sys.exit(1)
            parse_phase += 1 
    return class_map


class Generator:
    mutate_types = {"int8_t": "Int8", "int16_t": "Int16", "int32_t": "Int32", "int64_t": "Int64", "double": "Double", "float": "Float"}
    def __init__(self, class_map, dag, sample_times=10):
        self.class_map = class_map
        self.dag = dag
        self.black_list = self.load_black_list()
        self.sample_times = sample_times
        self.h = []
        self.c = []
        self.h.append("#ifndef MEMFUZZ_MUTATE_H_\n#define MEMFUZZ_MUTATE_H_\n")
        self.c.append('#include "memfuzz_mutate.h"\n')
        self.c.append('#include "memfuzz_struct.h"\n')
        self.c.append('#include "memfuzz_util.h"\n')
        self.c.append('#include "memfuzz_hook.h"\n')
        self.c.append('#include "memfuzz_pool.h"\n')
        self.c.append('#include "memfuzz_config.h"\n')

    @staticmethod
    def define(a, b):
        return "#define " + str(a) + " " + str(b) + "\n"
    
    def gen_macro(self):
        macro = []
        macro.append("#include <stdint.h>\n")
        macro.append(self.define("Int8_t_NUM", str(len(Values.Int8()))))
        macro.append(self.define("Int16_t_NUM", str(len(Values.Int16()))))
        macro.append(self.define("Int32_t_NUM", str(len(Values.Int32()))))
        macro.append(self.define("Int64_t_NUM", str(len(Values.Int64()))))
        macro.append(self.define("Float_NUM", str(len(Values.Float()))))
        macro.append(self.define("Double_NUM", str(len(Values.Double()))))
        return "".join(macro)

    #for(int i = 0; i < num; i++)
    @staticmethod
    def gen_forloop(cnt):
        code = "for(int i = 0; i < " + str(cnt) + "; i++)"
        return code

    @staticmethod
    def gen_basic_types():
        codes = []
        for mutate_type in Generator.mutate_types:
            code = "void assign_" + mutate_type + "(" + mutate_type + "* ptr, int level);\n"
            code = "void assign_" + mutate_type + "(" + mutate_type + "* ptr, int level)\n{\n"
            code += Generator.gen_forloop(Generator.mutate_types[mutate_type] + "_NUM")
            code += "\n{\n*ptr = " + str(Generator.mutate_types[mutate_type]) + "[i];\nsafe_print(MEMFUZZ_OUTFILE);\n}\n"
            code += "}\n"
            codes.append(code)
        return "".join(codes)

    @staticmethod
    def gen_enums():
        code = "void assign_enum(void* ptr, int num);\n{\nfor(int i = 0; i < num; i++)\n    {\n    *(int*)ptr = i;    \n}\n}"
        return code

    # generate the mutation code snippet for a class member
    def gen_struct_member_mutate(self, class_member, prefix):
        code = "    "
        pre = prefix
        herper_function = None
        if class_member.is_bitfield():
            code = "//ptr->" + class_member.name + " = ...(bitfield mutation);\n"
            return pre + code
        # Mutate base type
        if class_member.is_base():
            base_type = class_member.get_base_type()
            # We can not mutate void tyoe
            if base_type == "void " or base_type == "void":
                return code
            # Mutate pointer or array
            if class_member.is_pointer() or class_member.is_array():
                # a pointer to an array or an array of pointers, we do not mutate them
                if class_member.is_pointer() and class_member.is_array():
                    code = "//ptr->" + class_member.name + " = ...(base_type* array[])\n"
                # pointer of base type. It is believed to be a dynamic array, check relations.
                elif class_member.is_pointer():
                    pointer_level = class_member.get_pointer_level()
                    if pointer_level == 0:
                        print("Internal error! pointer Level is 0!")
                        sys.exit(1)
                    # May be some pointer or array
                    if pointer_level == 1:
                        # a special case is char*
                        if base_type == "char ":
                            # code = "//mutate_c_str(ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                            code = "mutate_c_str(ptr->" + class_member.name + ");\n"
                        # we assume it is a dynamic array
                        else:
                            mutate_type = Values.get_values(base_type)
                            code =  '#ifdef ALLOC_HOOK\n'
                            code += '    len = alloc_find(ptr->' + class_member.name + ');\n'
                            code += '    len /= sizeof(' + mutate_type + ');\n'
                            code += '    if(len != 0){ mutate_' + mutate_type + '_array(ptr->' + class_member.name + ', level + 1, len); }\n'
                            code += '    #else\n'
                            code += '    //ptr->' + class_member.name + ' = ...(' + str(class_member) + ')\n'
                            code += '    #endif\n'
                    # It should be 2d array, usually raw bytes, do not mutate and leave it to AFL
                    elif pointer_level == 2:
                        code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                    else:
                        code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                # array of base type
                else:
                    dimensions = class_member.get_array_dimension()
                    dimensions_len = len(dimensions)
                    total_elems = 1
                    for i in dimensions:
                        total_elems *= i
                    #dynamic array
                    if total_elems == 0:
                        code = "//ptr->" + class_member.name + " = (" + base_type + "*)realloc(sizeof(" + base_type + "));\n";
                    else:
                        #do sample mutation
                        mutate_type = Values.get_values(base_type)
                        code = "assign_" + mutate_type + "_array(&(ptr->" + class_member.name + "), level + 1, " + str(total_elems) + ");\n"
                        #do shuffle
            # Base type, do interesting, add/minus/shift/random
            else:
                #interesting
                mutate_type = Values.get_values(base_type)
                code = "mutate_" + mutate_type + "(&(ptr->" + class_member.name + "), level+1);\n"

        #complex type, we apply rules to all its fields. 
        elif class_member.is_structure():
            struct_type = class_member.get_struct_type()
            # Unknown structure, ignore
            if struct_type[0] != None and struct_type[0] not in self.class_map:
                code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
            # structre* or structure[]
            elif class_member.is_pointer() or class_member.is_array():
                # a pointer to array or an array of pointers? 
                if class_member.is_pointer() and class_member.is_array():
                    code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                # pointer of structure, usually it just point to one object. It can also be dynamic array, we may check it.
                # It should be checked by the malloc information
                elif class_member.is_pointer():
                    # named structure
                    if struct_type[0] != None:
                        code = "{\n        if(ptr->" + class_member.name + ") { mutate_" + struct_type[0] + "(ptr->" + class_member.name + ", level+1, 1); }\n"
                        code += '        len = 0;\n'
                        code += '        arr = pool_get_values("' + struct_type[0] + '", &len);\n'
                        code += '        shuffle(arr, len, sizeof(void*));\n'
                        code += '        ptr_save = ptr->' + class_member.name + ';\n'
                        code += '        for(i = 0; i < len && i < SAMPLE_TIMES; i++){\n'  
                        code += '            ptr->' + class_member.name + ' = arr[i];\n'
                        code += '            safe_print(MEMFUZZ_OUTFILE);\n'
                        code += '        }\n'
                        code += '        ptr->' + class_member.name + ' = ptr_save;\n'
                        code += '        free(arr);\n    }\n'
                    # anonymous structure
                    # TODO
                    else:
                        code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                # array of structure
                else:
                    # named structure
                    if struct_type[0] != None:
                        dimensions = class_member.get_array_dimension()
                        if len(dimensions) >= 2:
                            code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
                        else:
                        # we sample all element here
                            if dimensions[0] < self.sample_times:
                                code = "for(int i = 0; i < " + str(dimensions[0]) + "; i++)\n    {\n        mutate_" + struct_type[0] + "(&(ptr->" + class_member.name + ")[i], level+1, 0);\n    }\n"
                        # choose samples_times elements to mutate
                            else:
                                code = "for(int i = 0; i < SAMPLE_TIMES; i++)\n    {\n        mutate_" + struct_type[0] + "(&(ptr->" + class_member.name + ")[random()%" + str(dimensions[0]) + "], level+1, 0);\n    }\n"
                    # anonymous structure
                    # TODO
                    else:
                        code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
            # structure
            else:
                # named structure
                if struct_type[0] != None:
                    code = "mutate_" + struct_type[0] + "(&(ptr->" + class_member.name + "), level+1, 0);\n"
                # anonymous structure
                # TODO
                else:
                    code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"

        # Enumeration
        elif class_member.is_enumerate():
            # Can it really happen? Ignore.
            if class_member.is_pointer() or class_member.is_array():
                code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"
            # enum
            else:
                enum_num = class_member.get_enum_num()
                code = "mutate_enum(&(ptr->" + class_member.name + "), " + str(enum_num) + ");\n"
        else:
            code = "//ptr->" + class_member.name + " = ...(" + str(class_member) + ")\n"

        return pre + code
    
    # Some structure/class/union we do not want to mutate
    def load_black_list(self, black_list_path='./blacklist.txt'):
        black_list = []
        if(os.path.exists('blacklist.txt') == False):
            return black_list
        with open('blacklist.txt', 'r') as f:
            for line in f:
                black_list.append(line.strip())
        return black_list

    # generate mutation function for a class/struct/union
    def gen_struct_mutate(self, class_name):
        # patch for c++
        # if class_name in self.black_list or class_name not in self.dag.struct_codes:
        #     return ""
        struct = self.class_map[class_name]
        # we can only declare and define it as void*, otherwise compiler failed
        # ptr1 is the pointer we are mutating, level is the recursive level, check indicates if we need to check the address is valid
        prototype = "void mutate_" + struct.name + "(void* ptr1, int level, int check)"
        self.h.append(prototype + ";\n")
        codes = []
        # if it is not found in known struct
        if class_name in self.black_list or class_name not in self.dag.struct_codes:
            codes.append(prototype + "{return ;}\n")
            self.c.append("".join(codes))
            return "".join(codes)
        # Reach max recursion, return
        code = prototype + "{\n    if(level > MAX_LEVEL) return ;\n"
        codes.append(code)
        # NULL, return, why can it happen?
        code = "    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;\n"
        codes.append(code)
        # Debug information
        code = '    #ifdef DEBUG\n    printf("enter mutate_' + class_name + '  \\n"); fflush(stdout);\n    #endif\n'
        codes.append(code)
        # Check if the pointer is mutated before
        code = "    if(dup_is_in(ptr1)) return ;\n    dup_insert(ptr1);\n" 
        codes.append(code)
        # Some values for iteration
        code = '    int i, len;\n    void** arr;\n    void* ptr_save = NULL;\n'
        codes.append(code)
        # Cast to the correct type
        code = "    " + struct.type + " " + struct.name + "* ptr = ptr1;\n"
        codes.append(code)
        #struct, class or union
        if struct.type == "class" or struct.type == "struct" or struct.type == "union":
            for member in struct.members:
                code = self.gen_struct_member_mutate(member, "    ")
                codes.append(code)
        # Add to the pool
        code = '    pool_insert("' + struct.name + '", ptr1);\n'
        codes.append(code)
        # Debug
        code = '    #ifdef DEBUG\n    printf("leave mutate_' + class_name + '  \\n"); fflush(stdout);\n    #endif\n'
        codes.append(code)
        codes.append("}\n")
        self.c.append("".join(codes))
        return "".join(codes)
    
    def dump(self):
        print("Generate memfuzz_mutate.h")
        with open("memfuzz_mutate.h", "w") as f:
            for i in self.h:
                f.write(i)

        print("Generate memfuzz_mutate.c")
        with open("memfuzz_mutate.c", "w") as f:
            for i in self.c:
                f.write(i)

    # generate code for memfuzz_mutate.h and memfuzz_mutate.c
    def generate(self):
        for struct in self.class_map:
            self.gen_struct_mutate(struct)
        print("DEBUG: generate " + str(len(self.class_map)) + " structure types.")
        self.h.append("#endif\n")


# A DAG for class dependency, also handle enumeration
class DAG:
    def __init__(self, class_map, target):
        self.class_dep = {}
        self.target = target
        self.class_map = class_map
        # Build dependency
        for a_class in class_map:
            depends = self.find_dep(class_map[a_class].members)
            # "a_class" depends on "depends"
            self.class_dep[a_class] = depends

    def find_soft_dep(self, members):
        depends = []
        for a_member in members:
            if a_member.is_structure():
                struct_type = a_member.get_struct_type()
                if struct_type[0] != None:
                    depends.append(struct_type[0])
                # Anonymous class, check recursively
                if struct_type[1] != None:
                    depends = depends + self.find_dep(struct_type[1])
        return depends

    def find_dep(self, members):
        depends = []
        for a_member in members:
            
            if a_member.is_structure() and not a_member.is_pointer():
                struct_type = a_member.get_struct_type()
                if struct_type[0] != None:
                    depends.append(struct_type[0])
                # Anonymous class, check recursively
                if struct_type[1] != None:
                    depends = depends + self.find_dep(struct_type[1])
        return depends
        
    def __str__(self):
        s = ""
        for i in self.class_map:
            s += i
            s += ": [" + ", ".join(self.class_map[i]) + "]\n"
        return s

    # mutate function for each user defined enumeration
    def gen_enum_mutate(self):
        pattern = re.compile(' *([_a-zA-Z][_a-zA-Z0-9]*) *= *([0-9]+) *,')
        self.enum_item = {}
        for enum in self.enum_codes:
            l = re.findall(pattern, self.enum_codes)
            self.enum_item[enum] = l
        h_codes = []
        c_codes = []
        for enum in self.enum_item:
            code = 'void mutate_enum_' + enum + '(void *ptr1, int level)'
            h_codes.append(code + ';\n')
            c_codes.append(code + '\n{\nenum ' + enum + ' *ptr = (enum ' + enum + '*)ptr1;\n')
            for i in self.enum_item[enum]:
                c_codes.append('*ptr = ' + i[0] + ';\nsafe_print(MEMFUZZ_OUTFILE);\n')
            c_codes.append('}\n')
        return h_codes, c_codes

    # return an Enum class from a codes list
    def enum_codes_to_enum_class(self, codes):
        identifier_pattern = re.compile("[_a-zA-Z][_a-zA-Z0-9]*")
        # get name
        line = codes[0]
        index = line.find("enum")

        line = line[index + 4: ]
        index = re.search(identifier_pattern, line)
        if index:
            index1, index2 = index.span()
            name = line[index1: index2]
        else:
            name = None
        # get values
        vals = {}
        for line in codes:
            l = line.split("=")
            if len(l) == 2:
                l[0] = l[0].strip()
                l[1] = int(l[1].strip()[:-1])
                vals[l[0]] = l[1]
        ret = Enum(name, vals)
        return ret

    # return codes string with Anonymous enumeration replaced. It is used to avoid redefinition of anonymous enum
    def patch_struct(self, codes):
        pattern = re.compile("[ \t]*enum *{")
        identifier_pattern = re.compile("[_a-zA-Z][_a-zA-Z0-9]*")
        l = []
        length = len(codes)
        start = -1
        end = -1
        ret = []
        for i in range(length):
            line = codes[i]
            if start == -1:
                obj = re.search(pattern, line)
                # Enter enum
                if obj:
                    start = i
                # Not related to enum, copy line
                else:
                    ret.append(line)
            # In enum scope
            else:
                #The end of enum scope
                if line.endswith("*/\n"):
                    search_obj = re.search(identifier_pattern, line)
                    end = i
                    # Rare case some struct define anonymous enum but no member
                    if search_obj == None:
                        print("patch_struct warning! Can not find member name!\nCodes:\n")
                        print("".join(codes))
                        print("\n\nWhen parsing:\n")
                        print(line)
                        print("=================================WARNING END========================================\n")
                        member_name = ""
                    else:
                        index = search_obj.span()
                        member_name = line[index[0]: index[1]]

                    enum_obj = self.enum_codes_to_enum_class(codes[start: end])
                    if enum_obj not in self.enum_names:
                        print("path_struct error! Can not find the enum in map!\n")
                        print(enum_obj)
                        sys.exit(1)
                    start = end = -1
                    # Rebuild this class member with enum name
                    ret.append("\tenum " + self.enum_names[enum_obj] + " " + member_name + ";\n")
        return ret


        
    #extract all user defined structs and enumeration in the target program 
    def extract_struct(self, target):
        #path = "./third/src/pahole"
        path = "./pahole" #the pahole path
        if os.path.exists("./memfuzz_enum.h"):
            os.system("rm ./memfuzz_enum.h")
        if os.path.exists("./memfuzz_enum1.h"):
            os.system("rm ./memfuzz_enum1.h")
        cmd = path + " -a -A --show_private_classes -M -I --classes_as_structs " + target + " > /tmp/class.h"
        msg = os.system(cmd)
        if msg != 0:
            print('Error: pahole error or target not compiled with -g')
            sys.exit(1)
        identifier_pattern = re.compile("[_a-zA-Z][_a-zA-Z0-9]*")
        
        self.enum_codes = {}
        # check enumeration and put enum_obj-code into map
        if os.path.exists("./memfuzz_enum.h"):
            with open("./memfuzz_enum.h", "r") as f:
                # Then we should parse the enum to deduplicate
                codes = []
                stage = 0
                name = ""
                for line in f:
                    codes.append(line)
                    if line.endswith("};\n"):
                        enum_obj = self.enum_codes_to_enum_class(codes)
                        #print("Add enum " + enum_obj.name + "\n")
                        codes = "".join(codes)
                        self.enum_codes[enum_obj] = codes
                        codes = []
            
        # check anonymous enumeration and put anonymous_enum-code into map
        if os.path.exists("./memfuzz_enum1.h"):
            with open("./memfuzz_enum1.h", "r") as f:
                codes = []
                name = None
                for line in f:
                    codes.append(line)
                    if line.endswith("};\n"):
                        enum_obj = self.enum_codes_to_enum_class(codes)
                        codes = "".join(codes)
                        self.enum_codes[enum_obj] = codes
                        codes = []

        # Rename anonymous enum and put them into map, also change enum_codes so that it shows the new name of anonymous enum
        anonymous_num = 0
        self.enum_names = {}
        for i in self.enum_codes:
            if i.name == None:
                self.enum_names[i] = "memfuzz_anonymous_enum_" + str(anonymous_num)
                tmp = self.enum_codes[i].split("\n")
                tmp[0] = "enum memfuzz_anonymous_enum_" + str(anonymous_num) + " {"
                tmp = "\n".join(tmp)
                self.enum_codes[i] = tmp
                anonymous_num += 1

        # Get struct/class/union
        struct_map = {}
        anonymous_struct_cnt = 0
        typedef_name_set = set()
        with open("/tmp/class.h", "r") as f:
           # We should parse all struct and save them in a map
            stage = 0
            if_add = False
            codes = []
            name = ""
            for line in f:
                codes.append(line)
                # where it is used, ignore it
                if stage == 0:
                    stage = 1
                # check if it is a user defined struct
                elif stage == 1:
                    if re.search("/usr/", line):
                        if_add = False # make it true to avoid compiler complaining.
                    elif re.search("./", line):
                        if_add = True
                    elif re.search("/home/", line):
                        if_add = True
                    else:
                        print("Unknown source, check it manually")
                        sys.exit(1)
                    stage = 2
                # find the struct name or skip if typedef
                elif stage == 2:
                    # struct
                    if line[0] == 's':
                        line = line[7:]
                    # class
                    elif line[0] == 'c':
                        line = line[6:]
                    # union
                    elif line[0] == 'u':
                        line = line[6:]
                    # typedef
                    # Check here, it can also have name
                    elif line[0] == 't':
                        name = ""
                        stage = 3
                        continue
                    else:
                        print("Parse struct stage 2 failed\n")
                        sys.exit(1)
                    # Probably we need a better solution here
                    # find something between class/struct/union/typedef and {
                    obj = re.search(identifier_pattern, line)
                    if obj != None:
                        index1, index2 = obj.span()
                        name = line[index1: index2]
                    else:
                        name = ""
                    stage = 3
                # check if the struct ends
                elif stage == 3:
                    if line[:2] == "};":
                        if name == "":
                            name = "memfuzz_anonymous_struct_" + str(anonymous_struct_cnt)
                            anonymous_struct_cnt += 1
                            if codes[2][0] == "s":
                                codes[2] = "struct " + name + " {\n"
                            elif codes[2][0] == "c":
                                codes[2] = "class " + name + " {\n" 
                            elif codes[2][0] == "u":
                                codes[2] = "union " + name + " {\n" 
                            else: 
                                print("struct parse stage 3 pattern error! };\n")
                                print("Error codes:\n")
                                print("".join(codes))
                                sys.exit(1)
                        if if_add:
                            # patch the codes to replace anonymous enum to avoid redefinition
                            codes = self.patch_struct(codes)
                            struct_map[name] = "".join(codes)
                        stage = 0
                        if_add = False
                        name = ""
                        codes = []
                    # typedef struct/onion {} xxx; or struct (name) {} __attribute...;
                    elif line[:2] == "} ":
                        if name == "":
                            end_index = line.find(';')
                            typedef_name = line[2:end_index]
                            name = "memfuzz_anonymous_struct_" + str(anonymous_struct_cnt)
                            anonymous_struct_cnt += 1
                            # typedef struct {} xxx;
                            if codes[2][0] == "t":
                                if codes[2][8] == "s":
                                    codes[2] = "typedef struct " + name + " {\n" 
                                elif codes[2][8] == "u":
                                    codes[2] = "typedef union " + name + " {\n"
                                else:
                                    print("Error: unknown typedef type!")
                            elif codes[2][0] == "s":
                                codes[2] = "struct " + name + " {\n"
                            elif codes[2][0] == "u":
                                codes[2] = "union " + name + " {\n}"
                            elif codes[2][0] == "c":
                                codes[2] = "class " + name + " {\n}"
                            else:
                                print("struct parse stage 3 pattern error! } \n")
                                print("Error codes:\n")
                                print("".join(codes))
                                sys.exit(1)
                            # do not add duplicate typedef
                            if typedef_name in typedef_name_set:
                                if_add = False
                            else:
                                typedef_name_set.add(typedef_name)
                        else:
                            print("struct parse stage 3 failed\n")
                            print("Error near:\n")
                            print("".join(codes))
                            sys.exit(1)
                        if if_add:
                            codes = self.patch_struct(codes)
                            struct_map[name] = "".join(codes)
                        stage = 0
                        if_add = False
                        name = ""
                        codes = []
        # It stores the codes for each struct
        self.struct_codes = struct_map

    # Build the dependency of each class so we can generate them in order
    # Topological visit
    def get_order(self):
        class_dep = self.class_dep.copy()
        order = []
        while len(class_dep) > 0:
            flag = False
            # find a class without dependency
            for a_class in class_dep:
                if not class_dep[a_class]:
                    flag = True
                    order.append(a_class)
                    name = a_class
                    break
            if flag == False:
                print("Loop detected\n")
                for i in class_dep:
                    print(i, class_dep[i])
                sys.exit(1)
            for a_class in class_dep:
                class_dep[a_class] = list(filter(lambda a: a != name, class_dep[a_class]))
            class_dep.pop(name)
        return order
    
    # generate memfuzz_struct.h
    def gen_memfuzz_struct(self):
        print("Generate memfuzz_struct.h")
        self.extract_struct(self.target)
        print("DEBUG: generate " + str(len(self.enum_codes)) + " enum types.")
        codes = []
        code = "#ifndef _MEMFUZZ_STRUCT_H_\n#define _MEMFUZZ_STRUCT_H_\n#include<zlib.h>\n#include<setjmp.h>\n#include<pthread.h>\n/*Add necessary header here to avoid compile problems*/\n"
        codes.append(code)
        order = self.get_order()
        #declare all struct first
        codes.append("/*Struct Declaration Begin*/\n")
        for a_class in order:
            if a_class in self.struct_codes:
                code = self.class_map[a_class].type + " " + a_class + ";\n"
                codes.append(code)
        
        #define all enumerations
        codes.append("/*Enumeration Definition Begin*/\n")
        for enum_obj in self.enum_codes:
            codes.append(self.enum_codes[enum_obj])
        codes.append("/*Struct Definition Begin*/\n")
        #define all structs
        for name in order:
            #check if the struct is user defined
            if name in self.struct_codes:
                codes.append(self.struct_codes[name])
        code = "#endif\n"
        codes.append(code)
        with open("memfuzz_struct.h", "w") as f:
            for code in codes:
                f.write(code)
        

def extract_all_struct_types_in_members(class_map):
    ret = []
    for class_name in class_map:
        a_class = class_map[class_name]
        for a_member in a_class.members:
            if a_member.is_structure():
                ret.append(a_member.get_struct_type())
    return ret


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("./parser.py input_program")
        sys.exit(1)
    target = sys.argv[1]
    gen_classinfo = "./gen_classinfo -a -A --show_private_classes -M --classes_as_structs" # third/pahole/src/pahole
    pahole = "./pahole" # third/gen_struct/pahole
    os.system("rm -f class_info")
    # Note the target program should be compiled with -g
    os.system(gen_classinfo + " " + target + "> class_info")
    if not os.path.exists("class_info"):
        print("Error: pahole failed. The target program/library should be compiled with -g.")
        sys.exit(1)
    class_map = parse("./class_info")
    # for aclass in class_map:
    #     print(aclass)
    #     for member in class_map[aclass].members:
    #         print('    ' + str(member))
   
    # TODO: rename the anonymous struct
    rename_anonymous(class_map)

    all_struct_types_in_members = extract_all_struct_types_in_members(class_map)
    # fill in the missing type
    for a_struct in all_struct_types_in_members:
        if a_struct[0] is not None and a_struct[0] not in class_map:
            # We do not know the members and do not care about its type
            class_map[a_struct[0]] = Struct(a_struct[0], [], 'struct')

    classes = class_map.copy()
            
    # analyze the core structure
    for a_class in classes:
        print(str(classes[a_class]))
        for member in classes[a_class].members:
            print(str(member))
        print("=========================")


    # generate memfuzz_struct.h, the class is orgranized in dep order
    dag = DAG(classes, target)
    dag.gen_memfuzz_struct()
    # generate memfuzz_mutate.h and memfuzz_mutate.c
    generator = Generator(class_map, dag)
    generator.generate()
    generator.dump()
    # The generated memfuzz_struct.h may be incomplete because some structs are in dynamic libs. We manually fix them

