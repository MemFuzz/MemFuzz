Command line used to find this crash:

/home/youwei/MemFuzz/src//afl-2.52b/afl-fuzz -S generator -m 8G -t 5000 -G /home/youwei/MemFuzz/generator/pdf/xpdf/master/exe_raw/bin/pdfinfo -i input -o output -- /home/youwei/MemFuzz/Product/xpdf/master/exe_fuzz/bin/pdftops -f 2 -l 4 -level2 -noembt1 -preload -nocrop -noshrink -nocenter -pagecrop -userunit -duplex -upw rome @@ /dev/null

If you can't reproduce a bug outside of afl-fuzz, be sure to set the same
memory limit. The limit used for this fuzzing session was 8.00 GB.

Need a tool to minimize test cases before investigating the crashes or sending
them to a vendor? Check out the afl-tmin that comes with the fuzzer!

Found any cool bugs in open-source tools using afl-fuzz? If yes, please drop
me a mail at <lcamtuf@coredump.cx> once the issues are fixed - I'd love to
add your finds to the gallery at:

  http://lcamtuf.coredump.cx/afl/

Thanks :-)
