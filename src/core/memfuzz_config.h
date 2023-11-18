//Config file for memfuzz
#ifndef _MEMFUZZ_CONFIG_
#define _MEMFUZZ_CONFIG_
#define MAX_LEVEL 15 //max recursion level for mutate
#define MAX_FORK MAX_LEVEL+2
#define SAMPLE_TIMES 10 //max sample time for array
#define FILE_LENGTH_MAX 1<<22 //max file length, it should be the same with that in AFL
#define GENERATOR_FD 200  //fd for AFL to send to generator
#define GEN_CTL_FD 200  //fd for AFL to send to generator
#define GEN_ST_FD 201 //fd for generator to send to AFL
#define TYPE_FD 202 //fd for memfuzz child to send type message to root
#define MEMFUZZ_OUTFILE ".memfuzz_out.jp2"//the output file of memfuzz
#define MEMFUZZ_INFILE ".memfuzz_in.jp2" //the input file of memfuzz
#define SHM_ENV_VAR_GENERATOR "SHM_ENV_VAR_GENERATOR"
// #define DEBUG 1
#endif
