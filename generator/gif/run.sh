export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -G ./src/generator -i input -o output -m 8G -t 5000 --  ~/Product/giflib/master/exe_fuzz/bin/gif2rgb @@
