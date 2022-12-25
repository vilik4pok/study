#include <iostream>
#include <string.h>
//#include <clocale>
#include <fstream>
struct sportperson
{
    char name[79], gender, sport[32];
    int year, height;
};
typedef struct sportperson DataType;
struct element
{
    DataType data;
    struct element *next, *prev;
};
struct List
{
    struct element *begin, *end;
};

void makenull(struct List* list)
{
    list->begin = NULL;
    list->end = NULL;
};

struct List add_begin(struct List list, DataType data)
{
    struct element* temp = (struct element*) malloc (sizeof(struct element));
    temp->data = data;
    temp->prev = NULL;
    temp->next = list.begin;
    if (list.begin)
        list.begin->prev = temp;
    else
        list.end = temp;
    list.begin = temp;
    return list;
}

struct List add_end(struct List list, DataType data)
{
    struct element* temp = (struct element*) malloc(sizeof(struct element));
    temp->data = data;
    temp->next = NULL;
    temp->prev = list.end;
    if (list.end)
        list.end->next = temp;
    else
        list.begin = temp;
    list.end = temp;
    return list;
}

struct List delete_end(struct List list)
{
    struct element *temp;
    if (list.end)
    {
        temp = list.end;
        list.end = list.end->prev;
        if(!list.end)
            list.begin = NULL;
        else
            list.end->next = NULL;
        free(temp);
    }
    return list;
}

struct List delete_begin(struct List list)
{
    struct element *temp;
    if (list.begin)
    {
        temp = list.begin;
        list.begin = list.begin->next;
        if (!list.begin)
            list.end = NULL;
        else
            list.begin->prev = NULL;
        free(temp);
    };
    return list;
}

int sizeOfList(struct List list)
{
    int i=0;
    while(list.begin)
    {
        list.begin = list.begin->next;
        i++;
    }
    return i;
}

void printLine(DataType data, int i)
{
    printf("|%3d|%-31.31s|%-5c|%-12.12s|%5d|%6d|\n",i, data.name, data.gender, data.sport,
    data.year, data.height);
    puts("---------------------------------------------------------------------");
}

void printList(struct List list)
{
    int i=0, j, k, num, size = sizeOfList(list);
    if(!list.begin)
    {
        std::cout<<"Список пуст";
        return;
    };
    while (1)
    {
        system ("cls");
        puts("| N |              ФИО              | Пол | Вид спорта | Год | Рост |");
        puts("---------------------------------------------------------------------");
        for (j=0; j<10; j++)
        {
            printLine(list.begin->data, ++i);
            if(list.begin->next)
                list.begin = list.begin->next;
            else
            {
                j++;
                break;
            };
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
                    return;
                }
                else
                    for(k = 1; k<10+j; k++, list.begin = list.begin->prev);
                    i-=10+j;
                break;
            case 2 :
                if(i == size)
                {
                    puts("Следующих записей нет.");
                    return;
                };
                break;
            case 3 : return; break;
            default : std::cout << "Неправильный ввод"; return; break;
        };
    };
}

void printListBack(struct List list)
{
    int i=0, j, k, num, size = sizeOfList(list);
    while (1)
    {
        system ("cls");
        puts("| N |              ФИО              | Пол | Вид спорта | Год | Рост |");
        puts("---------------------------------------------------------------------");
        for (j=0; j<10; j++)
        {
            printLine(list.end->data, ++i);
            if(list.end->prev)
                list.end = list.end->prev;
            else
            {
                j++;
                break;
            };
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
                    return;
                }
                else
                    for(k = 1; k<10+j; k++, list.end = list.end->next);
                    i-=10+j;
                break;
            case 2 :
                if(i == size)
                {
                    puts("Следующих записей нет.");
                    return;
                };
                break;
            case 3 : return; break;
            default : std::cout << "Неправильный ввод"; return; break;
        };
    };
}

struct List deleteElementByNumber(struct List list, int number)
{
    int size = sizeOfList(list);
    if (number>size||number<1)
        return list;
    if (number == 1)
        list = delete_begin(list);
    else
        if (number == size)
            list = delete_end(list);
    else
    {
        struct element *temp = list.begin;
        for (int i=1; i<number; i++, temp=temp->next);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    };
    return list;

}

struct List deleteList(struct List list)
{
    while(list.begin)
        list = delete_begin(list);
    return list;
}

void insert(struct element* element, DataType data)
{
    struct element* temp = (struct element*) malloc (sizeof(struct element));
    temp->data = data;
    temp->prev = element;
    temp->next = element->next;
    element->next->prev = temp;
    element->next = temp;
}

