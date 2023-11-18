export AFL_SKIP_CPUFREQ=1
AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 ~/MemFuzz/src/afl-2.52b/afl-fuzz -S xpdf -m 8G -t 5000 -i input -o output -- ~/Product/xpdf/master/exe_fuzz/bin/pdftops -f 2 -l 4 -level2 -noembt1 -preload -nocrop -noshrink -nocenter -pagecrop -userunit -duplex -upw rome @@ /dev/null
