There are some special targets that are not built by Makefile but we may use them. Other apps will be built by Makefile by default.

1. ImageMagick: we use readWriteImages.cpp as target for parser finding result.
2. Miniz: Miniz has no built in apps. We use parser_target.c for parser finding result. We use fuzz_target.c for fuzzing target.
3. Zlib: minizip and miniunz is under contrib/minizip folder.