struct List addWithSort(struct List list, DataType data)
{
    struct element* temp = list.begin;
    while(temp&&strcmp(data.name, temp->data.name)>0)
        temp = temp->next;
    if(!temp)
        list = add_end(list, data);
    else
        if(!temp->prev)
            list = add_begin(list, data);
        else
            insert(temp->prev, data);
    return list;
}

struct List readFileToList(char *filename)
{
    struct List list;
    DataType data;
    makenull(&list);
    std::ifstream fin(filename, std::ios_base::binary);
    if (fin.is_open())
    {
        while(fin.read((char*)&data, sizeof(DataType)))
            list = addWithSort(list, data);
        fin.close();
    };
    return list;
}

void writeListToFile(struct List list, char *filename)
{
    std::ofstream fout(filename, std::ios_base::binary);
    if (!fout.is_open())
        printf("Ошибка при открытии файла.\n");
    else
    {
        while(list.begin&&fout.write((char*)&list.begin->data, sizeof(DataType)))
            list.begin = list.begin->next;
        fout.close();
    };
}

void toLowerString(char* str)
{
    for(; *str; str++)
        *str = std::tolower(*str);
}

DataType readData()
{
    DataType data;
    char temp[10];
    std::cout << "ФИО: ";
    std::cin.getline(data.name, 78);
    data.name[0] = std::toupper(data.name[0]);
    std::cout << "Пол(М/Ж): ";
    std::cin.getline(temp, 9);
    data.gender = std::toupper(temp[0]);
    std::cout << "Вид спорта: ";
    std::cin.getline(data.sport, 32);
    toLowerString(data.sport);
    std::cout << "Год рождения: ";
    std::cin >> data.year;
    std::cout << "Рост: ";
    std::cin >> data.height;
    return data;
}

void print1(DataType *data)
{
    printf("ФИО:%s\nПол:%c\nВид спорта:%s\nГод:%d\nРост:%d\n",
    data->name, data->gender, data->sport, data->year, data->height);
}

void findMan(struct List list)
{
    DataType entry;
    int flag = 0;
    while(list.begin)
    {
        if(list.begin->data.gender =='М'&&strcmp(list.begin->data.sport,"плавание")==0)
        {
            flag=1;
            entry = list.begin->data;
            break;
        };
        list.begin = list.begin->next;
    };
    if(flag)
    {
        while(list.begin)
        {
            if(list.begin->data.gender == 'М' && list.begin->data.height > entry.height && (strcmp(list.begin->data.sport,"плавание")==0))
                entry = list.begin->data;
            list.begin = list.begin->next;
        }
        print1(&entry);
    }
    else
        printf("Не найдено");
}

void findWomen(struct List list)
{
    struct List tmpList;
    makenull(&tmpList);
    while(list.begin)
    {
        if((list.begin->data.gender == 'Ж') && (2021 - list.begin->data.year>=14) && (2021 - list.begin->data.year<=17))
            tmpList = addWithSort(tmpList, list.begin->data);
        list.begin = list.begin->next;
    }
    if(tmpList.begin)
        printList(tmpList);
    else
        printf("Не найдено");
}

int main(int argc, char* files[])
{
    setlocale(LC_ALL, "rus");
    system("chcp 1251");
    system("cls");
    char filename[50];
    int menu, num;
    struct List list;
    if(argc<2)
    {
        puts ("Имя файла:");
        gets (filename);
    }
    else
        strcpy(filename,files[1]);
    list = readFileToList(filename);
    do
    {
        system ("CLS");
        puts ("1. Добавление записи");
        puts ("2. Просмотр записей");
        puts ("3. Просмотр записей в обратном порядке");
        puts ("4. Удаление записи");
        puts ("5. Найти мужчину");
        puts ("6. Найти женщин");
        puts ("7. Сохранить изменения и выйти");
        scanf ("%d%*c", &menu);
        system ("CLS");
        switch (menu)
        {
            case 1 :    list = addWithSort(list, readData()); break;
            case 2 :    printList(list); break;
            case 3 :    printListBack(list); break;
            case 4 :    std::cout << "Введите номер записи: ";
                        std::cin >> num;
                        if(num>0&&num<=sizeOfList(list))
                            list = deleteElementByNumber(list, num);
                        else
                            std::cout << "Неправильный ввод";
                        break;
            case 5 :    findMan(list); break;
            case 6 :    findWomen(list); break;
            case 7 :    break;
            default :   std::cout << "Неправильный ввод"; break;
        };
        getchar();
    } while (menu!=7);
    writeListToFile(list, filename);
    list = deleteList(list);
    return 0;
}
