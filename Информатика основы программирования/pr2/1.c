#include <stdio.h>
#include <float.h>
int main()
{
    double f, a, b;
    scanf("%lf%lf",&a,&b);
    f = fabs(a) > 5 ? 3*a*a : fabs(b)>=FLT_EPSILON ? a/b : b+a-1;
    printf("%lf",f);
    return 0;
}



