#include <stdio.h>
int main()
{
    double f, s=1.;
    int j,i,n;
    scanf("%d",&n);
    printf("1",f);
    for (i=2; i<=n; i++)
    {
        f=i;
        for (j=1; j<=i-1; j++)
            f*=i;
        s+=1/f;
        printf(" + 1/%.lf",f);
    };
    printf("\ns=%lf", s);
    return 0;
}


