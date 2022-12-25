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
    printf("������� Enter..\n");
    getchar();
    do
    {
        system ("CLS");
        puts (" 1. ������ � ���������� �������������� �����");
        puts (" 2. ������ � ���������� ������ �����");
        puts (" 3. ������ �������������� ����� �� ���������� c");
        puts (" 4. ������ ������ ����� �� ���������� c");
        puts (" 5. �������� �������������� ����� � ���������� c");
        puts (" 6. �������� ������ ����� � ���������� c");
        puts (" 7. �������� ����������� ����� � �������");
        puts (" 8. ������� ����������� �����");
        puts (" 9. ������� �������������� ����� ������������ �����");
        puts ("10. ������� ������ ����� ������������ �����");
        puts ("11. ��������� �� ��������� ����������� ����� a � b");
        puts ("12. ��������� �� ����������� ����������� ����� a � b");
        puts ("13. ������� ����������� ����� a � b (a+=b)");
        puts ("14. ������� ����������� ����� a � ���. ������ c (a+=c)");
        puts ("15. ������ � ���������� c");
        puts ("16. ������� c");
        puts ("17. �����");
        scanf("%d%*c", &menu);
        system ("CLS");
        switch(menu)
        {
            case 1: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.readRealCoefficient(); break;
                        case 2: b.readRealCoefficient(); break;
                    };
                    break;
            case 2: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.readImaginateCoefficient(); break;
                        case 2: b.readImaginateCoefficient(); break;
                    };
                    break;
            case 3: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.setRealCoefficient(c); break;
                        case 2: b.setRealCoefficient(c); break;
                    };
                    break;
            case 4: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.setImaginateCoefficient(c); break;
                        case 2: b.setImaginateCoefficient(c); break;
                    };
                    break;
            case 5: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: c = a.getRealCoefficient(); break;
                        case 2: c = b.getRealCoefficient(); break;
                    };
                    break;
            case 6: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: c = a.getImaginateCoefficient(); break;
                        case 2: c = b.getImaginateCoefficient(); break;
                    };
                    break;
            case 7: printf("������� �������: ");
                    scanf("%d", &n);
                    printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.exponent(n); break;
                        case 2: b.exponent(n); break;
                    };
                    break;
            case 8: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.print(); break;
                        case 2: b.print(); break;
                    };
                    break;
            case 9: printf("�������� �����:\n1. a\n2. b\n");
                    scanf("%d%*c", &menu2);
                    system ("CLS");
                    switch(menu2)
                    {
                        case 1: a.printRealCoefficient(); break;
                        case 2: b.printRealCoefficient(); break;
                    };
                    break;
            case 10:printf("�������� �����:\n1. a\n2. b\n");
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
            case 15:printf("������� �����: ");
                    scanf("%lf%*c", &c);
                    break;
            case 16:printf("%lf", c); break;
            case 17:break;
            default: printf("������������ ����"); break;
        };
        getchar();
    } while(menu !=17);
    return 0;
}
