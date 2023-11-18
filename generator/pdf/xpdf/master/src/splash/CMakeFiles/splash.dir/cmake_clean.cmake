file(REMOVE_RECURSE
  "libsplash.pdb"
  "libsplash.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/splash.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
