import sys
from elftools.elf.elffile import ELFFile
from elftools.dwarf import dwarfinfo

def extract_member_types(filename, structure_name):
    with open(filename, 'rb') as file:
        elffile = ELFFile(file)
        dwarf_info = elffile.get_dwarf_info()

        for CU in dwarf_info.iter_CUs():
            for DIE in CU.iter_DIEs():
                if DIE.tag == 'DW_TAG_structure_type' or DIE.tag == 'DW_TAG_class_type':
                    # Check if the DIE represents the structure you're interested in
                    if DIE.attributes['DW_AT_name'].value.decode('utf-8') == structure_name:
                        # Now, look for member variables within the structure DIE
                        for child in DIE.iter_children():
                            if child.tag == 'DW_TAG_member':
                                member_name = child.attributes['DW_AT_name'].value.decode('utf-8')
                                member_type_offset = child.attributes['DW_AT_type'].value
                                
                                # Retrieve type information from the type offset
                                member_type = None
                                for type_die in CU.iter_DIEs():
                                    if type_die.offset == member_type_offset:
                                        member_type = type_die
                                        break
                                
                                if member_type is not None:
                                    print(member_type)
                                    # member_type_name = member_type.attributes['DW_AT_name'].value.decode('utf-8')
                                else:
                                    member_type_name = 'UnknownType'
                                
                                # print(f"Member: {member_name}, Type: {member_type_name}")

if __name__ == '__main__':
    extract_member_types(sys.argv[1], 'A')
