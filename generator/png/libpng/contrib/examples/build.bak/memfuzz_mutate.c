#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_config.h"
void mutate_png_color_16_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_color_16_struct* ptr = ptr1;
    assign_int8_t(&(ptr->index), level+1);
    assign_int16_t(&(ptr->red), level+1);
    assign_int16_t(&(ptr->green), level+1);
    assign_int16_t(&(ptr->blue), level+1);
    assign_int16_t(&(ptr->gray), level+1);
}
void mutate_png_sPLT_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_sPLT_struct* ptr = ptr1;
    //ptr->name = ...(char  *name)
    assign_int8_t(&(ptr->depth), level+1);
    if(ptr->entries) mutate_png_sPLT_entry_struct(ptr->entries, level+1);
    assign_int32_t(&(ptr->nentries), level+1);
}
void mutate_png_color_8_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_color_8_struct* ptr = ptr1;
    assign_int8_t(&(ptr->red), level+1);
    assign_int8_t(&(ptr->green), level+1);
    assign_int8_t(&(ptr->blue), level+1);
    assign_int8_t(&(ptr->gray), level+1);
    assign_int8_t(&(ptr->alpha), level+1);
}
void mutate_memfuzz_anonymous_struct_20(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_21(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_22(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_22* ptr = ptr1;
    //ptr->input = ...(const *input)
    assign_int64_t(&(ptr->input_len), level+1);
    assign_int32_t(&(ptr->output_len), level+1);
    assign_int8_t_array(&(ptr->output), level + 1, 1024);
}
void mutate_png_control(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_control* ptr = ptr1;
    if(ptr->png_ptr) mutate_png_struct_def(ptr->png_ptr, level+1);
    if(ptr->info_ptr) mutate_png_info_def(ptr->info_ptr, level+1);
        //ptr->memory = ...(const *memory)
    assign_int64_t(&(ptr->size), level+1);
    //ptr->for_write = ...(bitfield mutation);
    //ptr->owned_file = ...(bitfield mutation);
}
void mutate_internal_state(void* ptr1, int level){return ;}
void mutate_png_sPLT_entry_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_sPLT_entry_struct* ptr = ptr1;
    assign_int16_t(&(ptr->red), level+1);
    assign_int16_t(&(ptr->green), level+1);
    assign_int16_t(&(ptr->blue), level+1);
    assign_int16_t(&(ptr->alpha), level+1);
    assign_int16_t(&(ptr->frequency), level+1);
}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_9* ptr = ptr1;
    if(ptr->opaque) mutate_png_control(ptr->opaque, level+1);
    assign_int32_t(&(ptr->version), level+1);
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->format), level+1);
    assign_int32_t(&(ptr->flags), level+1);
    assign_int32_t(&(ptr->colormap_entries), level+1);
    assign_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_tm(void* ptr1, int level){return ;}
