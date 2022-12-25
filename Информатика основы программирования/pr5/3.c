#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(double);
double f2(double);
double integral(int, double, double, double(*)(double));
int main()
{
    double integral_1, integral_2;
    integral_1 = integral(40, -1, 3, f1);
    integral_2 = integral(40, -3, 2, f2);
    printf("1=%lf\n2=%lf",integral_1,integral_2);
    return 0;
}

double f1(double x)
{
    return 2*x/exp(2*x);
}

double f2(double x)
{
    return sqrt(x*x+1);
}

double integral(int n, double a, double b, double (*f)(double))
{
    double h =(b-a)/n, s=((f(a)+f(b))/2);
    for(a+=h; a<b-h; a+=h)
        s+=f(a);
    return h*s;
}
