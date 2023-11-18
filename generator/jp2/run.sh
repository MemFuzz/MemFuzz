export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -f 1.jp2 -G ~/MemFuzz/generator/jp2/src/src/bin/jp2/generator -S openjpeg -m 8G -t 5000 -i input -o output -- ~/Product/openjpeg/master/exe_fuzz/bin/opj_decompress -i @@ -o /tmp/null.bmp
