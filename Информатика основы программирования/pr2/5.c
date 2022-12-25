#include <stdio.h>
int main()
{
    int i=2,a;
    scanf("%d",&a);
    printf("%d = 1",a);
    while (a != 1)
    {
        if (a%i==0)
        {
            a /= i;
            printf(" * %d",i);
            i--;
        }
        i++;
    }
    return 0;
}
