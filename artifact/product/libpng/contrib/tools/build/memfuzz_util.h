#ifndef _MEMFUZZ_UTIL_
#define _MEMFUZZ_UTIL_
#include <unistd.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <signal.h>
#include <stdint.h>
#include <time.h>
extern jmp_buf memfuzz_jmp_buf;

void safe_print(const char* outfile);
void memfuzz_init();
void memfuzz_init_test(void);

/*Mutation of basic type*/
#define Int8_NUM 9
#define Int16_NUM 19
#define Int32_NUM 27
#define Int64_NUM 28
#define Float_NUM 8
#define Double_NUM 8
extern int8_t Int8[Int8_NUM];
extern int16_t Int16[Int16_NUM];
extern int32_t Int32[Int32_NUM];
extern int64_t Int64[Int64_NUM];
extern double Double[Double_NUM];
extern float Float[Float_NUM];


//mutate single value
void mutate_double(void* ptr, int level);
void mutate_float(void* ptr, int level);
void mutate_int8_t(void* ptr, int level);
void mutate_int16_t(void* ptr, int level);
void mutate_int32_t(void* ptr, int level);
void mutate_int64_t(void* ptr, int level);
void mutate_enum(void* ptr, int num);
void mutate_enum_with_values(void* ptr, int num, int *values);
/*Interesting values*/
void assign_double(void* ptr, int level);
void assign_float(void* ptr, int level);
void assign_int8_t(void* ptr, int level);
void assign_int16_t(void* ptr, int level);
void assign_int32_t(void* ptr, int level);
void assign_int64_t(void* ptr, int level);
// /*Determine*/
void determine_int8_t(void* ptr, int level);
void determine_int16_t(void* ptr, int level);
void determine_int32_t(void* ptr, int level);
void determine_int64_t(void* ptr, int level);
/*Random*/
void random_int(void* ptr, int level);
/*String*/
#define mutate_c_str(ptr) {ptr_save = ptr; len = 0; arr = pool_get_values("memfuzz_str", &len); shuffle(arr, len, sizeof(char*)); for(i = 0; i < len && i < SAMPLE_TIMES; i++){ptr = arr[i]; safe_print(MEMFUZZ_OUTFILE); } ptr = ptr_save; free(arr); pool_insert("memfuzz_str", ptr);}
/*Shuffle*/
void shuffle(void *array, size_t n, size_t size);


//mutate array
void mutate_double_array(void* ptr, int level, int elems);
void mutate_float_array(void* ptr, int level, int elems);
void mutate_int8_t_array(void* ptr, int level, int elems);
void mutate_int16_t_array(void* ptr, int level, int elems);
void mutate_int32_t_array(void* ptr, int level, int elems);
void mutate_int64_t_array(void* ptr, int level, int elems);
void assign_double_array(void* ptr, int level, int elems);
void assign_float_array(void* ptr, int level, int elems);
void assign_int8_t_array(void* ptr, int level, int elems);
void assign_int16_t_array(void* ptr, int level, int elems);
void assign_int32_t_array(void* ptr, int level, int elems);
void assign_int64_t_array(void* ptr, int level, int elems);

//test function to see if our mutation crashes the program
void assign_double_test(void* ptr, int level);
void assign_float_test(void* ptr, int level);
void assign_int8_t_test(void* ptr, int level);
void assign_int16_t_test(void* ptr, int level);
void assign_int32_t_test(void* ptr, int level);
void assign_int64_t_test(void* ptr, int level);
void mutate_enum_test(void* ptr, int num);
void assign_double_array_test(void* ptr, int level, int elems);
void assign_float_array_test(void* ptr, int level, int elems);
void assign_int8_t_array_test(void* ptr, int level, int elems);
void assign_int16_t_array_test(void* ptr, int level, int elems);
void assign_int32_t_array_test(void* ptr, int level, int elems);
void assign_int64_t_array_test(void* ptr, int level, int elems);
void mutate_enum_with_values_test(void* ptr, int num, int *values);
#endif
