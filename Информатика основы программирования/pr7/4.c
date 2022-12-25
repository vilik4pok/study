#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

char toup(char);
char tolow(char);
void tolowerstring(char*);
void add (char*);
void show (char*);
struct sportperson* readmany(char*, int, int*);
void delete_entry(char*);
void findman(char*);
void findwomen(char*);
void print_entries(struct sportperson*, int);
void print1(struct sportperson*);
void edit (char*);

struct sportperson
{
    char name[79];
    char gender;
    char sport[32];
    int year, height;
};

int main(int argc, char* files[])
{
    setlocale(LC_ALL, "cp1251");
    system("chcp 1251");
    system ("CLS");
    setlocale(LC_ALL, "Rus");
    char filename[50];
    int k, menu;
    if(argc<2)
    {
        puts ("��� �����:");
        gets (filename);
    }
    else
        strcpy(filename,files[1]);
    do
    {
        system ("CLS");
        puts ("1. ���������� ������");
        puts ("2. �������� �������");
        puts ("3. �������� ������");
        puts ("4. ������������� ������");
        puts ("5. ����� �������");
        puts ("6. ����� ������");
        puts ("7. �����");
        scanf ("%d%*c", &menu);
        switch (menu)
        {
            case 1 : add (filename); break;
            case 2 : show (filename); break;
            case 3 : delete_entry (filename); break;
            case 4 : edit (filename); break;
            case 5 : findman(filename); break;
            case 6 : findwomen(filename); break;
        };
    } while (menu!=7);
    return 0;
}

struct sportperson* readmany(char*filename, int n, int* c)
{
    int k=0, i=0, size = sizeof(struct sportperson);
    struct sportperson *buf = calloc(1,1);
    FILE* f;
    system("cls");
    if(!(f=fopen(filename, "rb")))
    {
        perror("�� ������� ������� ����.");
        getchar();
        return NULL;
    };
    do
    {
        buf = realloc(buf, (n+i)*size);
        i=fread(buf+k, size, n, f);
        k+=i;
    } while(i==n);
    fclose(f);
    if(!k)
    {
        perror("���� ����");
        getchar();
        return NULL;
    };
    *c=k;
    buf = realloc(buf, k*size+1);
    return buf;
}

void findman(char* filename)
{
    struct sportperson *buf, entry;
    int k, i, j, num, k2=0;
    if(!(buf = readmany(filename, 10, &k)))
        return;
    for(i=0; i<k; i++)
        if(buf[i].gender =='�'&&strcmp(buf[i].sport,"��������")==0)
        {
            k2=1;
            entry = buf[i];
            break;
        };
    if(k2)
    {
        for(; i<k; i++)
            if(buf[i].gender == '�' && buf[i].height > entry.height && (strcmp(buf[i].sport,"��������")==0))
                entry = buf[i];
        print1(&entry);
    }
    else
        printf("�� �������");
    free(buf);
    getchar();
}
void print1(struct sportperson*buf)
{
    printf("���:%s\n���:%c\n��� ������:%s\n���:%d\n����:%d\n",
    buf->name, buf->gender, buf->sport, buf->year, buf->height);
}

void findwomen(char* filename)
{
    struct sportperson *buf;
    int k, i,j;
    if(!(buf = readmany(filename, 10, &k)))
        return;
    for(i=0; i<k; i++)
        if(buf[i].gender!= '�' || (2020 - buf[i].year<14) || (2020 - buf[i].year>17))
        {
            for (j=i; j<k-1; j++)
                buf[j] = buf[j+1];
            k--;
            i--;
        };
    if(k)
        print_entries(buf, k);
    else
    {
        printf("�� �������");
        getchar();
    };
    free(buf);
}

struct sportperson input_sportsman (void)
{
    struct sportperson sportsman;
    char c, buf[10];
    int temp;
    system ("cls");
    puts ("���");
    gets(sportsman.name);
    do
    {
        puts ("���(�/�)");
        gets(buf);
        buf[0]=toup(buf[0]);
        if (buf[0]=='�'||buf[0]=='�')
            break;
        else
            puts("������������ ����. ������� \"�\" ��� \"�\".");
    } while(1);
    sportsman.gender = buf[0];
    puts ("��� ������");
    gets (sportsman.sport);
    tolowerstring(sportsman.sport);
    puts ("��� ��������");
    scanf ("%d", &sportsman.year);
    puts ("����");
    scanf ("%d", &sportsman.height);
    return sportsman;
}