void mutate_png_struct_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_struct_def* ptr = ptr1;
    for(int i = 0; i < 1; i++)
    {
        mutate___jmp_buf_tag(&(ptr->jmp_buf_local)[i], level+1);
    }
    //ptr->longjmp_fn = ...(function longjmp_fn)
    //ptr->jmp_buf_ptr = ...(struct __jmp_buf_tag *jmp_buf_ptr[1])
    assign_int64_t(&(ptr->jmp_buf_size), level+1);
    //ptr->error_fn = ...(function error_fn)
    //ptr->warning_fn = ...(function warning_fn)
        //ptr->write_data_fn = ...(function write_data_fn)
    //ptr->read_data_fn = ...(function read_data_fn)
        //ptr->read_user_transform_fn = ...(function read_user_transform_fn)
    //ptr->write_user_transform_fn = ...(function write_user_transform_fn)
        assign_int8_t(&(ptr->user_transform_depth), level+1);
    assign_int8_t(&(ptr->user_transform_channels), level+1);
    assign_int32_t(&(ptr->mode), level+1);
    assign_int32_t(&(ptr->flags), level+1);
    assign_int32_t(&(ptr->transformations), level+1);
    assign_int32_t(&(ptr->zowner), level+1);
    mutate_z_stream_s(&(ptr->zstream), level+1);
    if(ptr->zbuffer_list) mutate_png_compression_buffer(ptr->zbuffer_list, level+1);
    assign_int32_t(&(ptr->zbuffer_size), level+1);
    assign_int32_t(&(ptr->zlib_level), level+1);
    assign_int32_t(&(ptr->zlib_method), level+1);
    assign_int32_t(&(ptr->zlib_window_bits), level+1);
    assign_int32_t(&(ptr->zlib_mem_level), level+1);
    assign_int32_t(&(ptr->zlib_strategy), level+1);
    assign_int32_t(&(ptr->zlib_text_level), level+1);
    assign_int32_t(&(ptr->zlib_text_method), level+1);
    assign_int32_t(&(ptr->zlib_text_window_bits), level+1);
    assign_int32_t(&(ptr->zlib_text_mem_level), level+1);
    assign_int32_t(&(ptr->zlib_text_strategy), level+1);
    assign_int32_t(&(ptr->zlib_set_level), level+1);
    assign_int32_t(&(ptr->zlib_set_method), level+1);
    assign_int32_t(&(ptr->zlib_set_window_bits), level+1);
    assign_int32_t(&(ptr->zlib_set_mem_level), level+1);
    assign_int32_t(&(ptr->zlib_set_strategy), level+1);
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->num_rows), level+1);
    assign_int32_t(&(ptr->usr_width), level+1);
    assign_int64_t(&(ptr->rowbytes), level+1);
    assign_int32_t(&(ptr->iwidth), level+1);
    assign_int32_t(&(ptr->row_number), level+1);
    assign_int32_t(&(ptr->chunk_name), level+1);
    //ptr->prev_row = ...(unsigned char  *prev_row)
    //ptr->row_buf = ...(unsigned char  *row_buf)
    //ptr->try_row = ...(unsigned char  *try_row)
    //ptr->tst_row = ...(unsigned char  *tst_row)
    assign_int64_t(&(ptr->info_rowbytes), level+1);
    assign_int32_t(&(ptr->idat_size), level+1);
    assign_int32_t(&(ptr->crc), level+1);
    if(ptr->palette) mutate_png_color_struct(ptr->palette, level+1);
    assign_int16_t(&(ptr->num_palette), level+1);
    assign_int32_t(&(ptr->num_palette_max), level+1);
    assign_int16_t(&(ptr->num_trans), level+1);
    assign_int8_t(&(ptr->compression), level+1);
    assign_int8_t(&(ptr->filter), level+1);
    assign_int8_t(&(ptr->interlaced), level+1);
    assign_int8_t(&(ptr->pass), level+1);
    assign_int8_t(&(ptr->do_filter), level+1);
    assign_int8_t(&(ptr->color_type), level+1);
    assign_int8_t(&(ptr->bit_depth), level+1);
    assign_int8_t(&(ptr->usr_bit_depth), level+1);
    assign_int8_t(&(ptr->pixel_depth), level+1);
    assign_int8_t(&(ptr->channels), level+1);
    assign_int8_t(&(ptr->usr_channels), level+1);
    assign_int8_t(&(ptr->sig_bytes), level+1);
    assign_int8_t(&(ptr->maximum_pixel_depth), level+1);
    assign_int8_t(&(ptr->transformed_pixel_depth), level+1);
    assign_int8_t(&(ptr->zstream_start), level+1);
    assign_int16_t(&(ptr->filler), level+1);
    assign_int8_t(&(ptr->background_gamma_type), level+1);
    assign_int32_t(&(ptr->background_gamma), level+1);
    mutate_png_color_16_struct(&(ptr->background), level+1);
    mutate_png_color_16_struct(&(ptr->background_1), level+1);
    //ptr->output_flush_fn = ...(function output_flush_fn)
    assign_int32_t(&(ptr->flush_dist), level+1);
    assign_int32_t(&(ptr->flush_rows), level+1);
    assign_int32_t(&(ptr->gamma_shift), level+1);
    assign_int32_t(&(ptr->screen_gamma), level+1);
    //ptr->gamma_table = ...(unsigned char  *gamma_table)
    //ptr->gamma_16_table = ...(unsigned short  **gamma_16_table)
    //ptr->gamma_from_1 = ...(unsigned char  *gamma_from_1)
    //ptr->gamma_to_1 = ...(unsigned char  *gamma_to_1)
    //ptr->gamma_16_from_1 = ...(unsigned short  **gamma_16_from_1)
    //ptr->gamma_16_to_1 = ...(unsigned short  **gamma_16_to_1)
    mutate_png_color_8_struct(&(ptr->sig_bit), level+1);
    mutate_png_color_8_struct(&(ptr->shift), level+1);
    //ptr->trans_alpha = ...(unsigned char  *trans_alpha)
    mutate_png_color_16_struct(&(ptr->trans_color), level+1);
    //ptr->read_row_fn = ...(function read_row_fn)
    //ptr->write_row_fn = ...(function write_row_fn)
    //ptr->info_fn = ...(function info_fn)
    //ptr->row_fn = ...(function row_fn)
    //ptr->end_fn = ...(function end_fn)
    //ptr->save_buffer_ptr = ...(unsigned char  *save_buffer_ptr)
    //ptr->save_buffer = ...(unsigned char  *save_buffer)
    //ptr->current_buffer_ptr = ...(unsigned char  *current_buffer_ptr)
    //ptr->current_buffer = ...(unsigned char  *current_buffer)
    assign_int32_t(&(ptr->push_length), level+1);
    assign_int32_t(&(ptr->skip_length), level+1);
    assign_int64_t(&(ptr->save_buffer_size), level+1);
    assign_int64_t(&(ptr->save_buffer_max), level+1);
    assign_int64_t(&(ptr->buffer_size), level+1);
    assign_int64_t(&(ptr->current_buffer_size), level+1);
    assign_int32_t(&(ptr->process_mode), level+1);
    assign_int32_t(&(ptr->cur_palette), level+1);
    //ptr->palette_lookup = ...(unsigned char  *palette_lookup)
    //ptr->quantize_index = ...(unsigned char  *quantize_index)
    assign_int32_t(&(ptr->options), level+1);
    assign_int8_t_array(&(ptr->time_buffer), level + 1, 29);
    assign_int32_t(&(ptr->free_me), level+1);
        //ptr->read_user_chunk_fn = ...(function read_user_chunk_fn)
    assign_int32_t(&(ptr->unknown_default), level+1);
    assign_int32_t(&(ptr->num_chunk_list), level+1);
    //ptr->chunk_list = ...(unsigned char  *chunk_list)
    assign_int8_t(&(ptr->rgb_to_gray_status), level+1);
    assign_int8_t(&(ptr->rgb_to_gray_coefficients_set), level+1);
    assign_int16_t(&(ptr->rgb_to_gray_red_coeff), level+1);
    assign_int16_t(&(ptr->rgb_to_gray_green_coeff), level+1);
    assign_int32_t(&(ptr->mng_features_permitted), level+1);
    assign_int8_t(&(ptr->filter_type), level+1);
        //ptr->malloc_fn = ...(function malloc_fn)
    //ptr->free_fn = ...(function free_fn)
    //ptr->big_row_buf = ...(unsigned char  *big_row_buf)
    //ptr->quantize_sort = ...(unsigned char  *quantize_sort)
    //ptr->index_to_palette = ...(unsigned char  *index_to_palette)
    //ptr->palette_to_index = ...(unsigned char  *palette_to_index)
    assign_int8_t(&(ptr->compression_type), level+1);
    assign_int32_t(&(ptr->user_width_max), level+1);
    assign_int32_t(&(ptr->user_height_max), level+1);
    assign_int32_t(&(ptr->user_chunk_cache_max), level+1);
    assign_int64_t(&(ptr->user_chunk_malloc_max), level+1);
    mutate_png_unknown_chunk_t(&(ptr->unknown_chunk), level+1);
    assign_int64_t(&(ptr->old_big_row_buf_size), level+1);
    //ptr->read_buffer = ...(unsigned char  *read_buffer)
    assign_int64_t(&(ptr->read_buffer_size), level+1);
    assign_int32_t(&(ptr->IDAT_read_size), level+1);
    assign_int32_t(&(ptr->io_state), level+1);
    //ptr->big_prev_row = ...(unsigned char  *big_prev_row)
    //ptr->read_filter = ...(*read_filter[4])
    mutate_png_colorspace(&(ptr->colorspace), level+1);
}
void mutate_png_colorspace(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_colorspace* ptr = ptr1;
    assign_int32_t(&(ptr->gamma), level+1);
    mutate_png_xy(&(ptr->end_points_xy), level+1);
    mutate_png_XYZ(&(ptr->end_points_XYZ), level+1);
    assign_int16_t(&(ptr->rendering_intent), level+1);
    assign_int16_t(&(ptr->flags), level+1);
}
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level){return ;}
void mutate___jmp_buf_tag(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_2(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_2* ptr = ptr1;
    if(ptr->opaque) mutate_png_control(ptr->opaque, level+1);
    assign_int32_t(&(ptr->version), level+1);
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->format), level+1);
    assign_int32_t(&(ptr->flags), level+1);
    assign_int32_t(&(ptr->colormap_entries), level+1);
    assign_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_4* ptr = ptr1;
    if(ptr->opaque) mutate_png_control(ptr->opaque, level+1);
    assign_int32_t(&(ptr->version), level+1);
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->format), level+1);
    assign_int32_t(&(ptr->flags), level+1);
    assign_int32_t(&(ptr->colormap_entries), level+1);
    assign_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){return ;}
