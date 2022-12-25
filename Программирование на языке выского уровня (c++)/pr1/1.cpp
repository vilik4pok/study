#include "complexnumber.cpp"
#include <iostream>
#include <stdlib.h>
#include <locale.h>
int main()
{
    setlocale(LC_ALL, "rus");
    ComplexNumber a(1,2), b(a);
    double c;
    int menu, menu2, n;
    printf("Нажмите Enter..\n");
    getchar();
    do
    {
        system ("CLS");
        puts (" 1. Ввести с клавиатуры действительную часть");
        puts (" 2. Ввести с клавиатуры мнимую часть");
        puts (" 3. Задать действительную часть из переменной c");
        puts (" 4. Задать мнимую часть из переменной c");
        puts (" 5. Записать действительную часть в переменную c");
        puts (" 6. Записать мнимую часть в переменную c");
        puts (" 7. Возвести комплексное число в степень");
        puts (" 8. Вывести комплексное число");
        puts (" 9. Вывести действительную часть комплексного числа");
        puts ("10. Вывести мнимую часть комплексного числа");
        puts ("11. Проверить на равенство комплексные числа a и b");
        puts ("12. Проверить на неравенство комплексные числа a и b");
        puts ("13. Сложить комплексное число a с b (a+=b)");
        puts ("14. Сложить комплексное число a с вещ. числом c (a+=c)");
        puts ("15. Ввести с клавиатуры c");
        puts ("16. Вывести c");
        puts ("17. Выйти");
        scanf("%d%*c", &menu);
        system ("CLS");
        switch(menu)
        {
            case 1: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.readRealCoefficient(); break;
                        case 2: b.readRealCoefficient(); break;
                    };
                    break;
            case 2: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.readImaginateCoefficient(); break;
                        case 2: b.readImaginateCoefficient(); break;
                    };
                    break;
            case 3: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.setRealCoefficient(c); break;
                        case 2: b.setRealCoefficient(c); break;
                    };
                    break;
            case 4: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.setImaginateCoefficient(c); break;
                        case 2: b.setImaginateCoefficient(c); break;
                    };
                    break;
            case 5: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: c = a.getRealCoefficient(); break;
                        case 2: c = b.getRealCoefficient(); break;
                    };
                    break;
            case 6: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: c = a.getImaginateCoefficient(); break;
                        case 2: c = b.getImaginateCoefficient(); break;
                    };
                    break;
            case 7: printf("Введите степень: ");
                    scanf("%d", &n);
                    printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.exponent(n); break;
                        case 2: b.exponent(n); break;
                    };
                    break;
            case 8: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.print(); break;
                        case 2: b.print(); break;
                    };
                    break;
            case 9: printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.printRealCoefficient(); break;
                        case 2: b.printRealCoefficient(); break;
                    };
                    break;
            case 10:printf("Выберите число:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.printImaginateCoefficient(); break;
                        case 2: b.printImaginateCoefficient(); break;
                    };
                    break;
            case 11:printf("a==b = %d", a==b); break;
            case 12:printf("a!=b = %d", a!=b); break;
            case 13:a+=b; break;
            case 14:a+=c; break;
            case 15:printf("Введите число: ");
                    scanf("%lf%*c", &c);
                    break;
            case 16:printf("%lf", c); break;
            case 17:break;
            default: printf("Неправильный ввод"); break;
        };
        getchar();
    } while(menu !=17);
    return 0;
}
