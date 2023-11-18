//An example to show chained fork and pipe works
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
pid_t child_pid;
void fk1(void)
{
    pid_t pid = fork();
    if(pid < 0)
        exit(2);
    int num;
    if (pid == 0)
    {
        for(int i = 0; i < 10; i++)
        {
            num = i;
            write(200, &num, 4);
        }
    }
    else
    {
        child_pid = pid;
        printf("child pid is %d\n", child_pid);
        int status;
        waitpid(pid, &status, 0);
    }
}

void fk(void)
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
        exit(1);
    if(pid == 0)
    {
        close(199);
        fk1();
        //int num = 1;
        //write(200, &num, 4);
    }
    else
    {
        close(200);
        int num;
        size_t count = 4;
        int status;
        child_pid = pid;
        printf("child id is %d\n", child_pid);
        while(read(199, &num, count) > 0)
        {
            printf("%d\n", num);
        }
        printf("pipe broken\n");
        waitpid(child_pid, &status, 0);
        printf("main end\n");
    }
    
}

int main()
{
    int fd[2];
    (void)pipe(fd);
    dup2(fd[0], 199);//read
    dup2(fd[1], 200);//write   
    //note that we must close then here, otherwise read won't end
    close(fd[0]);
    close(fd[1]);
    fk();
    printf("process whose child is %d exits\n", child_pid);
}
