#include <stdio.h>
#include <math.h>
int main()
{
    double f=0., s=0., v1=1., x, v2=1.;
    int n=1;
    do
    {
        printf("x=");
        scanf("%lf", &x);
    }
    while (x<=1.);
    printf("ln%lf=%lf\n", x, log(x));
    for (n=1,f=(x-1)/x; fabs(f)>=1e-5; n++)
    {
        v1 *= x-1;
        v2 *=x;
        f = v1/(n*v2);
        s += f;
    };
    printf("s=%lf\n", s);
    return 0;
}

