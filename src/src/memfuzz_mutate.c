#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_config.h"
void mutate_ColorMapObject(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct ColorMapObject* ptr = ptr1;
    assign_int32_t(&(ptr->ColorCount), level+1);
    assign_int32_t(&(ptr->BitsPerPixel), level+1);
    assign_int8_t(&(ptr->SortFlag), level+1);
    if(ptr->Colors) mutate_GifColorType(ptr->Colors, level+1);
}
void mutate_GifColorType(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct GifColorType* ptr = ptr1;
    assign_int8_t(&(ptr->Red), level+1);
    assign_int8_t(&(ptr->Green), level+1);
    assign_int8_t(&(ptr->Blue), level+1);
}
void mutate_GifFileType(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct GifFileType* ptr = ptr1;
    assign_int32_t(&(ptr->SWidth), level+1);
    assign_int32_t(&(ptr->SHeight), level+1);
    assign_int32_t(&(ptr->SColorResolution), level+1);
    assign_int32_t(&(ptr->SBackGroundColor), level+1);
    assign_int8_t(&(ptr->AspectByte), level+1);
    if(ptr->SColorMap) mutate_ColorMapObject(ptr->SColorMap, level+1);
    assign_int32_t(&(ptr->ImageCount), level+1);
    mutate_GifImageDesc(&(ptr->Image), level+1);
    if(ptr->SavedImages) mutate_SavedImage(ptr->SavedImages, level+1);
    assign_int32_t(&(ptr->ExtensionBlockCount), level+1);
    if(ptr->ExtensionBlocks) mutate_ExtensionBlock(ptr->ExtensionBlocks, level+1);
    assign_int32_t(&(ptr->Error), level+1);
        }
void mutate_GifImageDesc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct GifImageDesc* ptr = ptr1;
    assign_int32_t(&(ptr->Left), level+1);
    assign_int32_t(&(ptr->Top), level+1);
    assign_int32_t(&(ptr->Width), level+1);
    assign_int32_t(&(ptr->Height), level+1);
    assign_int8_t(&(ptr->Interlace), level+1);
    if(ptr->ColorMap) mutate_ColorMapObject(ptr->ColorMap, level+1);
}
void mutate_SavedImage(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct SavedImage* ptr = ptr1;
    mutate_GifImageDesc(&(ptr->ImageDesc), level+1);
    //ptr->RasterBits = ...(unsigned char  *RasterBits)
    assign_int32_t(&(ptr->ExtensionBlockCount), level+1);
    if(ptr->ExtensionBlocks) mutate_ExtensionBlock(ptr->ExtensionBlocks, level+1);
}
void mutate_ExtensionBlock(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct ExtensionBlock* ptr = ptr1;
    assign_int32_t(&(ptr->ByteCount), level+1);
    //ptr->Bytes = ...(unsigned char  *Bytes)
    assign_int32_t(&(ptr->Function), level+1);
}
