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
//0 greet
//1 AFL ask for more mutants
//2 stop the current mutation and start mutating a new file
static int receive_ctl();
//send 0 to greet AFL
static void greet_AFL();
static void send_msg(int msg);
//send a file to AFL, if len == 0, no more files to send
//send and receive files via shared memory
static void send_file(unsigned len, const unsigned char* buf);
static void receive_file(unsigned *len, unsigned char* buf);
static void setup_shm(void) ;
static void safe_mutate(void*ptr, int level, void (*mutate)(void*ptr, int level));
void safe_print(const char* outfile);
static void init_forkserver();
static void cleanup(void);
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
void mutate_c_str(void* ptr, int level);
/*Shuffle*/
static void shuffle(void *array, size_t n, size_t size);


//mutate array
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
