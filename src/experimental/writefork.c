#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <setjmp.h>
jmp_buf memfuzz_jmp_buf;
void f1()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        exit(3);
    }
    if(pid == 0)
    {
        longjmp(memfuzz_jmp_buf, 1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        FILE* out = fopen("./txt", "rb");

        if(out != NULL)
        {
            fseek(out, 0, SEEK_END);
            int length = ftell(out);
            fseek(out, 0, SEEK_SET);
            char buf[1024] = {0};
            fread(buf, length, 1, out);
            fprintf(stdout, "TXT: %s\n", buf);
        }
        return ;
    }
}
void f()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        exit(2);
    }
    if(pid == 0)
    {
        for(int i = 0; i < 4; i++)
        {
            f1();
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}
int main()
{
    char buf[] = "Hello world!\n";
    int length = strlen(buf);
    int fd = open("./txt", O_TRUNC | O_RDWR | O_CREAT, 0666);
    if (fd == -1)
        exit(1);
    if(setjmp(memfuzz_jmp_buf) == 0)
    {
        f();
        exit(0);
    }
    ftruncate(fd, 0);
    lseek(fd, 0, SEEK_SET);
    printf("Do write\n");
    write(fd, buf, length);
}
