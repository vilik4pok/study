#include <stdio.h>
#include <locale.h>
#include <string.h>
int check_prime(int);
int read_line(FILE*, FILE*);
int read_int(FILE*, int*);
int check_num(char);
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
int files_work(char* filename)
{
    int p;
    char newfilename[80];
    strcpy(newfilename, filename);
    newfilename[strlen(newfilename)-4] = '\0';
    strcat(newfilename, "_res2.txt");
    FILE *f1, *f2;
    f1 = fopen(filename,"r");
    if (!f1)
    {
        printf("Не удалось открыть файл.");
        return 1;
    };
    f2 = fopen(newfilename,"w");
    if (!f2)
    {
        printf("Не удалось создать файл для записи.");
        return 2;
    };
    while((p=read_line(f1, f2))!=2);
    fclose(f1);
    fclose(f2);
    filename[strlen(filename)-4] = '\0';
    rename("temp.txt", strcat(filename, "_res.txt"));
    printf("Успешно.");
    return 0;
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

int read_int(FILE*f, int* num)
{
    int c=fgetc(f);
    while(!check_num(c))
    {
            if(c =='\n')
                return 1;
            if(c ==EOF)
                return 2;
            c=fgetc(f);

    };
    if(check_num(c));
    {
        ungetc(c,f);
        fscanf(f,"%d",num);
    };
    return 0;
}

int read_line(FILE* f, FILE* f1)
{
    int num, p, k=0, c;
    static int i=1;
    while(!(p=read_int(f, &num)) && p!=1)
    {
        if(check_prime(num))
            k++;
    };
    while(!check_num(c=fgetc(f))&&c!=EOF);
        if (c==EOF)
            p=2;
        else
            ungetc(c,f);
    fprintf(f1, "%d %d\n", i++, k);
    return p;
}

int check_prime(int a)
{
    int i;
    if (a<2)
        return 0;
    for(i=2; i<=a/2; i++)
    {
        if(a%i==0)
            return 0;
    };
    return 1;
}

int check_num(char c)
{
    if(c>='0'&&c<='9' || c == '-')
        return 1;
    return 0;
}
