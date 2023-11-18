export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -G ./src/generator -S libjpeg -m 8G -t 5000 -i input -o output -- ~/Product/libjpeg/master/exe_fuzz/bin/djpeg -bmp @@
