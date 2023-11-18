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
extern unsigned char* a_file;
extern jmp_buf memfuzz_jmp_buf;
void mutate_enum(void* ptr, int num);//We may not use it, use mutate_int instead
//0 greet
//1 AFL ask for more mutants
//2 stop the current mutation and start mutating a new file
int receive_ctl();
//send 0 to greet AFL
void greet_AFL();
void send_msg(int msg);
//send a file to AFL, if len == 0, no more files to send
//send and receive files via shared memory
void send_file(unsigned len, const unsigned char* buf);
void receive_file(unsigned *len, unsigned char* buf);
void setup_shm(void) ;
void safe_mutate(void*ptr, int level, void (*mutate)(void*ptr, int level));
void safe_print(const char* outfile);
void memfuzz_init();
void init_forkserver();

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
void assign_double(void* ptr, int level);
void assign_float(void* ptr, int level);
void assign_int8_t(void* ptr, int level);
void assign_int16_t(void* ptr, int level);
void assign_int32_t(void* ptr, int level);
void assign_int64_t(void* ptr, int level);
void mutate_enum(void* ptr, int num);
//mutate array
void assign_double_array(void* ptr, int level, int elems);
void assign_float_array(void* ptr, int level, int elems);
void assign_int8_t_array(void* ptr, int level, int elems);
void assign_int16_t_array(void* ptr, int level, int elems);
void assign_int32_t_array(void* ptr, int level, int elems);
void assign_int64_t_array(void* ptr, int level, int elems);
#endif
