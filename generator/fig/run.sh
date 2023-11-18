export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -G ./src/xfig-3.2.8b/src/xfig -S xfig -m 8G -t 5000 -i input -o output -- ~/Product/fig2dev/master/exe_fuzz/bin/fig2dev @@ -L pdf /tmp/null
