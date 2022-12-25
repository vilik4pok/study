#include <stdio.h>
#include <string.h>

int check(char);
int word_len(char*);

int main()
{
    char str[80] = "Alkov Valentin Sergeevich Sergeevich",str2[80]="", *p=str;
    //gets(str);
    int i;
    for(i=0; i<2; i++)
    {
        p+=word_len(p)+1;
      sprintf(str2,"%s%c. ",str2,*p);
    };
    strncat(str2,str,word_len(str));
    strcpy(str, str2);
    printf("%s",str);
    return 0;
}
int check(char a)
{
    if ((a>='a' && a <='z') || (a>='A' && a <='Z'))
        return 1;
    return 0;
}

int word_len(char *a)
{
    int i;
    for(i=0; check(*a); i++, a++);
    return i;
}



