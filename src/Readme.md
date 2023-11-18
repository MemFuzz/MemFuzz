# MemFuzz

## Environment: 
The codes are tested under Ubuntu 18.04. The tool should work as long as your system supports malloc__hook_ because MemFuzz initializes all heap allocated memory to 0 and records the address as well as size to do safe memory access.

## Install:
`cd third/gen_struct && cmake . && make -j64`\
`cd third/pahole/src && cmake . && make -j64`\
`cd afl-2.52b && make -j64`

## Usage
We use giflib as an example to show the usage. Run the following command to start fuzzing.
1. `./mk_lib.sh ../../artifact/product/giflib/giffix`
2. `cp -r build ../../artifact/product/giflib/`
3. `cd ../../artifact/product/giflib/`
4. `./compile.sh`
5. `cd ../../../src/`
4. `./afl-2.52b/afl-fuzz -i ../../artifact/p2/seed/giflib -o output -S giflib -G ../../artifact/product/giflib/generator -t 5000 -m 8G -- ../../artifact/product/giflib/gif2rgb @@`
