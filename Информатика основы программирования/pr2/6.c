#include <stdio.h>
int main()
{
    int i=1,a,b,c,res=0;
    scanf("%d",&a);
    b=a%10;
    while(a/10 != 0)
    {
        i*=10;
        c=(a/=10)%10;
        res+=c*i;
    };
    res+=b*i-c*(i-1);
    printf("%d",res);
    return 0;
}

