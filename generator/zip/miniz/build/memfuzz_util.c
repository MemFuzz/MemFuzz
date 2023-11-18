#include "memfuzz_util.h"
#include "memfuzz_config.h"

#define debug(...) if(memfuzz_status_fp) {fprintf(memfuzz_status_fp, __VA_ARGS__); fflush(memfuzz_status_fp);}
#define err(...) if(memfuzz_status_fp) {fprintf(memfuzz_status_fp, __VA_ARGS__); fflush(memfuzz_status_fp);}

/*Statistical*/
//It is a shared memory so that every process can write data to it.
typedef struct MemStats_
{
    unsigned long fork_times;//The times we call fork function
    unsigned long succ_times;//Successfully generate a file
    unsigned long crash_times;//Crash captured by safe_print 
    unsigned long guard_times;//Crash captured by safe_mutate
    unsigned long tmout_times;//Time out 
} MemStats;
/*Statistical*/

/*Global Variables*/
jmp_buf memfuzz_jmp_buf; //used in target program for jumping out of mutation function
static unsigned char* a_file; // shared memory pointer for communicating with AFL
static FILE* memfuzz_status_fp;  //record the status for memfuzz, used for debugging
static pid_t child_pid; //pid for children
static MemStats *memfuzz_stats; //shm for stats
static int memfuzz_stats_shm_id; //id for stats shm

static int fork_depth;//The current fork depth
static int child_timeout;//True if child timeout
static int timeout = 1000;//Set timer for safe_print
/*Global Variables*/

/*Interesting Values*/
int8_t Int8[] = {-128, -1, 0, 1, 16, 32, 64, 100, 127};
int16_t Int16[] = {1024, 4096, 16, 32, -128, -129, 32767, 1, 0, -1, 1000, 127, 128, 64, 100, 512, 256, -32768, 255};
int32_t Int32[] = {100663045, 32768, 32767, 64, 65535, 65536, 256, 255, -2147483648, 1, 0, 4096, -128, -129, 2147483647, 127, 128, 100, -100663046, 1024, 16, 32, -1, 512, -32769, -32768, 1000};
int64_t Int64[] = {100663045, 32768, 32767, 64, 65535, 65536, 256, 255, -2147483648, 1, 0, 4096, -128, -129, (int64_t)9223372036854775808ULL, 2147483647, 127, 128, 100, -100663046, 1024, 16, 32, -1, 512, -32769, -32768, 1000};
double Double[] = {0.00001, 0.0000000001, 2147483647.0, 0.0, 0.1, 1.0, -0.1, -1.0};
float Float[] = {0.00001, 0.0000000001, 2147483647.0, 0.0, 0.1, 1.0, -0.1, -1.0};
/*Interesting Values*/

/*Static function prototypes*/
//0 greet
//1 AFL ask for more mutants
//2 stop the current mutation and start mutating a new file
// static int receive_ctl();
//send 0 to greet AFL
static void greet_AFL();
static void send_msg(int msg);
//send a file to AFL, if len == 0, no more files to send
//send and receive files via shared memory
static void send_file(unsigned len, const unsigned char* buf);
static void receive_file(unsigned *len, unsigned char* buf);
// static void setup_shm(void) ;
static void safe_mutate(void*ptr, int level, void (*mutate)(void*ptr, int level));
static void init_forkserver();
static void cleanup(void);
/*Static function prototypes*/


