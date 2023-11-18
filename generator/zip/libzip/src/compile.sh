gcc -g -o generator ./build/*.o -I.. -I../lib generator.c ../lib/libzip.a -I./build -lz -lm -lbz2  -llzma -lssl -lcrypto `pkg-config --cflags --libs glib-2.0` -Wno-deprecated-declarations 
#-fsanitize=address
#-l:../lib/libzip.so -L../lib/
