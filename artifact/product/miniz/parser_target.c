#include "zip.h"
#include "stdio.h"



int main(int argc, char** argv)
{
    if(argc < 2)
        return 1;
    struct zip_t *zip = zip_open(argv[1], 0, 'r');
    if(zip == NULL)
	return 1;
    zip_close(zip);
    return 0;
}

