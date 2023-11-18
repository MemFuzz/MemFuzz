#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate_ColorMapObject(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_ColorMapObject  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ColorMapObject* ptr = ptr1;
    mutate_int32_t(&(ptr->ColorCount), level+1);
    mutate_int32_t(&(ptr->BitsPerPixel), level+1);
    mutate_int8_t(&(ptr->SortFlag), level+1);
    {
        if(ptr->Colors) { mutate_GifColorType(ptr->Colors, level+1, 1); }
        len = 0;
        arr = pool_get_values("GifColorType", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->Colors;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->Colors = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->Colors = ptr_save;
        free(arr);
    }
    pool_insert("ColorMapObject", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ColorMapObject  \n"); fflush(stdout);
    #endif
}
void mutate_GifColorType(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_GifColorType  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct GifColorType* ptr = ptr1;
    mutate_int8_t(&(ptr->Red), level+1);
    mutate_int8_t(&(ptr->Green), level+1);
    mutate_int8_t(&(ptr->Blue), level+1);
    pool_insert("GifColorType", ptr1);
    #ifdef DEBUG
    printf("leave mutate_GifColorType  \n"); fflush(stdout);
    #endif
}
void mutate_GifFileType(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_GifFileType  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct GifFileType* ptr = ptr1;
    mutate_int32_t(&(ptr->SWidth), level+1);
    mutate_int32_t(&(ptr->SHeight), level+1);
    mutate_int32_t(&(ptr->SColorResolution), level+1);
    mutate_int32_t(&(ptr->SBackGroundColor), level+1);
    mutate_int8_t(&(ptr->AspectByte), level+1);
    {
        if(ptr->SColorMap) { mutate_ColorMapObject(ptr->SColorMap, level+1, 1); }
        len = 0;
        arr = pool_get_values("ColorMapObject", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->SColorMap;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->SColorMap = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->SColorMap = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->ImageCount), level+1);
    mutate_GifImageDesc(&(ptr->Image), level+1, 0);
    {
        if(ptr->SavedImages) { mutate_SavedImage(ptr->SavedImages, level+1, 1); }
        len = 0;
        arr = pool_get_values("SavedImage", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->SavedImages;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->SavedImages = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->SavedImages = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->ExtensionBlockCount), level+1);
    {
        if(ptr->ExtensionBlocks) { mutate_ExtensionBlock(ptr->ExtensionBlocks, level+1, 1); }
        len = 0;
        arr = pool_get_values("ExtensionBlock", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ExtensionBlocks;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ExtensionBlocks = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ExtensionBlocks = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->Error), level+1);
            pool_insert("GifFileType", ptr1);
    #ifdef DEBUG
    printf("leave mutate_GifFileType  \n"); fflush(stdout);
    #endif
}
void mutate_GifImageDesc(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_GifImageDesc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct GifImageDesc* ptr = ptr1;
    mutate_int32_t(&(ptr->Left), level+1);
    mutate_int32_t(&(ptr->Top), level+1);
    mutate_int32_t(&(ptr->Width), level+1);
    mutate_int32_t(&(ptr->Height), level+1);
    mutate_int8_t(&(ptr->Interlace), level+1);
    {
        if(ptr->ColorMap) { mutate_ColorMapObject(ptr->ColorMap, level+1, 1); }
        len = 0;
        arr = pool_get_values("ColorMapObject", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ColorMap;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ColorMap = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ColorMap = ptr_save;
        free(arr);
    }
    pool_insert("GifImageDesc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_GifImageDesc  \n"); fflush(stdout);
    #endif
}
void mutate_SavedImage(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_SavedImage  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct SavedImage* ptr = ptr1;
    mutate_GifImageDesc(&(ptr->ImageDesc), level+1, 0);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->RasterBits);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->RasterBits, level + 1, len); }
    #else
    //ptr->RasterBits = ...(unsigned char  *RasterBits)
    #endif
    mutate_int32_t(&(ptr->ExtensionBlockCount), level+1);
    {
        if(ptr->ExtensionBlocks) { mutate_ExtensionBlock(ptr->ExtensionBlocks, level+1, 1); }
        len = 0;
        arr = pool_get_values("ExtensionBlock", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ExtensionBlocks;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ExtensionBlocks = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ExtensionBlocks = ptr_save;
        free(arr);
    }
    pool_insert("SavedImage", ptr1);
    #ifdef DEBUG
    printf("leave mutate_SavedImage  \n"); fflush(stdout);
    #endif
}
void mutate_ExtensionBlock(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_ExtensionBlock  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ExtensionBlock* ptr = ptr1;
    mutate_int32_t(&(ptr->ByteCount), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->Bytes);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->Bytes, level + 1, len); }
    #else
    //ptr->Bytes = ...(unsigned char  *Bytes)
    #endif
    mutate_int32_t(&(ptr->Function), level+1);
    pool_insert("ExtensionBlock", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ExtensionBlock  \n"); fflush(stdout);
    #endif
}
void mutate__IO_FILE(void* ptr1, int level, int check){return ;}
void mutate__IO_marker(void* ptr1, int level, int check){return ;}
