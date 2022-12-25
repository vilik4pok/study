#include <stdio.h>
#include <string.h>
//#include <ctype.h>

int check(char);
int word_len(char*);
void cut_str(char*, char);
int main()
{
    char str[80] = "It is a good day to die.", *p;
    //gets(str);
    int i, mc=0;
    cut_str(str, '.');
    printf("%s\n",str);
    for (i=0;  str[i]!='\0' && str[i]!='.'; i++)
        if(check(str[i]) && !check(str[i-1]))
            if(word_len(&str[i])>mc)
            {
                p = &str[i];
                mc = word_len(&str[i]);
            };
    for(i=0; i<mc; i++)
        str[i] = *p++;
    str[i] = '\0';
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
void cut_str(char *a, char b)
{
    int i;
    for(i=0; a[i+1]!='\0'&&a[i]!=b; i++);
    a[i+1] = '\0';
}

