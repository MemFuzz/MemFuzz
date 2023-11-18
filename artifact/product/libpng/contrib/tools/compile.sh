#gcc -g -O0 -o pngfix1 pngfix1.c -l:libpng.a -L../../ -lm -lz `pkg-config --cflags --libs glib-2.0` -Wno-deprecated-declarations 
gcc -g -o generator ./build/*.o generator.c -I./build ../../libpng16.a  `pkg-config --cflags --libs glib-2.0` -lz -lm
