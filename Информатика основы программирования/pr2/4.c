#include <stdio.h>
int main()
{
    int n,a,i;
    double res=2.;
    scanf("%d",&n);
    printf("2/1");
    for (i=2;i<=n;i++)
    {
        if (i%2 == 1)
        {
            printf(" * %d/%d",i+1,i);
            res *= (double)(i+1)/i;
        }
        else
        {
            printf(" * %d/%d",i,i+1);
            res *= (double)i/(i+1);
        }
    }
    printf(" = %lf",res);
    return 0;
}
