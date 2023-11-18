#ifndef MEMFUZZ_MUTATE_H_
#define MEMFUZZ_MUTATE_H_
void mutate_ColorMapObject(void* ptr1, int level);
void mutate_GifColorType(void* ptr1, int level);
void mutate_GifFileType(void* ptr1, int level);
void mutate_GifImageDesc(void* ptr1, int level);
void mutate_SavedImage(void* ptr1, int level);
void mutate_ExtensionBlock(void* ptr1, int level);
#endif
