#include <stdio.h>
#include <stdlib.h>
#define N 8
int main()
{
    int a[N][N],i,j;
    for (i=0;i<N;i++)
    {
        for (j=i+1;j<N;j++)
            a[i][j]=1;
        a[i][i]=0;
        for (j=0;j<i&&i>0;j++)
            a[i][j]=-1;
    };
    for (i=0; i<N;i++)
    {
        for (j=0;j<N;j++)
            printf("%2d ",a[i][j]);
        printf("\n");
    };
    return 0;
}

