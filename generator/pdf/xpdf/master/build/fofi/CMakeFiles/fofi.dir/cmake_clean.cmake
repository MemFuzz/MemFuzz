file(REMOVE_RECURSE
  "libfofi.a"
  "libfofi.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/fofi.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
