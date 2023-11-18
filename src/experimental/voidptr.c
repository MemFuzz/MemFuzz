#include <stdio.h>
#include <stdlib.h>
void mutate(void* ptr1, int level, int dim)
{
    int *ptr = ptr1;
    for(int i = 0 ; i < dim; i++)
    {
        ptr[i] = i;
    }

}
int main()
{
    int a[20][20] = {1};
    mutate(a, 0, 400);
    for(int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
            printf("%d ",  a[i][j]);
    }
}
