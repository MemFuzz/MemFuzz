gcc -o generator -g generator.c libzip.a ./build/*.o -I./src -I./build `pkg-config --cflags --libs glib-2.0`
