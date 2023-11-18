#ifndef MEMFUZZ_MUTATE_H_
#define MEMFUZZ_MUTATE_H_
void mutate_jpeg_error_mgr(void* ptr1, int level);
void mutate_jpeg_forward_dct(void* ptr1, int level);
void mutate_jpeg_marker_reader(void* ptr1, int level);
void mutate_jpeg_memory_mgr(void* ptr1, int level);
void mutate_jpeg_entropy_encoder(void* ptr1, int level);
void mutate_jpeg_inverse_dct(void* ptr1, int level);
void mutate_jpeg_d_main_controller(void* ptr1, int level);
void mutate_jpeg_destination_mgr(void* ptr1, int level);
void mutate_jpeg_comp_master(void* ptr1, int level);
void mutate_jpeg_decompress_struct(void* ptr1, int level);
void mutate_jpeg_color_converter(void* ptr1, int level);
void mutate_jpeg_color_deconverter(void* ptr1, int level);
void mutate_jpeg_entropy_decoder(void* ptr1, int level);
void mutate__IO_marker(void* ptr1, int level);
void mutate_jpeg_common_struct(void* ptr1, int level);
void mutate_jpeg_source_mgr(void* ptr1, int level);
void mutate_jpeg_c_main_controller(void* ptr1, int level);
void mutate_jpeg_marker_struct(void* ptr1, int level);
void mutate_jpeg_input_controller(void* ptr1, int level);
void mutate_cdjpeg_progress_mgr(void* ptr1, int level);
void mutate_jpeg_d_coef_controller(void* ptr1, int level);
void mutate_jpeg_progress_mgr(void* ptr1, int level);
void mutate_jpeg_d_post_controller(void* ptr1, int level);
void mutate_jpeg_upsampler(void* ptr1, int level);
void mutate_jpeg_marker_writer(void* ptr1, int level);
void mutate_jpeg_color_quantizer(void* ptr1, int level);
void mutate_jpeg_c_prep_controller(void* ptr1, int level);
void mutate_jpeg_c_coef_controller(void* ptr1, int level);
void mutate_djpeg_dest_struct(void* ptr1, int level);
void mutate__IO_FILE(void* ptr1, int level);
void mutate_jvirt_barray_control(void* ptr1, int level);
void mutate_jpeg_decomp_master(void* ptr1, int level);
void mutate_jpeg_downsampler(void* ptr1, int level);
void mutate_jpeg_compress_struct(void* ptr1, int level);
#endif
