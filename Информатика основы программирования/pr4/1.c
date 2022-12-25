#include <stdio.h>
#include <stdlib.h>
#define N 20
int main()
{
    int a[N], x, i;
    for (i=0; i<N; i++)
        if (scanf("%d", &a[i])!= 1)
            return -1;
    for (i=0; i<N; i++)
        printf("a[%d]=%d\n",i,a[i]);
    for (i=0; i<N/2; i++)
    {
        x = a[i];
        a[i] = a[N-1-i];
        a[N-1-i] = x;
    };
    for (i=0; i<N; i++)
        printf("a[%d]=%d\n",i,a[i]);
    return 0;
}
