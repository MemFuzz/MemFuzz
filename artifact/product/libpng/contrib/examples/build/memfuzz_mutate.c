#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate_png_XYZ(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_XYZ  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_XYZ* ptr = ptr1;
    mutate_int32_t(&(ptr->red_X), level+1);
    mutate_int32_t(&(ptr->red_Y), level+1);
    mutate_int32_t(&(ptr->red_Z), level+1);
    mutate_int32_t(&(ptr->green_X), level+1);
    mutate_int32_t(&(ptr->green_Y), level+1);
    mutate_int32_t(&(ptr->green_Z), level+1);
    mutate_int32_t(&(ptr->blue_X), level+1);
    mutate_int32_t(&(ptr->blue_Y), level+1);
    mutate_int32_t(&(ptr->blue_Z), level+1);
    pool_insert("png_XYZ", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_XYZ  \n"); fflush(stdout);
    #endif
}
void mutate_png_xy(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_xy  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_xy* ptr = ptr1;
    mutate_int32_t(&(ptr->redx), level+1);
    mutate_int32_t(&(ptr->redy), level+1);
    mutate_int32_t(&(ptr->greenx), level+1);
    mutate_int32_t(&(ptr->greeny), level+1);
    mutate_int32_t(&(ptr->bluex), level+1);
    mutate_int32_t(&(ptr->bluey), level+1);
    mutate_int32_t(&(ptr->whitex), level+1);
    mutate_int32_t(&(ptr->whitey), level+1);
    pool_insert("png_xy", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_xy  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_0(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_0* ptr = ptr1;
    mutate_int32_t(&(ptr->adler), level+1);
    mutate_int32_t(&(ptr->crc), level+1);
    mutate_int32_t(&(ptr->length), level+1);
    assign_int32_t_array(&(ptr->md5), level + 1, 4);
    mutate_int8_t(&(ptr->have_md5), level+1);
    mutate_int8_t(&(ptr->is_broken), level+1);
    mutate_int16_t(&(ptr->intent), level+1);
    pool_insert("memfuzz_anonymous_struct_0", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
    #endif
}
void mutate_png_struct_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_struct_def  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_struct_def* ptr = ptr1;
    for(int i = 0; i < 1; i++)
    {
        mutate___jmp_buf_tag(&(ptr->jmp_buf_local)[i], level+1);
    }
    //ptr->longjmp_fn = ...(function longjmp_fn)
    //ptr->jmp_buf_ptr = ...(struct __jmp_buf_tag *jmp_buf_ptr[1])
    mutate_int64_t(&(ptr->jmp_buf_size), level+1);
    //ptr->error_fn = ...(function error_fn)
    //ptr->warning_fn = ...(function warning_fn)
        //ptr->write_data_fn = ...(function write_data_fn)
    //ptr->read_data_fn = ...(function read_data_fn)
        //ptr->read_user_transform_fn = ...(function read_user_transform_fn)
    //ptr->write_user_transform_fn = ...(function write_user_transform_fn)
        mutate_int8_t(&(ptr->user_transform_depth), level+1);
    mutate_int8_t(&(ptr->user_transform_channels), level+1);
    mutate_int32_t(&(ptr->mode), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->transformations), level+1);
    mutate_int32_t(&(ptr->zowner), level+1);
    mutate_z_stream_s(&(ptr->zstream), level+1);
    {
        if(ptr->zbuffer_list) { mutate_png_compression_buffer(ptr->zbuffer_list, level+1); }
        len = 0;
        arr = pool_get_values("png_compression_buffer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->zbuffer_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->zbuffer_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->zbuffer_list = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->zbuffer_size), level+1);
    mutate_int32_t(&(ptr->zlib_level), level+1);
    mutate_int32_t(&(ptr->zlib_method), level+1);
    mutate_int32_t(&(ptr->zlib_window_bits), level+1);
    mutate_int32_t(&(ptr->zlib_mem_level), level+1);
    mutate_int32_t(&(ptr->zlib_strategy), level+1);
    mutate_int32_t(&(ptr->zlib_text_level), level+1);
    mutate_int32_t(&(ptr->zlib_text_method), level+1);
    mutate_int32_t(&(ptr->zlib_text_window_bits), level+1);
    mutate_int32_t(&(ptr->zlib_text_mem_level), level+1);
    mutate_int32_t(&(ptr->zlib_text_strategy), level+1);
    mutate_int32_t(&(ptr->zlib_set_level), level+1);
    mutate_int32_t(&(ptr->zlib_set_method), level+1);
    mutate_int32_t(&(ptr->zlib_set_window_bits), level+1);
    mutate_int32_t(&(ptr->zlib_set_mem_level), level+1);
    mutate_int32_t(&(ptr->zlib_set_strategy), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->num_rows), level+1);
    mutate_int32_t(&(ptr->usr_width), level+1);
    mutate_int64_t(&(ptr->rowbytes), level+1);
    mutate_int32_t(&(ptr->iwidth), level+1);
    mutate_int32_t(&(ptr->row_number), level+1);
    mutate_int32_t(&(ptr->chunk_name), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->prev_row);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->prev_row, level + 1, len); }
    #else
    //ptr->prev_row = ...(unsigned char  *prev_row)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->row_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->row_buf, level + 1, len); }
    #else
    //ptr->row_buf = ...(unsigned char  *row_buf)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->try_row);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->try_row, level + 1, len); }
    #else
    //ptr->try_row = ...(unsigned char  *try_row)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->tst_row);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->tst_row, level + 1, len); }
    #else
    //ptr->tst_row = ...(unsigned char  *tst_row)
    #endif
    mutate_int64_t(&(ptr->info_rowbytes), level+1);
    mutate_int32_t(&(ptr->idat_size), level+1);
    mutate_int32_t(&(ptr->crc), level+1);
    {
        if(ptr->palette) { mutate_png_color_struct(ptr->palette, level+1); }
        len = 0;
        arr = pool_get_values("png_color_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->palette;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->palette = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->palette = ptr_save;
        free(arr);
    }
    mutate_int16_t(&(ptr->num_palette), level+1);
    mutate_int32_t(&(ptr->num_palette_max), level+1);
    mutate_int16_t(&(ptr->num_trans), level+1);
    mutate_int8_t(&(ptr->compression), level+1);
    mutate_int8_t(&(ptr->filter), level+1);
    mutate_int8_t(&(ptr->interlaced), level+1);
    mutate_int8_t(&(ptr->pass), level+1);
    mutate_int8_t(&(ptr->do_filter), level+1);
    mutate_int8_t(&(ptr->color_type), level+1);
    mutate_int8_t(&(ptr->bit_depth), level+1);
    mutate_int8_t(&(ptr->usr_bit_depth), level+1);
    mutate_int8_t(&(ptr->pixel_depth), level+1);
    mutate_int8_t(&(ptr->channels), level+1);
    mutate_int8_t(&(ptr->usr_channels), level+1);
    mutate_int8_t(&(ptr->sig_bytes), level+1);
    mutate_int8_t(&(ptr->maximum_pixel_depth), level+1);
    mutate_int8_t(&(ptr->transformed_pixel_depth), level+1);
    mutate_int8_t(&(ptr->zstream_start), level+1);
    mutate_int16_t(&(ptr->filler), level+1);
    mutate_int8_t(&(ptr->background_gamma_type), level+1);
    mutate_int32_t(&(ptr->background_gamma), level+1);
    mutate_png_color_16_struct(&(ptr->background), level+1);
    mutate_png_color_16_struct(&(ptr->background_1), level+1);
    //ptr->output_flush_fn = ...(function output_flush_fn)
    mutate_int32_t(&(ptr->flush_dist), level+1);
    mutate_int32_t(&(ptr->flush_rows), level+1);
    mutate_int32_t(&(ptr->gamma_shift), level+1);
    mutate_int32_t(&(ptr->screen_gamma), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->gamma_table);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->gamma_table, level + 1, len); }
    #else
    //ptr->gamma_table = ...(unsigned char  *gamma_table)
    #endif
    //ptr->gamma_16_table = ...(unsigned short  **gamma_16_table)
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->gamma_from_1);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->gamma_from_1, level + 1, len); }
    #else
    //ptr->gamma_from_1 = ...(unsigned char  *gamma_from_1)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->gamma_to_1);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->gamma_to_1, level + 1, len); }
    #else
    //ptr->gamma_to_1 = ...(unsigned char  *gamma_to_1)
    #endif
    //ptr->gamma_16_from_1 = ...(unsigned short  **gamma_16_from_1)
    //ptr->gamma_16_to_1 = ...(unsigned short  **gamma_16_to_1)
    mutate_png_color_8_struct(&(ptr->sig_bit), level+1);
    mutate_png_color_8_struct(&(ptr->shift), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->trans_alpha);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->trans_alpha, level + 1, len); }
    #else
    //ptr->trans_alpha = ...(unsigned char  *trans_alpha)
    #endif
    mutate_png_color_16_struct(&(ptr->trans_color), level+1);
    //ptr->read_row_fn = ...(function read_row_fn)
    //ptr->write_row_fn = ...(function write_row_fn)
    //ptr->info_fn = ...(function info_fn)
    //ptr->row_fn = ...(function row_fn)
    //ptr->end_fn = ...(function end_fn)
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->save_buffer_ptr);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->save_buffer_ptr, level + 1, len); }
    #else
    //ptr->save_buffer_ptr = ...(unsigned char  *save_buffer_ptr)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->save_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->save_buffer, level + 1, len); }
    #else
    //ptr->save_buffer = ...(unsigned char  *save_buffer)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->current_buffer_ptr);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->current_buffer_ptr, level + 1, len); }
    #else
    //ptr->current_buffer_ptr = ...(unsigned char  *current_buffer_ptr)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->current_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->current_buffer, level + 1, len); }
    #else
    //ptr->current_buffer = ...(unsigned char  *current_buffer)
    #endif
    mutate_int32_t(&(ptr->push_length), level+1);
    mutate_int32_t(&(ptr->skip_length), level+1);
    mutate_int64_t(&(ptr->save_buffer_size), level+1);
    mutate_int64_t(&(ptr->save_buffer_max), level+1);
    mutate_int64_t(&(ptr->buffer_size), level+1);
    mutate_int64_t(&(ptr->current_buffer_size), level+1);
    mutate_int32_t(&(ptr->process_mode), level+1);
    mutate_int32_t(&(ptr->cur_palette), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->palette_lookup);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->palette_lookup, level + 1, len); }
    #else
    //ptr->palette_lookup = ...(unsigned char  *palette_lookup)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->quantize_index);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->quantize_index, level + 1, len); }
    #else
    //ptr->quantize_index = ...(unsigned char  *quantize_index)
    #endif
    mutate_int32_t(&(ptr->options), level+1);
    assign_int8_t_array(&(ptr->time_buffer), level + 1, 29);
    mutate_int32_t(&(ptr->free_me), level+1);
        //ptr->read_user_chunk_fn = ...(function read_user_chunk_fn)
    mutate_int32_t(&(ptr->unknown_default), level+1);
    mutate_int32_t(&(ptr->num_chunk_list), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->chunk_list);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->chunk_list, level + 1, len); }
    #else
    //ptr->chunk_list = ...(unsigned char  *chunk_list)
    #endif
    mutate_int8_t(&(ptr->rgb_to_gray_status), level+1);
    mutate_int8_t(&(ptr->rgb_to_gray_coefficients_set), level+1);
    mutate_int16_t(&(ptr->rgb_to_gray_red_coeff), level+1);
    mutate_int16_t(&(ptr->rgb_to_gray_green_coeff), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->riffled_palette);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->riffled_palette, level + 1, len); }
    #else
    //ptr->riffled_palette = ...(unsigned char  *riffled_palette)
    #endif
    mutate_int32_t(&(ptr->mng_features_permitted), level+1);
    mutate_int8_t(&(ptr->filter_type), level+1);
        //ptr->malloc_fn = ...(function malloc_fn)
    //ptr->free_fn = ...(function free_fn)
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->big_row_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->big_row_buf, level + 1, len); }
    #else
    //ptr->big_row_buf = ...(unsigned char  *big_row_buf)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->quantize_sort);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->quantize_sort, level + 1, len); }
    #else
    //ptr->quantize_sort = ...(unsigned char  *quantize_sort)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->index_to_palette);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->index_to_palette, level + 1, len); }
    #else
    //ptr->index_to_palette = ...(unsigned char  *index_to_palette)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->palette_to_index);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->palette_to_index, level + 1, len); }
    #else
    //ptr->palette_to_index = ...(unsigned char  *palette_to_index)
    #endif
    mutate_int8_t(&(ptr->compression_type), level+1);
    mutate_int32_t(&(ptr->user_width_max), level+1);
    mutate_int32_t(&(ptr->user_height_max), level+1);
    mutate_int32_t(&(ptr->user_chunk_cache_max), level+1);
    mutate_int64_t(&(ptr->user_chunk_malloc_max), level+1);
    mutate_png_unknown_chunk_t(&(ptr->unknown_chunk), level+1);
    mutate_int64_t(&(ptr->old_big_row_buf_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->read_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->read_buffer, level + 1, len); }
    #else
    //ptr->read_buffer = ...(unsigned char  *read_buffer)
    #endif
    mutate_int64_t(&(ptr->read_buffer_size), level+1);
    mutate_int32_t(&(ptr->IDAT_read_size), level+1);
    mutate_int32_t(&(ptr->io_state), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->big_prev_row);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->big_prev_row, level + 1, len); }
    #else
    //ptr->big_prev_row = ...(unsigned char  *big_prev_row)
    #endif
    //ptr->read_filter = ...(*read_filter[4])
    mutate_png_colorspace(&(ptr->colorspace), level+1);
    pool_insert("png_struct_def", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_struct_def  \n"); fflush(stdout);
    #endif
}
void mutate___jmp_buf_tag(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level){return ;}
void mutate_png_row_info_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_row_info_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_row_info_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int64_t(&(ptr->rowbytes), level+1);
    mutate_int8_t(&(ptr->color_type), level+1);
    mutate_int8_t(&(ptr->bit_depth), level+1);
    mutate_int8_t(&(ptr->channels), level+1);
    mutate_int8_t(&(ptr->pixel_depth), level+1);
    pool_insert("png_row_info_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_row_info_struct  \n"); fflush(stdout);
    #endif
}
void mutate_z_stream_s(void* ptr1, int level){return ;}
void mutate_png_compression_buffer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_compression_buffer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_compression_buffer* ptr = ptr1;
    {
        if(ptr->next) { mutate_png_compression_buffer(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("png_compression_buffer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    assign_int8_t_array(&(ptr->output), level + 1, 1);
    pool_insert("png_compression_buffer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_compression_buffer  \n"); fflush(stdout);
    #endif
}
void mutate_png_color_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_color_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_color_struct* ptr = ptr1;
    mutate_int8_t(&(ptr->red), level+1);
    mutate_int8_t(&(ptr->green), level+1);
    mutate_int8_t(&(ptr->blue), level+1);
    pool_insert("png_color_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_color_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_color_16_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_color_16_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_color_16_struct* ptr = ptr1;
    mutate_int8_t(&(ptr->index), level+1);
    mutate_int16_t(&(ptr->red), level+1);
    mutate_int16_t(&(ptr->green), level+1);
    mutate_int16_t(&(ptr->blue), level+1);
    mutate_int16_t(&(ptr->gray), level+1);
    pool_insert("png_color_16_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_color_16_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_color_8_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_color_8_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_color_8_struct* ptr = ptr1;
    mutate_int8_t(&(ptr->red), level+1);
    mutate_int8_t(&(ptr->green), level+1);
    mutate_int8_t(&(ptr->blue), level+1);
    mutate_int8_t(&(ptr->gray), level+1);
    mutate_int8_t(&(ptr->alpha), level+1);
    pool_insert("png_color_8_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_color_8_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_info_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_info_def  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_info_def* ptr = ptr1;
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->valid), level+1);
    mutate_int64_t(&(ptr->rowbytes), level+1);
    {
        if(ptr->palette) { mutate_png_color_struct(ptr->palette, level+1); }
        len = 0;
        arr = pool_get_values("png_color_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->palette;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->palette = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->palette = ptr_save;
        free(arr);
    }
    mutate_int16_t(&(ptr->num_palette), level+1);
    mutate_int16_t(&(ptr->num_trans), level+1);
    mutate_int8_t(&(ptr->bit_depth), level+1);
    mutate_int8_t(&(ptr->color_type), level+1);
    mutate_int8_t(&(ptr->compression_type), level+1);
    mutate_int8_t(&(ptr->filter_type), level+1);
    mutate_int8_t(&(ptr->interlace_type), level+1);
    mutate_int8_t(&(ptr->channels), level+1);
    mutate_int8_t(&(ptr->pixel_depth), level+1);
    mutate_int8_t(&(ptr->spare_byte), level+1);
    assign_int8_t_array(&(ptr->signature), level + 1, 8);
    mutate_png_colorspace(&(ptr->colorspace), level+1);
    mutate_c_str(ptr->iccp_name);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->iccp_profile);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->iccp_profile, level + 1, len); }
    #else
    //ptr->iccp_profile = ...(unsigned char  *iccp_profile)
    #endif
    mutate_int32_t(&(ptr->iccp_proflen), level+1);
    mutate_int32_t(&(ptr->num_text), level+1);
    mutate_int32_t(&(ptr->max_text), level+1);
    {
        if(ptr->text) { mutate_png_text_struct(ptr->text, level+1); }
        len = 0;
        arr = pool_get_values("png_text_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->text;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->text = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->text = ptr_save;
        free(arr);
    }
    mutate_png_time_struct(&(ptr->mod_time), level+1);
    mutate_png_color_8_struct(&(ptr->sig_bit), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->trans_alpha);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->trans_alpha, level + 1, len); }
    #else
    //ptr->trans_alpha = ...(unsigned char  *trans_alpha)
    #endif
    mutate_png_color_16_struct(&(ptr->trans_color), level+1);
    mutate_png_color_16_struct(&(ptr->background), level+1);
    mutate_int32_t(&(ptr->x_offset), level+1);
    mutate_int32_t(&(ptr->y_offset), level+1);
    mutate_int8_t(&(ptr->offset_unit_type), level+1);
    mutate_int32_t(&(ptr->x_pixels_per_unit), level+1);
    mutate_int32_t(&(ptr->y_pixels_per_unit), level+1);
    mutate_int8_t(&(ptr->phys_unit_type), level+1);
    mutate_int32_t(&(ptr->num_exif), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->exif);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->exif, level + 1, len); }
    #else
    //ptr->exif = ...(unsigned char  *exif)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->eXIf_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->eXIf_buf, level + 1, len); }
    #else
    //ptr->eXIf_buf = ...(unsigned char  *eXIf_buf)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->hist);
    len /= sizeof(int16_t);
    if(len != 0){ mutate_int16_t_array(ptr->hist, level + 1, len); }
    #else
    //ptr->hist = ...(unsigned short  *hist)
    #endif
    mutate_c_str(ptr->pcal_purpose);
    mutate_int32_t(&(ptr->pcal_X0), level+1);
    mutate_int32_t(&(ptr->pcal_X1), level+1);
    mutate_c_str(ptr->pcal_units);
    //ptr->pcal_params = ...(char  **pcal_params)
    mutate_int8_t(&(ptr->pcal_type), level+1);
    mutate_int8_t(&(ptr->pcal_nparams), level+1);
    mutate_int32_t(&(ptr->free_me), level+1);
    {
        if(ptr->unknown_chunks) { mutate_png_unknown_chunk_t(ptr->unknown_chunks, level+1); }
        len = 0;
        arr = pool_get_values("png_unknown_chunk_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->unknown_chunks;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->unknown_chunks = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->unknown_chunks = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->unknown_chunks_num), level+1);
    {
        if(ptr->splt_palettes) { mutate_png_sPLT_struct(ptr->splt_palettes, level+1); }
        len = 0;
        arr = pool_get_values("png_sPLT_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->splt_palettes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->splt_palettes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->splt_palettes = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->splt_palettes_num), level+1);
    mutate_int8_t(&(ptr->scal_unit), level+1);
    mutate_c_str(ptr->scal_s_width);
    mutate_c_str(ptr->scal_s_height);
    //ptr->row_pointers = ...(unsigned char  **row_pointers)
    pool_insert("png_info_def", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_info_def  \n"); fflush(stdout);
    #endif
}
void mutate_png_colorspace(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_colorspace  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_colorspace* ptr = ptr1;
    mutate_int32_t(&(ptr->gamma), level+1);
    mutate_png_xy(&(ptr->end_points_xy), level+1);
    mutate_png_XYZ(&(ptr->end_points_XYZ), level+1);
    mutate_int16_t(&(ptr->rendering_intent), level+1);
    mutate_int16_t(&(ptr->flags), level+1);
    pool_insert("png_colorspace", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_colorspace  \n"); fflush(stdout);
    #endif
}
void mutate_png_text_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_text_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_text_struct* ptr = ptr1;
    mutate_int32_t(&(ptr->compression), level+1);
    mutate_c_str(ptr->key);
    mutate_c_str(ptr->text);
    mutate_int64_t(&(ptr->text_length), level+1);
    mutate_int64_t(&(ptr->itxt_length), level+1);
    mutate_c_str(ptr->lang);
    mutate_c_str(ptr->lang_key);
    pool_insert("png_text_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_text_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_time_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_time_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_time_struct* ptr = ptr1;
    mutate_int16_t(&(ptr->year), level+1);
    mutate_int8_t(&(ptr->month), level+1);
    mutate_int8_t(&(ptr->day), level+1);
    mutate_int8_t(&(ptr->hour), level+1);
    mutate_int8_t(&(ptr->minute), level+1);
    mutate_int8_t(&(ptr->second), level+1);
    pool_insert("png_time_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_time_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_unknown_chunk_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_unknown_chunk_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_unknown_chunk_t* ptr = ptr1;
    assign_int8_t_array(&(ptr->name), level + 1, 5);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int8_t(&(ptr->location), level+1);
    pool_insert("png_unknown_chunk_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_unknown_chunk_t  \n"); fflush(stdout);
    #endif
}
void mutate_png_sPLT_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_sPLT_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_sPLT_struct* ptr = ptr1;
    mutate_c_str(ptr->name);
    mutate_int8_t(&(ptr->depth), level+1);
    {
        if(ptr->entries) { mutate_png_sPLT_entry_struct(ptr->entries, level+1); }
        len = 0;
        arr = pool_get_values("png_sPLT_entry_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->entries;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->entries = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->entries = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->nentries), level+1);
    pool_insert("png_sPLT_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_sPLT_struct  \n"); fflush(stdout);
    #endif
}
void mutate_png_sPLT_entry_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_sPLT_entry_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_sPLT_entry_struct* ptr = ptr1;
    mutate_int16_t(&(ptr->red), level+1);
    mutate_int16_t(&(ptr->green), level+1);
    mutate_int16_t(&(ptr->blue), level+1);
    mutate_int16_t(&(ptr->alpha), level+1);
    mutate_int16_t(&(ptr->frequency), level+1);
    pool_insert("png_sPLT_entry_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_sPLT_entry_struct  \n"); fflush(stdout);
    #endif
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2* ptr = ptr1;
    {
        if(ptr->opaque) { mutate_png_control(ptr->opaque, level+1); }
        len = 0;
        arr = pool_get_values("png_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->opaque;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->opaque = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->opaque = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->version), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->format), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->colormap_entries), level+1);
    mutate_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
    pool_insert("memfuzz_anonymous_struct_2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
}
void mutate_png_control(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_control  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_control* ptr = ptr1;
    {
        if(ptr->png_ptr) { mutate_png_struct_def(ptr->png_ptr, level+1); }
        len = 0;
        arr = pool_get_values("png_struct_def", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->png_ptr;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->png_ptr = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->png_ptr = ptr_save;
        free(arr);
    }
    {
        if(ptr->info_ptr) { mutate_png_info_def(ptr->info_ptr, level+1); }
        len = 0;
        arr = pool_get_values("png_info_def", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->info_ptr;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->info_ptr = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->info_ptr = ptr_save;
        free(arr);
    }
        //ptr->memory = ...(const *memory)
    mutate_int64_t(&(ptr->size), level+1);
    //ptr->for_write = ...(bitfield mutation);
    //ptr->owned_file = ...(bitfield mutation);
    pool_insert("png_control", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_control  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_4* ptr = ptr1;
    {
        if(ptr->opaque) { mutate_png_control(ptr->opaque, level+1); }
        len = 0;
        arr = pool_get_values("png_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->opaque;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->opaque = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->opaque = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->version), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->format), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->colormap_entries), level+1);
    mutate_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
    pool_insert("memfuzz_anonymous_struct_4", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_9  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_9* ptr = ptr1;
    {
        if(ptr->opaque) { mutate_png_control(ptr->opaque, level+1); }
        len = 0;
        arr = pool_get_values("png_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->opaque;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->opaque = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->opaque = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->version), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->format), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->colormap_entries), level+1);
    mutate_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
    pool_insert("memfuzz_anonymous_struct_9", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_9  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_10  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_10* ptr = ptr1;
    //ptr->image = ...(struct anonymous *{struct png_control *opaque; unsigned int  version; unsigned int  width; unsigned int  height; unsigned int  format; unsigned int  flags; unsigned int  colormap_entries; unsigned int  warning_or_error; char  message[64]; } image)
        mutate_int32_t(&(ptr->row_stride), level+1);
        //ptr->background = ...(const *background)
            mutate_int64_t(&(ptr->row_bytes), level+1);
    mutate_int32_t(&(ptr->file_encoding), level+1);
    mutate_int32_t(&(ptr->gamma_to_linear), level+1);
    mutate_int32_t(&(ptr->colormap_processing), level+1);
    pool_insert("memfuzz_anonymous_struct_10", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_10  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_11(void* ptr1, int level){return ;}
void mutate_png_dsort_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_png_dsort_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct png_dsort_struct* ptr = ptr1;
    {
        if(ptr->next) { mutate_png_dsort_struct(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("png_dsort_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->left), level+1);
    mutate_int8_t(&(ptr->right), level+1);
    pool_insert("png_dsort_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_png_dsort_struct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_12(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_13(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_14(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_15(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_16(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_17(void* ptr1, int level){return ;}
void mutate_tm(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_18(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_18  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_18* ptr = ptr1;
    {
        if(ptr->opaque) { mutate_png_control(ptr->opaque, level+1); }
        len = 0;
        arr = pool_get_values("png_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->opaque;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->opaque = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->opaque = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->version), level+1);
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->format), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->colormap_entries), level+1);
    mutate_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
    pool_insert("memfuzz_anonymous_struct_18", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_18  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_19(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_19  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_19* ptr = ptr1;
    //ptr->image = ...(struct anonymous *{struct png_control *opaque; unsigned int  version; unsigned int  width; unsigned int  height; unsigned int  format; unsigned int  flags; unsigned int  colormap_entries; unsigned int  warning_or_error; char  message[64]; } image)
    //ptr->buffer = ...(const *buffer)
    mutate_int32_t(&(ptr->row_stride), level+1);
    //ptr->colormap = ...(const *colormap)
    mutate_int32_t(&(ptr->convert_to_8bit), level+1);
    //ptr->first_row = ...(const *first_row)
    mutate_int64_t(&(ptr->row_bytes), level+1);
        #ifdef ALLOC_HOOK
    len = alloc_find(ptr->memory);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->memory, level + 1, len); }
    #else
    //ptr->memory = ...(unsigned char  *memory)
    #endif
    mutate_int64_t(&(ptr->memory_bytes), level+1);
    mutate_int64_t(&(ptr->output_bytes), level+1);
    pool_insert("memfuzz_anonymous_struct_19", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_19  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_20(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_21(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_22(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_22  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_22* ptr = ptr1;
    //ptr->input = ...(const *input)
    mutate_int64_t(&(ptr->input_len), level+1);
    mutate_int32_t(&(ptr->output_len), level+1);
    assign_int8_t_array(&(ptr->output), level + 1, 1024);
    pool_insert("memfuzz_anonymous_struct_22", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_22  \n"); fflush(stdout);
    #endif
}
void mutate_internal_state(void* ptr1, int level){return ;}
