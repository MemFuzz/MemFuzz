#ifndef MEMFUZZ_MUTATE_H_
#define MEMFUZZ_MUTATE_H_
void mutate__IO_FILE(void* ptr1, int level, int check);
void mutate__IO_marker(void* ptr1, int level, int check);
void mutate_timespec(void* ptr1, int level, int check);
void mutate_stat(void* ptr1, int level, int check);
void mutate_tm(void* ptr1, int level, int check);
void mutate_mz_stream_s(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_0(void* ptr1, int level, int check);
void mutate_tinfl_decompressor_tag(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_1(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_2(void* ptr1, int level, int check);
void mutate_mz_zip_internal_state_tag(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_3(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_4(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_5(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_6(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_7(void* ptr1, int level, int check);
void mutate_utimbuf(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_8(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_9(void* ptr1, int level, int check);
void mutate_zip_entry_t(void* ptr1, int level, int check);
void mutate_zip_t(void* ptr1, int level, int check);
void mutate_zip_entry_mark_t(void* ptr1, int level, int check);
void mutate_memfuzz_anonymous_struct_10(void* ptr1, int level, int check);
void mutate_mz_internal_state(void* ptr1, int level, int check);
#endif