void mutate_z_stream_s(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_19(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_19* ptr = ptr1;
    //ptr->image = ...(struct anonymous *{struct png_control *opaque; unsigned int  version; unsigned int  width; unsigned int  height; unsigned int  format; unsigned int  flags; unsigned int  colormap_entries; unsigned int  warning_or_error; char  message[64]; } image)
    //ptr->buffer = ...(const *buffer)
    assign_int32_t(&(ptr->row_stride), level+1);
    //ptr->colormap = ...(const *colormap)
    assign_int32_t(&(ptr->convert_to_8bit), level+1);
    //ptr->first_row = ...(const *first_row)
    assign_int64_t(&(ptr->row_bytes), level+1);
        //ptr->memory = ...(unsigned char  *memory)
    assign_int64_t(&(ptr->memory_bytes), level+1);
    assign_int64_t(&(ptr->output_bytes), level+1);
}
void mutate_memfuzz_anonymous_struct_18(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_18* ptr = ptr1;
    if(ptr->opaque) mutate_png_control(ptr->opaque, level+1);
    assign_int32_t(&(ptr->version), level+1);
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->format), level+1);
    assign_int32_t(&(ptr->flags), level+1);
    assign_int32_t(&(ptr->colormap_entries), level+1);
    assign_int32_t(&(ptr->warning_or_error), level+1);
    assign_int8_t_array(&(ptr->message), level + 1, 64);
}
void mutate_memfuzz_anonymous_struct_15(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_14(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_17(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_16(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_11(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_10* ptr = ptr1;
    //ptr->image = ...(struct anonymous *{struct png_control *opaque; unsigned int  version; unsigned int  width; unsigned int  height; unsigned int  format; unsigned int  flags; unsigned int  colormap_entries; unsigned int  warning_or_error; char  message[64]; } image)
        assign_int32_t(&(ptr->row_stride), level+1);
        //ptr->background = ...(const *background)
            assign_int64_t(&(ptr->row_bytes), level+1);
    assign_int32_t(&(ptr->file_encoding), level+1);
    assign_int32_t(&(ptr->gamma_to_linear), level+1);
    assign_int32_t(&(ptr->colormap_processing), level+1);
}
void mutate_png_unknown_chunk_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_unknown_chunk_t* ptr = ptr1;
    assign_int8_t_array(&(ptr->name), level + 1, 5);
    //ptr->data = ...(unsigned char  *data)
    assign_int64_t(&(ptr->size), level+1);
    assign_int8_t(&(ptr->location), level+1);
}
void mutate_memfuzz_anonymous_struct_12(void* ptr1, int level){return ;}
void mutate_png_color_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_color_struct* ptr = ptr1;
    assign_int8_t(&(ptr->red), level+1);
    assign_int8_t(&(ptr->green), level+1);
    assign_int8_t(&(ptr->blue), level+1);
}
void mutate_png_info_def(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_info_def* ptr = ptr1;
    assign_int32_t(&(ptr->width), level+1);
    assign_int32_t(&(ptr->height), level+1);
    assign_int32_t(&(ptr->valid), level+1);
    assign_int64_t(&(ptr->rowbytes), level+1);
    if(ptr->palette) mutate_png_color_struct(ptr->palette, level+1);
    assign_int16_t(&(ptr->num_palette), level+1);
    assign_int16_t(&(ptr->num_trans), level+1);
    assign_int8_t(&(ptr->bit_depth), level+1);
    assign_int8_t(&(ptr->color_type), level+1);
    assign_int8_t(&(ptr->compression_type), level+1);
    assign_int8_t(&(ptr->filter_type), level+1);
    assign_int8_t(&(ptr->interlace_type), level+1);
    assign_int8_t(&(ptr->channels), level+1);
    assign_int8_t(&(ptr->pixel_depth), level+1);
    assign_int8_t(&(ptr->spare_byte), level+1);
    assign_int8_t_array(&(ptr->signature), level + 1, 8);
    mutate_png_colorspace(&(ptr->colorspace), level+1);
    //ptr->iccp_name = ...(char  *iccp_name)
    //ptr->iccp_profile = ...(unsigned char  *iccp_profile)
    assign_int32_t(&(ptr->iccp_proflen), level+1);
    assign_int32_t(&(ptr->num_text), level+1);
    assign_int32_t(&(ptr->max_text), level+1);
    if(ptr->text) mutate_png_text_struct(ptr->text, level+1);
    mutate_png_time_struct(&(ptr->mod_time), level+1);
    mutate_png_color_8_struct(&(ptr->sig_bit), level+1);
    //ptr->trans_alpha = ...(unsigned char  *trans_alpha)
    mutate_png_color_16_struct(&(ptr->trans_color), level+1);
    mutate_png_color_16_struct(&(ptr->background), level+1);
    assign_int32_t(&(ptr->x_offset), level+1);
    assign_int32_t(&(ptr->y_offset), level+1);
    assign_int8_t(&(ptr->offset_unit_type), level+1);
    assign_int32_t(&(ptr->x_pixels_per_unit), level+1);
    assign_int32_t(&(ptr->y_pixels_per_unit), level+1);
    assign_int8_t(&(ptr->phys_unit_type), level+1);
    assign_int32_t(&(ptr->num_exif), level+1);
    //ptr->exif = ...(unsigned char  *exif)
    //ptr->eXIf_buf = ...(unsigned char  *eXIf_buf)
    //ptr->hist = ...(unsigned short  *hist)
    //ptr->pcal_purpose = ...(char  *pcal_purpose)
    assign_int32_t(&(ptr->pcal_X0), level+1);
    assign_int32_t(&(ptr->pcal_X1), level+1);
    //ptr->pcal_units = ...(char  *pcal_units)
    //ptr->pcal_params = ...(char  **pcal_params)
    assign_int8_t(&(ptr->pcal_type), level+1);
    assign_int8_t(&(ptr->pcal_nparams), level+1);
    assign_int32_t(&(ptr->free_me), level+1);
    if(ptr->unknown_chunks) mutate_png_unknown_chunk_t(ptr->unknown_chunks, level+1);
    assign_int32_t(&(ptr->unknown_chunks_num), level+1);
    if(ptr->splt_palettes) mutate_png_sPLT_struct(ptr->splt_palettes, level+1);
    assign_int32_t(&(ptr->splt_palettes_num), level+1);
    assign_int8_t(&(ptr->scal_unit), level+1);
    //ptr->scal_s_width = ...(char  *scal_s_width)
    //ptr->scal_s_height = ...(char  *scal_s_height)
    //ptr->row_pointers = ...(unsigned char  **row_pointers)
}
void mutate_memfuzz_anonymous_struct_13(void* ptr1, int level){return ;}
void mutate_png_XYZ(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_XYZ* ptr = ptr1;
    assign_int32_t(&(ptr->red_X), level+1);
    assign_int32_t(&(ptr->red_Y), level+1);
    assign_int32_t(&(ptr->red_Z), level+1);
    assign_int32_t(&(ptr->green_X), level+1);
    assign_int32_t(&(ptr->green_Y), level+1);
    assign_int32_t(&(ptr->green_Z), level+1);
    assign_int32_t(&(ptr->blue_X), level+1);
    assign_int32_t(&(ptr->blue_Y), level+1);
    assign_int32_t(&(ptr->blue_Z), level+1);
}
void mutate_memfuzz_anonymous_struct_0(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct memfuzz_anonymous_struct_0* ptr = ptr1;
    assign_int32_t(&(ptr->adler), level+1);
    assign_int32_t(&(ptr->crc), level+1);
    assign_int32_t(&(ptr->length), level+1);
    assign_int32_t_array(&(ptr->md5), level + 1, 4);
    assign_int8_t(&(ptr->have_md5), level+1);
    assign_int8_t(&(ptr->is_broken), level+1);
    assign_int16_t(&(ptr->intent), level+1);
}
void mutate_png_xy(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_xy* ptr = ptr1;
    assign_int32_t(&(ptr->redx), level+1);
    assign_int32_t(&(ptr->redy), level+1);
    assign_int32_t(&(ptr->greenx), level+1);
    assign_int32_t(&(ptr->greeny), level+1);
    assign_int32_t(&(ptr->bluex), level+1);
    assign_int32_t(&(ptr->bluey), level+1);
    assign_int32_t(&(ptr->whitex), level+1);
    assign_int32_t(&(ptr->whitey), level+1);
}
void mutate_png_row_info_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_row_info_struct* ptr = ptr1;
    assign_int32_t(&(ptr->width), level+1);
    assign_int64_t(&(ptr->rowbytes), level+1);
    assign_int8_t(&(ptr->color_type), level+1);
    assign_int8_t(&(ptr->bit_depth), level+1);
    assign_int8_t(&(ptr->channels), level+1);
    assign_int8_t(&(ptr->pixel_depth), level+1);
}
void mutate_png_dsort_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_dsort_struct* ptr = ptr1;
    if(ptr->next) mutate_png_dsort_struct(ptr->next, level+1);
    assign_int8_t(&(ptr->left), level+1);
    assign_int8_t(&(ptr->right), level+1);
}
void mutate_png_compression_buffer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_compression_buffer* ptr = ptr1;
    if(ptr->next) mutate_png_compression_buffer(ptr->next, level+1);
    assign_int8_t_array(&(ptr->output), level + 1, 1);
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate_png_time_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_time_struct* ptr = ptr1;
    assign_int16_t(&(ptr->year), level+1);
    assign_int8_t(&(ptr->month), level+1);
    assign_int8_t(&(ptr->day), level+1);
    assign_int8_t(&(ptr->hour), level+1);
    assign_int8_t(&(ptr->minute), level+1);
    assign_int8_t(&(ptr->second), level+1);
}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level){return ;}
void mutate_png_text_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct png_text_struct* ptr = ptr1;
    assign_int32_t(&(ptr->compression), level+1);
    //ptr->key = ...(char  *key)
    //ptr->text = ...(char  *text)
    assign_int64_t(&(ptr->text_length), level+1);
    assign_int64_t(&(ptr->itxt_length), level+1);
    //ptr->lang = ...(char  *lang)
    //ptr->lang_key = ...(char  *lang_key)
}
