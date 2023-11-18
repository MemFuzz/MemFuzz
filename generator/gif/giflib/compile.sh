gcc generator.c libgif.a libutil.a libgif.a build/lib/libmemfuzz.a -Ibuild/include `pkg-config --cflags --libs glib-2.0` -Wno-deprecated-declarations -lm -o generator -g