/*Basic Mutating Functions for Leaf Node*/
void mutate_enum(void* ptr1, int num)
{
    int* ptr = ptr1;
    int val = *ptr;
    for(int i = 0; i < num; i++)
    {
        *ptr = i;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void mutate_enum_with_values(void* ptr1, int num, int *values)
{
    int* ptr = ptr1;
    int val = *ptr;
    for(int i = 0; i < num; i++)
    {
        *ptr = values[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void mutate_double(void* ptr, int level)
{
    assign_double(ptr, level);
}

void mutate_double_array(void* ptr, int level, int elems)
{
    assign_double_array(ptr, level, elems);
}

void mutate_float(void* ptr, int level)
{
    assign_float(ptr, level);
}

void mutate_float_array(void* ptr, int level, int elems)
{
    assign_float_array(ptr, level, elems);
}

void mutate_int8_t(void* ptr, int level)
{
    assign_int8_t(ptr, level);
    determine_int8_t(ptr, level);
    random_int(ptr, level);
}

void mutate_int8_t_array(void* ptr, int level, int elems)
{
    assign_int8_t_array(ptr, level, elems);
}

void mutate_int16_t(void* ptr, int level)
{
    assign_int16_t(ptr, level);
    determine_int16_t(ptr, level);
    random_int(ptr, level);
}

void mutate_int16_t_array(void* ptr, int level, int elems)
{
    assign_int16_t_array(ptr, level, elems);
}

void mutate_int32_t(void* ptr, int level)
{
    assign_int32_t(ptr, level);
    determine_int32_t(ptr, level);
    random_int(ptr, level);
}

void mutate_int32_t_array(void* ptr, int level, int elems)
{
    assign_int32_t_array(ptr, level, elems);
}

void mutate_int64_t(void* ptr, int level)
{
    assign_int64_t(ptr, level);
    determine_int64_t(ptr, level);
    random_int(ptr, level);
}

void mutate_int64_t_array(void* ptr, int level, int elems)
{
    assign_int64_t_array(ptr, level, elems);
}

/*Interesting values*/
void assign_double_array(void* ptr1, int level, int elems)
{
    double* ptr = ptr1;
    double val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Double_NUM; j++)
        {
            ptr[pos] = Double[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
}

void assign_double(void* ptr1, int level)
{
    double* ptr = (double*) ptr1;
    double val = *ptr;
    for(int i = 0; i < Double_NUM; i++)
    {
        *ptr = Double[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    //restore the original value
    *ptr = val;
}

void assign_int32_t_array(void* ptr1, int level, int elems)
{
    int32_t* ptr = ptr1;
    int32_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int32_NUM; j++)
        {
            ptr[pos] = Int32[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
    
}

void assign_int32_t(void* ptr1, int level)
{
    int32_t* ptr = (int32_t*)ptr1;
    int32_t val = *ptr;
    for(int i = 0; i < Int32_NUM; i++)
    {
        *ptr = Int32[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}


void assign_float_array(void* ptr1, int level, int elems)
{
    float* ptr = ptr1;
    float val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Float_NUM; j++)
        {
            ptr[pos] = Float[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
}

void assign_float(void* ptr1, int level)
{
    float* ptr = (float*) ptr1;
    float val = *ptr;
    for(int i = 0; i < Float_NUM; i++)
    {
        *ptr = Float[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void assign_int8_t_array(void* ptr1, int level, int elems)
{
    int8_t* ptr = ptr1;
    int8_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int8_NUM; j++)
        {
            ptr[pos] = Int8[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
}

void assign_int8_t(void* ptr1, int level)
{
    int8_t *ptr = (int8_t*) ptr1;
    int8_t val = *ptr;
    for(int i = 0; i < Int8_NUM; i++)
    {
        *ptr = Int8[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void assign_int16_t_array(void* ptr1, int level, int elems)
{
    int16_t* ptr = ptr1;
    int16_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int16_NUM; j++)
        {
            ptr[pos] = Int16[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
}

void assign_int16_t(void* ptr1, int level)
{
    int16_t *ptr = (int16_t*)ptr1;
    int16_t val = *ptr;
    for(int i = 0; i < Int16_NUM; i++)
    {
        *ptr = Int16[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void assign_int64_t_array(void* ptr1, int level, int elems)
{
    int64_t* ptr = ptr1;
    int64_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int64_NUM; j++)
        {
            ptr[pos] = Int64[j];
            safe_print(MEMFUZZ_OUTFILE);
        }
        ptr[pos] = val;
    }
}

void assign_int64_t(void* ptr1, int level)
{
    int64_t *ptr = (int64_t*) ptr1;
    int64_t val = *ptr;
    for(int i = 0; i < Int64_NUM; i++)
    {
        *ptr = Int64[i];
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}


//determine
void determine_int8_t(void* ptr1, int level)
{
    int8_t *ptr = (int8_t*) ptr1;
    int8_t val = *ptr;
    int op_num = 4;
    for(int i = 0; i < op_num; i++)
    {
        *ptr <<= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr >>= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr += 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr -= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void determine_int16_t(void* ptr1, int level)
{
    int16_t *ptr = (int16_t*) ptr1;
    int16_t val = *ptr;
    int op_num = 8;
    for(int i = 0; i < op_num; i++)
    {
        *ptr <<= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr >>= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr += 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr -= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}


void determine_int32_t(void* ptr1, int level)
{
    int32_t *ptr = (int32_t*) ptr1;
    int32_t val = *ptr;
    int op_num = 16;
    for(int i = 0; i < op_num; i++)
    {
        *ptr <<= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr >>= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr += 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr -= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void determine_int64_t(void* ptr1, int level)
{
    int64_t *ptr = (int64_t*) ptr1;
    int64_t val = *ptr;
    int op_num = 32;
    for(int i = 0; i < op_num; i++)
    {
        *ptr += 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
    for(int i = 0; i < op_num; i++)
    {
        *ptr -= 1;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

//random 
void random_int(void* ptr1, int level)
{
    int8_t *ptr = (int8_t*) ptr1;
    int8_t val = *ptr;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        *ptr = random() % 256;
        safe_print(MEMFUZZ_OUTFILE);
    }
    *ptr = val;
}

void shuffle(void *array, size_t n, size_t size) {
    char tmp[size];
    char *arr = array;
    size_t stride = size * sizeof(char);

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; ++i) {
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);
            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}

char* gen_random_str(int length)
{
    char* ret = malloc(length + 1);
    for(int i = 0; i < length; i++)
    {
        ret[i] = rand() % 95 + 32;
    }
    return ret;
}

void* gen_array_copy(void* arr, size_t n, size_t size)
{
    if(arr == NULL)
        return NULL;
    size_t new_size = n * size;
    void* cp = malloc(new_size);
    memcpy(cp, arr, new_size);
    return cp;
}

void* gen_array_increase(void* arr, size_t n0, size_t size, size_t n1)
{
    if(arr == NULL)
        return NULL;
    size_t num_of_bytes = n1 * size;
    void* res = malloc(num_of_bytes);
    memset(res, 0, num_of_bytes);
    memcpy(res, arr, n0 * size);
    // Append random data chosen from the old one
    for(int i = n0; i < n1; i++)
    {
        int idx = rand() % n0;
        memcpy(res + i * size, arr + idx * size, size);
    }
    return res;
}
/*Basic Mutating Functions for Leaf Node*/












/*Communication with AFL*/
//0 greet
//1 AFL ask for more mutants
//2 stop the current mutation and start mutating a new file
int receive_msg()
{
    int flag;
    read(GEN_CTL_FD, &flag, 4);
    return flag;
}

//send 0 to greet AFL so that AFL knows we are active
void greet_AFL()
{
    int flag = 0;
    write(GEN_ST_FD, &flag, 4);
}

void send_msg(int msg)
{
    write(GEN_ST_FD, &msg, 4);
}

//send a file to AFL, if len == 0, no more files to send
//send and receive files via shared memory
//if len > FILE_LENGTH_MAX, we truncate the len to FILE_LENGTH_MAX
void send_file(unsigned len, const unsigned char* buf)
{
    if(len > FILE_LENGTH_MAX)
    {
        //write(GEN_ST_FD, &len, 4);
        //return ;
        len = FILE_LENGTH_MAX;
    }
    if(len > 0)
        memcpy(a_file, buf, len);
    write(GEN_ST_FD, &len, 4);
}

//if len > FILE_LENGTH_MAX, we truncate the len to FILE_LENGTH_MAX
void receive_file(unsigned *len, unsigned char* buf)
{
    if(read(GEN_CTL_FD, len, 4) != 4)
    {
        printf("read error in receive_file()\n");
        exit(1);
    }
    if(*len >= FILE_LENGTH_MAX)
    {
        //return ;
        *len = FILE_LENGTH_MAX;
    }
    memcpy(buf, a_file, *len);
}

//Not in use, I think using a shared memory for probing is better
static void wait_msg(int fd)
{
    int msg;
    while(1)
    {
        if (read(fd, &msg, 4) != 4)
            break;
        //TODO: type feedback
    }
    close(fd);
}
/*Communication with AFL*/









/*MemFuzz Core Function*/
//dump stats information
void dump_MemStats(void)
{   
    if(!memfuzz_stats)
        return ;
    FILE* fp = fopen("/tmp/memfuzz_stats", "w");
    fprintf(fp, "fork_times: %ld\n", memfuzz_stats->fork_times);
    fprintf(fp, "crash_times: %ld\n", memfuzz_stats->crash_times);
    fprintf(fp, "guard_times: %ld\n", memfuzz_stats->guard_times);
    fprintf(fp, "succ_times: %ld\n", memfuzz_stats->succ_times);
    fprintf(fp, "tmout_times: %ld\n", memfuzz_stats->tmout_times);
    fclose(fp);
}

//should not be invoked in atexit. fork + atexit cause problems
static void remove_stats_shm(void)
{
    if(memfuzz_stats_shm_id && memfuzz_stats)
    {
        shmdt(memfuzz_stats);
        shmctl(memfuzz_stats_shm_id, IPC_RMID, NULL);
        memfuzz_stats_shm_id = 0;
    }
}

//recursively kill all child process, in the leaf process, clean up shm
static void sigint_handler(int sig)
{
    //kill all descestors
    if(child_pid)
        kill(child_pid, SIGINT);
    //do clean up
    // if(fork_depth == 0)
    // {
    //     dump_MemStats();
    //     remove_stats_shm();
    // }
    exit(sig);
}

static void sigsegv_handler(int sig)
{
    FILE* fp = fopen("Memfuzz.log", "w");
    fprintf(fp, "It seems the generator crashes. OOM?\n");
    fclose(fp);
}

static void sigalrm_handler(int sig)
{
    if (child_pid > 0) 
    {
        child_timeout = 1; 
        kill(child_pid, SIGINT);
    }
}

//setup the shm for stats
//The shm needs to be closed when exiting
static void setup_stats_shm(void)
{
    memfuzz_stats_shm_id = shmget(IPC_PRIVATE, FILE_LENGTH_MAX, IPC_CREAT | IPC_EXCL | 0600);
    if(memfuzz_stats_shm_id < 0)
    {
        err("stats shm id failed\n");
        exit(1);
    }
    memfuzz_stats = (MemStats*)shmat(memfuzz_stats_shm_id, NULL, 0);
    if(!memfuzz_stats)
    {
        err("stats shmat failed\n");
        exit(1);
    }
    memset(memfuzz_stats, 0, sizeof(MemStats));
}

//shm for communicating with AFL, we do not close it in MemFuzz but in AFL
void setup_AFL_shm(void) 
{
    char* shm_str = getenv(SHM_ENV_VAR_GENERATOR);
    //fprintf(memfuzz_status_fp, "shm_id is %s\n", shm_str);
    if(shm_str == NULL)
    {
        exit(1);
    }
    int shm_id = atoi(shm_str);
    if(shm_id < 0)
    {
        exit(1);
    }
    a_file = (unsigned char*)shmat(shm_id, NULL, 0);
    if(!a_file)
    {
        exit(1);
    }
}

//Not in use anymore as we turn to malloc_hook
//guard some dangerous mutation operation, such as access array
void safe_mutate(void* ptr, int level, void (*mutate)(void*ptr, int level))
{
    pid_t pid = fork();
    int status;
    if(pid < 0)
    {
        err("fork() failed in safe_mutate(), continue mutate anyway...\n");
        child_pid = 0;
        (mutate)(ptr, level);
    }
    else if(pid > 0)
    {
        memfuzz_stats->fork_times++;
        child_pid = pid;
        if(waitpid(pid, &status, 0) < 0)
        {
            exit(1);
        }
        //killed by signal
        if(WIFSIGNALED(status))
        {
            //we should also tell if it is killed by sigalarm
            memfuzz_stats->guard_times++;
        }
        return ;
    }
    else
    {
        child_pid = 0;
        fork_depth++;
        (mutate)(ptr, level);
    }
}

#ifdef MEMFUZZ_DEBUG
void safe_print(const char* outfile)
{
    static struct itimerval it;
    child_timeout = 0;
    pid_t pid = fork();
    int status;
    if(pid < 0)
    {
        err("fork() failed in safe_print(), continue print anyway...\n");
        child_pid = 0;
        return ;
    }
    // in the parent process, we send the file to afl
    else if(pid > 0)
    {
        memfuzz_stats->fork_times++;
        child_pid = pid;

        it.it_value.tv_sec = (timeout / 1000);
        it.it_value.tv_usec = (timeout % 1000) * 1000;
        setitimer(ITIMER_REAL, &it, NULL);

        //TODO: add alarm here to avoid hang
        if(waitpid(pid, &status, 0) < 0)
        {
            exit(1);
        }

        it.it_value.tv_sec = 0;
        it.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &it, NULL);

        child_pid = 0;
        
        //abnormal exit, killed by signal
        if(WIFSIGNALED(status))
        {
            //we should tell if it is timeout
            if (child_timeout && WTERMSIG(status) == SIGINT)
            {
                memfuzz_stats->tmout_times++;
                return ;
            }
            //killed by other signal
            memfuzz_stats->crash_times++;
            return ;
        }
        //normal exit
        FILE* fp = fopen(outfile, "rb");
        if(fp == NULL)
        {
            return ;
        }
        fseek(fp, 0, SEEK_END);
        size_t length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        unsigned char* buf = malloc(length);
        fread(buf, 1, length, fp);
        fclose(fp);
        //Sending file with 0 length means we reach mutation limitation, so we should not send this file
        if(length == 0)
        {
            return ;
        }
        memfuzz_stats->succ_times++;//inc success time
        free(buf);
        //something wrong, exit and kill all process
        return ;
    }
    // in the child process, we jump to the print function
    else
    {
        child_pid = 0;
        fork_depth++;
        //set an alarm here to end the process
        longjmp(memfuzz_jmp_buf, 1);
    }
}
#else
//make sure print function does not result in crash of the entire program
void safe_print(const char* outfile)
{
    static struct itimerval it;
    child_timeout = 0;
    pid_t pid = fork();
    int status;
    if(pid < 0)
    {
        err("fork() failed in safe_print(), continue print anyway...\n");
        child_pid = 0;
        return ;
    }
    // in the parent process, we send the file to afl
    else if(pid > 0)
    {
        memfuzz_stats->fork_times++;
        child_pid = pid;

        it.it_value.tv_sec = (timeout / 1000);
        it.it_value.tv_usec = (timeout % 1000) * 1000;
        setitimer(ITIMER_REAL, &it, NULL);

        //TODO: add alarm here to avoid hang
        if(waitpid(pid, &status, 0) < 0)
        {
            exit(1);
        }

        it.it_value.tv_sec = 0;
        it.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &it, NULL);

        child_pid = 0;
        
        //abnormal exit, killed by signal
        if(WIFSIGNALED(status))
        {
            //we should tell if it is timeout
            if (child_timeout && WTERMSIG(status) == SIGINT)
            {
                memfuzz_stats->tmout_times++;
                return ;
            }
            //killed by other signal
            memfuzz_stats->crash_times++;
            return ;
        }
        //normal exit
        FILE* fp = fopen(outfile, "rb");
        if(fp == NULL)
        {
            return ;
        }
        fseek(fp, 0, SEEK_END);
        size_t length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        unsigned char* buf = malloc(length);
        fread(buf, 1, length, fp);
        fclose(fp);
        //Sending file with 0 length means we reach mutation limitation, so we should not send this file
        if(length == 0)
        {
            return ;
        }
        int msg = receive_msg();
        if(msg != 1)// a read here is necessary since we should prevent executing before the next AFL read
        {
            //fprintf(memfuzz_status_fp, "safe_print receive msg(%d) != 1\n", msg);
        }
        memfuzz_stats->succ_times++;//inc success time
        send_file(length, buf);
        free(buf);
        
        //something wrong, exit and kill all process
        return ;
    }
    // in the child process, we jump to the print function
    else
    {
        child_pid = 0;
        fork_depth++;
        //set an alarm here to end the process
        longjmp(memfuzz_jmp_buf, 1);
    }
}
#endif

#ifdef MEMFUZZ_DEBUG
void init_forkserver()
{
    return ;
}
#else
void init_forkserver()
{
    //tell afl we are alive
    greet_AFL();
    pid_t pid;
    int status;
    int ctrl_message;
    int t_fd[2];
    int cnt = 0;
    while(1)
    {   
        cnt += 1;
        //if it is the first time, it is used for greet AFL
        //otherwise, it is for sending an empty file to AFL and notify AFL we are done with an input
        ctrl_message = receive_msg();
        //fprintf(memfuzz_status_fp, "Ctrl %d received in init_forkserver()\n", ctrl_message);
        if(ctrl_message != 2)
        {
            //fprintf(memfuzz_status_fp, "init_forkserver(): Unknown message from AFL!\n");
            exit(1);
        }
        unsigned len;
        //write the file to disk
        receive_file(&len, a_file);
        FILE* fp = fopen(MEMFUZZ_INFILE, "wb");
        fwrite(a_file, 1, len, fp);
        fclose(fp);
        //notify AFL that we receive the file
        send_msg(0);
        if(pipe(t_fd) || dup2(t_fd[1], TYPE_FD) < 0)
        {
            printf("pipe() or dup2() failed\n");
            exit(2);
        }
        close(t_fd[1]);
        // fflush(memfuzz_status_fp);
        pid = fork();
        if(pid < 0)
        {
            // fprintf(memfuzz_status_fp, "init_forkserver() fork failed!\n");
            exit(1);
        }
        //child
        if (pid == 0)
        {
            child_pid = 0;
            fork_depth++;
            return ; //continue to execute the original main function
        }
        //parent
        else
        {
            child_pid = pid;
            //wait_msg(t_fd[0]); //TODO: some pipe problem in this line, fix it
            if(waitpid(pid, &status, 0) < 0)
            {
                printf("waitpid() failed\n");
                exit(3);
            }
            //receive the last ctrl message and then notify AFL the file mutation is done
            int msg = receive_msg();
            if(msg != 1)
            {
                //fprintf(memfuzz_status_fp, "init_forkserver() receive ctl(%d) != 1\n", msg);
            }
            send_msg(0);
        }
    }
}
#endif

void setup_signal(void)
{
    struct sigaction sa;
    sa.sa_handler = NULL;
    sa.sa_flags = SA_RESTART;
    sa.sa_sigaction = NULL;

    sigemptyset(&sa.sa_mask);

    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sa.sa_handler = sigalrm_handler;
    sigaction(SIGALRM, &sa, NULL);
}

void memfuzz_init(void)
{
    srandom(time(NULL));
    srand(time(NULL));
    memfuzz_status_fp = fopen(MEMFUZZ_STATS_FILE, "w");
    #ifndef MEMFUZZ_DEBUG
        setup_AFL_shm();// Setup shared memory for communicating with AFL
    #endif
    setup_stats_shm();// Setup shared memory for stats
    //fprintf(memfuzz_status_fp, "setup_AFL_shm() done!\n");
    setup_signal();
    atexit(cleanup);
    //fprintf(memfuzz_status_fp, "setup_signal() done!\n");
    init_forkserver();
}

void cleanup(void)
{
    if(fork_depth == 0)
    {
        dump_MemStats();
        remove_stats_shm();
    }
}

/*MemFuzz Core Function*/


































//debug version, without AFL
/*
void init_forkserver()
{
    //tell afl we are alive
    pid_t pid;
    int status;
    int ctrl_message;
    int t_fd[2];
    int cnt = 0;
    while(cnt < 1)
    {
        cnt++;
        fprintf(memfuzz_status_fp, "Loop num: %d\n", cnt);
        fflush(memfuzz_status_fp);
        //if it is the first time, it is used for greet AFL
        //otherwise, it is for sending an empty file to AFL and notify AFL we are done with an input
        pid = fork();
        if(pid < 0)
        {
            printf("fork failed!\n");
            exit(1);
        }
        //child
        if (pid == 0)
        {
            child_pid = 0;
            return ; //continue to execute the original main function
        }
        //parent
        else
        {
            child_pid = pid;
            fprintf(memfuzz_status_fp, "child pid %d\n", pid);
            fflush(memfuzz_status_fp);
            //wait_msg(t_fd[0]); //TODO: some pipe problem in this line, fix it
            if(waitpid(pid, &status, 0) < 0)
            {
                printf("waitpid() failed\n");
                exit(3);
            }
            fprintf(memfuzz_status_fp, "Loop num: %d done!\n", cnt);
            fflush(memfuzz_status_fp);
        }
    }
}
*/

//A safe print for test, without AFL
/*
void safe_print()
{
    pid_t pid = fork();
    int status;
    if(pid < 0)
    {
        printf("fork() failed, continue print without fork()\n");
        longjmp(memfuzz_jmp_buf, 1);
    }
    else if(pid > 0)
    {
        child_pid = pid;
        //TODO: add alarm here to avoid hang
        if(waitpid(pid, &status, 0) < 0)
        {
            exit(1);
        }
        //TODO: do something about status
        FILE* fp = fopen(MEMFUZZ_OUTFILE, "rb");
        fseek(fp, 0, SEEK_END);
        size_t length = ftell(fp);
        unsigned char* buf = malloc(length);
        fread(buf, 1, length, fp);
        fclose(fp);
        return ;
    }
    // in the child process, we jump to the print function
    else
    {
        printf("child process jmp to print\n");
        child_pid = 0;
        //set an alarm here to end the process
        longjmp(memfuzz_jmp_buf, 1);
    }
}
*/

void mutate_enum_test(void* ptr1, int num)
{
    int* ptr = ptr1;
    int val = *ptr;
    for(int i = 0; i < num; i++)
    {
        *ptr = i;
    }
    *ptr = val;
}

void mutate_enum_with_values_test(void* ptr1, int num, int *values)
{
    int* ptr = ptr1;
    int val = *ptr;
    for(int i = 0; i < num; i++)
    {
        *ptr = values[i];
    }
    *ptr = val;
}

void memfuzz_init_test(void)
{
    // memfuzz_status_fp = fopen("/tmp/memfuzz_status", "w");
    // setup_stats_shm();// Setup shared memory for stats
    //fprintf(memfuzz_status_fp, "setup_AFL_shm() done!\n");
    // setup_signal();
}


void assign_int64_t_test(void* ptr1, int level)
{
    int64_t *ptr = (int64_t*) ptr1;
    int64_t val = *ptr;
    for(int i = 0; i < Int64_NUM; i++)
    {
        *ptr = Int64[i];
    }
    *ptr = val;
}


void assign_double_array_test(void* ptr1, int level, int elems)
{
    double* ptr = ptr1;
    double val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Double_NUM; j++)
        {
            ptr[pos] = Double[j];
        }
        ptr[pos] = val;
    }
}


void assign_int32_t_array_test(void* ptr1, int level, int elems)
{
    int32_t* ptr = ptr1;
    int32_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int32_NUM; j++)
        {
            ptr[pos] = Int32[j];
        }
        ptr[pos] = val;
    }
    
}


void assign_int32_t_test(void* ptr1, int level)
{
    int32_t* ptr = (int32_t*)ptr1;
    int32_t val = *ptr;
    for(int i = 0; i < Int32_NUM; i++)
    {
        *ptr = Int32[i];
    }
    *ptr = val;
}


void assign_float_array_test(void* ptr1, int level, int elems)
{
    float* ptr = ptr1;
    float val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Float_NUM; j++)
        {
            ptr[pos] = Float[j];
        }
        ptr[pos] = val;
    }
    
}



void assign_float_test(void* ptr1, int level)
{
    float* ptr = (float*) ptr1;
    float val = *ptr;
    for(int i = 0; i < Float_NUM; i++)
    {
        *ptr = Float[i];
    }
    *ptr = val;
}


void assign_int8_t_array_test(void* ptr1, int level, int elems)
{
    int8_t* ptr = ptr1;
    int8_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int8_NUM; j++)
        {
            ptr[pos] = Int8[j];
        }
        ptr[pos] = val;
    }
    
}


void assign_int8_t_test(void* ptr1, int level)
{
    int8_t *ptr = (int8_t*) ptr1;
    int8_t val = *ptr;
    for(int i = 0; i < Int8_NUM; i++)
    {
        *ptr = Int8[i];
    }
    *ptr = val;
}


void assign_int16_t_array_test(void* ptr1, int level, int elems)
{
    int16_t* ptr = ptr1;
    int16_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int16_NUM; j++)
        {
            ptr[pos] = Int16[j];
        }
        ptr[pos] = val;
    }
}


void assign_int16_t_test(void* ptr1, int level)
{
    int16_t *ptr = (int16_t*)ptr1;
    int16_t val = *ptr;
    for(int i = 0; i < Int16_NUM; i++)
    {
        *ptr = Int16[i];
    }
    *ptr = val;
}


void assign_int64_t_array_test(void* ptr1, int level, int elems)
{
    int64_t* ptr = ptr1;
    int64_t val;
    for(int i = 0; i < SAMPLE_TIMES; i++)
    {
        int pos = random() % elems;
        val = ptr[pos];
        for(int j = 0; j < Int64_NUM; j++)
        {
            ptr[pos] = Int64[j];
        }
        ptr[pos] = val;
    }
}

