#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int toup(char);
int check_sentence(char*);
int check(char);
void delete_symbols(char*, int);
void replace_n(char*);
int files_work(char*);
void files_is_empty();
void files_is_not_empty(int, char*[]);

int main(int argc, char* files[])
{
    setlocale(LC_ALL, "rus");
    char c, filename[80] = "";
    if(argc<2)
        files_is_empty();
    else
        files_is_not_empty(argc, files);
    return 0;
}

void files_is_not_empty(int argc, char* files[])
{
    int i;
    printf("%-20.20s %-20.20s\n","Файл", "Результат");
    for (i=1; i<argc; i++)
    {
        printf("%-20.20s ",files[i]);
        files_work(files[i]);
        printf("\n");
    };
}

void files_is_empty()
{
    int i=0;
    char c, filename[80] = "";
    printf("Введите названия файлов:");
    do
    {
        scanf("%s", filename);
        if(i==0)
        {
            printf("%-20.20s %-20.20s\n","Файл", "Результат");
            i++;
        };
        printf("%-20.20s ",filename);
        files_work(filename);
        printf("\n");
        while((c=fgetc(stdin))==' ');
            if(c!='\n')
                ungetc(c,stdin);
    } while(c!='\n');
}

int files_work(char *filename)
{
    FILE *f1, *f2;
    int c, cbuf, i=0;
    char *buf = calloc(1,1);
    f1 = fopen(filename,"r");
    if (!f1)
    {
        printf("Не удалось открыть файл.");
        return 1;
    };
    f2 = fopen("temp.txt","w");
    if (!f2)
    {
        printf("Не удалось создать файл для записи.");
        return 1;
    };
    while ((c=fgetc(f1)) != EOF)
    {   buf = realloc(buf, 2+i);
        buf[i] = c;
        if((cbuf=fgetc(f1)) == EOF || c=='.')
        {
            buf[i+1] ='\0';
            if(!ftell(f2))
                replace_n(buf);
            if (check_sentence(buf))
                fprintf(f2, "%s", buf);
            i=-1;
        };
        ungetc(cbuf,f1);
        i++;
    };
    fclose(f1);
    fclose(f2);
    remove(filename);
    rename("temp.txt", filename);
    printf("Успешно.");
    return 0;
}

int check(char a)
{
    if ((a>='a' && a <='z') || (a>='A' && a <='Z')||(a>='А' && a <='Я')||(a>='а' && a <='я'))
        return 1;
    return 0;
}

int check_sentence(char* a)
{
    int i;
    char c1, c2;
    for(i=0; !check(a[i])&&a[i]!='\0'; i++);
    c1=a[i];
    for(i; a[i]!='\0'; i++)
        if(check(a[i]))
            c2=a[i];
    return toup(c1)!=toup(c2);
}

int toup(char c)
{
    if ((c>='a'&& c<='z') || (c>='а'&& c<='я'))
        c-=32;
    return c;
}

void delete_symbols(char *a, int b)
{
    int i, len = strlen(a);
    for (i=0; i<len-b+1&&a[i+b-1]!='\0'; i++)
        a[i] = a[i+b];
}
void replace_n(char* a)
{
    int i;
    for(i=0; !check(a[i])&&a[i]!='\0'; i++)
        if (a[i] == '\n'|| a[i] == ' ')
        {
            delete_symbols(a, 1);
            i--;
        };
}
