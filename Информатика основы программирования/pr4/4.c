#include <stdio.h>
#include <stdlib.h>
#define N 9
#define M 11
int main()
{
    int a[N][M],i,j,a1=0,b1=0,x,c,min, z=0;
    if (scanf("%d",&x)!=1)
        return -1;
    for (i=0;i<N;i++)
        for (j=0;j<M;j++)
            if (scanf("%d",&a[i][j])!=1)
                return -1;
    min = a[0][0];
    for (i=0;i<N;i++)
        for (j=0;j<M;j++)
            if (a[i][j]<min)
            {
                min = a[i][j];
                a1=i;
                b1=j;
            };
    for (i=0;i<N;i++)
        for (j=0;j<M;j++)
        {
            c=a[i][j];
            if (x == a[i][j])
            {
                c=a[i][j];
                a[i][j] = a[a1][b1];
                a[a1][b1] = c;
                z=1;
            };
        };
    printf("\n");
    for (i=0; i<N;i++)
    {
        for (j=0;j<M;j++)
            printf("%3d ",a[i][j]);
        printf("\n");
    };
    if (z==0)
        printf("x not found");
    return 0;
}

