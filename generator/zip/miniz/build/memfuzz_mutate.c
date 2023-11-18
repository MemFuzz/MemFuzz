#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate__IO_FILE(void* ptr1, int level, int check){return ;}
void mutate__IO_marker(void* ptr1, int level, int check){return ;}
void mutate_timespec(void* ptr1, int level, int check){return ;}
void mutate_stat(void* ptr1, int level, int check){return ;}
void mutate_tm(void* ptr1, int level, int check){return ;}
void mutate_mz_stream_s(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_mz_stream_s  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct mz_stream_s* ptr = ptr1;
    //ptr->next_in = ...(const *next_in)
    mutate_int32_t(&(ptr->avail_in), level+1);
    mutate_int64_t(&(ptr->total_in), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->next_out);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->next_out, level + 1, len); }
    #else
    //ptr->next_out = ...(unsigned char  *next_out)
    #endif
    mutate_int32_t(&(ptr->avail_out), level+1);
    mutate_int64_t(&(ptr->total_out), level+1);
    mutate_c_str(ptr->msg);
    {
        if(ptr->state) { mutate_mz_internal_state(ptr->state, level+1, 1); }
        len = 0;
        arr = pool_get_values("mz_internal_state", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->state;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->state = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->state = ptr_save;
        free(arr);
    }
    //ptr->zalloc = ...(function zalloc)
    //ptr->zfree = ...(function zfree)
        mutate_int32_t(&(ptr->data_type), level+1);
    mutate_int64_t(&(ptr->adler), level+1);
    mutate_int64_t(&(ptr->reserved), level+1);
    pool_insert("mz_stream_s", ptr1);
    #ifdef DEBUG
    printf("leave mutate_mz_stream_s  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_0(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_0* ptr = ptr1;
    //ptr->m_pPut_buf_func = ...(function m_pPut_buf_func)
        mutate_int32_t(&(ptr->m_flags), level+1);
    assign_int32_t_array(&(ptr->m_max_probes), level + 1, 2);
    mutate_int32_t(&(ptr->m_greedy_parsing), level+1);
    mutate_int32_t(&(ptr->m_adler32), level+1);
    mutate_int32_t(&(ptr->m_lookahead_pos), level+1);
    mutate_int32_t(&(ptr->m_lookahead_size), level+1);
    mutate_int32_t(&(ptr->m_dict_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pLZ_code_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_pLZ_code_buf, level + 1, len); }
    #else
    //ptr->m_pLZ_code_buf = ...(unsigned char  *m_pLZ_code_buf)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pLZ_flags);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_pLZ_flags, level + 1, len); }
    #else
    //ptr->m_pLZ_flags = ...(unsigned char  *m_pLZ_flags)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pOutput_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_pOutput_buf, level + 1, len); }
    #else
    //ptr->m_pOutput_buf = ...(unsigned char  *m_pOutput_buf)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pOutput_buf_end);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_pOutput_buf_end, level + 1, len); }
    #else
    //ptr->m_pOutput_buf_end = ...(unsigned char  *m_pOutput_buf_end)
    #endif
    mutate_int32_t(&(ptr->m_num_flags_left), level+1);
    mutate_int32_t(&(ptr->m_total_lz_bytes), level+1);
    mutate_int32_t(&(ptr->m_lz_code_buf_dict_pos), level+1);
    mutate_int32_t(&(ptr->m_bits_in), level+1);
    mutate_int32_t(&(ptr->m_bit_buffer), level+1);
    mutate_int32_t(&(ptr->m_saved_match_dist), level+1);
    mutate_int32_t(&(ptr->m_saved_match_len), level+1);
    mutate_int32_t(&(ptr->m_saved_lit), level+1);
    mutate_int32_t(&(ptr->m_output_flush_ofs), level+1);
    mutate_int32_t(&(ptr->m_output_flush_remaining), level+1);
    mutate_int32_t(&(ptr->m_finished), level+1);
    mutate_int32_t(&(ptr->m_block_index), level+1);
    mutate_int32_t(&(ptr->m_wants_to_finish), level+1);
    mutate_enum(&(ptr->m_prev_return_status), 4);
    //ptr->m_pIn_buf = ...(const *m_pIn_buf)
        #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pIn_buf_size);
    len /= sizeof(int64_t);
    if(len != 0){ mutate_int64_t_array(ptr->m_pIn_buf_size, level + 1, len); }
    #else
    //ptr->m_pIn_buf_size = ...(long unsigned int  *m_pIn_buf_size)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pOut_buf_size);
    len /= sizeof(int64_t);
    if(len != 0){ mutate_int64_t_array(ptr->m_pOut_buf_size, level + 1, len); }
    #else
    //ptr->m_pOut_buf_size = ...(long unsigned int  *m_pOut_buf_size)
    #endif
    mutate_enum(&(ptr->m_flush), 4);
    //ptr->m_pSrc = ...(const *m_pSrc)
    mutate_int64_t(&(ptr->m_src_buf_left), level+1);
    mutate_int64_t(&(ptr->m_out_buf_ofs), level+1);
    assign_int8_t_array(&(ptr->m_dict), level + 1, 33025);
    assign_int16_t_array(&(ptr->m_huff_count), level + 1, 864);
    assign_int16_t_array(&(ptr->m_huff_codes), level + 1, 864);
    assign_int8_t_array(&(ptr->m_huff_code_sizes), level + 1, 864);
    assign_int8_t_array(&(ptr->m_lz_code_buf), level + 1, 65536);
    assign_int16_t_array(&(ptr->m_next), level + 1, 32768);
    assign_int16_t_array(&(ptr->m_hash), level + 1, 32768);
    assign_int8_t_array(&(ptr->m_output_buf), level + 1, 85196);
    pool_insert("memfuzz_anonymous_struct_0", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
    #endif
}
void mutate_tinfl_decompressor_tag(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_tinfl_decompressor_tag  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct tinfl_decompressor_tag* ptr = ptr1;
    mutate_int32_t(&(ptr->m_state), level+1);
    mutate_int32_t(&(ptr->m_num_bits), level+1);
    mutate_int32_t(&(ptr->m_zhdr0), level+1);
    mutate_int32_t(&(ptr->m_zhdr1), level+1);
    mutate_int32_t(&(ptr->m_z_adler32), level+1);
    mutate_int32_t(&(ptr->m_final), level+1);
    mutate_int32_t(&(ptr->m_type), level+1);
    mutate_int32_t(&(ptr->m_check_adler32), level+1);
    mutate_int32_t(&(ptr->m_dist), level+1);
    mutate_int32_t(&(ptr->m_counter), level+1);
    mutate_int32_t(&(ptr->m_num_extra), level+1);
    assign_int32_t_array(&(ptr->m_table_sizes), level + 1, 3);
    mutate_int64_t(&(ptr->m_bit_buf), level+1);
    mutate_int64_t(&(ptr->m_dist_from_out_buf_start), level+1);
    //ptr->m_tables = ...(struct anonymous {unsigned char  m_code_size[288]; short int  m_look_up[1024]; short int  m_tree[576]; } m_tables[3])
    assign_int8_t_array(&(ptr->m_raw_header), level + 1, 4);
    assign_int8_t_array(&(ptr->m_len_codes), level + 1, 457);
    pool_insert("tinfl_decompressor_tag", ptr1);
    #ifdef DEBUG
    printf("leave mutate_tinfl_decompressor_tag  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_1* ptr = ptr1;
    assign_int8_t_array(&(ptr->m_code_size), level + 1, 288);
    assign_int16_t_array(&(ptr->m_look_up), level + 1, 1024);
    assign_int16_t_array(&(ptr->m_tree), level + 1, 576);
    pool_insert("memfuzz_anonymous_struct_1", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_2(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_2* ptr = ptr1;
    mutate_int32_t(&(ptr->m_file_index), level+1);
    mutate_int64_t(&(ptr->m_central_dir_ofs), level+1);
    mutate_int16_t(&(ptr->m_version_made_by), level+1);
    mutate_int16_t(&(ptr->m_version_needed), level+1);
    mutate_int16_t(&(ptr->m_bit_flag), level+1);
    mutate_int16_t(&(ptr->m_method), level+1);
    mutate_int64_t(&(ptr->m_time), level+1);
    mutate_int32_t(&(ptr->m_crc32), level+1);
    mutate_int64_t(&(ptr->m_comp_size), level+1);
    mutate_int64_t(&(ptr->m_uncomp_size), level+1);
    mutate_int16_t(&(ptr->m_internal_attr), level+1);
    mutate_int32_t(&(ptr->m_external_attr), level+1);
    mutate_int64_t(&(ptr->m_local_header_ofs), level+1);
    mutate_int32_t(&(ptr->m_comment_size), level+1);
    mutate_int32_t(&(ptr->m_is_directory), level+1);
    mutate_int32_t(&(ptr->m_is_encrypted), level+1);
    mutate_int32_t(&(ptr->m_is_supported), level+1);
    assign_int8_t_array(&(ptr->m_filename), level + 1, 512);
    assign_int8_t_array(&(ptr->m_comment), level + 1, 512);
    pool_insert("memfuzz_anonymous_struct_2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
}
void mutate_mz_zip_internal_state_tag(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_mz_zip_internal_state_tag  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct mz_zip_internal_state_tag* ptr = ptr1;
    //ptr->m_central_dir = ...(struct anonymous {void  *m_p; long unsigned int  m_size; long unsigned int  m_capacity; unsigned int  m_element_size; } m_central_dir)
    //ptr->m_central_dir_offsets = ...(struct anonymous {void  *m_p; long unsigned int  m_size; long unsigned int  m_capacity; unsigned int  m_element_size; } m_central_dir_offsets)
    //ptr->m_sorted_central_dir_offsets = ...(struct anonymous {void  *m_p; long unsigned int  m_size; long unsigned int  m_capacity; unsigned int  m_element_size; } m_sorted_central_dir_offsets)
    mutate_int32_t(&(ptr->m_init_flags), level+1);
    mutate_int32_t(&(ptr->m_zip64), level+1);
    mutate_int32_t(&(ptr->m_zip64_has_extended_info_fields), level+1);
    {
        if(ptr->m_pFile) { mutate__IO_FILE(ptr->m_pFile, level+1, 1); }
        len = 0;
        arr = pool_get_values("_IO_FILE", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_pFile;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_pFile = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_pFile = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->m_file_archive_start_ofs), level+1);
        mutate_int64_t(&(ptr->m_mem_size), level+1);
    mutate_int64_t(&(ptr->m_mem_capacity), level+1);
    pool_insert("mz_zip_internal_state_tag", ptr1);
    #ifdef DEBUG
    printf("leave mutate_mz_zip_internal_state_tag  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_3  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_3* ptr = ptr1;
    mutate_int64_t(&(ptr->m_archive_size), level+1);
    mutate_int64_t(&(ptr->m_central_directory_file_ofs), level+1);
    mutate_int32_t(&(ptr->m_total_files), level+1);
    mutate_enum(&(ptr->m_zip_mode), 4);
    mutate_enum(&(ptr->m_zip_type), 7);
    mutate_enum(&(ptr->m_last_error), 33);
    mutate_int64_t(&(ptr->m_file_offset_alignment), level+1);
    //ptr->m_pAlloc = ...(function m_pAlloc)
    //ptr->m_pFree = ...(function m_pFree)
    //ptr->m_pRealloc = ...(function m_pRealloc)
        //ptr->m_pRead = ...(function m_pRead)
    //ptr->m_pWrite = ...(function m_pWrite)
    //ptr->m_pNeeds_keepalive = ...(function m_pNeeds_keepalive)
        {
        if(ptr->m_pState) { mutate_mz_zip_internal_state_tag(ptr->m_pState, level+1, 1); }
        len = 0;
        arr = pool_get_values("mz_zip_internal_state_tag", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_pState;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_pState = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_pState = ptr_save;
        free(arr);
    }
    pool_insert("memfuzz_anonymous_struct_3", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_3  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_4* ptr = ptr1;
    //ptr->pZip = ...(struct anonymous *{long unsigned int  m_archive_size; long unsigned int  m_central_directory_file_ofs; unsigned int  m_total_files; enum m_zip_mode; enum m_zip_type; enum m_last_error; long unsigned int  m_file_offset_alignment; function m_pAlloc; function m_pFree; function m_pRealloc; void  *m_pAlloc_opaque; function m_pRead; function m_pWrite; function m_pNeeds_keepalive; void  *m_pIO_opaque; struct mz_zip_internal_state_tag *m_pState; } pZip)
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->status), level+1);
    mutate_int32_t(&(ptr->file_crc32), level+1);
    mutate_int64_t(&(ptr->read_buf_size), level+1);
    mutate_int64_t(&(ptr->read_buf_ofs), level+1);
    mutate_int64_t(&(ptr->read_buf_avail), level+1);
    mutate_int64_t(&(ptr->comp_remaining), level+1);
    mutate_int64_t(&(ptr->out_buf_ofs), level+1);
    mutate_int64_t(&(ptr->cur_file_ofs), level+1);
    //ptr->file_stat = ...(struct anonymous {unsigned int  m_file_index; long unsigned int  m_central_dir_ofs; short unsigned int  m_version_made_by; short unsigned int  m_version_needed; short unsigned int  m_bit_flag; short unsigned int  m_method; long int  m_time; unsigned int  m_crc32; long unsigned int  m_comp_size; long unsigned int  m_uncomp_size; short unsigned int  m_internal_attr; unsigned int  m_external_attr; long unsigned int  m_local_header_ofs; unsigned int  m_comment_size; int  m_is_directory; int  m_is_encrypted; int  m_is_supported; char  m_filename[512]; char  m_comment[512]; } file_stat)
            mutate_int64_t(&(ptr->out_blk_remain), level+1);
    mutate_tinfl_decompressor_tag(&(ptr->inflator), level+1, 0);
    pool_insert("memfuzz_anonymous_struct_4", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_5  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_5* ptr = ptr1;
    mutate_tinfl_decompressor_tag(&(ptr->m_decomp), level+1, 0);
    mutate_int32_t(&(ptr->m_dict_ofs), level+1);
    mutate_int32_t(&(ptr->m_dict_avail), level+1);
    mutate_int32_t(&(ptr->m_first_call), level+1);
    mutate_int32_t(&(ptr->m_has_flushed), level+1);
    mutate_int32_t(&(ptr->m_window_bits), level+1);
    assign_int8_t_array(&(ptr->m_dict), level + 1, 32768);
    mutate_enum(&(ptr->m_last_status), 7);
    pool_insert("memfuzz_anonymous_struct_5", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_5  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_6  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_6* ptr = ptr1;
    mutate_int16_t(&(ptr->m_key), level+1);
    mutate_int16_t(&(ptr->m_sym_index), level+1);
    pool_insert("memfuzz_anonymous_struct_6", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_6  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_7  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_7* ptr = ptr1;
    mutate_int64_t(&(ptr->m_size), level+1);
    mutate_int64_t(&(ptr->m_capacity), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_pBuf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_pBuf, level + 1, len); }
    #else
    //ptr->m_pBuf = ...(unsigned char  *m_pBuf)
    #endif
    mutate_int32_t(&(ptr->m_expandable), level+1);
    pool_insert("memfuzz_anonymous_struct_7", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_7  \n"); fflush(stdout);
    #endif
}
void mutate_utimbuf(void* ptr1, int level, int check){return ;}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_8  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_8* ptr = ptr1;
        mutate_int64_t(&(ptr->m_size), level+1);
    mutate_int64_t(&(ptr->m_capacity), level+1);
    mutate_int32_t(&(ptr->m_element_size), level+1);
    pool_insert("memfuzz_anonymous_struct_8", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_8  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_9  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_9* ptr = ptr1;
    //ptr->m_pZip = ...(struct anonymous *{long unsigned int  m_archive_size; long unsigned int  m_central_directory_file_ofs; unsigned int  m_total_files; enum m_zip_mode; enum m_zip_type; enum m_last_error; long unsigned int  m_file_offset_alignment; function m_pAlloc; function m_pFree; function m_pRealloc; void  *m_pAlloc_opaque; function m_pRead; function m_pWrite; function m_pNeeds_keepalive; void  *m_pIO_opaque; struct mz_zip_internal_state_tag *m_pState; } m_pZip)
    mutate_int64_t(&(ptr->m_cur_archive_file_ofs), level+1);
    mutate_int64_t(&(ptr->m_comp_size), level+1);
    pool_insert("memfuzz_anonymous_struct_9", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_9  \n"); fflush(stdout);
    #endif
}
void mutate_zip_entry_t(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_entry_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_entry_t* ptr = ptr1;
    mutate_int64_t(&(ptr->index), level+1);
    mutate_c_str(ptr->name);
    mutate_int64_t(&(ptr->uncomp_size), level+1);
    mutate_int64_t(&(ptr->comp_size), level+1);
    mutate_int32_t(&(ptr->uncomp_crc32), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    assign_int8_t_array(&(ptr->header), level + 1, 30);
    mutate_int64_t(&(ptr->header_offset), level+1);
    mutate_int16_t(&(ptr->method), level+1);
    //ptr->state = ...(struct anonymous {struct anonymous *{long unsigned int  m_archive_size; long unsigned int  m_central_directory_file_ofs; unsigned int  m_total_files; enum m_zip_mode; enum m_zip_type; enum m_last_error; long unsigned int  m_file_offset_alignment; function m_pAlloc; function m_pFree; function m_pRealloc; void  *m_pAlloc_opaque; function m_pRead; function m_pWrite; function m_pNeeds_keepalive; void  *m_pIO_opaque; struct mz_zip_internal_state_tag *m_pState; } m_pZip; long unsigned int  m_cur_archive_file_ofs; long unsigned int  m_comp_size; } state)
    //ptr->comp = ...(struct anonymous {function m_pPut_buf_func; void  *m_pPut_buf_user; unsigned int  m_flags; unsigned int  m_max_probes[2]; int  m_greedy_parsing; unsigned int  m_adler32; unsigned int  m_lookahead_pos; unsigned int  m_lookahead_size; unsigned int  m_dict_size; unsigned char  *m_pLZ_code_buf; unsigned char  *m_pLZ_flags; unsigned char  *m_pOutput_buf; unsigned char  *m_pOutput_buf_end; unsigned int  m_num_flags_left; unsigned int  m_total_lz_bytes; unsigned int  m_lz_code_buf_dict_pos; unsigned int  m_bits_in; unsigned int  m_bit_buffer; unsigned int  m_saved_match_dist; unsigned int  m_saved_match_len; unsigned int  m_saved_lit; unsigned int  m_output_flush_ofs; unsigned int  m_output_flush_remaining; unsigned int  m_finished; unsigned int  m_block_index; unsigned int  m_wants_to_finish; enum m_prev_return_status; const *m_pIn_buf; void  *m_pOut_buf; long unsigned int  *m_pIn_buf_size; long unsigned int  *m_pOut_buf_size; enum m_flush; const *m_pSrc; long unsigned int  m_src_buf_left; long unsigned int  m_out_buf_ofs; unsigned char  m_dict[33025]; short unsigned int  m_huff_count[3][288]; short unsigned int  m_huff_codes[3][288]; unsigned char  m_huff_code_sizes[3][288]; unsigned char  m_lz_code_buf[65536]; short unsigned int  m_next[32768]; short unsigned int  m_hash[32768]; unsigned char  m_output_buf[85196]; } comp)
    mutate_memfuzz_anonymous_struct_0(&(ptr->comp), level + 1, 0);
    mutate_int32_t(&(ptr->external_attr), level+1);
    mutate_int64_t(&(ptr->m_time), level+1);
    pool_insert("zip_entry_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_entry_t  \n"); fflush(stdout);
    #endif
}
void mutate_zip_t(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_t* ptr = ptr1;
    //ptr->archive = ...(struct anonymous {long unsigned int  m_archive_size; long unsigned int  m_central_directory_file_ofs; unsigned int  m_total_files; enum m_zip_mode; enum m_zip_type; enum m_last_error; long unsigned int  m_file_offset_alignment; function m_pAlloc; function m_pFree; function m_pRealloc; void  *m_pAlloc_opaque; function m_pRead; function m_pWrite; function m_pNeeds_keepalive; void  *m_pIO_opaque; struct mz_zip_internal_state_tag *m_pState; } archive)
    mutate_int32_t(&(ptr->level), level+1);
    mutate_zip_entry_t(&(ptr->entry), level+1, 0);
    pool_insert("zip_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_t  \n"); fflush(stdout);
    #endif
}
void mutate_zip_entry_mark_t(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_entry_mark_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_entry_mark_t* ptr = ptr1;
    mutate_int64_t(&(ptr->file_index), level+1);
    mutate_enum(&(ptr->type), 3);
    mutate_int64_t(&(ptr->m_local_header_ofs), level+1);
    mutate_int64_t(&(ptr->lf_length), level+1);
    pool_insert("zip_entry_mark_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_entry_mark_t  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level, int check){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || (check && alloc_find(ptr1) == 0)) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_10  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_10* ptr = ptr1;
    mutate_int32_t(&(ptr->m_err), level+1);
    //ptr->m_pDesc = ...(const *m_pDesc)
    pool_insert("memfuzz_anonymous_struct_10", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_10  \n"); fflush(stdout);
    #endif
}
void mutate_mz_internal_state(void* ptr1, int level, int check){return ;}
