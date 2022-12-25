#include <stdio.h>
#include <stdlib.h>
#define N 4
int main()
{
    int a[N][N][N], i, j, c, d;
    for (i=0;i<N;i++)
        for (j=0;j<N;j++)
            for (c=0;c<N;c++)
                a[i][j][c] = 0;
    for (i=0;i<N;i++)
        for (j=0,c=i;j<N;j++,c++)
        {
            c%=N;
            a[i][j][c] = 1;
        };
     for (i=0;i<N;i++)
     {
        printf("stage %d\n",i);
        for (j=0;j<N;j++)
        {
            for (c=0;c<N;c++)
                printf("%3d", a[i][j][c]);
            printf("\n");
        }
     }
    return 0;
}



