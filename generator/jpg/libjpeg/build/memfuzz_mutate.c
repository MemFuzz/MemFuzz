#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
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
    mutate_enum(&(ptr->transform), 10);
    mutate_int32_t(&(ptr->perfect), level+1);
    mutate_int32_t(&(ptr->trim), level+1);
    mutate_int32_t(&(ptr->force_grayscale), level+1);
    mutate_int32_t(&(ptr->crop), level+1);
    mutate_int32_t(&(ptr->slow_hflip), level+1);
    mutate_int32_t(&(ptr->crop_width), level+1);
    mutate_enum(&(ptr->crop_width_set), 5);
    mutate_int32_t(&(ptr->crop_height), level+1);
    mutate_enum(&(ptr->crop_height_set), 5);
    mutate_int32_t(&(ptr->crop_xoffset), level+1);
    mutate_enum(&(ptr->crop_xoffset_set), 5);
    mutate_int32_t(&(ptr->crop_yoffset), level+1);
    mutate_enum(&(ptr->crop_yoffset_set), 5);
    {
        if(ptr->drop_ptr) { mutate_jpeg_decompress_struct(ptr->drop_ptr, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_decompress_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->drop_ptr;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->drop_ptr = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->drop_ptr = ptr_save;
        free(arr);
    }
    {
        if(ptr->drop_coef_arrays) { mutate_jvirt_barray_control(ptr->drop_coef_arrays, level+1); }
        len = 0;
        arr = pool_get_values("jvirt_barray_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->drop_coef_arrays;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->drop_coef_arrays = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->drop_coef_arrays = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->num_components), level+1);
    {
        if(ptr->workspace_coef_arrays) { mutate_jvirt_barray_control(ptr->workspace_coef_arrays, level+1); }
        len = 0;
        arr = pool_get_values("jvirt_barray_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->workspace_coef_arrays;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->workspace_coef_arrays = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->workspace_coef_arrays = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->output_width), level+1);
    mutate_int32_t(&(ptr->output_height), level+1);
    mutate_int32_t(&(ptr->x_crop_offset), level+1);
    mutate_int32_t(&(ptr->y_crop_offset), level+1);
    mutate_int32_t(&(ptr->drop_width), level+1);
    mutate_int32_t(&(ptr->drop_height), level+1);
    mutate_int32_t(&(ptr->iMCU_sample_width), level+1);
    mutate_int32_t(&(ptr->iMCU_sample_height), level+1);
    pool_insert("memfuzz_anonymous_struct_0", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_decompress_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_decompress_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_decompress_struct* ptr = ptr1;
    {
        if(ptr->err) { mutate_jpeg_error_mgr(ptr->err, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_error_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->err;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->err = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->err = ptr_save;
        free(arr);
    }
    {
        if(ptr->mem) { mutate_jpeg_memory_mgr(ptr->mem, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_memory_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mem;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mem = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mem = ptr_save;
        free(arr);
    }
    {
        if(ptr->progress) { mutate_jpeg_progress_mgr(ptr->progress, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_progress_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->progress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->progress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->progress = ptr_save;
        free(arr);
    }
        mutate_int32_t(&(ptr->is_decompressor), level+1);
    mutate_int32_t(&(ptr->global_state), level+1);
    {
        if(ptr->src) { mutate_jpeg_source_mgr(ptr->src, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_source_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->src;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->src = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->src = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->image_width), level+1);
    mutate_int32_t(&(ptr->image_height), level+1);
    mutate_int32_t(&(ptr->num_components), level+1);
    mutate_enum(&(ptr->jpeg_color_space), 17);
    mutate_enum(&(ptr->out_color_space), 17);
    mutate_int32_t(&(ptr->scale_num), level+1);
    mutate_int32_t(&(ptr->scale_denom), level+1);
    mutate_double(&(ptr->output_gamma), level+1);
    mutate_int32_t(&(ptr->buffered_image), level+1);
    mutate_int32_t(&(ptr->raw_data_out), level+1);
    mutate_enum(&(ptr->dct_method), 3);
    mutate_int32_t(&(ptr->do_fancy_upsampling), level+1);
    mutate_int32_t(&(ptr->do_block_smoothing), level+1);
    mutate_int32_t(&(ptr->quantize_colors), level+1);
    mutate_enum(&(ptr->dither_mode), 3);
    mutate_int32_t(&(ptr->two_pass_quantize), level+1);
    mutate_int32_t(&(ptr->desired_number_of_colors), level+1);
    mutate_int32_t(&(ptr->enable_1pass_quant), level+1);
    mutate_int32_t(&(ptr->enable_external_quant), level+1);
    mutate_int32_t(&(ptr->enable_2pass_quant), level+1);
    mutate_int32_t(&(ptr->output_width), level+1);
    mutate_int32_t(&(ptr->output_height), level+1);
    mutate_int32_t(&(ptr->out_color_components), level+1);
    mutate_int32_t(&(ptr->output_components), level+1);
    mutate_int32_t(&(ptr->rec_outbuf_height), level+1);
    mutate_int32_t(&(ptr->actual_number_of_colors), level+1);
    //ptr->colormap = ...(unsigned char  **colormap)
    mutate_int32_t(&(ptr->output_scanline), level+1);
    mutate_int32_t(&(ptr->input_scan_number), level+1);
    mutate_int32_t(&(ptr->input_iMCU_row), level+1);
    mutate_int32_t(&(ptr->output_scan_number), level+1);
    mutate_int32_t(&(ptr->output_iMCU_row), level+1);
    //ptr->coef_bits = ...(base_type* array[])
    //ptr->quant_tbl_ptrs = ...(*quant_tbl_ptrs[4])
    //ptr->dc_huff_tbl_ptrs = ...(*dc_huff_tbl_ptrs[4])
    //ptr->ac_huff_tbl_ptrs = ...(*ac_huff_tbl_ptrs[4])
    mutate_int32_t(&(ptr->data_precision), level+1);
    //ptr->comp_info = ...(struct anonymous *{int  component_id; int  component_index; int  h_samp_factor; int  v_samp_factor; int  quant_tbl_no; int  dc_tbl_no; int  ac_tbl_no; unsigned int  width_in_blocks; unsigned int  height_in_blocks; int  DCT_scaled_size; unsigned int  downsampled_width; unsigned int  downsampled_height; int  component_needed; int  MCU_width; int  MCU_height; int  MCU_blocks; int  MCU_sample_width; int  last_col_width; int  last_row_height; struct anonymous *{unsigned short  quantval[64]; int  sent_table; } quant_table; void  *dct_table; } comp_info)
    mutate_int32_t(&(ptr->progressive_mode), level+1);
    mutate_int32_t(&(ptr->arith_code), level+1);
    assign_int8_t_array(&(ptr->arith_dc_L), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_dc_U), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_ac_K), level + 1, 16);
    mutate_int32_t(&(ptr->restart_interval), level+1);
    mutate_int32_t(&(ptr->saw_JFIF_marker), level+1);
    mutate_int8_t(&(ptr->JFIF_major_version), level+1);
    mutate_int8_t(&(ptr->JFIF_minor_version), level+1);
    mutate_int8_t(&(ptr->density_unit), level+1);
    mutate_int16_t(&(ptr->X_density), level+1);
    mutate_int16_t(&(ptr->Y_density), level+1);
    mutate_int32_t(&(ptr->saw_Adobe_marker), level+1);
    mutate_int8_t(&(ptr->Adobe_transform), level+1);
    mutate_int32_t(&(ptr->CCIR601_sampling), level+1);
    {
        if(ptr->marker_list) { mutate_jpeg_marker_struct(ptr->marker_list, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_marker_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker_list = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->max_h_samp_factor), level+1);
    mutate_int32_t(&(ptr->max_v_samp_factor), level+1);
    mutate_int32_t(&(ptr->min_DCT_scaled_size), level+1);
    mutate_int32_t(&(ptr->total_iMCU_rows), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->sample_range_limit);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->sample_range_limit, level + 1, len); }
    #else
    //ptr->sample_range_limit = ...(unsigned char  *sample_range_limit)
    #endif
    mutate_int32_t(&(ptr->comps_in_scan), level+1);
    //ptr->cur_comp_info = ...(*cur_comp_info[4])
    mutate_int32_t(&(ptr->MCUs_per_row), level+1);
    mutate_int32_t(&(ptr->MCU_rows_in_scan), level+1);
    mutate_int32_t(&(ptr->blocks_in_MCU), level+1);
    assign_int32_t_array(&(ptr->MCU_membership), level + 1, 10);
    mutate_int32_t(&(ptr->Ss), level+1);
    mutate_int32_t(&(ptr->Se), level+1);
    mutate_int32_t(&(ptr->Ah), level+1);
    mutate_int32_t(&(ptr->Al), level+1);
    mutate_int32_t(&(ptr->unread_marker), level+1);
    {
        if(ptr->master) { mutate_jpeg_decomp_master(ptr->master, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_decomp_master", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->master;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->master = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->master = ptr_save;
        free(arr);
    }
    {
        if(ptr->main) { mutate_jpeg_d_main_controller(ptr->main, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_d_main_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->main;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->main = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->main = ptr_save;
        free(arr);
    }
    {
        if(ptr->coef) { mutate_jpeg_d_coef_controller(ptr->coef, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_d_coef_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->coef;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->coef = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->coef = ptr_save;
        free(arr);
    }
    {
        if(ptr->post) { mutate_jpeg_d_post_controller(ptr->post, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_d_post_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->post;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->post = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->post = ptr_save;
        free(arr);
    }
    {
        if(ptr->inputctl) { mutate_jpeg_input_controller(ptr->inputctl, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_input_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->inputctl;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->inputctl = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->inputctl = ptr_save;
        free(arr);
    }
    {
        if(ptr->marker) { mutate_jpeg_marker_reader(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_marker_reader", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    {
        if(ptr->entropy) { mutate_jpeg_entropy_decoder(ptr->entropy, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_entropy_decoder", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->entropy;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->entropy = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->entropy = ptr_save;
        free(arr);
    }
    {
        if(ptr->idct) { mutate_jpeg_inverse_dct(ptr->idct, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_inverse_dct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->idct;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->idct = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->idct = ptr_save;
        free(arr);
    }
    {
        if(ptr->upsample) { mutate_jpeg_upsampler(ptr->upsample, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_upsampler", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->upsample;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->upsample = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->upsample = ptr_save;
        free(arr);
    }
    {
        if(ptr->cconvert) { mutate_jpeg_color_deconverter(ptr->cconvert, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_color_deconverter", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cconvert;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cconvert = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cconvert = ptr_save;
        free(arr);
    }
    {
        if(ptr->cquantize) { mutate_jpeg_color_quantizer(ptr->cquantize, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_color_quantizer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cquantize;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cquantize = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cquantize = ptr_save;
        free(arr);
    }
    pool_insert("jpeg_decompress_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_decompress_struct  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_1* ptr = ptr1;
    assign_int32_t_array(&(ptr->i), level + 1, 8);
    assign_int8_t_array(&(ptr->s), level + 1, 80);
    pool_insert("memfuzz_anonymous_struct_1", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_error_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_error_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_error_mgr* ptr = ptr1;
    //ptr->error_exit = ...(function error_exit)
    //ptr->emit_message = ...(function emit_message)
    //ptr->output_message = ...(function output_message)
    //ptr->format_message = ...(function format_message)
    //ptr->reset_error_mgr = ...(function reset_error_mgr)
    mutate_int32_t(&(ptr->msg_code), level+1);
    //ptr->msg_parm = ...(union anonymous {int  i[8]; char  s[80]; } msg_parm)
    mutate_int32_t(&(ptr->trace_level), level+1);
    mutate_int64_t(&(ptr->num_warnings), level+1);
    //ptr->jpeg_message_table = ...(const *jpeg_message_table)
    mutate_int32_t(&(ptr->last_jpeg_message), level+1);
    //ptr->addon_message_table = ...(const *addon_message_table)
    mutate_int32_t(&(ptr->first_addon_message), level+1);
    mutate_int32_t(&(ptr->last_addon_message), level+1);
    pool_insert("jpeg_error_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_error_mgr  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_common_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_common_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_common_struct* ptr = ptr1;
    {
        if(ptr->err) { mutate_jpeg_error_mgr(ptr->err, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_error_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->err;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->err = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->err = ptr_save;
        free(arr);
    }
    {
        if(ptr->mem) { mutate_jpeg_memory_mgr(ptr->mem, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_memory_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mem;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mem = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mem = ptr_save;
        free(arr);
    }
    {
        if(ptr->progress) { mutate_jpeg_progress_mgr(ptr->progress, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_progress_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->progress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->progress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->progress = ptr_save;
        free(arr);
    }
        mutate_int32_t(&(ptr->is_decompressor), level+1);
    mutate_int32_t(&(ptr->global_state), level+1);
    pool_insert("jpeg_common_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_common_struct  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_memory_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_memory_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_memory_mgr* ptr = ptr1;
    //ptr->alloc_small = ...(function alloc_small)
    //ptr->alloc_large = ...(function alloc_large)
    //ptr->alloc_sarray = ...(function alloc_sarray)
    //ptr->alloc_barray = ...(function alloc_barray)
    //ptr->request_virt_sarray = ...(function request_virt_sarray)
    //ptr->request_virt_barray = ...(function request_virt_barray)
    //ptr->realize_virt_arrays = ...(function realize_virt_arrays)
    //ptr->access_virt_sarray = ...(function access_virt_sarray)
    //ptr->access_virt_barray = ...(function access_virt_barray)
    //ptr->free_pool = ...(function free_pool)
    //ptr->self_destruct = ...(function self_destruct)
    mutate_int64_t(&(ptr->max_memory_to_use), level+1);
    mutate_int64_t(&(ptr->max_alloc_chunk), level+1);
    pool_insert("jpeg_memory_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_memory_mgr  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_progress_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_progress_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_progress_mgr* ptr = ptr1;
    //ptr->progress_monitor = ...(function progress_monitor)
    mutate_int64_t(&(ptr->pass_counter), level+1);
    mutate_int64_t(&(ptr->pass_limit), level+1);
    mutate_int32_t(&(ptr->completed_passes), level+1);
    mutate_int32_t(&(ptr->total_passes), level+1);
    pool_insert("jpeg_progress_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_progress_mgr  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_source_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_source_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_source_mgr* ptr = ptr1;
    //ptr->next_input_byte = ...(const *next_input_byte)
    mutate_int64_t(&(ptr->bytes_in_buffer), level+1);
    //ptr->init_source = ...(function init_source)
    //ptr->fill_input_buffer = ...(function fill_input_buffer)
    //ptr->skip_input_data = ...(function skip_input_data)
    //ptr->resync_to_restart = ...(function resync_to_restart)
    //ptr->term_source = ...(function term_source)
    pool_insert("jpeg_source_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_source_mgr  \n"); fflush(stdout);
    #endif
}
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
    assign_int16_t_array(&(ptr->quantval), level + 1, 64);
    mutate_int32_t(&(ptr->sent_table), level+1);
    pool_insert("memfuzz_anonymous_struct_2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_3  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_3* ptr = ptr1;
    assign_int8_t_array(&(ptr->bits), level + 1, 17);
    assign_int8_t_array(&(ptr->huffval), level + 1, 256);
    mutate_int32_t(&(ptr->sent_table), level+1);
    pool_insert("memfuzz_anonymous_struct_3", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_3  \n"); fflush(stdout);
    #endif
}
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
    mutate_int32_t(&(ptr->component_id), level+1);
    mutate_int32_t(&(ptr->component_index), level+1);
    mutate_int32_t(&(ptr->h_samp_factor), level+1);
    mutate_int32_t(&(ptr->v_samp_factor), level+1);
    mutate_int32_t(&(ptr->quant_tbl_no), level+1);
    mutate_int32_t(&(ptr->dc_tbl_no), level+1);
    mutate_int32_t(&(ptr->ac_tbl_no), level+1);
    mutate_int32_t(&(ptr->width_in_blocks), level+1);
    mutate_int32_t(&(ptr->height_in_blocks), level+1);
    mutate_int32_t(&(ptr->DCT_scaled_size), level+1);
    mutate_int32_t(&(ptr->downsampled_width), level+1);
    mutate_int32_t(&(ptr->downsampled_height), level+1);
    mutate_int32_t(&(ptr->component_needed), level+1);
    mutate_int32_t(&(ptr->MCU_width), level+1);
    mutate_int32_t(&(ptr->MCU_height), level+1);
    mutate_int32_t(&(ptr->MCU_blocks), level+1);
    mutate_int32_t(&(ptr->MCU_sample_width), level+1);
    mutate_int32_t(&(ptr->last_col_width), level+1);
    mutate_int32_t(&(ptr->last_row_height), level+1);
    //ptr->quant_table = ...(struct anonymous *{unsigned short  quantval[64]; int  sent_table; } quant_table)
        pool_insert("memfuzz_anonymous_struct_4", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_marker_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_marker_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_marker_struct* ptr = ptr1;
    {
        if(ptr->next) { mutate_jpeg_marker_struct(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_marker_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->marker), level+1);
    mutate_int32_t(&(ptr->original_length), level+1);
    mutate_int32_t(&(ptr->data_length), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    pool_insert("jpeg_marker_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_marker_struct  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_compress_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_compress_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_compress_struct* ptr = ptr1;
    {
        if(ptr->err) { mutate_jpeg_error_mgr(ptr->err, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_error_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->err;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->err = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->err = ptr_save;
        free(arr);
    }
    {
        if(ptr->mem) { mutate_jpeg_memory_mgr(ptr->mem, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_memory_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mem;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mem = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mem = ptr_save;
        free(arr);
    }
    {
        if(ptr->progress) { mutate_jpeg_progress_mgr(ptr->progress, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_progress_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->progress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->progress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->progress = ptr_save;
        free(arr);
    }
        mutate_int32_t(&(ptr->is_decompressor), level+1);
    mutate_int32_t(&(ptr->global_state), level+1);
    {
        if(ptr->dest) { mutate_jpeg_destination_mgr(ptr->dest, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_destination_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dest;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dest = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dest = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->image_width), level+1);
    mutate_int32_t(&(ptr->image_height), level+1);
    mutate_int32_t(&(ptr->input_components), level+1);
    mutate_enum(&(ptr->in_color_space), 17);
    mutate_double(&(ptr->input_gamma), level+1);
    mutate_int32_t(&(ptr->data_precision), level+1);
    mutate_int32_t(&(ptr->num_components), level+1);
    mutate_enum(&(ptr->jpeg_color_space), 17);
    //ptr->comp_info = ...(struct anonymous *{int  component_id; int  component_index; int  h_samp_factor; int  v_samp_factor; int  quant_tbl_no; int  dc_tbl_no; int  ac_tbl_no; unsigned int  width_in_blocks; unsigned int  height_in_blocks; int  DCT_scaled_size; unsigned int  downsampled_width; unsigned int  downsampled_height; int  component_needed; int  MCU_width; int  MCU_height; int  MCU_blocks; int  MCU_sample_width; int  last_col_width; int  last_row_height; struct anonymous *{unsigned short  quantval[64]; int  sent_table; } quant_table; void  *dct_table; } comp_info)
    //ptr->quant_tbl_ptrs = ...(*quant_tbl_ptrs[4])
    //ptr->dc_huff_tbl_ptrs = ...(*dc_huff_tbl_ptrs[4])
    //ptr->ac_huff_tbl_ptrs = ...(*ac_huff_tbl_ptrs[4])
    assign_int8_t_array(&(ptr->arith_dc_L), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_dc_U), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_ac_K), level + 1, 16);
    mutate_int32_t(&(ptr->num_scans), level+1);
    //ptr->scan_info = ...(const *scan_info)
    mutate_int32_t(&(ptr->raw_data_in), level+1);
    mutate_int32_t(&(ptr->arith_code), level+1);
    mutate_int32_t(&(ptr->optimize_coding), level+1);
    mutate_int32_t(&(ptr->CCIR601_sampling), level+1);
    mutate_int32_t(&(ptr->smoothing_factor), level+1);
    mutate_enum(&(ptr->dct_method), 3);
    mutate_int32_t(&(ptr->restart_interval), level+1);
    mutate_int32_t(&(ptr->restart_in_rows), level+1);
    mutate_int32_t(&(ptr->write_JFIF_header), level+1);
    mutate_int8_t(&(ptr->JFIF_major_version), level+1);
    mutate_int8_t(&(ptr->JFIF_minor_version), level+1);
    mutate_int8_t(&(ptr->density_unit), level+1);
    mutate_int16_t(&(ptr->X_density), level+1);
    mutate_int16_t(&(ptr->Y_density), level+1);
    mutate_int32_t(&(ptr->write_Adobe_marker), level+1);
    mutate_int32_t(&(ptr->next_scanline), level+1);
    mutate_int32_t(&(ptr->progressive_mode), level+1);
    mutate_int32_t(&(ptr->max_h_samp_factor), level+1);
    mutate_int32_t(&(ptr->max_v_samp_factor), level+1);
    mutate_int32_t(&(ptr->total_iMCU_rows), level+1);
    mutate_int32_t(&(ptr->comps_in_scan), level+1);
    //ptr->cur_comp_info = ...(*cur_comp_info[4])
    mutate_int32_t(&(ptr->MCUs_per_row), level+1);
    mutate_int32_t(&(ptr->MCU_rows_in_scan), level+1);
    mutate_int32_t(&(ptr->blocks_in_MCU), level+1);
    assign_int32_t_array(&(ptr->MCU_membership), level + 1, 10);
    mutate_int32_t(&(ptr->Ss), level+1);
    mutate_int32_t(&(ptr->Se), level+1);
    mutate_int32_t(&(ptr->Ah), level+1);
    mutate_int32_t(&(ptr->Al), level+1);
    {
        if(ptr->master) { mutate_jpeg_comp_master(ptr->master, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_comp_master", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->master;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->master = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->master = ptr_save;
        free(arr);
    }
    {
        if(ptr->main) { mutate_jpeg_c_main_controller(ptr->main, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_c_main_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->main;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->main = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->main = ptr_save;
        free(arr);
    }
    {
        if(ptr->prep) { mutate_jpeg_c_prep_controller(ptr->prep, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_c_prep_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->prep;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->prep = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->prep = ptr_save;
        free(arr);
    }
    {
        if(ptr->coef) { mutate_jpeg_c_coef_controller(ptr->coef, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_c_coef_controller", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->coef;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->coef = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->coef = ptr_save;
        free(arr);
    }
    {
        if(ptr->marker) { mutate_jpeg_marker_writer(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_marker_writer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    {
        if(ptr->cconvert) { mutate_jpeg_color_converter(ptr->cconvert, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_color_converter", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cconvert;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cconvert = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cconvert = ptr_save;
        free(arr);
    }
    {
        if(ptr->downsample) { mutate_jpeg_downsampler(ptr->downsample, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_downsampler", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->downsample;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->downsample = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->downsample = ptr_save;
        free(arr);
    }
    {
        if(ptr->fdct) { mutate_jpeg_forward_dct(ptr->fdct, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_forward_dct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->fdct;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->fdct = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->fdct = ptr_save;
        free(arr);
    }
    {
        if(ptr->entropy) { mutate_jpeg_entropy_encoder(ptr->entropy, level+1); }
        len = 0;
        arr = pool_get_values("jpeg_entropy_encoder", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->entropy;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->entropy = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->entropy = ptr_save;
        free(arr);
    }
    //ptr->script_space = ...(struct anonymous *{int  comps_in_scan; int  component_index[4]; int  Ss; int  Se; int  Ah; int  Al; } script_space)
    mutate_int32_t(&(ptr->script_space_size), level+1);
    pool_insert("jpeg_compress_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_compress_struct  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_destination_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_destination_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_destination_mgr* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->next_output_byte);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->next_output_byte, level + 1, len); }
    #else
    //ptr->next_output_byte = ...(unsigned char  *next_output_byte)
    #endif
    mutate_int64_t(&(ptr->free_in_buffer), level+1);
    //ptr->init_destination = ...(function init_destination)
    //ptr->empty_output_buffer = ...(function empty_output_buffer)
    //ptr->term_destination = ...(function term_destination)
    pool_insert("jpeg_destination_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_destination_mgr  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_5  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_5* ptr = ptr1;
    mutate_int32_t(&(ptr->comps_in_scan), level+1);
    assign_int32_t_array(&(ptr->component_index), level + 1, 4);
    mutate_int32_t(&(ptr->Ss), level+1);
    mutate_int32_t(&(ptr->Se), level+1);
    mutate_int32_t(&(ptr->Ah), level+1);
    mutate_int32_t(&(ptr->Al), level+1);
    pool_insert("memfuzz_anonymous_struct_5", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_5  \n"); fflush(stdout);
    #endif
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_cdjpeg_progress_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_cdjpeg_progress_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct cdjpeg_progress_mgr* ptr = ptr1;
    mutate_jpeg_progress_mgr(&(ptr->pub), level+1);
    mutate_int32_t(&(ptr->completed_extra_passes), level+1);
    mutate_int32_t(&(ptr->total_extra_passes), level+1);
    mutate_int32_t(&(ptr->max_scans), level+1);
    mutate_int32_t(&(ptr->report), level+1);
    mutate_int32_t(&(ptr->percent_done), level+1);
    pool_insert("cdjpeg_progress_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_cdjpeg_progress_mgr  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_6  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_6* ptr = ptr1;
    assign_int32_t_array(&(ptr->i), level + 1, 8);
    assign_int8_t_array(&(ptr->s), level + 1, 80);
    pool_insert("memfuzz_anonymous_struct_6", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_6  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_11(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_11  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_11* ptr = ptr1;
    assign_int32_t_array(&(ptr->i), level + 1, 8);
    assign_int8_t_array(&(ptr->s), level + 1, 80);
    pool_insert("memfuzz_anonymous_struct_11", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_11  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_12(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_13(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_14(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_15(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_15  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_15* ptr = ptr1;
    assign_int32_t_array(&(ptr->i), level + 1, 8);
    assign_int8_t_array(&(ptr->s), level + 1, 80);
    pool_insert("memfuzz_anonymous_struct_15", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_15  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_16(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_17(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_18(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_19(void* ptr1, int level){return ;}
void mutate_jpeg_decomp_master(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_decomp_master  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_decomp_master* ptr = ptr1;
    //ptr->prepare_for_output_pass = ...(function prepare_for_output_pass)
    //ptr->finish_output_pass = ...(function finish_output_pass)
    mutate_int32_t(&(ptr->is_dummy_pass), level+1);
    mutate_int32_t(&(ptr->first_iMCU_col), level+1);
    mutate_int32_t(&(ptr->last_iMCU_col), level+1);
    assign_int32_t_array(&(ptr->first_MCU_col), level + 1, 10);
    assign_int32_t_array(&(ptr->last_MCU_col), level + 1, 10);
    mutate_int32_t(&(ptr->jinit_upsampler_no_alloc), level+1);
    mutate_int32_t(&(ptr->last_good_iMCU_row), level+1);
    pool_insert("jpeg_decomp_master", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_decomp_master  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_d_main_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_d_main_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_d_main_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->process_data = ...(function process_data)
    pool_insert("jpeg_d_main_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_d_main_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_d_coef_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_d_coef_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_d_coef_controller* ptr = ptr1;
    //ptr->start_input_pass = ...(function start_input_pass)
    //ptr->consume_data = ...(function consume_data)
    //ptr->start_output_pass = ...(function start_output_pass)
    //ptr->decompress_data = ...(function decompress_data)
    {
        if(ptr->coef_arrays) { mutate_jvirt_barray_control(ptr->coef_arrays, level+1); }
        len = 0;
        arr = pool_get_values("jvirt_barray_control", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->coef_arrays;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->coef_arrays = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->coef_arrays = ptr_save;
        free(arr);
    }
    pool_insert("jpeg_d_coef_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_d_coef_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_d_post_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_d_post_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_d_post_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->post_process_data = ...(function post_process_data)
    pool_insert("jpeg_d_post_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_d_post_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_input_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_input_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_input_controller* ptr = ptr1;
    //ptr->consume_input = ...(function consume_input)
    //ptr->reset_input_controller = ...(function reset_input_controller)
    //ptr->start_input_pass = ...(function start_input_pass)
    //ptr->finish_input_pass = ...(function finish_input_pass)
    mutate_int32_t(&(ptr->has_multiple_scans), level+1);
    mutate_int32_t(&(ptr->eoi_reached), level+1);
    pool_insert("jpeg_input_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_input_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_marker_reader(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_marker_reader  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_marker_reader* ptr = ptr1;
    //ptr->reset_marker_reader = ...(function reset_marker_reader)
    //ptr->read_markers = ...(function read_markers)
    //ptr->read_restart_marker = ...(function read_restart_marker)
    mutate_int32_t(&(ptr->saw_SOI), level+1);
    mutate_int32_t(&(ptr->saw_SOF), level+1);
    mutate_int32_t(&(ptr->next_restart_num), level+1);
    mutate_int32_t(&(ptr->discarded_bytes), level+1);
    pool_insert("jpeg_marker_reader", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_marker_reader  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_entropy_decoder(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_entropy_decoder  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_entropy_decoder* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->decode_mcu = ...(function decode_mcu)
    mutate_int32_t(&(ptr->insufficient_data), level+1);
    pool_insert("jpeg_entropy_decoder", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_entropy_decoder  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_inverse_dct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_inverse_dct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_inverse_dct* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->inverse_DCT = ...(*inverse_DCT[10])
    pool_insert("jpeg_inverse_dct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_inverse_dct  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_upsampler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_upsampler  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_upsampler* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->upsample = ...(function upsample)
    mutate_int32_t(&(ptr->need_context_rows), level+1);
    pool_insert("jpeg_upsampler", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_upsampler  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_color_deconverter(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_color_deconverter  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_color_deconverter* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->color_convert = ...(function color_convert)
    pool_insert("jpeg_color_deconverter", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_color_deconverter  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_color_quantizer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_color_quantizer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_color_quantizer* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->color_quantize = ...(function color_quantize)
    //ptr->finish_pass = ...(function finish_pass)
    //ptr->new_color_map = ...(function new_color_map)
    pool_insert("jpeg_color_quantizer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_color_quantizer  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_20(void* ptr1, int level){return ;}
void mutate_jpeg_comp_master(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_comp_master  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_comp_master* ptr = ptr1;
    //ptr->prepare_for_pass = ...(function prepare_for_pass)
    //ptr->pass_startup = ...(function pass_startup)
    //ptr->finish_pass = ...(function finish_pass)
    mutate_int32_t(&(ptr->call_pass_startup), level+1);
    mutate_int32_t(&(ptr->is_last_pass), level+1);
    pool_insert("jpeg_comp_master", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_comp_master  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_c_main_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_c_main_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_c_main_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->process_data = ...(function process_data)
    pool_insert("jpeg_c_main_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_c_main_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_c_prep_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_c_prep_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_c_prep_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->pre_process_data = ...(function pre_process_data)
    pool_insert("jpeg_c_prep_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_c_prep_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_c_coef_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_c_coef_controller  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_c_coef_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->compress_data = ...(function compress_data)
    pool_insert("jpeg_c_coef_controller", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_c_coef_controller  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_marker_writer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_marker_writer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_marker_writer* ptr = ptr1;
    //ptr->write_file_header = ...(function write_file_header)
    //ptr->write_frame_header = ...(function write_frame_header)
    //ptr->write_scan_header = ...(function write_scan_header)
    //ptr->write_file_trailer = ...(function write_file_trailer)
    //ptr->write_tables_only = ...(function write_tables_only)
    //ptr->write_marker_header = ...(function write_marker_header)
    //ptr->write_marker_byte = ...(function write_marker_byte)
    pool_insert("jpeg_marker_writer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_marker_writer  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_color_converter(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_color_converter  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_color_converter* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->color_convert = ...(function color_convert)
    pool_insert("jpeg_color_converter", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_color_converter  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_downsampler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_downsampler  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_downsampler* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->downsample = ...(function downsample)
    mutate_int32_t(&(ptr->need_context_rows), level+1);
    pool_insert("jpeg_downsampler", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_downsampler  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_forward_dct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_forward_dct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_forward_dct* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->forward_DCT = ...(function forward_DCT)
    pool_insert("jpeg_forward_dct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_forward_dct  \n"); fflush(stdout);
    #endif
}
void mutate_jpeg_entropy_encoder(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_jpeg_entropy_encoder  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct jpeg_entropy_encoder* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->encode_mcu = ...(function encode_mcu)
    //ptr->finish_pass = ...(function finish_pass)
    pool_insert("jpeg_entropy_encoder", ptr1);
    #ifdef DEBUG
    printf("leave mutate_jpeg_entropy_encoder  \n"); fflush(stdout);
    #endif
}
void mutate_jvirt_barray_control(void* ptr1, int level){return ;}
