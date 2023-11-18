#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate_dircnt(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_dircnt  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct dircnt* ptr = ptr1;
    mutate_c_str(ptr->filename_buf);
    //ptr->filename = ...(char  **filename)
    pool_insert("dircnt", ptr1);
    #ifdef DEBUG
    printf("leave mutate_dircnt  \n"); fflush(stdout);
    #endif
}
void mutate_opj_prec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_prec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_prec* ptr = ptr1;
    mutate_int32_t(&(ptr->prec), level+1);
    mutate_enum(&(ptr->mode), 2);
    pool_insert("opj_prec", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_prec  \n"); fflush(stdout);
    #endif
}
void mutate_opj_image_comptparm(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_image_comptparm  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_image_comptparm* ptr = ptr1;
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    mutate_int32_t(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->prec), level+1);
    mutate_int32_t(&(ptr->bpp), level+1);
    mutate_int32_t(&(ptr->sgnd), level+1);
    pool_insert("opj_image_comptparm", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_image_comptparm  \n"); fflush(stdout);
    #endif
}
void mutate_opj_image(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_image  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_image* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    mutate_enum(&(ptr->color_space), 7);
    {
        if(ptr->comps) { mutate_opj_image_comp(ptr->comps, level+1); }
        len = 0;
        arr = pool_get_values("opj_image_comp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comps = ptr_save;
        free(arr);
    }
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->icc_profile_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->icc_profile_buf, level + 1, len); }
    #else
    //ptr->icc_profile_buf = ...(unsigned char  *icc_profile_buf)
    #endif
    mutate_int32_t(&(ptr->icc_profile_len), level+1);
    pool_insert("opj_image", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_image  \n"); fflush(stdout);
    #endif
}
void mutate_opj_image_comp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_image_comp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_image_comp* ptr = ptr1;
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    mutate_int32_t(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->prec), level+1);
    mutate_int32_t(&(ptr->bpp), level+1);
    mutate_int32_t(&(ptr->sgnd), level+1);
    mutate_int32_t(&(ptr->resno_decoded), level+1);
    mutate_int32_t(&(ptr->factor), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(int  *data)
    #endif
    mutate_int16_t(&(ptr->alpha), level+1);
    pool_insert("opj_image_comp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_image_comp  \n"); fflush(stdout);
    #endif
}
void mutate_dirent(void* ptr1, int level){return ;}
void mutate_img_folder(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_img_folder  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct img_folder* ptr = ptr1;
    mutate_c_str(ptr->imgdirpath);
    //ptr->out_format = ...(const *out_format)
    mutate_int8_t(&(ptr->set_imgdir), level+1);
    mutate_int8_t(&(ptr->set_out_format), level+1);
    pool_insert("img_folder", ptr1);
    #ifdef DEBUG
    printf("leave mutate_img_folder  \n"); fflush(stdout);
    #endif
}
void mutate_opj_decompress_params(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_decompress_params  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_decompress_params* ptr = ptr1;
    mutate_opj_dparameters(&(ptr->core), level+1);
    assign_int8_t_array(&(ptr->infile), level + 1, 4096);
    assign_int8_t_array(&(ptr->outfile), level + 1, 4096);
    mutate_int32_t(&(ptr->decod_format), level+1);
    mutate_int32_t(&(ptr->cod_format), level+1);
    assign_int8_t_array(&(ptr->indexfilename), level + 1, 4096);
    mutate_int32_t(&(ptr->DA_x0), level+1);
    mutate_int32_t(&(ptr->DA_x1), level+1);
    mutate_int32_t(&(ptr->DA_y0), level+1);
    mutate_int32_t(&(ptr->DA_y1), level+1);
    mutate_int32_t(&(ptr->m_verbose), level+1);
    mutate_int32_t(&(ptr->tile_index), level+1);
    mutate_int32_t(&(ptr->nb_tile_to_decode), level+1);
    {
        if(ptr->precision) { mutate_opj_prec(ptr->precision, level+1); }
        len = 0;
        arr = pool_get_values("opj_prec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->precision;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->precision = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->precision = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->nb_precision), level+1);
    mutate_int32_t(&(ptr->force_rgb), level+1);
    mutate_int32_t(&(ptr->upsample), level+1);
    mutate_int32_t(&(ptr->split_pnm), level+1);
    mutate_int32_t(&(ptr->num_threads), level+1);
    mutate_int32_t(&(ptr->quiet), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->comps_indices);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->comps_indices, level + 1, len); }
    #else
    //ptr->comps_indices = ...(unsigned int  *comps_indices)
    #endif
    pool_insert("opj_decompress_params", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_decompress_params  \n"); fflush(stdout);
    #endif
}
void mutate_opj_dparameters(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_dparameters  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_dparameters* ptr = ptr1;
    mutate_int32_t(&(ptr->cp_reduce), level+1);
    mutate_int32_t(&(ptr->cp_layer), level+1);
    assign_int8_t_array(&(ptr->infile), level + 1, 4096);
    assign_int8_t_array(&(ptr->outfile), level + 1, 4096);
    mutate_int32_t(&(ptr->decod_format), level+1);
    mutate_int32_t(&(ptr->cod_format), level+1);
    mutate_int32_t(&(ptr->DA_x0), level+1);
    mutate_int32_t(&(ptr->DA_x1), level+1);
    mutate_int32_t(&(ptr->DA_y0), level+1);
    mutate_int32_t(&(ptr->DA_y1), level+1);
    mutate_int32_t(&(ptr->m_verbose), level+1);
    mutate_int32_t(&(ptr->tile_index), level+1);
    mutate_int32_t(&(ptr->nb_tile_to_decode), level+1);
    mutate_int32_t(&(ptr->jpwl_correct), level+1);
    mutate_int32_t(&(ptr->jpwl_exp_comps), level+1);
    mutate_int32_t(&(ptr->jpwl_max_tiles), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    pool_insert("opj_dparameters", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_dparameters  \n"); fflush(stdout);
    #endif
}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_opj_option(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_option  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_option* ptr = ptr1;
    //ptr->name = ...(const *name)
    mutate_int32_t(&(ptr->has_arg), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->flag);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->flag, level + 1, len); }
    #else
    //ptr->flag = ...(int  *flag)
    #endif
    mutate_int32_t(&(ptr->val), level+1);
    pool_insert("opj_option", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_option  \n"); fflush(stdout);
    #endif
}
void mutate_timespec(void* ptr1, int level){return ;}
void mutate_opj_codestream_index(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_codestream_index  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_codestream_index* ptr = ptr1;
    mutate_int64_t(&(ptr->main_head_start), level+1);
    mutate_int64_t(&(ptr->main_head_end), level+1);
    mutate_int64_t(&(ptr->codestream_size), level+1);
    mutate_int32_t(&(ptr->marknum), level+1);
    {
        if(ptr->marker) { mutate_opj_marker_info(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("opj_marker_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->maxmarknum), level+1);
    mutate_int32_t(&(ptr->nb_of_tiles), level+1);
    {
        if(ptr->tile_index) { mutate_opj_tile_index(ptr->tile_index, level+1); }
        len = 0;
        arr = pool_get_values("opj_tile_index", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tile_index;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tile_index = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tile_index = ptr_save;
        free(arr);
    }
    pool_insert("opj_codestream_index", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_codestream_index  \n"); fflush(stdout);
    #endif
}
void mutate_opj_marker_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_marker_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_marker_info* ptr = ptr1;
    mutate_int16_t(&(ptr->type), level+1);
    mutate_int64_t(&(ptr->pos), level+1);
    mutate_int32_t(&(ptr->len), level+1);
    pool_insert("opj_marker_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_marker_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tile_index(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tile_index  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tile_index* ptr = ptr1;
    mutate_int32_t(&(ptr->tileno), level+1);
    mutate_int32_t(&(ptr->nb_tps), level+1);
    mutate_int32_t(&(ptr->current_nb_tps), level+1);
    mutate_int32_t(&(ptr->current_tpsno), level+1);
    {
        if(ptr->tp_index) { mutate_opj_tp_index(ptr->tp_index, level+1); }
        len = 0;
        arr = pool_get_values("opj_tp_index", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tp_index;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tp_index = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tp_index = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->marknum), level+1);
    {
        if(ptr->marker) { mutate_opj_marker_info(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("opj_marker_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->maxmarknum), level+1);
    mutate_int32_t(&(ptr->nb_packet), level+1);
    {
        if(ptr->packet_index) { mutate_opj_packet_info(ptr->packet_index, level+1); }
        len = 0;
        arr = pool_get_values("opj_packet_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->packet_index;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->packet_index = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->packet_index = ptr_save;
        free(arr);
    }
    pool_insert("opj_tile_index", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tile_index  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tp_index(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tp_index  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tp_index* ptr = ptr1;
    mutate_int64_t(&(ptr->start_pos), level+1);
    mutate_int64_t(&(ptr->end_header), level+1);
    mutate_int64_t(&(ptr->end_pos), level+1);
    pool_insert("opj_tp_index", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tp_index  \n"); fflush(stdout);
    #endif
}
void mutate_opj_packet_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_packet_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_packet_info* ptr = ptr1;
    mutate_int64_t(&(ptr->start_pos), level+1);
    mutate_int64_t(&(ptr->end_ph_pos), level+1);
    mutate_int64_t(&(ptr->end_pos), level+1);
    mutate_double(&(ptr->disto), level+1);
    pool_insert("opj_packet_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_packet_info  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_0* ptr = ptr1;
    mutate_int16_t(&(ptr->val), level+1);
    assign_int8_t_array(&(ptr->vals), level + 1, 2);
    pool_insert("memfuzz_anonymous_struct_0", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_0  \n"); fflush(stdout);
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
    mutate_int16_t(&(ptr->val), level+1);
    assign_int8_t_array(&(ptr->vals), level + 1, 2);
    pool_insert("memfuzz_anonymous_struct_1", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
}
void mutate_opj_cparameters(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_cparameters  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_cparameters* ptr = ptr1;
    mutate_int32_t(&(ptr->tile_size_on), level+1);
    mutate_int32_t(&(ptr->cp_tx0), level+1);
    mutate_int32_t(&(ptr->cp_ty0), level+1);
    mutate_int32_t(&(ptr->cp_tdx), level+1);
    mutate_int32_t(&(ptr->cp_tdy), level+1);
    mutate_int32_t(&(ptr->cp_disto_alloc), level+1);
    mutate_int32_t(&(ptr->cp_fixed_alloc), level+1);
    mutate_int32_t(&(ptr->cp_fixed_quality), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->cp_matrice);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->cp_matrice, level + 1, len); }
    #else
    //ptr->cp_matrice = ...(int  *cp_matrice)
    #endif
    mutate_c_str(ptr->cp_comment);
    mutate_int32_t(&(ptr->csty), level+1);
    mutate_enum(&(ptr->prog_order), 6);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_opj_poc(&(ptr->POC)[random()%32], level+1);
    }
    mutate_int32_t(&(ptr->numpocs), level+1);
    mutate_int32_t(&(ptr->tcp_numlayers), level+1);
    assign_float_array(&(ptr->tcp_rates), level + 1, 100);
    assign_float_array(&(ptr->tcp_distoratio), level + 1, 100);
    mutate_int32_t(&(ptr->numresolution), level+1);
    mutate_int32_t(&(ptr->cblockw_init), level+1);
    mutate_int32_t(&(ptr->cblockh_init), level+1);
    mutate_int32_t(&(ptr->mode), level+1);
    mutate_int32_t(&(ptr->irreversible), level+1);
    mutate_int32_t(&(ptr->roi_compno), level+1);
    mutate_int32_t(&(ptr->roi_shift), level+1);
    mutate_int32_t(&(ptr->res_spec), level+1);
    assign_int32_t_array(&(ptr->prcw_init), level + 1, 33);
    assign_int32_t_array(&(ptr->prch_init), level + 1, 33);
    assign_int8_t_array(&(ptr->infile), level + 1, 4096);
    assign_int8_t_array(&(ptr->outfile), level + 1, 4096);
    mutate_int32_t(&(ptr->index_on), level+1);
    assign_int8_t_array(&(ptr->index), level + 1, 4096);
    mutate_int32_t(&(ptr->image_offset_x0), level+1);
    mutate_int32_t(&(ptr->image_offset_y0), level+1);
    mutate_int32_t(&(ptr->subsampling_dx), level+1);
    mutate_int32_t(&(ptr->subsampling_dy), level+1);
    mutate_int32_t(&(ptr->decod_format), level+1);
    mutate_int32_t(&(ptr->cod_format), level+1);
    mutate_int32_t(&(ptr->jpwl_epc_on), level+1);
    mutate_int32_t(&(ptr->jpwl_hprot_MH), level+1);
    assign_int32_t_array(&(ptr->jpwl_hprot_TPH_tileno), level + 1, 16);
    assign_int32_t_array(&(ptr->jpwl_hprot_TPH), level + 1, 16);
    assign_int32_t_array(&(ptr->jpwl_pprot_tileno), level + 1, 16);
    assign_int32_t_array(&(ptr->jpwl_pprot_packno), level + 1, 16);
    assign_int32_t_array(&(ptr->jpwl_pprot), level + 1, 16);
    mutate_int32_t(&(ptr->jpwl_sens_size), level+1);
    mutate_int32_t(&(ptr->jpwl_sens_addr), level+1);
    mutate_int32_t(&(ptr->jpwl_sens_range), level+1);
    mutate_int32_t(&(ptr->jpwl_sens_MH), level+1);
    assign_int32_t_array(&(ptr->jpwl_sens_TPH_tileno), level + 1, 16);
    assign_int32_t_array(&(ptr->jpwl_sens_TPH), level + 1, 16);
    mutate_enum(&(ptr->cp_cinema), 4);
    mutate_int32_t(&(ptr->max_comp_size), level+1);
    mutate_enum(&(ptr->cp_rsiz), 4);
    mutate_int8_t(&(ptr->tp_on), level+1);
    mutate_int8_t(&(ptr->tp_flag), level+1);
    mutate_int8_t(&(ptr->tcp_mct), level+1);
    mutate_int32_t(&(ptr->jpip_on), level+1);
        mutate_int32_t(&(ptr->max_cs_size), level+1);
    mutate_int16_t(&(ptr->rsiz), level+1);
    pool_insert("opj_cparameters", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_cparameters  \n"); fflush(stdout);
    #endif
}
void mutate_opj_poc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_poc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_poc* ptr = ptr1;
    mutate_int32_t(&(ptr->resno0), level+1);
    mutate_int32_t(&(ptr->compno0), level+1);
    mutate_int32_t(&(ptr->layno1), level+1);
    mutate_int32_t(&(ptr->resno1), level+1);
    mutate_int32_t(&(ptr->compno1), level+1);
    mutate_int32_t(&(ptr->layno0), level+1);
    mutate_int32_t(&(ptr->precno0), level+1);
    mutate_int32_t(&(ptr->precno1), level+1);
    mutate_enum(&(ptr->prg1), 6);
    mutate_enum(&(ptr->prg), 6);
    assign_int8_t_array(&(ptr->progorder), level + 1, 5);
    mutate_int32_t(&(ptr->tile), level+1);
    mutate_int32_t(&(ptr->tx0), level+1);
    mutate_int32_t(&(ptr->tx1), level+1);
    mutate_int32_t(&(ptr->ty0), level+1);
    mutate_int32_t(&(ptr->ty1), level+1);
    mutate_int32_t(&(ptr->layS), level+1);
    mutate_int32_t(&(ptr->resS), level+1);
    mutate_int32_t(&(ptr->compS), level+1);
    mutate_int32_t(&(ptr->prcS), level+1);
    mutate_int32_t(&(ptr->layE), level+1);
    mutate_int32_t(&(ptr->resE), level+1);
    mutate_int32_t(&(ptr->compE), level+1);
    mutate_int32_t(&(ptr->prcE), level+1);
    mutate_int32_t(&(ptr->txS), level+1);
    mutate_int32_t(&(ptr->txE), level+1);
    mutate_int32_t(&(ptr->tyS), level+1);
    mutate_int32_t(&(ptr->tyE), level+1);
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    mutate_int32_t(&(ptr->lay_t), level+1);
    mutate_int32_t(&(ptr->res_t), level+1);
    mutate_int32_t(&(ptr->comp_t), level+1);
    mutate_int32_t(&(ptr->prc_t), level+1);
    mutate_int32_t(&(ptr->tx0_t), level+1);
    mutate_int32_t(&(ptr->ty0_t), level+1);
    pool_insert("opj_poc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_poc  \n"); fflush(stdout);
    #endif
}
void mutate_pnm_header(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_pnm_header  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct pnm_header* ptr = ptr1;
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->maxval), level+1);
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->format), level+1);
    mutate_int8_t(&(ptr->rgb), level+1);
    mutate_int8_t(&(ptr->rgba), level+1);
    mutate_int8_t(&(ptr->gray), level+1);
    mutate_int8_t(&(ptr->graya), level+1);
    mutate_int8_t(&(ptr->bw), level+1);
    mutate_int8_t(&(ptr->ok), level+1);
    pool_insert("pnm_header", ptr1);
    #ifdef DEBUG
    printf("leave mutate_pnm_header  \n"); fflush(stdout);
    #endif
}
void mutate_raw_cparameters(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_raw_cparameters  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct raw_cparameters* ptr = ptr1;
    mutate_int32_t(&(ptr->rawWidth), level+1);
    mutate_int32_t(&(ptr->rawHeight), level+1);
    mutate_int32_t(&(ptr->rawComp), level+1);
    mutate_int32_t(&(ptr->rawBitDepth), level+1);
    mutate_int32_t(&(ptr->rawSigned), level+1);
    {
        if(ptr->rawComps) { mutate_raw_comp_cparameters(ptr->rawComps, level+1); }
        len = 0;
        arr = pool_get_values("raw_comp_cparameters", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->rawComps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->rawComps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->rawComps = ptr_save;
        free(arr);
    }
    pool_insert("raw_cparameters", ptr1);
    #ifdef DEBUG
    printf("leave mutate_raw_cparameters  \n"); fflush(stdout);
    #endif
}
void mutate_raw_comp_cparameters(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_raw_comp_cparameters  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct raw_comp_cparameters* ptr = ptr1;
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    pool_insert("raw_comp_cparameters", ptr1);
    #ifdef DEBUG
    printf("leave mutate_raw_comp_cparameters  \n"); fflush(stdout);
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
    mutate_int16_t(&(ptr->bfType), level+1);
    mutate_int32_t(&(ptr->bfSize), level+1);
    mutate_int16_t(&(ptr->bfReserved1), level+1);
    mutate_int16_t(&(ptr->bfReserved2), level+1);
    mutate_int32_t(&(ptr->bfOffBits), level+1);
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
    mutate_int32_t(&(ptr->biSize), level+1);
    mutate_int32_t(&(ptr->biWidth), level+1);
    mutate_int32_t(&(ptr->biHeight), level+1);
    mutate_int16_t(&(ptr->biPlanes), level+1);
    mutate_int16_t(&(ptr->biBitCount), level+1);
    mutate_int32_t(&(ptr->biCompression), level+1);
    mutate_int32_t(&(ptr->biSizeImage), level+1);
    mutate_int32_t(&(ptr->biXpelsPerMeter), level+1);
    mutate_int32_t(&(ptr->biYpelsPerMeter), level+1);
    mutate_int32_t(&(ptr->biClrUsed), level+1);
    mutate_int32_t(&(ptr->biClrImportant), level+1);
    mutate_int32_t(&(ptr->biRedMask), level+1);
    mutate_int32_t(&(ptr->biGreenMask), level+1);
    mutate_int32_t(&(ptr->biBlueMask), level+1);
    mutate_int32_t(&(ptr->biAlphaMask), level+1);
    mutate_int32_t(&(ptr->biColorSpaceType), level+1);
    assign_int8_t_array(&(ptr->biColorSpaceEP), level + 1, 36);
    mutate_int32_t(&(ptr->biRedGamma), level+1);
    mutate_int32_t(&(ptr->biGreenGamma), level+1);
    mutate_int32_t(&(ptr->biBlueGamma), level+1);
    mutate_int32_t(&(ptr->biIntent), level+1);
    mutate_int32_t(&(ptr->biIccProfileData), level+1);
    mutate_int32_t(&(ptr->biIccProfileSize), level+1);
    mutate_int32_t(&(ptr->biReserved), level+1);
    pool_insert("memfuzz_anonymous_struct_3", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_3  \n"); fflush(stdout);
    #endif
}
void mutate_opj_codestream_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_codestream_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_codestream_info* ptr = ptr1;
    mutate_double(&(ptr->D_max), level+1);
    mutate_int32_t(&(ptr->packno), level+1);
    mutate_int32_t(&(ptr->index_write), level+1);
    mutate_int32_t(&(ptr->image_w), level+1);
    mutate_int32_t(&(ptr->image_h), level+1);
    mutate_enum(&(ptr->prog), 6);
    mutate_int32_t(&(ptr->tile_x), level+1);
    mutate_int32_t(&(ptr->tile_y), level+1);
    mutate_int32_t(&(ptr->tile_Ox), level+1);
    mutate_int32_t(&(ptr->tile_Oy), level+1);
    mutate_int32_t(&(ptr->tw), level+1);
    mutate_int32_t(&(ptr->th), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    mutate_int32_t(&(ptr->numlayers), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->numdecompos);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->numdecompos, level + 1, len); }
    #else
    //ptr->numdecompos = ...(int  *numdecompos)
    #endif
    mutate_int32_t(&(ptr->marknum), level+1);
    {
        if(ptr->marker) { mutate_opj_marker_info(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("opj_marker_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->maxmarknum), level+1);
    mutate_int32_t(&(ptr->main_head_start), level+1);
    mutate_int32_t(&(ptr->main_head_end), level+1);
    mutate_int32_t(&(ptr->codestream_size), level+1);
    {
        if(ptr->tile) { mutate_opj_tile_info(ptr->tile, level+1); }
        len = 0;
        arr = pool_get_values("opj_tile_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tile;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tile = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tile = ptr_save;
        free(arr);
    }
    pool_insert("opj_codestream_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_codestream_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tile_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tile_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tile_info* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->thresh);
    len /= sizeof(double);
    if(len != 0){ mutate_double_array(ptr->thresh, level + 1, len); }
    #else
    //ptr->thresh = ...(double  *thresh)
    #endif
    mutate_int32_t(&(ptr->tileno), level+1);
    mutate_int32_t(&(ptr->start_pos), level+1);
    mutate_int32_t(&(ptr->end_header), level+1);
    mutate_int32_t(&(ptr->end_pos), level+1);
    assign_int32_t_array(&(ptr->pw), level + 1, 33);
    assign_int32_t_array(&(ptr->ph), level + 1, 33);
    assign_int32_t_array(&(ptr->pdx), level + 1, 33);
    assign_int32_t_array(&(ptr->pdy), level + 1, 33);
    {
        if(ptr->packet) { mutate_opj_packet_info(ptr->packet, level+1); }
        len = 0;
        arr = pool_get_values("opj_packet_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->packet;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->packet = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->packet = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->numpix), level+1);
    mutate_double(&(ptr->distotile), level+1);
    mutate_int32_t(&(ptr->marknum), level+1);
    {
        if(ptr->marker) { mutate_opj_marker_info(ptr->marker, level+1); }
        len = 0;
        arr = pool_get_values("opj_marker_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->marker;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->marker = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->marker = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->maxmarknum), level+1);
    mutate_int32_t(&(ptr->num_tps), level+1);
    {
        if(ptr->tp) { mutate_opj_tp_info(ptr->tp, level+1); }
        len = 0;
        arr = pool_get_values("opj_tp_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tp = ptr_save;
        free(arr);
    }
    pool_insert("opj_tile_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tile_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tp_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tp_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tp_info* ptr = ptr1;
    mutate_int32_t(&(ptr->tp_start_pos), level+1);
    mutate_int32_t(&(ptr->tp_end_header), level+1);
    mutate_int32_t(&(ptr->tp_end_pos), level+1);
    mutate_int32_t(&(ptr->tp_start_pack), level+1);
    mutate_int32_t(&(ptr->tp_numpacks), level+1);
    pool_insert("opj_tp_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tp_info  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level){return ;}
void mutate_png_color_8_struct(void* ptr1, int level){return ;}
void mutate_opj_mutex_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_mutex_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_mutex_t* ptr = ptr1;
    //ptr->mutex = ...(union anonymous {struct __pthread_mutex_s __data; char  __size[40]; long int  __align; } mutex)
    pool_insert("opj_mutex_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_mutex_t  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level){return ;}
void mutate___pthread_mutex_s(void* ptr1, int level){return ;}
void mutate___pthread_internal_list(void* ptr1, int level){return ;}
void mutate_opj_cond_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_cond_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_cond_t* ptr = ptr1;
    //ptr->cond = ...(union anonymous {struct __pthread_cond_s __data; char  __size[48]; long long int  __align; } cond)
    pool_insert("opj_cond_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_cond_t  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level){return ;}
void mutate___pthread_cond_s(void* ptr1, int level){return ;}
void mutate_opj_thread_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_thread_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_thread_t* ptr = ptr1;
    //ptr->thread_fn = ...(function thread_fn)
        mutate_int64_t(&(ptr->thread), level+1);
    pool_insert("opj_thread_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_thread_t  \n"); fflush(stdout);
    #endif
}
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
    struct memfuzz_anonymous_struct_11* ptr = ptr1;
    mutate_int32_t(&(ptr->key), level+1);
        //ptr->opj_free_func = ...(function opj_free_func)
    pool_insert("memfuzz_anonymous_struct_11", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_11  \n"); fflush(stdout);
    #endif
}
void mutate_opj_thread_pool_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_thread_pool_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_thread_pool_t* ptr = ptr1;
    //ptr->worker_threads = ...(struct anonymous *{struct opj_thread_pool_t *tp; struct opj_thread_t *thread; int  marked_as_waiting; struct opj_mutex_t *mutex; struct opj_cond_t *cond; } worker_threads)
    mutate_int32_t(&(ptr->worker_threads_count), level+1);
    {
        if(ptr->cond) { mutate_opj_cond_t(ptr->cond, level+1); }
        len = 0;
        arr = pool_get_values("opj_cond_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cond;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cond = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cond = ptr_save;
        free(arr);
    }
    {
        if(ptr->mutex) { mutate_opj_mutex_t(ptr->mutex, level+1); }
        len = 0;
        arr = pool_get_values("opj_mutex_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mutex;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mutex = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mutex = ptr_save;
        free(arr);
    }
    //ptr->state = ...(unknown state)
    {
        if(ptr->job_queue) { mutate_opj_job_list_t(ptr->job_queue, level+1); }
        len = 0;
        arr = pool_get_values("opj_job_list_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->job_queue;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->job_queue = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->job_queue = ptr_save;
        free(arr);
    }
    //ptr->pending_jobs_count = ...(unknown pending_jobs_count)
    {
        if(ptr->waiting_worker_thread_list) { mutate_opj_worker_thread_list_t(ptr->waiting_worker_thread_list, level+1); }
        len = 0;
        arr = pool_get_values("opj_worker_thread_list_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->waiting_worker_thread_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->waiting_worker_thread_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->waiting_worker_thread_list = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->waiting_worker_thread_count), level+1);
    {
        if(ptr->tls) { mutate_opj_tls_t(ptr->tls, level+1); }
        len = 0;
        arr = pool_get_values("opj_tls_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tls;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tls = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tls = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->signaling_threshold), level+1);
    pool_insert("opj_thread_pool_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_thread_pool_t  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_12(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_12  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_12* ptr = ptr1;
    {
        if(ptr->tp) { mutate_opj_thread_pool_t(ptr->tp, level+1); }
        len = 0;
        arr = pool_get_values("opj_thread_pool_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tp = ptr_save;
        free(arr);
    }
    {
        if(ptr->thread) { mutate_opj_thread_t(ptr->thread, level+1); }
        len = 0;
        arr = pool_get_values("opj_thread_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->thread;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->thread = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->thread = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->marked_as_waiting), level+1);
    {
        if(ptr->mutex) { mutate_opj_mutex_t(ptr->mutex, level+1); }
        len = 0;
        arr = pool_get_values("opj_mutex_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mutex;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mutex = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mutex = ptr_save;
        free(arr);
    }
    {
        if(ptr->cond) { mutate_opj_cond_t(ptr->cond, level+1); }
        len = 0;
        arr = pool_get_values("opj_cond_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cond;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cond = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cond = ptr_save;
        free(arr);
    }
    pool_insert("memfuzz_anonymous_struct_12", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_12  \n"); fflush(stdout);
    #endif
}
void mutate_opj_job_list_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_job_list_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_job_list_t* ptr = ptr1;
    //ptr->job = ...(struct anonymous *{function job_fn; void  *user_data; } job)
    {
        if(ptr->next) { mutate_opj_job_list_t(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("opj_job_list_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("opj_job_list_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_job_list_t  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_13(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_13  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_13* ptr = ptr1;
    //ptr->job_fn = ...(function job_fn)
        pool_insert("memfuzz_anonymous_struct_13", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_13  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tls_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tls_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tls_t* ptr = ptr1;
    //ptr->key_val = ...(struct anonymous *{int  key; void  *value; function opj_free_func; } key_val)
    mutate_int32_t(&(ptr->key_val_count), level+1);
    pool_insert("opj_tls_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tls_t  \n"); fflush(stdout);
    #endif
}
void mutate_opj_worker_thread_list_t(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_worker_thread_list_t  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_worker_thread_list_t* ptr = ptr1;
    //ptr->worker_thread = ...(struct anonymous *{struct opj_thread_pool_t *tp; struct opj_thread_t *thread; int  marked_as_waiting; struct opj_mutex_t *mutex; struct opj_cond_t *cond; } worker_thread)
    {
        if(ptr->next) { mutate_opj_worker_thread_list_t(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("opj_worker_thread_list_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    pool_insert("opj_worker_thread_list_t", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_worker_thread_list_t  \n"); fflush(stdout);
    #endif
}
void mutate_pthread_attr_t(void* ptr1, int level){return ;}
void mutate_opj_stream_private(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_stream_private  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_stream_private* ptr = ptr1;
        //ptr->m_free_user_data_fn = ...(function m_free_user_data_fn)
    mutate_int64_t(&(ptr->m_user_data_length), level+1);
    //ptr->m_read_fn = ...(function m_read_fn)
    //ptr->m_write_fn = ...(function m_write_fn)
    //ptr->m_skip_fn = ...(function m_skip_fn)
    //ptr->m_seek_fn = ...(function m_seek_fn)
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_stored_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_stored_data, level + 1, len); }
    #else
    //ptr->m_stored_data = ...(unsigned char  *m_stored_data)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_current_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_current_data, level + 1, len); }
    #else
    //ptr->m_current_data = ...(unsigned char  *m_current_data)
    #endif
    //ptr->m_opj_skip = ...(function m_opj_skip)
    //ptr->m_opj_seek = ...(function m_opj_seek)
    mutate_int64_t(&(ptr->m_bytes_in_buffer), level+1);
    mutate_int64_t(&(ptr->m_byte_offset), level+1);
    mutate_int64_t(&(ptr->m_buffer_size), level+1);
    mutate_int32_t(&(ptr->m_status), level+1);
    pool_insert("opj_stream_private", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_stream_private  \n"); fflush(stdout);
    #endif
}
void mutate_opj_event_mgr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_event_mgr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_event_mgr* ptr = ptr1;
                //ptr->error_handler = ...(function error_handler)
    //ptr->warning_handler = ...(function warning_handler)
    //ptr->info_handler = ...(function info_handler)
    pool_insert("opj_event_mgr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_event_mgr  \n"); fflush(stdout);
    #endif
}
void mutate___va_list_tag(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate___va_list_tag  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct __va_list_tag* ptr = ptr1;
    mutate_int32_t(&(ptr->gp_offset), level+1);
    mutate_int32_t(&(ptr->fp_offset), level+1);
            pool_insert("__va_list_tag", ptr1);
    #ifdef DEBUG
    printf("leave mutate___va_list_tag  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_14(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_14  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_14* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_14", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_14  \n"); fflush(stdout);
    #endif
}
void mutate_opj_cp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_cp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_cp* ptr = ptr1;
    mutate_int16_t(&(ptr->rsiz), level+1);
    mutate_int32_t(&(ptr->tx0), level+1);
    mutate_int32_t(&(ptr->ty0), level+1);
    mutate_int32_t(&(ptr->tdx), level+1);
    mutate_int32_t(&(ptr->tdy), level+1);
    mutate_c_str(ptr->comment);
    mutate_int32_t(&(ptr->tw), level+1);
    mutate_int32_t(&(ptr->th), level+1);
    mutate_int32_t(&(ptr->ppm_markers_count), level+1);
    {
        if(ptr->ppm_markers) { mutate_opj_ppx_struct(ptr->ppm_markers, level+1); }
        len = 0;
        arr = pool_get_values("opj_ppx_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ppm_markers;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ppm_markers = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ppm_markers = ptr_save;
        free(arr);
    }
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppm_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppm_data, level + 1, len); }
    #else
    //ptr->ppm_data = ...(unsigned char  *ppm_data)
    #endif
    mutate_int32_t(&(ptr->ppm_len), level+1);
    mutate_int32_t(&(ptr->ppm_data_read), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppm_data_current);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppm_data_current, level + 1, len); }
    #else
    //ptr->ppm_data_current = ...(unsigned char  *ppm_data_current)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppm_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppm_buffer, level + 1, len); }
    #else
    //ptr->ppm_buffer = ...(unsigned char  *ppm_buffer)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppm_data_first);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppm_data_first, level + 1, len); }
    #else
    //ptr->ppm_data_first = ...(unsigned char  *ppm_data_first)
    #endif
    mutate_int32_t(&(ptr->ppm_data_size), level+1);
    mutate_int32_t(&(ptr->ppm_store), level+1);
    mutate_int32_t(&(ptr->ppm_previous), level+1);
    {
        if(ptr->tcps) { mutate_opj_tcp(ptr->tcps, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tcps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tcps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tcps = ptr_save;
        free(arr);
    }
    //ptr->m_specific_param = ...(union anonymous {struct opj_decoding_param m_dec; struct opj_encoding_param m_enc; } m_specific_param)
    //ptr->ppm = ...(bitfield mutation);
    //ptr->m_is_decoder = ...(bitfield mutation);
    //ptr->allow_different_bit_depth_sign = ...(bitfield mutation);
    pool_insert("opj_cp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_cp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_ppx_struct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_ppx_struct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_ppx_struct* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_data, level + 1, len); }
    #else
    //ptr->m_data = ...(unsigned char  *m_data)
    #endif
    mutate_int32_t(&(ptr->m_data_size), level+1);
    pool_insert("opj_ppx_struct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_ppx_struct  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcp* ptr = ptr1;
    mutate_int32_t(&(ptr->csty), level+1);
    mutate_enum(&(ptr->prg), 6);
    mutate_int32_t(&(ptr->numlayers), level+1);
    mutate_int32_t(&(ptr->num_layers_to_decode), level+1);
    mutate_int32_t(&(ptr->mct), level+1);
    assign_float_array(&(ptr->rates), level + 1, 100);
    mutate_int32_t(&(ptr->numpocs), level+1);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_opj_poc(&(ptr->pocs)[random()%32], level+1);
    }
    mutate_int32_t(&(ptr->ppt_markers_count), level+1);
    {
        if(ptr->ppt_markers) { mutate_opj_ppx_struct(ptr->ppt_markers, level+1); }
        len = 0;
        arr = pool_get_values("opj_ppx_struct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ppt_markers;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ppt_markers = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ppt_markers = ptr_save;
        free(arr);
    }
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppt_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppt_data, level + 1, len); }
    #else
    //ptr->ppt_data = ...(unsigned char  *ppt_data)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->ppt_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->ppt_buffer, level + 1, len); }
    #else
    //ptr->ppt_buffer = ...(unsigned char  *ppt_buffer)
    #endif
    mutate_int32_t(&(ptr->ppt_data_size), level+1);
    mutate_int32_t(&(ptr->ppt_len), level+1);
    assign_float_array(&(ptr->distoratio), level + 1, 100);
    {
        if(ptr->tccps) { mutate_opj_tccp(ptr->tccps, level+1); }
        len = 0;
        arr = pool_get_values("opj_tccp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tccps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tccps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tccps = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->m_current_tile_part_number), level+1);
    mutate_int32_t(&(ptr->m_nb_tile_parts), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_data, level + 1, len); }
    #else
    //ptr->m_data = ...(unsigned char  *m_data)
    #endif
    mutate_int32_t(&(ptr->m_data_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->mct_norms);
    len /= sizeof(double);
    if(len != 0){ mutate_double_array(ptr->mct_norms, level + 1, len); }
    #else
    //ptr->mct_norms = ...(double  *mct_norms)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_mct_decoding_matrix);
    len /= sizeof(float);
    if(len != 0){ mutate_float_array(ptr->m_mct_decoding_matrix, level + 1, len); }
    #else
    //ptr->m_mct_decoding_matrix = ...(float  *m_mct_decoding_matrix)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_mct_coding_matrix);
    len /= sizeof(float);
    if(len != 0){ mutate_float_array(ptr->m_mct_coding_matrix, level + 1, len); }
    #else
    //ptr->m_mct_coding_matrix = ...(float  *m_mct_coding_matrix)
    #endif
    {
        if(ptr->m_mct_records) { mutate_opj_mct_data(ptr->m_mct_records, level+1); }
        len = 0;
        arr = pool_get_values("opj_mct_data", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_mct_records;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_mct_records = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_mct_records = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->m_nb_mct_records), level+1);
    mutate_int32_t(&(ptr->m_nb_max_mct_records), level+1);
    {
        if(ptr->m_mcc_records) { mutate_opj_simple_mcc_decorrelation_data(ptr->m_mcc_records, level+1); }
        len = 0;
        arr = pool_get_values("opj_simple_mcc_decorrelation_data", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_mcc_records;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_mcc_records = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_mcc_records = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->m_nb_mcc_records), level+1);
    mutate_int32_t(&(ptr->m_nb_max_mcc_records), level+1);
    //ptr->cod = ...(bitfield mutation);
    //ptr->ppt = ...(bitfield mutation);
    //ptr->POC = ...(bitfield mutation);
    pool_insert("opj_tcp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tccp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tccp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tccp* ptr = ptr1;
    mutate_int32_t(&(ptr->csty), level+1);
    mutate_int32_t(&(ptr->numresolutions), level+1);
    mutate_int32_t(&(ptr->cblkw), level+1);
    mutate_int32_t(&(ptr->cblkh), level+1);
    mutate_int32_t(&(ptr->cblksty), level+1);
    mutate_int32_t(&(ptr->qmfbid), level+1);
    mutate_int32_t(&(ptr->qntsty), level+1);
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        mutate_opj_stepsize(&(ptr->stepsizes)[random()%97], level+1);
    }
    mutate_int32_t(&(ptr->numgbits), level+1);
    mutate_int32_t(&(ptr->roishift), level+1);
    assign_int32_t_array(&(ptr->prcw), level + 1, 33);
    assign_int32_t_array(&(ptr->prch), level + 1, 33);
    mutate_int32_t(&(ptr->m_dc_level_shift), level+1);
    pool_insert("opj_tccp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tccp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_stepsize(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_stepsize  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_stepsize* ptr = ptr1;
    mutate_int32_t(&(ptr->expn), level+1);
    mutate_int32_t(&(ptr->mant), level+1);
    pool_insert("opj_stepsize", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_stepsize  \n"); fflush(stdout);
    #endif
}
void mutate_opj_mct_data(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_mct_data  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_mct_data* ptr = ptr1;
    mutate_enum(&(ptr->m_element_type), 4);
    mutate_enum(&(ptr->m_array_type), 3);
    mutate_int32_t(&(ptr->m_index), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_data, level + 1, len); }
    #else
    //ptr->m_data = ...(unsigned char  *m_data)
    #endif
    mutate_int32_t(&(ptr->m_data_size), level+1);
    pool_insert("opj_mct_data", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_mct_data  \n"); fflush(stdout);
    #endif
}
void mutate_opj_simple_mcc_decorrelation_data(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_simple_mcc_decorrelation_data  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_simple_mcc_decorrelation_data* ptr = ptr1;
    mutate_int32_t(&(ptr->m_index), level+1);
    mutate_int32_t(&(ptr->m_nb_comps), level+1);
    {
        if(ptr->m_decorrelation_array) { mutate_opj_mct_data(ptr->m_decorrelation_array, level+1); }
        len = 0;
        arr = pool_get_values("opj_mct_data", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_decorrelation_array;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_decorrelation_array = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_decorrelation_array = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_offset_array) { mutate_opj_mct_data(ptr->m_offset_array, level+1); }
        len = 0;
        arr = pool_get_values("opj_mct_data", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_offset_array;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_offset_array = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_offset_array = ptr_save;
        free(arr);
    }
    //ptr->m_is_irreversible = ...(bitfield mutation);
    pool_insert("opj_simple_mcc_decorrelation_data", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_simple_mcc_decorrelation_data  \n"); fflush(stdout);
    #endif
}
void mutate_opj_decoding_param(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_decoding_param  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_decoding_param* ptr = ptr1;
    mutate_int32_t(&(ptr->m_reduce), level+1);
    mutate_int32_t(&(ptr->m_layer), level+1);
    pool_insert("opj_decoding_param", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_decoding_param  \n"); fflush(stdout);
    #endif
}
void mutate_opj_encoding_param(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_encoding_param  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_encoding_param* ptr = ptr1;
    mutate_int32_t(&(ptr->m_max_comp_size), level+1);
    mutate_int32_t(&(ptr->m_tp_pos), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_matrice);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->m_matrice, level + 1, len); }
    #else
    //ptr->m_matrice = ...(int  *m_matrice)
    #endif
    mutate_int8_t(&(ptr->m_tp_flag), level+1);
    //ptr->m_disto_alloc = ...(bitfield mutation);
    //ptr->m_fixed_alloc = ...(bitfield mutation);
    //ptr->m_fixed_quality = ...(bitfield mutation);
    //ptr->m_tp_on = ...(bitfield mutation);
    pool_insert("opj_encoding_param", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_encoding_param  \n"); fflush(stdout);
    #endif
}
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
    mutate_opj_decompression(&(ptr->m_decompression), level+1);
    mutate_opj_compression(&(ptr->m_compression), level+1);
    pool_insert("memfuzz_anonymous_struct_15", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_15  \n"); fflush(stdout);
    #endif
}
void mutate_opj_codec_private(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_codec_private  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_codec_private* ptr = ptr1;
    //ptr->m_codec_data = ...(union anonymous {struct opj_decompression m_decompression; struct opj_compression m_compression; } m_codec_data)
        mutate_opj_event_mgr(&(ptr->m_event_mgr), level+1);
    mutate_int32_t(&(ptr->is_decompressor), level+1);
    //ptr->opj_dump_codec = ...(function opj_dump_codec)
    //ptr->opj_get_codec_info = ...(function opj_get_codec_info)
    //ptr->opj_get_codec_index = ...(function opj_get_codec_index)
    //ptr->opj_set_threads = ...(function opj_set_threads)
    pool_insert("opj_codec_private", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_codec_private  \n"); fflush(stdout);
    #endif
}
void mutate_opj_decompression(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_decompression  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_decompression* ptr = ptr1;
    //ptr->opj_read_header = ...(function opj_read_header)
    //ptr->opj_decode = ...(function opj_decode)
    //ptr->opj_read_tile_header = ...(function opj_read_tile_header)
    //ptr->opj_decode_tile_data = ...(function opj_decode_tile_data)
    //ptr->opj_end_decompress = ...(function opj_end_decompress)
    //ptr->opj_destroy = ...(function opj_destroy)
    //ptr->opj_setup_decoder = ...(function opj_setup_decoder)
    //ptr->opj_set_decode_area = ...(function opj_set_decode_area)
    //ptr->opj_get_decoded_tile = ...(function opj_get_decoded_tile)
    //ptr->opj_set_decoded_resolution_factor = ...(function opj_set_decoded_resolution_factor)
    //ptr->opj_set_decoded_components = ...(function opj_set_decoded_components)
    pool_insert("opj_decompression", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_decompression  \n"); fflush(stdout);
    #endif
}
void mutate_opj_compression(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_compression  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_compression* ptr = ptr1;
    //ptr->opj_start_compress = ...(function opj_start_compress)
    //ptr->opj_encode = ...(function opj_encode)
    //ptr->opj_write_tile = ...(function opj_write_tile)
    //ptr->opj_end_compress = ...(function opj_end_compress)
    //ptr->opj_destroy = ...(function opj_destroy)
    //ptr->opj_setup_encoder = ...(function opj_setup_encoder)
    //ptr->opj_encoder_set_extra_options = ...(function opj_encoder_set_extra_options)
    pool_insert("opj_compression", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_compression  \n"); fflush(stdout);
    #endif
}
void mutate_opj_codestream_info_v2(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_codestream_info_v2  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_codestream_info_v2* ptr = ptr1;
    mutate_int32_t(&(ptr->tx0), level+1);
    mutate_int32_t(&(ptr->ty0), level+1);
    mutate_int32_t(&(ptr->tdx), level+1);
    mutate_int32_t(&(ptr->tdy), level+1);
    mutate_int32_t(&(ptr->tw), level+1);
    mutate_int32_t(&(ptr->th), level+1);
    mutate_int32_t(&(ptr->nbcomps), level+1);
    mutate_opj_tile_v2_info(&(ptr->m_default_tile_info), level+1);
    {
        if(ptr->tile_info) { mutate_opj_tile_v2_info(ptr->tile_info, level+1); }
        len = 0;
        arr = pool_get_values("opj_tile_v2_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tile_info;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tile_info = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tile_info = ptr_save;
        free(arr);
    }
    pool_insert("opj_codestream_info_v2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_codestream_info_v2  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tile_v2_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tile_v2_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tile_v2_info* ptr = ptr1;
    mutate_int32_t(&(ptr->tileno), level+1);
    mutate_int32_t(&(ptr->csty), level+1);
    mutate_enum(&(ptr->prg), 6);
    mutate_int32_t(&(ptr->numlayers), level+1);
    mutate_int32_t(&(ptr->mct), level+1);
    {
        if(ptr->tccp_info) { mutate_opj_tccp_info(ptr->tccp_info, level+1); }
        len = 0;
        arr = pool_get_values("opj_tccp_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tccp_info;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tccp_info = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tccp_info = ptr_save;
        free(arr);
    }
    pool_insert("opj_tile_v2_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tile_v2_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tccp_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tccp_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tccp_info* ptr = ptr1;
    mutate_int32_t(&(ptr->compno), level+1);
    mutate_int32_t(&(ptr->csty), level+1);
    mutate_int32_t(&(ptr->numresolutions), level+1);
    mutate_int32_t(&(ptr->cblkw), level+1);
    mutate_int32_t(&(ptr->cblkh), level+1);
    mutate_int32_t(&(ptr->cblksty), level+1);
    mutate_int32_t(&(ptr->qmfbid), level+1);
    mutate_int32_t(&(ptr->qntsty), level+1);
    assign_int32_t_array(&(ptr->stepsizes_mant), level + 1, 97);
    assign_int32_t_array(&(ptr->stepsizes_expn), level + 1, 97);
    mutate_int32_t(&(ptr->numgbits), level+1);
    mutate_int32_t(&(ptr->roishift), level+1);
    assign_int32_t_array(&(ptr->prcw), level + 1, 33);
    assign_int32_t_array(&(ptr->prch), level + 1, 33);
    pool_insert("opj_tccp_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tccp_info  \n"); fflush(stdout);
    #endif
}
void mutate_j2k_prog_order(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_j2k_prog_order  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct j2k_prog_order* ptr = ptr1;
    mutate_enum(&(ptr->enum_prog), 6);
    assign_int8_t_array(&(ptr->str_prog), level + 1, 5);
    pool_insert("j2k_prog_order", ptr1);
    #ifdef DEBUG
    printf("leave mutate_j2k_prog_order  \n"); fflush(stdout);
    #endif
}
void mutate_opj_dec_memory_marker_handler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_dec_memory_marker_handler  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_dec_memory_marker_handler* ptr = ptr1;
    mutate_int32_t(&(ptr->id), level+1);
    mutate_int32_t(&(ptr->states), level+1);
    //ptr->handler = ...(function handler)
    pool_insert("opj_dec_memory_marker_handler", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_dec_memory_marker_handler  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_16(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_16  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_16* ptr = ptr1;
    mutate_opj_j2k_dec(&(ptr->m_decoder), level+1);
    mutate_opj_j2k_enc(&(ptr->m_encoder), level+1);
    pool_insert("memfuzz_anonymous_struct_16", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_16  \n"); fflush(stdout);
    #endif
}
void mutate_opj_j2k(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_j2k  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_j2k* ptr = ptr1;
    mutate_int32_t(&(ptr->m_is_decoder), level+1);
    //ptr->m_specific_param = ...(union anonymous {struct opj_j2k_dec m_decoder; struct opj_j2k_enc m_encoder; } m_specific_param)
    {
        if(ptr->m_private_image) { mutate_opj_image(ptr->m_private_image, level+1); }
        len = 0;
        arr = pool_get_values("opj_image", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_private_image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_private_image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_private_image = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_output_image) { mutate_opj_image(ptr->m_output_image, level+1); }
        len = 0;
        arr = pool_get_values("opj_image", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_output_image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_output_image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_output_image = ptr_save;
        free(arr);
    }
    mutate_opj_cp(&(ptr->m_cp), level+1);
    {
        if(ptr->m_procedure_list) { mutate_opj_procedure_list(ptr->m_procedure_list, level+1); }
        len = 0;
        arr = pool_get_values("opj_procedure_list", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_procedure_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_procedure_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_procedure_list = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_validation_list) { mutate_opj_procedure_list(ptr->m_validation_list, level+1); }
        len = 0;
        arr = pool_get_values("opj_procedure_list", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_validation_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_validation_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_validation_list = ptr_save;
        free(arr);
    }
    {
        if(ptr->cstr_index) { mutate_opj_codestream_index(ptr->cstr_index, level+1); }
        len = 0;
        arr = pool_get_values("opj_codestream_index", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cstr_index;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cstr_index = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cstr_index = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->m_current_tile_number), level+1);
    {
        if(ptr->m_tcd) { mutate_opj_tcd(ptr->m_tcd, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_tcd;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_tcd = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_tcd = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_tp) { mutate_opj_thread_pool_t(ptr->m_tp, level+1); }
        len = 0;
        arr = pool_get_values("opj_thread_pool_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_tp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_tp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_tp = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->ihdr_w), level+1);
    mutate_int32_t(&(ptr->ihdr_h), level+1);
    mutate_int32_t(&(ptr->dump_state), level+1);
    pool_insert("opj_j2k", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_j2k  \n"); fflush(stdout);
    #endif
}
void mutate_opj_j2k_dec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_j2k_dec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_j2k_dec* ptr = ptr1;
    mutate_int32_t(&(ptr->m_state), level+1);
    {
        if(ptr->m_default_tcp) { mutate_opj_tcp(ptr->m_default_tcp, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_default_tcp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_default_tcp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_default_tcp = ptr_save;
        free(arr);
    }
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_header_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_header_data, level + 1, len); }
    #else
    //ptr->m_header_data = ...(unsigned char  *m_header_data)
    #endif
    mutate_int32_t(&(ptr->m_header_data_size), level+1);
    mutate_int32_t(&(ptr->m_sot_length), level+1);
    mutate_int32_t(&(ptr->m_start_tile_x), level+1);
    mutate_int32_t(&(ptr->m_start_tile_y), level+1);
    mutate_int32_t(&(ptr->m_end_tile_x), level+1);
    mutate_int32_t(&(ptr->m_end_tile_y), level+1);
    mutate_int32_t(&(ptr->m_tile_ind_to_dec), level+1);
    mutate_int64_t(&(ptr->m_last_sot_read_pos), level+1);
    mutate_int32_t(&(ptr->m_last_tile_part), level+1);
    mutate_int32_t(&(ptr->m_numcomps_to_decode), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_comps_indices_to_decode);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->m_comps_indices_to_decode, level + 1, len); }
    #else
    //ptr->m_comps_indices_to_decode = ...(unsigned int  *m_comps_indices_to_decode)
    #endif
    //ptr->m_can_decode = ...(bitfield mutation);
    //ptr->m_discard_tiles = ...(bitfield mutation);
    //ptr->m_skip_data = ...(bitfield mutation);
    //ptr->m_nb_tile_parts_correction_checked = ...(bitfield mutation);
    //ptr->m_nb_tile_parts_correction = ...(bitfield mutation);
    pool_insert("opj_j2k_dec", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_j2k_dec  \n"); fflush(stdout);
    #endif
}
void mutate_opj_j2k_enc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_j2k_enc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_j2k_enc* ptr = ptr1;
    mutate_int32_t(&(ptr->m_current_poc_tile_part_number), level+1);
    mutate_int32_t(&(ptr->m_current_tile_part_number), level+1);
    mutate_int32_t(&(ptr->m_TLM), level+1);
    mutate_int32_t(&(ptr->m_Ttlmi_is_byte), level+1);
    mutate_int64_t(&(ptr->m_tlm_start), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_tlm_sot_offsets_buffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_tlm_sot_offsets_buffer, level + 1, len); }
    #else
    //ptr->m_tlm_sot_offsets_buffer = ...(unsigned char  *m_tlm_sot_offsets_buffer)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_tlm_sot_offsets_current);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_tlm_sot_offsets_current, level + 1, len); }
    #else
    //ptr->m_tlm_sot_offsets_current = ...(unsigned char  *m_tlm_sot_offsets_current)
    #endif
    mutate_int32_t(&(ptr->m_total_tile_parts), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_encoded_tile_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_encoded_tile_data, level + 1, len); }
    #else
    //ptr->m_encoded_tile_data = ...(unsigned char  *m_encoded_tile_data)
    #endif
    mutate_int32_t(&(ptr->m_encoded_tile_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_header_tile_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_header_tile_data, level + 1, len); }
    #else
    //ptr->m_header_tile_data = ...(unsigned char  *m_header_tile_data)
    #endif
    mutate_int32_t(&(ptr->m_header_tile_data_size), level+1);
    mutate_int32_t(&(ptr->m_PLT), level+1);
    mutate_int32_t(&(ptr->m_reserved_bytes_for_PLT), level+1);
    pool_insert("opj_j2k_enc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_j2k_enc  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_17(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_17  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_17* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_17", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_17  \n"); fflush(stdout);
    #endif
}
void mutate_opj_procedure_list(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_procedure_list  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_procedure_list* ptr = ptr1;
    mutate_int32_t(&(ptr->m_nb_procedures), level+1);
    mutate_int32_t(&(ptr->m_nb_max_procedures), level+1);
    //ptr->m_procedures = ...(function m_procedures)
    pool_insert("opj_procedure_list", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_procedure_list  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd* ptr = ptr1;
    mutate_int32_t(&(ptr->tp_pos), level+1);
    mutate_int32_t(&(ptr->tp_num), level+1);
    mutate_int32_t(&(ptr->cur_tp_num), level+1);
    mutate_int32_t(&(ptr->cur_totnum_tp), level+1);
    mutate_int32_t(&(ptr->cur_pino), level+1);
    {
        if(ptr->tcd_image) { mutate_opj_tcd_image(ptr->tcd_image, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_image", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tcd_image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tcd_image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tcd_image = ptr_save;
        free(arr);
    }
    {
        if(ptr->image) { mutate_opj_image(ptr->image, level+1); }
        len = 0;
        arr = pool_get_values("opj_image", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->image = ptr_save;
        free(arr);
    }
    {
        if(ptr->cp) { mutate_opj_cp(ptr->cp, level+1); }
        len = 0;
        arr = pool_get_values("opj_cp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cp = ptr_save;
        free(arr);
    }
    {
        if(ptr->tcp) { mutate_opj_tcp(ptr->tcp, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tcp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tcp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tcp = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->tcd_tileno), level+1);
    //ptr->m_is_decoder = ...(bitfield mutation);
    {
        if(ptr->thread_pool) { mutate_opj_thread_pool_t(ptr->thread_pool, level+1); }
        len = 0;
        arr = pool_get_values("opj_thread_pool_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->thread_pool;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->thread_pool = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->thread_pool = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->win_x0), level+1);
    mutate_int32_t(&(ptr->win_y0), level+1);
    mutate_int32_t(&(ptr->win_x1), level+1);
    mutate_int32_t(&(ptr->win_y1), level+1);
    mutate_int32_t(&(ptr->whole_tile_decoding), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->used_component);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->used_component, level + 1, len); }
    #else
    //ptr->used_component = ...(int  *used_component)
    #endif
    pool_insert("opj_tcd", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_image(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_image  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_image* ptr = ptr1;
    {
        if(ptr->tiles) { mutate_opj_tcd_tile(ptr->tiles, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_tile", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tiles;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tiles = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tiles = ptr_save;
        free(arr);
    }
    pool_insert("opj_tcd_image", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_image  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_tile(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_tile  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_tile* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    {
        if(ptr->comps) { mutate_opj_tcd_tilecomp(ptr->comps, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_tilecomp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comps = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->numpix), level+1);
    mutate_double(&(ptr->distotile), level+1);
    assign_double_array(&(ptr->distolayer), level + 1, 100);
    mutate_int32_t(&(ptr->packno), level+1);
    pool_insert("opj_tcd_tile", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_tile  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_tilecomp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_tilecomp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_tilecomp* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->compno), level+1);
    mutate_int32_t(&(ptr->numresolutions), level+1);
    mutate_int32_t(&(ptr->minimum_num_resolutions), level+1);
    {
        if(ptr->resolutions) { mutate_opj_tcd_resolution(ptr->resolutions, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_resolution", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->resolutions;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->resolutions = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->resolutions = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->resolutions_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(int  *data)
    #endif
    mutate_int32_t(&(ptr->ownsData), level+1);
    mutate_int64_t(&(ptr->data_size_needed), level+1);
    mutate_int64_t(&(ptr->data_size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data_win);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->data_win, level + 1, len); }
    #else
    //ptr->data_win = ...(int  *data_win)
    #endif
    mutate_int32_t(&(ptr->win_x0), level+1);
    mutate_int32_t(&(ptr->win_y0), level+1);
    mutate_int32_t(&(ptr->win_x1), level+1);
    mutate_int32_t(&(ptr->win_y1), level+1);
    mutate_int32_t(&(ptr->numpix), level+1);
    pool_insert("opj_tcd_tilecomp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_tilecomp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_resolution(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_resolution  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_resolution* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->pw), level+1);
    mutate_int32_t(&(ptr->ph), level+1);
    mutate_int32_t(&(ptr->numbands), level+1);
    for(int i = 0; i < 3; i++)
    {
        mutate_opj_tcd_band(&(ptr->bands)[i], level+1);
    }
    mutate_int32_t(&(ptr->win_x0), level+1);
    mutate_int32_t(&(ptr->win_y0), level+1);
    mutate_int32_t(&(ptr->win_x1), level+1);
    mutate_int32_t(&(ptr->win_y1), level+1);
    pool_insert("opj_tcd_resolution", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_resolution  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_band(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_band  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_band* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->bandno), level+1);
    {
        if(ptr->precincts) { mutate_opj_tcd_precinct(ptr->precincts, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_precinct", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->precincts;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->precincts = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->precincts = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->precincts_data_size), level+1);
    mutate_int32_t(&(ptr->numbps), level+1);
    mutate_float(&(ptr->stepsize), level+1);
    pool_insert("opj_tcd_band", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_band  \n"); fflush(stdout);
    #endif
}
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
    union memfuzz_anonymous_struct_18* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_18", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_18  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_precinct(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_precinct  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_precinct* ptr = ptr1;
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->cw), level+1);
    mutate_int32_t(&(ptr->ch), level+1);
    //ptr->cblks = ...(union anonymous {struct opj_tcd_cblk_enc *enc; struct opj_tcd_cblk_dec *dec; void  *blocks; } cblks)
    mutate_int32_t(&(ptr->block_size), level+1);
    {
        if(ptr->incltree) { mutate_opj_tgt_tree(ptr->incltree, level+1); }
        len = 0;
        arr = pool_get_values("opj_tgt_tree", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->incltree;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->incltree = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->incltree = ptr_save;
        free(arr);
    }
    {
        if(ptr->imsbtree) { mutate_opj_tgt_tree(ptr->imsbtree, level+1); }
        len = 0;
        arr = pool_get_values("opj_tgt_tree", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->imsbtree;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->imsbtree = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->imsbtree = ptr_save;
        free(arr);
    }
    pool_insert("opj_tcd_precinct", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_precinct  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_cblk_enc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_cblk_enc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_cblk_enc* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    {
        if(ptr->layers) { mutate_opj_tcd_layer(ptr->layers, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_layer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->layers;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->layers = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->layers = ptr_save;
        free(arr);
    }
    {
        if(ptr->passes) { mutate_opj_tcd_pass(ptr->passes, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_pass", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->passes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->passes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->passes = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->numbps), level+1);
    mutate_int32_t(&(ptr->numlenbits), level+1);
    mutate_int32_t(&(ptr->data_size), level+1);
    mutate_int32_t(&(ptr->numpasses), level+1);
    mutate_int32_t(&(ptr->numpassesinlayers), level+1);
    mutate_int32_t(&(ptr->totalpasses), level+1);
    pool_insert("opj_tcd_cblk_enc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_cblk_enc  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_layer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_layer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_layer* ptr = ptr1;
    mutate_int32_t(&(ptr->numpasses), level+1);
    mutate_int32_t(&(ptr->len), level+1);
    mutate_double(&(ptr->disto), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    pool_insert("opj_tcd_layer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_layer  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_pass(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_pass  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_pass* ptr = ptr1;
    mutate_int32_t(&(ptr->rate), level+1);
    mutate_double(&(ptr->distortiondec), level+1);
    mutate_int32_t(&(ptr->len), level+1);
    //ptr->term = ...(bitfield mutation);
    pool_insert("opj_tcd_pass", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_pass  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_cblk_dec(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_cblk_dec  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_cblk_dec* ptr = ptr1;
    {
        if(ptr->segs) { mutate_opj_tcd_seg(ptr->segs, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_seg", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->segs;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->segs = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->segs = ptr_save;
        free(arr);
    }
    {
        if(ptr->chunks) { mutate_opj_tcd_seg_data_chunk(ptr->chunks, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_seg_data_chunk", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->chunks;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->chunks = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->chunks = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->x0), level+1);
    mutate_int32_t(&(ptr->y0), level+1);
    mutate_int32_t(&(ptr->x1), level+1);
    mutate_int32_t(&(ptr->y1), level+1);
    mutate_int32_t(&(ptr->numbps), level+1);
    mutate_int32_t(&(ptr->numlenbits), level+1);
    mutate_int32_t(&(ptr->numnewpasses), level+1);
    mutate_int32_t(&(ptr->numsegs), level+1);
    mutate_int32_t(&(ptr->real_num_segs), level+1);
    mutate_int32_t(&(ptr->m_current_max_segs), level+1);
    mutate_int32_t(&(ptr->numchunks), level+1);
    mutate_int32_t(&(ptr->numchunksalloc), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->decoded_data);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->decoded_data, level + 1, len); }
    #else
    //ptr->decoded_data = ...(int  *decoded_data)
    #endif
    pool_insert("opj_tcd_cblk_dec", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_cblk_dec  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_seg(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_seg  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_seg* ptr = ptr1;
    mutate_int32_t(&(ptr->len), level+1);
    mutate_int32_t(&(ptr->numpasses), level+1);
    mutate_int32_t(&(ptr->real_num_passes), level+1);
    mutate_int32_t(&(ptr->maxpasses), level+1);
    mutate_int32_t(&(ptr->numnewpasses), level+1);
    mutate_int32_t(&(ptr->newlen), level+1);
    pool_insert("opj_tcd_seg", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_seg  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_seg_data_chunk(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_seg_data_chunk  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_seg_data_chunk* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    mutate_int32_t(&(ptr->len), level+1);
    pool_insert("opj_tcd_seg_data_chunk", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_seg_data_chunk  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tgt_tree(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tgt_tree  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tgt_tree* ptr = ptr1;
    mutate_int32_t(&(ptr->numleafsh), level+1);
    mutate_int32_t(&(ptr->numleafsv), level+1);
    mutate_int32_t(&(ptr->numnodes), level+1);
    {
        if(ptr->nodes) { mutate_opj_tgt_node(ptr->nodes, level+1); }
        len = 0;
        arr = pool_get_values("opj_tgt_node", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->nodes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->nodes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->nodes = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->nodes_size), level+1);
    pool_insert("opj_tgt_tree", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tgt_tree  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tgt_node(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tgt_node  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tgt_node* ptr = ptr1;
    {
        if(ptr->parent) { mutate_opj_tgt_node(ptr->parent, level+1); }
        len = 0;
        arr = pool_get_values("opj_tgt_node", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->parent;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->parent = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->parent = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->value), level+1);
    mutate_int32_t(&(ptr->low), level+1);
    mutate_int32_t(&(ptr->known), level+1);
    pool_insert("opj_tgt_node", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tgt_node  \n"); fflush(stdout);
    #endif
}
void mutate_opj_tcd_marker_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_tcd_marker_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_tcd_marker_info* ptr = ptr1;
    mutate_int32_t(&(ptr->need_PLT), level+1);
    mutate_int32_t(&(ptr->packet_count), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->p_packet_size);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->p_packet_size, level + 1, len); }
    #else
    //ptr->p_packet_size = ...(unsigned int  *p_packet_size)
    #endif
    pool_insert("opj_tcd_marker_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_tcd_marker_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_header_handler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_header_handler  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_header_handler* ptr = ptr1;
    mutate_int32_t(&(ptr->id), level+1);
    //ptr->handler = ...(function handler)
    pool_insert("opj_jp2_header_handler", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_header_handler  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2* ptr = ptr1;
    {
        if(ptr->j2k) { mutate_opj_j2k(ptr->j2k, level+1); }
        len = 0;
        arr = pool_get_values("opj_j2k", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->j2k;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->j2k = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->j2k = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_validation_list) { mutate_opj_procedure_list(ptr->m_validation_list, level+1); }
        len = 0;
        arr = pool_get_values("opj_procedure_list", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_validation_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_validation_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_validation_list = ptr_save;
        free(arr);
    }
    {
        if(ptr->m_procedure_list) { mutate_opj_procedure_list(ptr->m_procedure_list, level+1); }
        len = 0;
        arr = pool_get_values("opj_procedure_list", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->m_procedure_list;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->m_procedure_list = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->m_procedure_list = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->w), level+1);
    mutate_int32_t(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    mutate_int32_t(&(ptr->bpc), level+1);
    mutate_int32_t(&(ptr->C), level+1);
    mutate_int32_t(&(ptr->UnkC), level+1);
    mutate_int32_t(&(ptr->IPR), level+1);
    mutate_int32_t(&(ptr->meth), level+1);
    mutate_int32_t(&(ptr->approx), level+1);
    mutate_int32_t(&(ptr->enumcs), level+1);
    mutate_int32_t(&(ptr->precedence), level+1);
    mutate_int32_t(&(ptr->brand), level+1);
    mutate_int32_t(&(ptr->minversion), level+1);
    mutate_int32_t(&(ptr->numcl), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->cl);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->cl, level + 1, len); }
    #else
    //ptr->cl = ...(unsigned int  *cl)
    #endif
    {
        if(ptr->comps) { mutate_opj_jp2_comps(ptr->comps, level+1); }
        len = 0;
        arr = pool_get_values("opj_jp2_comps", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comps = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->j2k_codestream_offset), level+1);
    mutate_int64_t(&(ptr->jpip_iptr_offset), level+1);
    mutate_int32_t(&(ptr->jpip_on), level+1);
    mutate_int32_t(&(ptr->jp2_state), level+1);
    mutate_int32_t(&(ptr->jp2_img_state), level+1);
    mutate_opj_jp2_color(&(ptr->color), level+1);
    mutate_int32_t(&(ptr->ignore_pclr_cmap_cdef), level+1);
    mutate_int8_t(&(ptr->has_jp2h), level+1);
    mutate_int8_t(&(ptr->has_ihdr), level+1);
    pool_insert("opj_jp2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_19* ptr = ptr1;
    mutate_opj_j2k_dec(&(ptr->m_decoder), level+1);
    mutate_opj_j2k_enc(&(ptr->m_encoder), level+1);
    pool_insert("memfuzz_anonymous_struct_19", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_19  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_20(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_20  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_20* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_20", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_20  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_21(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_21  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_21* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_21", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_21  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_comps(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_comps  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_comps* ptr = ptr1;
    mutate_int32_t(&(ptr->depth), level+1);
    mutate_int32_t(&(ptr->sgnd), level+1);
    mutate_int32_t(&(ptr->bpcc), level+1);
    pool_insert("opj_jp2_comps", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_comps  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_color(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_color  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_color* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->icc_profile_buf);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->icc_profile_buf, level + 1, len); }
    #else
    //ptr->icc_profile_buf = ...(unsigned char  *icc_profile_buf)
    #endif
    mutate_int32_t(&(ptr->icc_profile_len), level+1);
    {
        if(ptr->jp2_cdef) { mutate_opj_jp2_cdef(ptr->jp2_cdef, level+1); }
        len = 0;
        arr = pool_get_values("opj_jp2_cdef", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->jp2_cdef;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->jp2_cdef = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->jp2_cdef = ptr_save;
        free(arr);
    }
    {
        if(ptr->jp2_pclr) { mutate_opj_jp2_pclr(ptr->jp2_pclr, level+1); }
        len = 0;
        arr = pool_get_values("opj_jp2_pclr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->jp2_pclr;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->jp2_pclr = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->jp2_pclr = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->jp2_has_colr), level+1);
    pool_insert("opj_jp2_color", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_color  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_cdef(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_cdef  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_cdef* ptr = ptr1;
    {
        if(ptr->info) { mutate_opj_jp2_cdef_info(ptr->info, level+1); }
        len = 0;
        arr = pool_get_values("opj_jp2_cdef_info", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->info;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->info = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->info = ptr_save;
        free(arr);
    }
    mutate_int16_t(&(ptr->n), level+1);
    pool_insert("opj_jp2_cdef", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_cdef  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_cdef_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_cdef_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_cdef_info* ptr = ptr1;
    mutate_int16_t(&(ptr->cn), level+1);
    mutate_int16_t(&(ptr->typ), level+1);
    mutate_int16_t(&(ptr->asoc), level+1);
    pool_insert("opj_jp2_cdef_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_cdef_info  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_pclr(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_pclr  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_pclr* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->entries);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->entries, level + 1, len); }
    #else
    //ptr->entries = ...(unsigned int  *entries)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->channel_sign);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->channel_sign, level + 1, len); }
    #else
    //ptr->channel_sign = ...(unsigned char  *channel_sign)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->channel_size);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->channel_size, level + 1, len); }
    #else
    //ptr->channel_size = ...(unsigned char  *channel_size)
    #endif
    {
        if(ptr->cmap) { mutate_opj_jp2_cmap_comp(ptr->cmap, level+1); }
        len = 0;
        arr = pool_get_values("opj_jp2_cmap_comp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cmap;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cmap = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cmap = ptr_save;
        free(arr);
    }
    mutate_int16_t(&(ptr->nr_entries), level+1);
    mutate_int8_t(&(ptr->nr_channels), level+1);
    pool_insert("opj_jp2_pclr", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_pclr  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_cmap_comp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_cmap_comp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_cmap_comp* ptr = ptr1;
    mutate_int16_t(&(ptr->cmp), level+1);
    mutate_int8_t(&(ptr->mtyp), level+1);
    mutate_int8_t(&(ptr->pcol), level+1);
    pool_insert("opj_jp2_cmap_comp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_cmap_comp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_box(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_box  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_box* ptr = ptr1;
    mutate_int32_t(&(ptr->length), level+1);
    mutate_int32_t(&(ptr->type), level+1);
    mutate_int32_t(&(ptr->init_pos), level+1);
    pool_insert("opj_jp2_box", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_box  \n"); fflush(stdout);
    #endif
}
void mutate_opj_jp2_img_header_writer_handler(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_jp2_img_header_writer_handler  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_jp2_img_header_writer_handler* ptr = ptr1;
    //ptr->handler = ...(function handler)
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->m_data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->m_data, level + 1, len); }
    #else
    //ptr->m_data = ...(unsigned char  *m_data)
    #endif
    mutate_int32_t(&(ptr->m_size), level+1);
    pool_insert("opj_jp2_img_header_writer_handler", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_jp2_img_header_writer_handler  \n"); fflush(stdout);
    #endif
}
void mutate_opj_pi_iterator(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_pi_iterator  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_pi_iterator* ptr = ptr1;
    mutate_int8_t(&(ptr->tp_on), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->include);
    len /= sizeof(int16_t);
    if(len != 0){ mutate_int16_t_array(ptr->include, level + 1, len); }
    #else
    //ptr->include = ...(short  *include)
    #endif
    mutate_int32_t(&(ptr->include_size), level+1);
    mutate_int32_t(&(ptr->step_l), level+1);
    mutate_int32_t(&(ptr->step_r), level+1);
    mutate_int32_t(&(ptr->step_c), level+1);
    mutate_int32_t(&(ptr->step_p), level+1);
    mutate_int32_t(&(ptr->compno), level+1);
    mutate_int32_t(&(ptr->resno), level+1);
    mutate_int32_t(&(ptr->precno), level+1);
    mutate_int32_t(&(ptr->layno), level+1);
    mutate_int32_t(&(ptr->first), level+1);
    mutate_opj_poc(&(ptr->poc), level+1);
    mutate_int32_t(&(ptr->numcomps), level+1);
    {
        if(ptr->comps) { mutate_opj_pi_comp(ptr->comps, level+1); }
        len = 0;
        arr = pool_get_values("opj_pi_comp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comps;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comps = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comps = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->tx0), level+1);
    mutate_int32_t(&(ptr->ty0), level+1);
    mutate_int32_t(&(ptr->tx1), level+1);
    mutate_int32_t(&(ptr->ty1), level+1);
    mutate_int32_t(&(ptr->x), level+1);
    mutate_int32_t(&(ptr->y), level+1);
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    {
        if(ptr->manager) { mutate_opj_event_mgr(ptr->manager, level+1); }
        len = 0;
        arr = pool_get_values("opj_event_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->manager;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->manager = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->manager = ptr_save;
        free(arr);
    }
    pool_insert("opj_pi_iterator", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_pi_iterator  \n"); fflush(stdout);
    #endif
}
void mutate_opj_pi_comp(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_pi_comp  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_pi_comp* ptr = ptr1;
    mutate_int32_t(&(ptr->dx), level+1);
    mutate_int32_t(&(ptr->dy), level+1);
    mutate_int32_t(&(ptr->numresolutions), level+1);
    {
        if(ptr->resolutions) { mutate_opj_pi_resolution(ptr->resolutions, level+1); }
        len = 0;
        arr = pool_get_values("opj_pi_resolution", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->resolutions;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->resolutions = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->resolutions = ptr_save;
        free(arr);
    }
    pool_insert("opj_pi_comp", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_pi_comp  \n"); fflush(stdout);
    #endif
}
void mutate_opj_pi_resolution(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_pi_resolution  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_pi_resolution* ptr = ptr1;
    mutate_int32_t(&(ptr->pdx), level+1);
    mutate_int32_t(&(ptr->pdy), level+1);
    mutate_int32_t(&(ptr->pw), level+1);
    mutate_int32_t(&(ptr->ph), level+1);
    pool_insert("opj_pi_resolution", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_pi_resolution  \n"); fflush(stdout);
    #endif
}
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
    union memfuzz_anonymous_struct_22* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_22", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_22  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_23(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_23  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_23* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_23", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_23  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_24(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_24  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_24* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_24", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_24  \n"); fflush(stdout);
    #endif
}
void mutate_opj_t2(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_t2  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_t2* ptr = ptr1;
    {
        if(ptr->image) { mutate_opj_image(ptr->image, level+1); }
        len = 0;
        arr = pool_get_values("opj_image", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->image;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->image = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->image = ptr_save;
        free(arr);
    }
    {
        if(ptr->cp) { mutate_opj_cp(ptr->cp, level+1); }
        len = 0;
        arr = pool_get_values("opj_cp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cp = ptr_save;
        free(arr);
    }
    pool_insert("opj_t2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_t2  \n"); fflush(stdout);
    #endif
}
void mutate_opj_bio(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_bio  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_bio* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->start);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->start, level + 1, len); }
    #else
    //ptr->start = ...(unsigned char  *start)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->end);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->end, level + 1, len); }
    #else
    //ptr->end = ...(unsigned char  *end)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->bp);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->bp, level + 1, len); }
    #else
    //ptr->bp = ...(unsigned char  *bp)
    #endif
    mutate_int32_t(&(ptr->buf), level+1);
    mutate_int32_t(&(ptr->ct), level+1);
    pool_insert("opj_bio", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_bio  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_25(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_25  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_25* ptr = ptr1;
    mutate_dwt_local(&(ptr->v), level+1);
    mutate_int32_t(&(ptr->rh), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->tiledp = ...(unknown tiledp)
    mutate_int32_t(&(ptr->min_j), level+1);
    mutate_int32_t(&(ptr->max_j), level+1);
    //ptr->p_encode_and_deinterleave_v = ...(function p_encode_and_deinterleave_v)
    pool_insert("memfuzz_anonymous_struct_25", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_25  \n"); fflush(stdout);
    #endif
}
void mutate_dwt_local(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_dwt_local  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct dwt_local* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->mem);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->mem, level + 1, len); }
    #else
    //ptr->mem = ...(int  *mem)
    #endif
    mutate_int32_t(&(ptr->dn), level+1);
    mutate_int32_t(&(ptr->sn), level+1);
    mutate_int32_t(&(ptr->cas), level+1);
    pool_insert("dwt_local", ptr1);
    #ifdef DEBUG
    printf("leave mutate_dwt_local  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_26(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_26  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_26* ptr = ptr1;
    mutate_dwt_local(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->rw), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->tiledp = ...(unknown tiledp)
    mutate_int32_t(&(ptr->min_j), level+1);
    mutate_int32_t(&(ptr->max_j), level+1);
    //ptr->p_function = ...(function p_function)
    pool_insert("memfuzz_anonymous_struct_26", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_26  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_27(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_27  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_27* ptr = ptr1;
    mutate_dwt_local(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->rw), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->tiledp = ...(unknown tiledp)
    mutate_int32_t(&(ptr->min_j), level+1);
    mutate_int32_t(&(ptr->max_j), level+1);
    pool_insert("memfuzz_anonymous_struct_27", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_27  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_28(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_28  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_28* ptr = ptr1;
    mutate_dwt_local(&(ptr->v), level+1);
    mutate_int32_t(&(ptr->rh), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->tiledp = ...(unknown tiledp)
    mutate_int32_t(&(ptr->min_j), level+1);
    mutate_int32_t(&(ptr->max_j), level+1);
    pool_insert("memfuzz_anonymous_struct_28", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_28  \n"); fflush(stdout);
    #endif
}
void mutate___loadu_si128(void* ptr1, int level){return ;}
void mutate___storeu_si128(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_29(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_29  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_29* ptr = ptr1;
    assign_float_array(&(ptr->f), level + 1, 8);
    pool_insert("memfuzz_anonymous_struct_29", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_29  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_30(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_30  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_30* ptr = ptr1;
    mutate_v8dwt_local(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->rw), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->aj = ...(unknown aj)
    mutate_int32_t(&(ptr->nb_rows), level+1);
    pool_insert("memfuzz_anonymous_struct_30", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_30  \n"); fflush(stdout);
    #endif
}
void mutate_v8dwt_local(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_v8dwt_local  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct v8dwt_local* ptr = ptr1;
    //ptr->wavelet = ...(union anonymous *{float  f[8]; } wavelet)
    mutate_int32_t(&(ptr->dn), level+1);
    mutate_int32_t(&(ptr->sn), level+1);
    mutate_int32_t(&(ptr->cas), level+1);
    mutate_int32_t(&(ptr->win_l_x0), level+1);
    mutate_int32_t(&(ptr->win_l_x1), level+1);
    mutate_int32_t(&(ptr->win_h_x0), level+1);
    mutate_int32_t(&(ptr->win_h_x1), level+1);
    pool_insert("v8dwt_local", ptr1);
    #ifdef DEBUG
    printf("leave mutate_v8dwt_local  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_31(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_31  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_31* ptr = ptr1;
    mutate_v8dwt_local(&(ptr->v), level+1);
    mutate_int32_t(&(ptr->rh), level+1);
    mutate_int32_t(&(ptr->w), level+1);
    //ptr->aj = ...(unknown aj)
    mutate_int32_t(&(ptr->nb_columns), level+1);
    pool_insert("memfuzz_anonymous_struct_31", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_31  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_32(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_32  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_32* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_32", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_32  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_33(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_33  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_33* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_33", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_33  \n"); fflush(stdout);
    #endif
}
void mutate_opj_t1(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_t1  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_t1* ptr = ptr1;
    mutate_opj_mqc(&(ptr->mqc), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(int  *data)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->flags);
    len /= sizeof(int32_t);
    if(len != 0){ mutate_int32_t_array(ptr->flags, level + 1, len); }
    #else
    //ptr->flags = ...(unsigned int  *flags)
    #endif
    mutate_int32_t(&(ptr->w), level+1);
    mutate_int32_t(&(ptr->h), level+1);
    mutate_int32_t(&(ptr->datasize), level+1);
    mutate_int32_t(&(ptr->flagssize), level+1);
    mutate_int32_t(&(ptr->encoder), level+1);
    mutate_int32_t(&(ptr->mustuse_cblkdatabuffer), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->cblkdatabuffer);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->cblkdatabuffer, level + 1, len); }
    #else
    //ptr->cblkdatabuffer = ...(unsigned char  *cblkdatabuffer)
    #endif
    mutate_int32_t(&(ptr->cblkdatabuffersize), level+1);
    pool_insert("opj_t1", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_t1  \n"); fflush(stdout);
    #endif
}
void mutate_opj_mqc(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_mqc  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_mqc* ptr = ptr1;
    mutate_int32_t(&(ptr->c), level+1);
    mutate_int32_t(&(ptr->a), level+1);
    mutate_int32_t(&(ptr->ct), level+1);
    mutate_int32_t(&(ptr->end_of_byte_stream_counter), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->bp);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->bp, level + 1, len); }
    #else
    //ptr->bp = ...(unsigned char  *bp)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->start);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->start, level + 1, len); }
    #else
    //ptr->start = ...(unsigned char  *start)
    #endif
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->end);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->end, level + 1, len); }
    #else
    //ptr->end = ...(unsigned char  *end)
    #endif
    //ptr->ctxs = ...(*ctxs[19])
    //ptr->curctx = ...(const **curctx)
    //ptr->lut_ctxno_zc_orient = ...(const *lut_ctxno_zc_orient)
    assign_int8_t_array(&(ptr->backup), level + 1, 2);
    pool_insert("opj_mqc", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_mqc  \n"); fflush(stdout);
    #endif
}
void mutate_opj_mqc_state(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_mqc_state  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_mqc_state* ptr = ptr1;
    mutate_int32_t(&(ptr->qeval), level+1);
    mutate_int32_t(&(ptr->mps), level+1);
    //ptr->nmps = ...(const *nmps)
    //ptr->nlps = ...(const *nlps)
    pool_insert("opj_mqc_state", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_mqc_state  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_34(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_34  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_34* ptr = ptr1;
    mutate_int32_t(&(ptr->whole_tile_decoding), level+1);
    mutate_int32_t(&(ptr->resno), level+1);
    {
        if(ptr->cblk) { mutate_opj_tcd_cblk_dec(ptr->cblk, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cblk;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cblk = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cblk = ptr_save;
        free(arr);
    }
    {
        if(ptr->band) { mutate_opj_tcd_band(ptr->band, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_band", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->band;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->band = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->band = ptr_save;
        free(arr);
    }
    {
        if(ptr->tilec) { mutate_opj_tcd_tilecomp(ptr->tilec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_tilecomp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tilec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tilec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tilec = ptr_save;
        free(arr);
    }
    {
        if(ptr->tccp) { mutate_opj_tccp(ptr->tccp, level+1); }
        len = 0;
        arr = pool_get_values("opj_tccp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tccp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tccp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tccp = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->mustuse_cblkdatabuffer), level+1);
    //ptr->pret = ...(unknown pret)
    {
        if(ptr->p_manager) { mutate_opj_event_mgr(ptr->p_manager, level+1); }
        len = 0;
        arr = pool_get_values("opj_event_mgr", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->p_manager;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->p_manager = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->p_manager = ptr_save;
        free(arr);
    }
    {
        if(ptr->p_manager_mutex) { mutate_opj_mutex_t(ptr->p_manager_mutex, level+1); }
        len = 0;
        arr = pool_get_values("opj_mutex_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->p_manager_mutex;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->p_manager_mutex = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->p_manager_mutex = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->check_pterm), level+1);
    pool_insert("memfuzz_anonymous_struct_34", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_34  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_35(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_35  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_35* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_35", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_35  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_36(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_36  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct memfuzz_anonymous_struct_36* ptr = ptr1;
    mutate_int32_t(&(ptr->compno), level+1);
    mutate_int32_t(&(ptr->resno), level+1);
    {
        if(ptr->cblk) { mutate_opj_tcd_cblk_enc(ptr->cblk, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->cblk;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->cblk = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->cblk = ptr_save;
        free(arr);
    }
    {
        if(ptr->tile) { mutate_opj_tcd_tile(ptr->tile, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_tile", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tile;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tile = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tile = ptr_save;
        free(arr);
    }
    {
        if(ptr->band) { mutate_opj_tcd_band(ptr->band, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_band", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->band;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->band = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->band = ptr_save;
        free(arr);
    }
    {
        if(ptr->tilec) { mutate_opj_tcd_tilecomp(ptr->tilec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_tilecomp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tilec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tilec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tilec = ptr_save;
        free(arr);
    }
    {
        if(ptr->tccp) { mutate_opj_tccp(ptr->tccp, level+1); }
        len = 0;
        arr = pool_get_values("opj_tccp", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->tccp;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->tccp = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->tccp = ptr_save;
        free(arr);
    }
    //ptr->mct_norms = ...(const *mct_norms)
    mutate_int32_t(&(ptr->mct_numcomps), level+1);
    //ptr->pret = ...(unknown pret)
    {
        if(ptr->mutex) { mutate_opj_mutex_t(ptr->mutex, level+1); }
        len = 0;
        arr = pool_get_values("opj_mutex_t", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->mutex;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->mutex = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->mutex = ptr_save;
        free(arr);
    }
    pool_insert("memfuzz_anonymous_struct_36", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_36  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_37(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_37  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_37* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_37", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_37  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_38(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_38  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_38* ptr = ptr1;
    mutate_opj_decoding_param(&(ptr->m_dec), level+1);
    mutate_opj_encoding_param(&(ptr->m_enc), level+1);
    pool_insert("memfuzz_anonymous_struct_38", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_38  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_39(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_39  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_39* ptr = ptr1;
    {
        if(ptr->enc) { mutate_opj_tcd_cblk_enc(ptr->enc, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_enc", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->enc;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->enc = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->enc = ptr_save;
        free(arr);
    }
    {
        if(ptr->dec) { mutate_opj_tcd_cblk_dec(ptr->dec, level+1); }
        len = 0;
        arr = pool_get_values("opj_tcd_cblk_dec", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->dec;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->dec = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->dec = ptr_save;
        free(arr);
    }
        pool_insert("memfuzz_anonymous_struct_39", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_39  \n"); fflush(stdout);
    #endif
}
void mutate_opj_sparse_array_int32(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_opj_sparse_array_int32  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct opj_sparse_array_int32* ptr = ptr1;
    mutate_int32_t(&(ptr->width), level+1);
    mutate_int32_t(&(ptr->height), level+1);
    mutate_int32_t(&(ptr->block_width), level+1);
    mutate_int32_t(&(ptr->block_height), level+1);
    mutate_int32_t(&(ptr->block_count_hor), level+1);
    mutate_int32_t(&(ptr->block_count_ver), level+1);
    //ptr->data_blocks = ...(int  **data_blocks)
    pool_insert("opj_sparse_array_int32", ptr1);
    #ifdef DEBUG
    printf("leave mutate_opj_sparse_array_int32  \n"); fflush(stdout);
    #endif
}
