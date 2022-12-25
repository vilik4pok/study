#include <stdio.h>

int check_num(char);
int read_double(FILE*, double*);
int read_line(FILE*);

int main()
{
    FILE* f;
    f=fopen("3.bin","wb");
    if(!f)
    {
        printf("Error.\n");
        return 1;
    };
    read_line(f);
    fclose(f);
    return 0;
}

int read_double(FILE*f, double* num)
{
    int c=fgetc(f);
    while(!check_num(c))
    {
            if(c =='\n')
                return 1;
            c=fgetc(f);
    };
    if(check_num(c));
    {
        ungetc(c,f);
        scanf("%lf",num);
    };
    return 0;
}

int read_line(FILE* f)
{
    int p;
    double num;
    while(!(p=read_double(stdin, &num)))
        fwrite(&num, sizeof(double), 1, f);
    return p;
}

int check_num(char c)
{
    if(c>='0'&&c<='9' || c == '-')
        return 1;
    return 0;
}
