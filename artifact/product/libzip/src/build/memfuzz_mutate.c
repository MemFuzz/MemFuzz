#include "memfuzz_mutate.h"
#include "memfuzz_struct.h"
#include "memfuzz_util.h"
#include "memfuzz_hook.h"
#include "memfuzz_pool.h"
#include "memfuzz_config.h"
void mutate_tm(void* ptr1, int level){return ;}
void mutate__IO_FILE(void* ptr1, int level){return ;}
void mutate__IO_marker(void* ptr1, int level){return ;}
void mutate_zip_error(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_error  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_error* ptr = ptr1;
    mutate_int32_t(&(ptr->zip_err), level+1);
    mutate_int32_t(&(ptr->sys_err), level+1);
    mutate_c_str(ptr->str);
    pool_insert("zip_error", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_error  \n"); fflush(stdout);
    #endif
}
void mutate_zip_stat(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_stat  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_stat* ptr = ptr1;
    mutate_int64_t(&(ptr->valid), level+1);
    //ptr->name = ...(const *name)
    mutate_int64_t(&(ptr->index), level+1);
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->comp_size), level+1);
    mutate_int64_t(&(ptr->mtime), level+1);
    mutate_int32_t(&(ptr->crc), level+1);
    mutate_int16_t(&(ptr->comp_method), level+1);
    mutate_int16_t(&(ptr->encryption_method), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    pool_insert("zip_stat", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_stat  \n"); fflush(stdout);
    #endif
}
void mutate_dispatch_table_s(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_dispatch_table_s  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct dispatch_table_s* ptr = ptr1;
    //ptr->cmdline_name = ...(const *cmdline_name)
    mutate_int32_t(&(ptr->argument_count), level+1);
    //ptr->arg_names = ...(const *arg_names)
    //ptr->description = ...(const *description)
    //ptr->function = ...(function function)
    pool_insert("dispatch_table_s", ptr1);
    #ifdef DEBUG
    printf("leave mutate_dispatch_table_s  \n"); fflush(stdout);
    #endif
}
void mutate_progress_userdata_s(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_progress_userdata_s  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct progress_userdata_s* ptr = ptr1;
    mutate_double(&(ptr->percentage), level+1);
    mutate_double(&(ptr->limit), level+1);
    pool_insert("progress_userdata_s", ptr1);
    #ifdef DEBUG
    printf("leave mutate_progress_userdata_s  \n"); fflush(stdout);
    #endif
}
void mutate_zip_file_attributes(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_file_attributes  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_file_attributes* ptr = ptr1;
    mutate_int64_t(&(ptr->valid), level+1);
    mutate_int8_t(&(ptr->version), level+1);
    mutate_int8_t(&(ptr->host_system), level+1);
    mutate_int8_t(&(ptr->ascii), level+1);
    mutate_int8_t(&(ptr->version_needed), level+1);
    mutate_int32_t(&(ptr->external_file_attributes), level+1);
    mutate_int16_t(&(ptr->general_purpose_bit_flags), level+1);
    mutate_int16_t(&(ptr->general_purpose_bit_mask), level+1);
    pool_insert("zip_file_attributes", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_file_attributes  \n"); fflush(stdout);
    #endif
}
void mutate_zip(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip* ptr = ptr1;
    {
        if(ptr->src) { mutate_zip_source(ptr->src, level+1); }
        len = 0;
        arr = pool_get_values("zip_source", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->src;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->src = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->src = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->open_flags), level+1);
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int32_t(&(ptr->ch_flags), level+1);
    mutate_c_str(ptr->default_password);
    {
        if(ptr->comment_orig) { mutate_zip_string(ptr->comment_orig, level+1); }
        len = 0;
        arr = pool_get_values("zip_string", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comment_orig;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comment_orig = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comment_orig = ptr_save;
        free(arr);
    }
    {
        if(ptr->comment_changes) { mutate_zip_string(ptr->comment_changes, level+1); }
        len = 0;
        arr = pool_get_values("zip_string", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comment_changes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comment_changes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comment_changes = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->comment_changed), level+1);
    mutate_int64_t(&(ptr->nentry), level+1);
    mutate_int64_t(&(ptr->nentry_alloc), level+1);
    {
        if(ptr->entry) { mutate_zip_entry(ptr->entry, level+1); }
        len = 0;
        arr = pool_get_values("zip_entry", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->entry;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->entry = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->entry = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->nopen_source), level+1);
    mutate_int32_t(&(ptr->nopen_source_alloc), level+1);
    {
        if(ptr->open_source) { mutate_zip_source(ptr->open_source, level+1); }
        len = 0;
        arr = pool_get_values("zip_source", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->open_source;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->open_source = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->open_source = ptr_save;
        free(arr);
    }
    {
        if(ptr->names) { mutate_zip_hash(ptr->names, level+1); }
        len = 0;
        arr = pool_get_values("zip_hash", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->names;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->names = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->names = ptr_save;
        free(arr);
    }
    {
        if(ptr->progress) { mutate_zip_progress(ptr->progress, level+1); }
        len = 0;
        arr = pool_get_values("zip_progress", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->progress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->progress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->progress = ptr_save;
        free(arr);
    }
    pool_insert("zip", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip  \n"); fflush(stdout);
    #endif
}
void mutate_zip_source(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_source  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_source* ptr = ptr1;
    {
        if(ptr->src) { mutate_zip_source(ptr->src, level+1); }
        len = 0;
        arr = pool_get_values("zip_source", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->src;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->src = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->src = ptr_save;
        free(arr);
    }
    //ptr->cb = ...(union anonymous {function f; function l; } cb)
        mutate_zip_error(&(ptr->error), level+1);
    mutate_int64_t(&(ptr->supports), level+1);
    mutate_int32_t(&(ptr->open_count), level+1);
    mutate_enum(&(ptr->write_state), 4);
    mutate_int8_t(&(ptr->source_closed), level+1);
    {
        if(ptr->source_archive) { mutate_zip(ptr->source_archive, level+1); }
        len = 0;
        arr = pool_get_values("zip", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->source_archive;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->source_archive = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->source_archive = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->refcount), level+1);
    mutate_int8_t(&(ptr->eof), level+1);
    mutate_int8_t(&(ptr->had_read_error), level+1);
    mutate_int64_t(&(ptr->bytes_read), level+1);
    pool_insert("zip_source", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_source  \n"); fflush(stdout);
    #endif
}
void mutate_zip_compression_algorithm(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_compression_algorithm  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_compression_algorithm* ptr = ptr1;
    //ptr->maximum_compressed_size = ...(function maximum_compressed_size)
    //ptr->allocate = ...(function allocate)
    //ptr->deallocate = ...(function deallocate)
    //ptr->general_purpose_bit_flags = ...(function general_purpose_bit_flags)
    mutate_int8_t(&(ptr->version_needed), level+1);
    //ptr->start = ...(function start)
    //ptr->end = ...(function end)
    //ptr->input = ...(function input)
    //ptr->end_of_input = ...(function end_of_input)
    //ptr->process = ...(function process)
    pool_insert("zip_compression_algorithm", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_compression_algorithm  \n"); fflush(stdout);
    #endif
}
void mutate__zip_err_info(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__zip_err_info  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _zip_err_info* ptr = ptr1;
    mutate_int32_t(&(ptr->type), level+1);
    //ptr->description = ...(const *description)
    pool_insert("_zip_err_info", ptr1);
    #ifdef DEBUG
    printf("leave mutate__zip_err_info  \n"); fflush(stdout);
    #endif
}
void mutate_zip_dirent(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_dirent  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_dirent* ptr = ptr1;
    mutate_int32_t(&(ptr->changed), level+1);
    mutate_int8_t(&(ptr->local_extra_fields_read), level+1);
    mutate_int8_t(&(ptr->cloned), level+1);
    mutate_int8_t(&(ptr->crc_valid), level+1);
    mutate_int16_t(&(ptr->version_madeby), level+1);
    mutate_int16_t(&(ptr->version_needed), level+1);
    mutate_int16_t(&(ptr->bitflags), level+1);
    mutate_int32_t(&(ptr->comp_method), level+1);
    mutate_int64_t(&(ptr->last_mod), level+1);
    mutate_int32_t(&(ptr->crc), level+1);
    mutate_int64_t(&(ptr->comp_size), level+1);
    mutate_int64_t(&(ptr->uncomp_size), level+1);
    {
        if(ptr->filename) { mutate_zip_string(ptr->filename, level+1); }
        len = 0;
        arr = pool_get_values("zip_string", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->filename;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->filename = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->filename = ptr_save;
        free(arr);
    }
    {
        if(ptr->extra_fields) { mutate_zip_extra_field(ptr->extra_fields, level+1); }
        len = 0;
        arr = pool_get_values("zip_extra_field", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->extra_fields;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->extra_fields = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->extra_fields = ptr_save;
        free(arr);
    }
    {
        if(ptr->comment) { mutate_zip_string(ptr->comment, level+1); }
        len = 0;
        arr = pool_get_values("zip_string", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comment;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comment = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comment = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->disk_number), level+1);
    mutate_int16_t(&(ptr->int_attrib), level+1);
    mutate_int32_t(&(ptr->ext_attrib), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    mutate_int16_t(&(ptr->compression_level), level+1);
    mutate_int16_t(&(ptr->encryption_method), level+1);
    mutate_c_str(ptr->password);
    pool_insert("zip_dirent", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_dirent  \n"); fflush(stdout);
    #endif
}
void mutate_zip_entry(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_entry  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_entry* ptr = ptr1;
    {
        if(ptr->orig) { mutate_zip_dirent(ptr->orig, level+1); }
        len = 0;
        arr = pool_get_values("zip_dirent", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->orig;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->orig = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->orig = ptr_save;
        free(arr);
    }
    {
        if(ptr->changes) { mutate_zip_dirent(ptr->changes, level+1); }
        len = 0;
        arr = pool_get_values("zip_dirent", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->changes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->changes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->changes = ptr_save;
        free(arr);
    }
    {
        if(ptr->source) { mutate_zip_source(ptr->source, level+1); }
        len = 0;
        arr = pool_get_values("zip_source", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->source;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->source = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->source = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->deleted), level+1);
    pool_insert("zip_entry", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_entry  \n"); fflush(stdout);
    #endif
}
void mutate_zip_extra_field(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_extra_field  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_extra_field* ptr = ptr1;
    {
        if(ptr->next) { mutate_zip_extra_field(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("zip_extra_field", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->flags), level+1);
    mutate_int16_t(&(ptr->id), level+1);
    mutate_int16_t(&(ptr->size), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    pool_insert("zip_extra_field", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_extra_field  \n"); fflush(stdout);
    #endif
}
void mutate_zip_string(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_string  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_string* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->raw);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->raw, level + 1, len); }
    #else
    //ptr->raw = ...(unsigned char  *raw)
    #endif
    mutate_int16_t(&(ptr->length), level+1);
    mutate_enum(&(ptr->encoding), 6);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->converted);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->converted, level + 1, len); }
    #else
    //ptr->converted = ...(unsigned char  *converted)
    #endif
    mutate_int32_t(&(ptr->converted_length), level+1);
    pool_insert("zip_string", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_string  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_1", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_1  \n"); fflush(stdout);
    #endif
}
void mutate_zip_buffer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_buffer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_buffer* ptr = ptr1;
    mutate_int8_t(&(ptr->ok), level+1);
    mutate_int8_t(&(ptr->free_data), level+1);
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    pool_insert("zip_buffer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_buffer  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_2* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_2", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_2  \n"); fflush(stdout);
    #endif
}
void mutate_zip_filelist(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_filelist  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_filelist* ptr = ptr1;
    mutate_int64_t(&(ptr->idx), level+1);
    pool_insert("zip_filelist", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_filelist  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_3* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    union memfuzz_anonymous_struct_4* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_4", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_4  \n"); fflush(stdout);
    #endif
}
void mutate_zip_cdir(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_cdir  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_cdir* ptr = ptr1;
    {
        if(ptr->entry) { mutate_zip_entry(ptr->entry, level+1); }
        len = 0;
        arr = pool_get_values("zip_entry", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->entry;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->entry = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->entry = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->nentry), level+1);
    mutate_int64_t(&(ptr->nentry_alloc), level+1);
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    {
        if(ptr->comment) { mutate_zip_string(ptr->comment, level+1); }
        len = 0;
        arr = pool_get_values("zip_string", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->comment;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->comment = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->comment = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->is_zip64), level+1);
    pool_insert("zip_cdir", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_cdir  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_5* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_5", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_5  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_6", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_6  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_7  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_7* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_7", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_7  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_8  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_8* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_8", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_8  \n"); fflush(stdout);
    #endif
}
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
    union memfuzz_anonymous_struct_9* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    union memfuzz_anonymous_struct_10* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_10", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_10  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_11* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_11", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_11  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_12* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_12", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_12  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_13* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_13", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_13  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_14", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_14  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_15", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_15  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_16", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_16  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_17", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_17  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    union memfuzz_anonymous_struct_19* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_21", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_21  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_23", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_23  \n"); fflush(stdout);
    #endif
}
void mutate_zip_hash(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_hash  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_hash* ptr = ptr1;
    mutate_int32_t(&(ptr->table_size), level+1);
    mutate_int64_t(&(ptr->nentries), level+1);
    {
        if(ptr->table) { mutate_zip_hash_entry(ptr->table, level+1); }
        len = 0;
        arr = pool_get_values("zip_hash_entry", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->table;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->table = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->table = ptr_save;
        free(arr);
    }
    pool_insert("zip_hash", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_hash  \n"); fflush(stdout);
    #endif
}
void mutate_zip_hash_entry(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_hash_entry  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_hash_entry* ptr = ptr1;
    //ptr->name = ...(const *name)
    mutate_int64_t(&(ptr->orig_index), level+1);
    mutate_int64_t(&(ptr->current_index), level+1);
    {
        if(ptr->next) { mutate_zip_hash_entry(ptr->next, level+1); }
        len = 0;
        arr = pool_get_values("zip_hash_entry", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->next;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->next = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->next = ptr_save;
        free(arr);
    }
    mutate_int32_t(&(ptr->hash_value), level+1);
    pool_insert("zip_hash_entry", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_hash_entry  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_24", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_24  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_25* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_25", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_25  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_26* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_26", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_26  \n"); fflush(stdout);
    #endif
}
void mutate_zip_progress(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_progress  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_progress* ptr = ptr1;
    {
        if(ptr->za) { mutate_zip(ptr->za, level+1); }
        len = 0;
        arr = pool_get_values("zip", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->za;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->za = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->za = ptr_save;
        free(arr);
    }
    //ptr->callback_progress = ...(function callback_progress)
    //ptr->ud_progress_free = ...(function ud_progress_free)
        //ptr->callback_cancel = ...(function callback_cancel)
    //ptr->ud_cancel_free = ...(function ud_cancel_free)
        mutate_double(&(ptr->precision), level+1);
    mutate_double(&(ptr->last_update), level+1);
    mutate_double(&(ptr->start), level+1);
    mutate_double(&(ptr->end), level+1);
    pool_insert("zip_progress", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_progress  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_27* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_27", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_27  \n"); fflush(stdout);
    #endif
}
void mutate_legacy_ud(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_legacy_ud  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct legacy_ud* ptr = ptr1;
    //ptr->callback = ...(function callback)
    pool_insert("legacy_ud", ptr1);
    #ifdef DEBUG
    printf("leave mutate_legacy_ud  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_28* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_28", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_28  \n"); fflush(stdout);
    #endif
}
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    union memfuzz_anonymous_struct_30* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_30", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_30  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_31* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_33", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_33  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_34* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_35", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_35  \n"); fflush(stdout);
    #endif
}
void mutate_zip_buffer_fragment(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_buffer_fragment  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_buffer_fragment* ptr = ptr1;
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->data);
    len /= sizeof(int8_t);
    if(len != 0){ mutate_int8_t_array(ptr->data, level + 1, len); }
    #else
    //ptr->data = ...(unsigned char  *data)
    #endif
    mutate_int64_t(&(ptr->length), level+1);
    pool_insert("zip_buffer_fragment", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_buffer_fragment  \n"); fflush(stdout);
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
    union memfuzz_anonymous_struct_36* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_36", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_36  \n"); fflush(stdout);
    #endif
}
void mutate_buffer(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_buffer  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct buffer* ptr = ptr1;
    {
        if(ptr->fragments) { mutate_zip_buffer_fragment(ptr->fragments, level+1); }
        len = 0;
        arr = pool_get_values("zip_buffer_fragment", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->fragments;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->fragments = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->fragments = ptr_save;
        free(arr);
    }
    #ifdef ALLOC_HOOK
    len = alloc_find(ptr->fragment_offsets);
    len /= sizeof(int64_t);
    if(len != 0){ mutate_int64_t_array(ptr->fragment_offsets, level + 1, len); }
    #else
    //ptr->fragment_offsets = ...(long unsigned int  *fragment_offsets)
    #endif
    mutate_int64_t(&(ptr->nfragments), level+1);
    mutate_int64_t(&(ptr->fragments_capacity), level+1);
    mutate_int64_t(&(ptr->first_owned_fragment), level+1);
    mutate_int64_t(&(ptr->shared_fragments), level+1);
    {
        if(ptr->shared_buffer) { mutate_buffer(ptr->shared_buffer, level+1); }
        len = 0;
        arr = pool_get_values("buffer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->shared_buffer;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->shared_buffer = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->shared_buffer = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    mutate_int64_t(&(ptr->current_fragment), level+1);
    pool_insert("buffer", ptr1);
    #ifdef DEBUG
    printf("leave mutate_buffer  \n"); fflush(stdout);
    #endif
}
void mutate_read_data(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_read_data  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct read_data* ptr = ptr1;
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int64_t(&(ptr->mtime), level+1);
    mutate_zip_file_attributes(&(ptr->attributes), level+1);
    {
        if(ptr->in) { mutate_buffer(ptr->in, level+1); }
        len = 0;
        arr = pool_get_values("buffer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->in;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->in = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->in = ptr_save;
        free(arr);
    }
    {
        if(ptr->out) { mutate_buffer(ptr->out, level+1); }
        len = 0;
        arr = pool_get_values("buffer", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->out;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->out = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->out = ptr_save;
        free(arr);
    }
    pool_insert("read_data", ptr1);
    #ifdef DEBUG
    printf("leave mutate_read_data  \n"); fflush(stdout);
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
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
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_39", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_39  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_40(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_40  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_40* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_40", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_40  \n"); fflush(stdout);
    #endif
}
void mutate_context(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_context  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct context* ptr = ptr1;
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int8_t(&(ptr->end_of_input), level+1);
    mutate_int8_t(&(ptr->end_of_stream), level+1);
    mutate_int8_t(&(ptr->can_store), level+1);
    mutate_int8_t(&(ptr->is_stored), level+1);
    mutate_int8_t(&(ptr->compress), level+1);
    mutate_int32_t(&(ptr->method), level+1);
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->first_read), level+1);
    assign_int8_t_array(&(ptr->buffer), level + 1, 8192);
    {
        if(ptr->algorithm) { mutate_zip_compression_algorithm(ptr->algorithm, level+1); }
        len = 0;
        arr = pool_get_values("zip_compression_algorithm", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->algorithm;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->algorithm = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->algorithm = ptr_save;
        free(arr);
    }
        pool_insert("context", ptr1);
    #ifdef DEBUG
    printf("leave mutate_context  \n"); fflush(stdout);
    #endif
}
void mutate_implementation(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_implementation  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct implementation* ptr = ptr1;
    mutate_int16_t(&(ptr->method), level+1);
    {
        if(ptr->compress) { mutate_zip_compression_algorithm(ptr->compress, level+1); }
        len = 0;
        arr = pool_get_values("zip_compression_algorithm", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->compress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->compress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->compress = ptr_save;
        free(arr);
    }
    {
        if(ptr->decompress) { mutate_zip_compression_algorithm(ptr->decompress, level+1); }
        len = 0;
        arr = pool_get_values("zip_compression_algorithm", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->decompress;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->decompress = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->decompress = ptr_save;
        free(arr);
    }
    pool_insert("implementation", ptr1);
    #ifdef DEBUG
    printf("leave mutate_implementation  \n"); fflush(stdout);
    #endif
}
void mutate_zip_source_args_seek(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_source_args_seek  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_source_args_seek* ptr = ptr1;
    mutate_int64_t(&(ptr->offset), level+1);
    mutate_int32_t(&(ptr->whence), level+1);
    pool_insert("zip_source_args_seek", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_source_args_seek  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_41(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_41  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_41* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_41", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_41  \n"); fflush(stdout);
    #endif
}
void mutate_crc_context(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_crc_context  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct crc_context* ptr = ptr1;
    mutate_int32_t(&(ptr->validate), level+1);
    mutate_int32_t(&(ptr->crc_complete), level+1);
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->position), level+1);
    mutate_int64_t(&(ptr->crc_position), level+1);
    mutate_int32_t(&(ptr->crc), level+1);
    pool_insert("crc_context", ptr1);
    #ifdef DEBUG
    printf("leave mutate_crc_context  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_42(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_42  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_42* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_42", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_42  \n"); fflush(stdout);
    #endif
}
void mutate_timespec(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_43(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_43  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_43* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_43", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_43  \n"); fflush(stdout);
    #endif
}
void mutate_zip_source_file_stat(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_source_file_stat  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_source_file_stat* ptr = ptr1;
    mutate_int64_t(&(ptr->size), level+1);
    mutate_int64_t(&(ptr->mtime), level+1);
    mutate_int8_t(&(ptr->exists), level+1);
    mutate_int8_t(&(ptr->regular_file), level+1);
    pool_insert("zip_source_file_stat", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_source_file_stat  \n"); fflush(stdout);
    #endif
}
void mutate_zip_source_file_context(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_source_file_context  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_source_file_context* ptr = ptr1;
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int64_t(&(ptr->supports), level+1);
    mutate_c_str(ptr->fname);
        mutate_zip_stat(&(ptr->st), level+1);
    mutate_zip_file_attributes(&(ptr->attributes), level+1);
    mutate_zip_error(&(ptr->stat_error), level+1);
    mutate_int64_t(&(ptr->start), level+1);
    mutate_int64_t(&(ptr->len), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    mutate_c_str(ptr->tmpname);
        {
        if(ptr->ops) { mutate_zip_source_file_operations(ptr->ops, level+1); }
        len = 0;
        arr = pool_get_values("zip_source_file_operations", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->ops;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->ops = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->ops = ptr_save;
        free(arr);
    }
        pool_insert("zip_source_file_context", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_source_file_context  \n"); fflush(stdout);
    #endif
}
void mutate_zip_source_file_operations(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_zip_source_file_operations  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct zip_source_file_operations* ptr = ptr1;
    //ptr->close = ...(function close)
    //ptr->commit_write = ...(function commit_write)
    //ptr->create_temp_output = ...(function create_temp_output)
    //ptr->create_temp_output_cloning = ...(function create_temp_output_cloning)
    //ptr->open = ...(function open)
    //ptr->read = ...(function read)
    //ptr->remove = ...(function remove)
    //ptr->rollback_write = ...(function rollback_write)
    //ptr->seek = ...(function seek)
    //ptr->stat = ...(function stat)
    //ptr->string_duplicate = ...(function string_duplicate)
    //ptr->tell = ...(function tell)
    //ptr->write = ...(function write)
    pool_insert("zip_source_file_operations", ptr1);
    #ifdef DEBUG
    printf("leave mutate_zip_source_file_operations  \n"); fflush(stdout);
    #endif
}
void mutate_stat(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_44(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_44  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_44* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_44", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_44  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_45(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_45  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_45* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_45", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_45  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_46(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_46  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_46* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_46", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_46  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_47(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_47  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_47* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_47", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_47  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_48(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_48  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_48* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_48", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_48  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_49(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_49  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_49* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_49", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_49  \n"); fflush(stdout);
    #endif
}
void mutate__zip_pkware_keys(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__zip_pkware_keys  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _zip_pkware_keys* ptr = ptr1;
    assign_int32_t_array(&(ptr->key), level + 1, 3);
    pool_insert("_zip_pkware_keys", ptr1);
    #ifdef DEBUG
    printf("leave mutate__zip_pkware_keys  \n"); fflush(stdout);
    #endif
}
void mutate_trad_pkware(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_trad_pkware  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct trad_pkware* ptr = ptr1;
    mutate_c_str(ptr->password);
    mutate__zip_pkware_keys(&(ptr->keys), level+1);
    mutate_zip_error(&(ptr->error), level+1);
    pool_insert("trad_pkware", ptr1);
    #ifdef DEBUG
    printf("leave mutate_trad_pkware  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_50(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_50  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_50* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_50", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_50  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_51(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_51  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_51* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_51", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_51  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_52(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_52  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_52* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_52", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_52  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_53(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_53  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_53* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_53", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_53  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_54(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_54  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_54* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_54", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_54  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_55(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_55  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_55* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_55", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_55  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_56(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_56  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_56* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_56", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_56  \n"); fflush(stdout);
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
void mutate_memfuzz_anonymous_struct_57(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_57  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_57* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_57", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_57  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_58(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_58  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_58* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_58", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_58  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_59(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_59  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_59* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_59", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_59  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_60(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_60  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_60* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_60", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_60  \n"); fflush(stdout);
    #endif
}
void mutate_window(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_window  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct window* ptr = ptr1;
    mutate_int64_t(&(ptr->start), level+1);
    mutate_int64_t(&(ptr->end), level+1);
    mutate_int8_t(&(ptr->end_valid), level+1);
    {
        if(ptr->source_archive) { mutate_zip(ptr->source_archive, level+1); }
        len = 0;
        arr = pool_get_values("zip", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->source_archive;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->source_archive = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->source_archive = ptr_save;
        free(arr);
    }
    mutate_int64_t(&(ptr->source_index), level+1);
    mutate_int64_t(&(ptr->offset), level+1);
    mutate_zip_stat(&(ptr->stat), level+1);
    mutate_zip_file_attributes(&(ptr->attributes), level+1);
    mutate_zip_error(&(ptr->error), level+1);
    mutate_int64_t(&(ptr->supports), level+1);
    mutate_int8_t(&(ptr->needs_seek), level+1);
    pool_insert("window", ptr1);
    #ifdef DEBUG
    printf("leave mutate_window  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_61(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_61  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_61* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_61", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_61  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_62(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_62  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_62* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_62", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_62  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_63(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_63  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_63* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_63", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_63  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_64(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_64  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_64* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_64", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_64  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_65(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_65  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_65* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_65", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_65  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_66(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_66  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_66* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_66", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_66  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_67(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_67  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_67* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_67", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_67  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_68(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_68  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_68* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_68", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_68  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_69(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_69  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_69* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_69", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_69  \n"); fflush(stdout);
    #endif
}
void mutate_file_clone_range(void* ptr1, int level){return ;}
void mutate_memfuzz_anonymous_struct_70(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_70  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_70* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_70", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_70  \n"); fflush(stdout);
    #endif
}
void mutate_winzip_aes(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_winzip_aes  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct winzip_aes* ptr = ptr1;
    mutate_c_str(ptr->password);
    mutate_int16_t(&(ptr->encryption_method), level+1);
    mutate_int64_t(&(ptr->data_length), level+1);
    mutate_int64_t(&(ptr->current_position), level+1);
    {
        if(ptr->aes_ctx) { mutate__zip_winzip_aes(ptr->aes_ctx, level+1); }
        len = 0;
        arr = pool_get_values("_zip_winzip_aes", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->aes_ctx;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->aes_ctx = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->aes_ctx = ptr_save;
        free(arr);
    }
    mutate_zip_error(&(ptr->error), level+1);
    pool_insert("winzip_aes", ptr1);
    #ifdef DEBUG
    printf("leave mutate_winzip_aes  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_71(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_71  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_71* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_71", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_71  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_72(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_72  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_72* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_72", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_72  \n"); fflush(stdout);
    #endif
}
void mutate_z_stream_s(void* ptr1, int level){return ;}
void mutate_ctx(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_ctx  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct ctx* ptr = ptr1;
    {
        if(ptr->error) { mutate_zip_error(ptr->error, level+1); }
        len = 0;
        arr = pool_get_values("zip_error", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->error;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->error = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->error = ptr_save;
        free(arr);
    }
    mutate_int8_t(&(ptr->compress), level+1);
    mutate_int32_t(&(ptr->compression_flags), level+1);
    mutate_int8_t(&(ptr->end_of_input), level+1);
    mutate_z_stream_s(&(ptr->zstr), level+1);
    pool_insert("ctx", ptr1);
    #ifdef DEBUG
    printf("leave mutate_ctx  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_73(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_73  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_73* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_73", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_73  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_74(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_74  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_74* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_74", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_74  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_75(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_75  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_75* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_75", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_75  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_76(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_76  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_76* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_76", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_76  \n"); fflush(stdout);
    #endif
}
void mutate_memfuzz_anonymous_struct_77(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate_memfuzz_anonymous_struct_77  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    union memfuzz_anonymous_struct_77* ptr = ptr1;
    //ptr->f = ...(function f)
    //ptr->l = ...(function l)
    pool_insert("memfuzz_anonymous_struct_77", ptr1);
    #ifdef DEBUG
    printf("leave mutate_memfuzz_anonymous_struct_77  \n"); fflush(stdout);
    #endif
}
void mutate__zip_winzip_aes(void* ptr1, int level){
    if(level > MAX_LEVEL) return ;
    if(ptr1 == NULL || alloc_find(ptr1) == 0) return ;
    #ifdef DEBUG
    printf("enter mutate__zip_winzip_aes  \n"); fflush(stdout);
    #endif
    if(dup_is_in(ptr1)) return ;
    dup_insert(ptr1);
    int i, len;
    void** arr;
    void* ptr_save = NULL;
    struct _zip_winzip_aes* ptr = ptr1;
    {
        if(ptr->aes) { mutate_evp_cipher_ctx_st(ptr->aes, level+1); }
        len = 0;
        arr = pool_get_values("evp_cipher_ctx_st", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->aes;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->aes = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->aes = ptr_save;
        free(arr);
    }
    {
        if(ptr->hmac) { mutate_hmac_ctx_st(ptr->hmac, level+1); }
        len = 0;
        arr = pool_get_values("hmac_ctx_st", &len);
        shuffle(arr, len, sizeof(void*));
        ptr_save = ptr->hmac;
        for(i = 0; i < len && i < SAMPLE_TIMES; i++){
            ptr->hmac = arr[i];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr->hmac = ptr_save;
        free(arr);
    }
    assign_int8_t_array(&(ptr->counter), level + 1, 16);
    assign_int8_t_array(&(ptr->pad), level + 1, 16);
    mutate_int32_t(&(ptr->pad_offset), level+1);
    pool_insert("_zip_winzip_aes", ptr1);
    #ifdef DEBUG
    printf("leave mutate__zip_winzip_aes  \n"); fflush(stdout);
    #endif
}
void mutate_internal_state(void* ptr1, int level){return ;}
void mutate_evp_cipher_ctx_st(void* ptr1, int level){return ;}
void mutate_hmac_ctx_st(void* ptr1, int level){return ;}
