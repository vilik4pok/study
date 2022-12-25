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
        puts ("Имя файла:");
        gets (filename);
    }
    else
        strcpy(filename,files[1]);
    do
    {
        system ("CLS");
        puts ("1. Добавление записи");
        puts ("2. Просмотр записей");
        puts ("3. Удаление записи");
        puts ("4. Редактировать запись");
        puts ("5. Найти мужчину");
        puts ("6. Найти женщин");
        puts ("7. Выход");
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
        perror("Не удалось открыть файл.");
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
        perror("Файл пуст");
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
        if(buf[i].gender =='М'&&strcmp(buf[i].sport,"плавание")==0)
        {
            k2=1;
            entry = buf[i];
            break;
        };
    if(k2)
    {
        for(; i<k; i++)
            if(buf[i].gender == 'М' && buf[i].height > entry.height && (strcmp(buf[i].sport,"плавание")==0))
                entry = buf[i];
        print1(&entry);
    }
    else
        printf("Не найдено");
    free(buf);
    getchar();
}
void print1(struct sportperson*buf)
{
    printf("ФИО:%s\nПол:%c\nВид спорта:%s\nГод:%d\nРост:%d\n",
    buf->name, buf->gender, buf->sport, buf->year, buf->height);
}

void findwomen(char* filename)
{
    struct sportperson *buf;
    int k, i,j;
    if(!(buf = readmany(filename, 10, &k)))
        return;
    for(i=0; i<k; i++)
        if(buf[i].gender!= 'Ж' || (2020 - buf[i].year<14) || (2020 - buf[i].year>17))
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
        printf("Не найдено");
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
    puts ("ФИО");
    gets(sportsman.name);
    do
    {
        puts ("Пол(М/Ж)");
        gets(buf);
        buf[0]=toup(buf[0]);
        if (buf[0]=='М'||buf[0]=='Ж')
            break;
        else
            puts("Неправильный ввод. Введите \"М\" или \"Ж\".");
    } while(1);
    sportsman.gender = buf[0];
    puts ("Вид спорта");
    gets (sportsman.sport);
    tolowerstring(sportsman.sport);
    puts ("Год рождения");
    scanf ("%d", &sportsman.year);
    puts ("Рост");
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
    puts("Введите номер записи");
    scanf("%d", &num);
    getchar();
    if(num<1 || num>k)
    {
        system ("cls");
        printf("Неправильный ввод");
        free(buf);
        getchar();
        return;
    };
    print1(&buf[num-1]);
    puts("Редактировать(Д/Н)");
    gets(str);
    str[0] = toup(str[0]);
    if (str[0] == 'Д' || str[0]=='Н')
    {
        buf[num-1] = input_sportsman();
        f = fopen(filename, "wb");
        fwrite(buf, sizeof(struct sportperson), k, f);
        fclose(f);
    }
    else
            printf("Неправильный ввод");
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
        perror ("Ошибка открытия файла");
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
        puts("| N |              ФИО              | Пол | Вид спорта | Год | Рост |");
        puts("---------------------------------------------------------------------");
        for(j=0; j<10&&i<k; j++,i++)
        {
            printf("|%3d|%-31.31s|%-5c|%-12.12s|%5d|%6d|\n",
            i+1, buf[i].name, buf[i].gender, buf[i].sport,buf[i].year, buf[i].height);
            puts("---------------------------------------------------------------------");
        };
        puts("1. Вывести предыдущие 10 записей");
        puts("2. Вывести следующие 10 записей");
        puts("3. Прекратить вывод");
        scanf("%d%*c", &num);
        system ("cls");
        switch (num)
        {
            case 1 :
                if(i<11)
                {
                    puts("Предыдущих записей нет.");
                    getchar();
                    return;
                }
                else
                    i-=10+j;
                break;
            case 2 :
                if(i>=k)
                {
                    puts("Следующих записей нет.");
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
    puts("Введите номер записи");
    scanf("%d", &num);
    getchar();
    if(num<1 || num>k)
    {
        system ("cls");
        printf("Неправильный ввод");
        free(buf);
        getchar();
        return;
    };
    if (!(f=fopen(filename, "wb")))
    {
        perror("Не удалось открыть файл.");
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
    if ((c>='a'&& c<='z') || (c>='а'&& c<='я'))
        c-=32;
    return c;
}

char tolow(char c)
{
    if ((c>='A'&& c<='Z') || (c>='А'&& c<='Я'))
        c+=32;
    return c;
}

void tolowerstring(char *a)
{
    int i;
    for (i=0; a[i]!='\0'; i++)
        a[i]=tolow(a[i]);
}
