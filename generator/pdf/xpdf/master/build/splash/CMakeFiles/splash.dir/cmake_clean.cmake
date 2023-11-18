file(REMOVE_RECURSE
  "libsplash.a"
  "libsplash.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/splash.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
