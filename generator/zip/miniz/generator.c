#include "zip.h"
#include <stdio.h>
#include <stdlib.h>
#include "memfuzz.h"


int main(int argc, char** argv)
{
    alloc_init();
    memfuzz_init();
    char *outbuf = NULL;
    size_t outbufsize = 0;
    struct zip_t *zip = zip_open(MEMFUZZ_INFILE, 0, 'r');
    int i, n = zip_entries_total(zip);
    struct zip_t *zip_out = zip_stream_open(NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    
    for(i = 0; i < n; i++)
    {
        zip_entry_openbyindex(zip, i);
        {
            const char *name = zip_entry_name(zip);
            int isdir = zip_entry_isdir(zip);
            unsigned long long size = zip_entry_size(zip);
            unsigned int crc32 = zip_entry_crc32(zip);
            size_t bufsize = 0;
            char *buf = NULL;
            zip_entry_read(zip, (void **)&buf, &bufsize);
            zip_entry_open(zip_out, name);
            {
                zip_entry_write(zip_out, buf, bufsize);
            }
            zip_entry_close(zip_out);
        }
        zip_entry_close(zip);
    }
    /*Modification Begin*/
    if(setjmp(memfuzz_jmp_buf) == 0)
    {
        mutate_zip_t(zip_out, 0, 1);
        exit(0);
    }
    /*Modification End*/
    zip_stream_copy(zip_out, (void **)&outbuf, &outbufsize);
    zip_stream_close(zip_out);
    FILE* fp = fopen(MEMFUZZ_OUTFILE, "w");
    fwrite(outbuf, outbufsize, 1, fp);
    free(outbuf);
}
