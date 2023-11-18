file(REMOVE_RECURSE
  "libgoo.pdb"
  "libgoo.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/goo.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
