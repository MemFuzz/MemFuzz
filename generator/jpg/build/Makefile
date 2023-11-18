all:
	make static
	gcc -g -c a.c
	gcc -g -o a a.o libmemfuzz.a

static:
	gcc -c -g memfuzz_util.c	
	gcc -c -g memfuzz_mutate.c
	ar rcs libmemfuzz.a memfuzz_util.o memfuzz_mutate.o

shared:
	gcc -g -fPIC -c memfuzz_util.c
	gcc -g -fPIC -c memfuzz_mutate.c
	gcc -g -shared -fPIC -o libmemfuzz.so memfuzz_util.o memfuzz_mutate.o

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf a
	rm -rf *.a

