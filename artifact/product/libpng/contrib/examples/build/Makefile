all:
	make static
	gcc -g -c a.c `pkg-config --cflags --libs glib-2.0`  -Wdeprecated-declarations
	gcc -g -o a a.o libmemfuzz.a `pkg-config --cflags --libs glib-2.0` -Wdeprecated-declarations

static:
	gcc -c -g memfuzz_util.c `pkg-config --cflags --libs glib-2.0`  -Wdeprecated-declarations
	gcc -c -g memfuzz_mutate.c `pkg-config --cflags --libs glib-2.0` -Wdeprecated-declarations
	gcc -c -g memfuzz_hook.c `pkg-config --cflags --libs glib-2.0`  -Wdeprecated-declarations
	gcc -c -g memfuzz_pool.c `pkg-config --cflags --libs glib-2.0`  -Wdeprecated-declarations
	ar rcs libmemfuzz.a memfuzz_util.o memfuzz_mutate.o memfuzz_hook.o memfuzz_pool.o 
	#gcc -c -g alloc_hook.c `pkg-config --cflags --libs glib-2.0` 
	#ar rcs liballochook.a alloc_hook.o

shared:
	gcc -g -fPIC -c memfuzz_util.c `pkg-config --cflags --libs glib-2.0` -Wdeprecated-declarations
	gcc -g -fPIC -c memfuzz_mutate.c `pkg-config --cflags --libs glib-2.0` -Wdeprecated-declarations
	gcc -g -fPIC -c memfuzz_hook.c `pkg-config --cflags --libs glib-2.0`-Wdeprecated-declarations
	gcc -c -g memfuzz_pool.c `pkg-config --cflags --libs glib-2.0`-Wdeprecated-declarations
	gcc -g -shared -fPIC -o libmemfuzz.so memfuzz_util.o memfuzz_mutate.o memfuzz_hook.o memfuzz_pool.o -Wdeprecated-declarations

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf a
	rm -rf *.a

