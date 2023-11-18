gcc -g -O0 -o generator generator.c libpng16.a -L./build/ -lm -lz -l:libmemfuzz.a `pkg-config --cflags --libs glib-2.0` -Wno-deprecated-declarations
