#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *a, i,c=0,k;
    double x=0.;
    if (scanf("%d", &k)!= 1)
        return -1;
    a = malloc(k*sizeof(int));
    if (a==NULL)
        return -1;
    for (i=0; i<k; i++)
        if (scanf("%d", &a[i])!= 1)
            return -1;
    for (i=0; i<k; i++)
        x+=a[i];
    x/=k;
    for (i=0; i<k; i++)
        if (a[i]>x)
            c++;
    printf("srednee = %lf\n>srednego %d\n",x,c);
    free(a);
    return 0;
}
