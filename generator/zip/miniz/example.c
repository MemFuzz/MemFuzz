#include "zip.h"

int on_extract_entry(const char *filename, void *arg) {
    static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

    return 0;
}


int main(int argc, char** argv)
{
    if(argc < 2)
        return 1;
    int arg = 2;
    int res = zip_extract(argv[1], "/tmp", on_extract_entry, &arg);
    return res;
}

