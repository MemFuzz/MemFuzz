#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_config.h"
void mutate_jpeg_error_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_error_mgr* ptr = ptr1;
    //ptr->error_exit = ...(function error_exit)
    //ptr->emit_message = ...(function emit_message)
    //ptr->output_message = ...(function output_message)
    //ptr->format_message = ...(function format_message)
    //ptr->reset_error_mgr = ...(function reset_error_mgr)
    assign_int32_t(&(ptr->msg_code), level+1);
    //ptr->msg_parm = ...(union anonymous {int  i[8]; char  s[80]; } msg_parm)
    assign_int32_t(&(ptr->trace_level), level+1);
    assign_int64_t(&(ptr->num_warnings), level+1);
    //ptr->jpeg_message_table = ...(const *jpeg_message_table)
    assign_int32_t(&(ptr->last_jpeg_message), level+1);
    //ptr->addon_message_table = ...(const *addon_message_table)
    assign_int32_t(&(ptr->first_addon_message), level+1);
    assign_int32_t(&(ptr->last_addon_message), level+1);
}
void mutate_jpeg_forward_dct(void* ptr1, int level){return ;}
void mutate_jpeg_marker_reader(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_marker_reader* ptr = ptr1;
    //ptr->reset_marker_reader = ...(function reset_marker_reader)
    //ptr->read_markers = ...(function read_markers)
    //ptr->read_restart_marker = ...(function read_restart_marker)
    assign_int32_t(&(ptr->saw_SOI), level+1);
    assign_int32_t(&(ptr->saw_SOF), level+1);
    assign_int32_t(&(ptr->next_restart_num), level+1);
    assign_int32_t(&(ptr->discarded_bytes), level+1);
}
void mutate_jpeg_memory_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
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
    assign_int64_t(&(ptr->max_memory_to_use), level+1);
    assign_int64_t(&(ptr->max_alloc_chunk), level+1);
}
void mutate_jpeg_entropy_encoder(void* ptr1, int level){return ;}
void mutate_jpeg_inverse_dct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_inverse_dct* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->inverse_DCT = ...(*inverse_DCT[10])
}
void mutate_jpeg_d_main_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_d_main_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->process_data = ...(function process_data)
}
void mutate_jpeg_destination_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_destination_mgr* ptr = ptr1;
    //ptr->next_output_byte = ...(unsigned char  *next_output_byte)
    assign_int64_t(&(ptr->free_in_buffer), level+1);
    //ptr->init_destination = ...(function init_destination)
    //ptr->empty_output_buffer = ...(function empty_output_buffer)
    //ptr->term_destination = ...(function term_destination)
}
void mutate_jpeg_comp_master(void* ptr1, int level){return ;}
void mutate_jpeg_decompress_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_decompress_struct* ptr = ptr1;
    if(ptr->err) mutate_jpeg_error_mgr(ptr->err, level+1);
    if(ptr->mem) mutate_jpeg_memory_mgr(ptr->mem, level+1);
    if(ptr->progress) mutate_jpeg_progress_mgr(ptr->progress, level+1);
        assign_int32_t(&(ptr->is_decompressor), level+1);
    assign_int32_t(&(ptr->global_state), level+1);
    if(ptr->src) mutate_jpeg_source_mgr(ptr->src, level+1);
    assign_int32_t(&(ptr->image_width), level+1);
    assign_int32_t(&(ptr->image_height), level+1);
    assign_int32_t(&(ptr->num_components), level+1);
    mutate_enum(&(ptr->jpeg_color_space), 17);
    mutate_enum(&(ptr->out_color_space), 17);
    assign_int32_t(&(ptr->scale_num), level+1);
    assign_int32_t(&(ptr->scale_denom), level+1);
    assign_double(&(ptr->output_gamma), level+1);
    assign_int32_t(&(ptr->buffered_image), level+1);
    assign_int32_t(&(ptr->raw_data_out), level+1);
    mutate_enum(&(ptr->dct_method), 3);
    assign_int32_t(&(ptr->do_fancy_upsampling), level+1);
    assign_int32_t(&(ptr->do_block_smoothing), level+1);
    assign_int32_t(&(ptr->quantize_colors), level+1);
    mutate_enum(&(ptr->dither_mode), 3);
    assign_int32_t(&(ptr->two_pass_quantize), level+1);
    assign_int32_t(&(ptr->desired_number_of_colors), level+1);
    assign_int32_t(&(ptr->enable_1pass_quant), level+1);
    assign_int32_t(&(ptr->enable_external_quant), level+1);
    assign_int32_t(&(ptr->enable_2pass_quant), level+1);
    assign_int32_t(&(ptr->output_width), level+1);
    assign_int32_t(&(ptr->output_height), level+1);
    assign_int32_t(&(ptr->out_color_components), level+1);
    assign_int32_t(&(ptr->output_components), level+1);
    assign_int32_t(&(ptr->rec_outbuf_height), level+1);
    assign_int32_t(&(ptr->actual_number_of_colors), level+1);
    //ptr->colormap = ...(unsigned char  **colormap)
    assign_int32_t(&(ptr->output_scanline), level+1);
    assign_int32_t(&(ptr->input_scan_number), level+1);
    assign_int32_t(&(ptr->input_iMCU_row), level+1);
    assign_int32_t(&(ptr->output_scan_number), level+1);
    assign_int32_t(&(ptr->output_iMCU_row), level+1);
    //ptr->coef_bits = ...(base_type* array[])
    //ptr->quant_tbl_ptrs = ...(*quant_tbl_ptrs[4])
    //ptr->dc_huff_tbl_ptrs = ...(*dc_huff_tbl_ptrs[4])
    //ptr->ac_huff_tbl_ptrs = ...(*ac_huff_tbl_ptrs[4])
    assign_int32_t(&(ptr->data_precision), level+1);
    //ptr->comp_info = ...(struct anonymous *{int  component_id; int  component_index; int  h_samp_factor; int  v_samp_factor; int  quant_tbl_no; int  dc_tbl_no; int  ac_tbl_no; unsigned int  width_in_blocks; unsigned int  height_in_blocks; int  DCT_scaled_size; unsigned int  downsampled_width; unsigned int  downsampled_height; int  component_needed; int  MCU_width; int  MCU_height; int  MCU_blocks; int  MCU_sample_width; int  last_col_width; int  last_row_height; struct anonymous *{unsigned short  quantval[64]; int  sent_table; } quant_table; void  *dct_table; } comp_info)
    assign_int32_t(&(ptr->progressive_mode), level+1);
    assign_int32_t(&(ptr->arith_code), level+1);
    assign_int8_t_array(&(ptr->arith_dc_L), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_dc_U), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_ac_K), level + 1, 16);
    assign_int32_t(&(ptr->restart_interval), level+1);
    assign_int32_t(&(ptr->saw_JFIF_marker), level+1);
    assign_int8_t(&(ptr->JFIF_major_version), level+1);
    assign_int8_t(&(ptr->JFIF_minor_version), level+1);
    assign_int8_t(&(ptr->density_unit), level+1);
    assign_int16_t(&(ptr->X_density), level+1);
    assign_int16_t(&(ptr->Y_density), level+1);
    assign_int32_t(&(ptr->saw_Adobe_marker), level+1);
    assign_int8_t(&(ptr->Adobe_transform), level+1);
    assign_int32_t(&(ptr->CCIR601_sampling), level+1);
    if(ptr->marker_list) mutate_jpeg_marker_struct(ptr->marker_list, level+1);
    assign_int32_t(&(ptr->max_h_samp_factor), level+1);
    assign_int32_t(&(ptr->max_v_samp_factor), level+1);
    assign_int32_t(&(ptr->min_DCT_scaled_size), level+1);
    assign_int32_t(&(ptr->total_iMCU_rows), level+1);
    //ptr->sample_range_limit = ...(unsigned char  *sample_range_limit)
    assign_int32_t(&(ptr->comps_in_scan), level+1);
    //ptr->cur_comp_info = ...(*cur_comp_info[4])
    assign_int32_t(&(ptr->MCUs_per_row), level+1);
    assign_int32_t(&(ptr->MCU_rows_in_scan), level+1);
    assign_int32_t(&(ptr->blocks_in_MCU), level+1);
    assign_int32_t_array(&(ptr->MCU_membership), level + 1, 10);
    assign_int32_t(&(ptr->Ss1), level+1);
    assign_int32_t(&(ptr->Se1), level+1);
    assign_int32_t(&(ptr->Ah1), level+1);
    assign_int32_t(&(ptr->Al1), level+1);
    assign_int32_t(&(ptr->unread_marker), level+1);
    if(ptr->master) mutate_jpeg_decomp_master(ptr->master, level+1);
    if(ptr->main) mutate_jpeg_d_main_controller(ptr->main, level+1);
    if(ptr->coef) mutate_jpeg_d_coef_controller(ptr->coef, level+1);
    if(ptr->post) mutate_jpeg_d_post_controller(ptr->post, level+1);
    if(ptr->inputctl) mutate_jpeg_input_controller(ptr->inputctl, level+1);
    if(ptr->marker) mutate_jpeg_marker_reader(ptr->marker, level+1);
    if(ptr->entropy) mutate_jpeg_entropy_decoder(ptr->entropy, level+1);
    if(ptr->idct) mutate_jpeg_inverse_dct(ptr->idct, level+1);
    if(ptr->upsample) mutate_jpeg_upsampler(ptr->upsample, level+1);
    if(ptr->cconvert) mutate_jpeg_color_deconverter(ptr->cconvert, level+1);
    if(ptr->cquantize) mutate_jpeg_color_quantizer(ptr->cquantize, level+1);
}
void mutate_jpeg_color_converter(void* ptr1, int level){return ;}
void mutate_jpeg_color_deconverter(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_color_deconverter* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->color_convert = ...(function color_convert)
}
void mutate_jpeg_entropy_decoder(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_entropy_decoder* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->decode_mcu = ...(function decode_mcu)
    assign_int32_t(&(ptr->insufficient_data), level+1);
}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_jpeg_common_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_common_struct* ptr = ptr1;
    if(ptr->err) mutate_jpeg_error_mgr(ptr->err, level+1);
    if(ptr->mem) mutate_jpeg_memory_mgr(ptr->mem, level+1);
    if(ptr->progress) mutate_jpeg_progress_mgr(ptr->progress, level+1);
        assign_int32_t(&(ptr->is_decompressor), level+1);
    assign_int32_t(&(ptr->global_state), level+1);
}
void mutate_jpeg_source_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_source_mgr* ptr = ptr1;
    //ptr->next_input_byte = ...(const *next_input_byte)
    assign_int64_t(&(ptr->bytes_in_buffer), level+1);
    //ptr->init_source = ...(function init_source)
    //ptr->fill_input_buffer = ...(function fill_input_buffer)
    //ptr->skip_input_data = ...(function skip_input_data)
    //ptr->resync_to_restart = ...(function resync_to_restart)
    //ptr->term_source = ...(function term_source)
}
void mutate_jpeg_c_main_controller(void* ptr1, int level){return ;}
void mutate_jpeg_marker_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_marker_struct* ptr = ptr1;
    if(ptr->next) mutate_jpeg_marker_struct(ptr->next, level+1);
    assign_int8_t(&(ptr->marker), level+1);
    assign_int32_t(&(ptr->original_length), level+1);
    assign_int32_t(&(ptr->data_length), level+1);
    //ptr->data = ...(unsigned char  *data)
}
void mutate_jpeg_input_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_input_controller* ptr = ptr1;
    //ptr->consume_input = ...(function consume_input)
    //ptr->reset_input_controller = ...(function reset_input_controller)
    //ptr->start_input_pass = ...(function start_input_pass)
    //ptr->finish_input_pass = ...(function finish_input_pass)
    assign_int32_t(&(ptr->has_multiple_scans), level+1);
    assign_int32_t(&(ptr->eoi_reached), level+1);
}
void mutate_cdjpeg_progress_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct cdjpeg_progress_mgr* ptr = ptr1;
    mutate_jpeg_progress_mgr(&(ptr->pub), level+1);
    assign_int32_t(&(ptr->completed_extra_passes), level+1);
    assign_int32_t(&(ptr->total_extra_passes), level+1);
    assign_int32_t(&(ptr->max_scans), level+1);
    assign_int32_t(&(ptr->report), level+1);
    assign_int32_t(&(ptr->percent_done), level+1);
}
void mutate_jpeg_d_coef_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_d_coef_controller* ptr = ptr1;
    //ptr->start_input_pass = ...(function start_input_pass)
    //ptr->consume_data = ...(function consume_data)
    //ptr->start_output_pass = ...(function start_output_pass)
    //ptr->decompress_data = ...(function decompress_data)
    if(ptr->coef_arrays) mutate_jvirt_barray_control(ptr->coef_arrays, level+1);
}
void mutate_jpeg_progress_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_progress_mgr* ptr = ptr1;
    //ptr->progress_monitor = ...(function progress_monitor)
    assign_int64_t(&(ptr->pass_counter), level+1);
    assign_int64_t(&(ptr->pass_limit), level+1);
    assign_int32_t(&(ptr->completed_passes), level+1);
    assign_int32_t(&(ptr->total_passes), level+1);
}
void mutate_jpeg_d_post_controller(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_d_post_controller* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->post_process_data = ...(function post_process_data)
}
void mutate_jpeg_upsampler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_upsampler* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->upsample = ...(function upsample)
    assign_int32_t(&(ptr->need_context_rows), level+1);
}
void mutate_jpeg_marker_writer(void* ptr1, int level){return ;}
void mutate_jpeg_color_quantizer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_color_quantizer* ptr = ptr1;
    //ptr->start_pass = ...(function start_pass)
    //ptr->color_quantize = ...(function color_quantize)
    //ptr->finish_pass = ...(function finish_pass)
    //ptr->new_color_map = ...(function new_color_map)
}
void mutate_jpeg_c_prep_controller(void* ptr1, int level){return ;}
void mutate_jpeg_c_coef_controller(void* ptr1, int level){return ;}
void mutate_djpeg_dest_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct djpeg_dest_struct* ptr = ptr1;
    //ptr->start_output = ...(function start_output)
    //ptr->put_pixel_rows = ...(function put_pixel_rows)
    //ptr->finish_output = ...(function finish_output)
    //ptr->calc_buffer_dimensions = ...(function calc_buffer_dimensions)
    if(ptr->output_file) mutate__IO_FILE(ptr->output_file, level+1);
    //ptr->buffer = ...(unsigned char  **buffer)
    assign_int32_t(&(ptr->buffer_height), level+1);
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate_jvirt_barray_control(void* ptr1, int level){return ;}
void mutate_jpeg_decomp_master(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_decomp_master* ptr = ptr1;
    //ptr->prepare_for_output_pass = ...(function prepare_for_output_pass)
    //ptr->finish_output_pass = ...(function finish_output_pass)
    assign_int32_t(&(ptr->is_dummy_pass), level+1);
    assign_int32_t(&(ptr->first_iMCU_col), level+1);
    assign_int32_t(&(ptr->last_iMCU_col), level+1);
    assign_int32_t_array(&(ptr->first_MCU_col), level + 1, 10);
    assign_int32_t_array(&(ptr->last_MCU_col), level + 1, 10);
    assign_int32_t(&(ptr->jinit_upsampler_no_alloc), level+1);
    assign_int32_t(&(ptr->last_good_iMCU_row), level+1);
}
void mutate_jpeg_downsampler(void* ptr1, int level){return ;}
void mutate_jpeg_compress_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    struct jpeg_compress_struct* ptr = ptr1;
    if(ptr->err) mutate_jpeg_error_mgr(ptr->err, level+1);
    if(ptr->mem) mutate_jpeg_memory_mgr(ptr->mem, level+1);
    if(ptr->progress) mutate_jpeg_progress_mgr(ptr->progress, level+1);
        assign_int32_t(&(ptr->is_decompressor), level+1);
    assign_int32_t(&(ptr->global_state), level+1);
    if(ptr->dest) mutate_jpeg_destination_mgr(ptr->dest, level+1);
    assign_int32_t(&(ptr->image_width), level+1);
    assign_int32_t(&(ptr->image_height), level+1);
    assign_int32_t(&(ptr->input_components), level+1);
    mutate_enum(&(ptr->in_color_space), 17);
    assign_double(&(ptr->input_gamma), level+1);
    assign_int32_t(&(ptr->data_precision), level+1);
    assign_int32_t(&(ptr->num_components), level+1);
    mutate_enum(&(ptr->jpeg_color_space), 17);
    //ptr->comp_info = ...(struct anonymous *{int  component_id; int  component_index; int  h_samp_factor; int  v_samp_factor; int  quant_tbl_no; int  dc_tbl_no; int  ac_tbl_no; unsigned int  width_in_blocks; unsigned int  height_in_blocks; int  DCT_scaled_size; unsigned int  downsampled_width; unsigned int  downsampled_height; int  component_needed; int  MCU_width; int  MCU_height; int  MCU_blocks; int  MCU_sample_width; int  last_col_width; int  last_row_height; struct anonymous *{unsigned short  quantval[64]; int  sent_table; } quant_table; void  *dct_table; } comp_info)
    //ptr->quant_tbl_ptrs = ...(*quant_tbl_ptrs[4])
    //ptr->dc_huff_tbl_ptrs = ...(*dc_huff_tbl_ptrs[4])
    //ptr->ac_huff_tbl_ptrs = ...(*ac_huff_tbl_ptrs[4])
    assign_int8_t_array(&(ptr->arith_dc_L), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_dc_U), level + 1, 16);
    assign_int8_t_array(&(ptr->arith_ac_K), level + 1, 16);
    assign_int32_t(&(ptr->num_scans), level+1);
    //ptr->scan_info = ...(const *scan_info)
    assign_int32_t(&(ptr->raw_data_in), level+1);
    assign_int32_t(&(ptr->arith_code), level+1);
    assign_int32_t(&(ptr->optimize_coding), level+1);
    assign_int32_t(&(ptr->CCIR601_sampling), level+1);
    assign_int32_t(&(ptr->smoothing_factor), level+1);
    mutate_enum(&(ptr->dct_method), 3);
    assign_int32_t(&(ptr->restart_interval), level+1);
    assign_int32_t(&(ptr->restart_in_rows), level+1);
    assign_int32_t(&(ptr->write_JFIF_header), level+1);
    assign_int8_t(&(ptr->JFIF_major_version), level+1);
    assign_int8_t(&(ptr->JFIF_minor_version), level+1);
    assign_int8_t(&(ptr->density_unit), level+1);
    assign_int16_t(&(ptr->X_density), level+1);
    assign_int16_t(&(ptr->Y_density), level+1);
    assign_int32_t(&(ptr->write_Adobe_marker), level+1);
    assign_int32_t(&(ptr->next_scanline), level+1);
    assign_int32_t(&(ptr->progressive_mode), level+1);
    assign_int32_t(&(ptr->max_h_samp_factor), level+1);
    assign_int32_t(&(ptr->max_v_samp_factor), level+1);
    assign_int32_t(&(ptr->total_iMCU_rows), level+1);
    assign_int32_t(&(ptr->comps_in_scan), level+1);
    //ptr->cur_comp_info = ...(*cur_comp_info[4])
    assign_int32_t(&(ptr->MCUs_per_row), level+1);
    assign_int32_t(&(ptr->MCU_rows_in_scan), level+1);
    assign_int32_t(&(ptr->blocks_in_MCU), level+1);
    assign_int32_t_array(&(ptr->MCU_membership), level + 1, 10);
    assign_int32_t(&(ptr->Ss), level+1);
    assign_int32_t(&(ptr->Se), level+1);
    assign_int32_t(&(ptr->Ah), level+1);
    assign_int32_t(&(ptr->Al), level+1);
    if(ptr->master) mutate_jpeg_comp_master(ptr->master, level+1);
    if(ptr->main) mutate_jpeg_c_main_controller(ptr->main, level+1);
    if(ptr->prep) mutate_jpeg_c_prep_controller(ptr->prep, level+1);
    if(ptr->coef) mutate_jpeg_c_coef_controller(ptr->coef, level+1);
    if(ptr->marker) mutate_jpeg_marker_writer(ptr->marker, level+1);
    if(ptr->cconvert) mutate_jpeg_color_converter(ptr->cconvert, level+1);
    if(ptr->downsample) mutate_jpeg_downsampler(ptr->downsample, level+1);
    if(ptr->fdct) mutate_jpeg_forward_dct(ptr->fdct, level+1);
    if(ptr->entropy) mutate_jpeg_entropy_encoder(ptr->entropy, level+1);
    //ptr->script_space = ...(struct anonymous *{int  comps_in_scan; int  component_index[4]; int  Ss; int  Se; int  Ah; int  Al; } script_space)
    assign_int32_t(&(ptr->script_space_size), level+1);
}
