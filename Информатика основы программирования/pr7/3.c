#include <stdio.h>
void printf_file(FILE*);
int minmax(FILE*, int);
double readpos(FILE*, int);
void replace(FILE*, int, int);
void files_work(char*);
void files_is_empty();
void files_is_not_empty(int, char*[]);

void files_work(char* filename)
{
    FILE* f;
    int posmax, posmin, posend;
    double max, min;
    f = fopen(filename, "rb+");
    if (!f)
    {
        printf("Can't open file.\n");
        return;
    };
    printf("File before changes\n");
    printf_file(f);
    posmin = minmax(f, -1);
    replace(f,posmin, 0);
    fseek(f,0,SEEK_END);
    posend = ftell(f);
    posmax = minmax(f, 1);
    replace(f,posmax, posend-sizeof(double));
    printf("File after changes\n");
    printf_file(f);
    fclose(f);
}

int main(int argc, char* files[])
{
    if(argc<2)
        files_is_empty();
    else
        files_is_not_empty(argc, files);
    return 0;
}

void files_is_not_empty(int argc, char* files[])
{
    int i;
    for (i=1; i<argc; i++)
    {
        printf("%-20.20s ",files[i]);
        files_work(files[i]);
        printf("\n");
    };
}

void files_is_empty()
{
    char c, filename[80] = "";
    printf("Enter files names:");
    do
    {
        scanf("%s", filename);
        printf("%s\n",filename);
        files_work(filename);
        printf("\n");
        while((c=fgetc(stdin))==' ');
            if(c!='\n')
                ungetc(c,stdin);
    } while(c!='\n');
}

void replace(FILE* f, int pos1, int pos2)
{
    double num1, num2;
    num1 = readpos(f,pos1);
    num2 = readpos(f,pos2);
    fseek(f,pos1,SEEK_SET);
    fwrite(&num2,sizeof(double),1,f);
    fseek(f,pos2,SEEK_SET);
    fwrite(&num1,sizeof(double),1,f);
}

double readpos(FILE* f, int pos)
{
    double num;
    fseek(f, pos, SEEK_SET);
    fread(&num, sizeof(double), 1, f);
    return num;
}

int minmax(FILE* f, int p)
{
    double num, buf;
    int pos=0;
    rewind(f);
    fread(&buf, sizeof(double), 1, f);
    while(fread(&num, sizeof(double), 1, f))
        if (num*p>buf*p)
        {
            pos = ftell(f)-sizeof(double);
            buf = num;
        };
    return pos;
}

void printf_file(FILE*f)
{
    double num;
    rewind(f);
    while(fread(&num, sizeof(double), 1, f))
        printf("%lf ", num);
    printf("\n");
}
