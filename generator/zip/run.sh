export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -S libzip -m 8G -G ./src/src/generator -t 5000 -i input -o output -- ~/Product/libzip/master/exe_fuzz/bin/ziptool -c @@ cat 0
