#gcc -o generator generator.c -ljpeg -L./build/lib -l:libmemfuzz.a
gcc -o generator ./build/*.o jpegtran.c cdjpeg.c transupp.c rdswitch.c libjpeg.a -I./build `pkg-config --cflags --libs glib-2.0` -Wno-deprecated-declarations

