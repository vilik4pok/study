#include <stdio.h>
#include <math.h>
#include <float.h>
int main()
{
    double f,v1,v2,a,b;
    scanf("%lf%lf",&a,&b);
    if (fabs(b)<FLT_EPSILON) return -1;
    v1 = sin(a)*sin(a) + 12 * fabs(log(fabs(b)));
    if (v1 < 0) return -1;
    if (cos(a/b) == 0) return -1;
    v2 = (b-a)*(b-a)*exp(tan(a/b));
    if (fabs(v2)< FLT_EPSILON) return -1;
    f = (-sin(a) + v1)/v2;
    printf("f=%lf\n", f);
    return 0;
}