void edit (char* filename)
{
    FILE * f;
    int num,k;
    struct sportperson *buf;
    char str[5];
    if(!(buf = readmany(filename, 10, &k)))
        return;
    system ("cls");
    puts("������� ����� ������");
    scanf("%d", &num);
    getchar();
    if(num<1 || num>k)
    {
        system ("cls");
        printf("������������ ����");
        free(buf);
        getchar();
        return;
    };
    print1(&buf[num-1]);
    puts("�������������(�/�)");
    gets(str);
    str[0] = toup(str[0]);
    if (str[0] == '�' || str[0]=='�')
    {
        buf[num-1] = input_sportsman();
        f = fopen(filename, "wb");
        fwrite(buf, sizeof(struct sportperson), k, f);
        fclose(f);
    }
    else
            printf("������������ ����");
    free(buf);
    getchar();
}

void add(char* filename)
{
    FILE*f;
    struct sportperson sportsman;
    system ("cls");
    if(!(f=fopen(filename, "ab")))
    {
        perror ("������ �������� �����");
        getchar();
        return;
    };
    sportsman = input_sportsman();
    fwrite(&sportsman, sizeof(sportsman), 1, f);
    fclose(f);
    getchar();
}

void print_entries(struct sportperson*buf, int k)
{
    int i=0,j,num;
    if (!buf)
        return;
    while (1)
    {
        system ("cls");
        puts("| N |              ���              | ��� | ��� ������ | ��� | ���� |");
        puts("---------------------------------------------------------------------");
        for(j=0; j<10&&i<k; j++,i++)
        {
            printf("|%3d|%-31.31s|%-5c|%-12.12s|%5d|%6d|\n",
            i+1, buf[i].name, buf[i].gender, buf[i].sport,buf[i].year, buf[i].height);
            puts("---------------------------------------------------------------------");
        };
        puts("1. ������� ���������� 10 �������");
        puts("2. ������� ��������� 10 �������");
        puts("3. ���������� �����");
        scanf("%d%*c", &num);
        system ("cls");
        switch (num)
        {
            case 1 :
                if(i<11)
                {
                    puts("���������� ������� ���.");
                    getchar();
                    return;
                }
                else
                    i-=10+j;
                break;
            case 2 :
                if(i>=k)
                {
                    puts("��������� ������� ���.");
                    getchar();
                    return;
                };
                break;
            case 3 : return; break;
        };
    };
}
void show(char* filename)
{
    struct sportperson *buf;
    int k;
    if(!(buf = readmany(filename, 10, &k)))
        return;
    print_entries(buf,k);
    free(buf);
}

void delete_entry(char* filename)
{
    system ("cls");
    int num;
    FILE* f;
    struct sportperson *buf;
    int k, i;
    if(!(buf = readmany(filename, 10, &k)))
        return;
    puts("������� ����� ������");
    scanf("%d", &num);
    getchar();
    if(num<1 || num>k)
    {
        system ("cls");
        printf("������������ ����");
        free(buf);
        getchar();
        return;
    };
    if (!(f=fopen(filename, "wb")))
    {
        perror("�� ������� ������� ����.");
        free(buf);
        getchar();
        return;
    };
    for (i=num-1; i<k-1; i++)
        buf[i] = buf[i+1];
    fwrite(buf, sizeof(struct sportperson), k-1, f);
    fclose(f);
    free(buf);
}

char toup(char c)
{
    if ((c>='a'&& c<='z') || (c>='�'&& c<='�'))
        c-=32;
    return c;
}

char tolow(char c)
{
    if ((c>='A'&& c<='Z') || (c>='�'&& c<='�'))
        c+=32;
    return c;
}

void tolowerstring(char *a)
{
    int i;
    for (i=0; a[i]!='\0'; i++)
        a[i]=tolow(a[i]);
}
