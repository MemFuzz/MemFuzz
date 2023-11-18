export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -S libpng -m 8G -t 5000 -G ~/MemFuzz/generator/png/src/contrib/tools/generator -i input -o output -- ~/Product/libpng/master/exe_fuzz/bin/pngfix @@
