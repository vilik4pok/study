#include <stdio.h>
#include <math.h>
int main()
{
    double f=0., s=1., v1=1., x, a;
    int n=1,v2=1;
    do
    {
        printf("x=");
        scanf("%lf", &x);
        printf("a=");
        scanf("%lf", &a);
    }
    while (x < 0.1 || x > 1.0 || a==0);
    printf("%lf^%lf=%lf\n", a, x, pow(a,x));
    printf("= 1 ", f);
    for (n=1,f=x*log(a)/n; fabs(f)>=1e-4; n++)
    {
        v1 *= x*log(a);
        v2 *=n;
        f = v1/v2;
        s += f;
        printf(" + %lf", f);
    };
    printf("s=%lf\n", s);
    return 0;
}
