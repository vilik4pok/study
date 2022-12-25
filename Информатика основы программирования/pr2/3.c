#include <stdio.h>
int main()
{
    int a,b;
    scanf("%d%d", &a, &b);
    if (a!=0 && b !=0)
        if (a>0)
            if (b>0)
                if (a>b)
                    a = (a + b) / 2;
                else
                    b = (a + b) / 2;
            else
            {
                a*=2;
                b*=2;
            }
        else
            if (b>0)
            {
                a*=2;
                b*=2;
            }
            else
                if (a<b)
                    a=-a;
                else
                    b=-b;
    printf("%d %d", a, b);
    return 0;
}


