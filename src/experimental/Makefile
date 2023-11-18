all:
	gcc -c cwrapper.cpp
	ar rcs libcwrapper.a cwrapper.o
	gcc main.c libcwrapper.a
