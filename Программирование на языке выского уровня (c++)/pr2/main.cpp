#include "string.h"
#include "identifier.h"
#include "decimal.h"
#include <iostream>
int main()
{
    int menu, menu1, flag = 0, **numbers, i=0,countString=0,countIdentifier=0,countDecimal=0, operand1, operand2,  count, typeOperand1, typeOperand2;
    String **p;
    char start[80] ="", operator1;
    system("chcp 1251");
    do
    {
        system("cls");
        std::cout<<"1. �������������\n";
        std::cout<<"2. �����������\n";
        std::cout<<"3. �����\n";
        std::cin >> menu1;
        getchar();
        system("cls");
        switch(menu1)
        {
            case 1: std::cout<<"1. ����� ���������\n";
                    std::cout<<"2. ��������� ��������\n";
                    std::cin >> menu;
                    getchar();
                    switch(menu)
                    {
                        case 1: if(flag)
                                {
                                    std::cout<<"������ ����� ��������� ����� ������ ���� ���\n";
                                    getchar();
                                    break;
                                }
                                std::cout<<"������� ����� ���������: ";
                                std::cin >> count;
                                getchar();
                                if(count > 0)
                                {
                                    p = new String*[count];
                                    numbers = new int*[3];
                                    numbers[0] = new int[count];
                                    numbers[1] = new int[count];
                                    numbers[2] = new int[count];
                                    flag = 1;
                                }
                                else
                                    std::cout<<"������������ ����\n";
                                break;
                        case 2: if(!flag)
                                {
                                    std::cout << "������� ���-�� ���������\n";
                                    getchar();
                                    break;
                                };
                                std::cout<<"1. ��� ���� ���������\n";
                                std::cout<<"2. �������� �������� ��������\n";
                                std::cin >> menu;
                                getchar();
                                switch(menu)
                                {
                                    case 1: if(flag == 2)
                                            {
                                                std::cout<<"������ ��������� �������� ����� ������ ���� ���\n";
                                                getchar();
                                                break;
                                            };
                                            for(i=0; i<count; i++)
                                            {
                                                system("cls");
                                                std::cout<<"������� " << i+1<<"\n";
                                                std::cout<<"�������� ���\n";
                                                std::cout<<"1. ������\n";
                                                std::cout<<"2. ������-�������������\n";
                                                std::cout<<"3. ���������� �����\n";
                                                std::cin>> menu;
                                                getchar();
                                                std::cout<<"��������� �������� ��������: ";
                                                std::cin.getline(start, 79);
                                                switch(menu)
                                                {
                                                    case 1: p[i] = new String(start); numbers[0][countString++] = i; break;
                                                    case 2: p[i] = new Identifier(start); numbers[1][countIdentifier++] = i; break;
                                                    case 3: p[i] = new Decimal(start); numbers[2][countDecimal++] = i; break;
                                                    default: std::cout<< "������������ ����. ������� ����� ���� ������";
                                                             p[i] = new String(start);
                                                             numbers[0][countString++] = i;
                                                             getchar();
                                                             break;
                                                };
                                                getchar();
                                            };
                                            flag=2;
                                            break;
                                    case 2: if(flag!=2)
                                            {
                                                std::cout<< "��������� �� ���� ��������� ��������� �������� � ����� 1, ������ �������� ��������\n";
                                                getchar();
                                                break;
                                            };
                                            std::cout<<"������� ����� ��������: ";
                                            std::cin>> menu;
                                            getchar();
                                            if(menu>0 && menu<=count)
                                            {
                                                std::cout<<"����� �������� ��������: ";
                                                std::cin.getline(start, 79);
                                                int type = p[--menu]->getType();
                                                if(type == 2)
                                                    *(static_cast<Identifier*>(p[menu])) = start;
                                                else
                                                    if(type == 3)
                                                        *(static_cast<Decimal*>(p[menu])) = start;
                                                    else
                                                        *p[menu] = start;
                                            }
                                            else
                                                std::cout<<"������������ ����\n";
                                            getchar();
                                            break;
                                    default: std::cout<<"������������ ����"; break;
                                };
                                break;
                        default: std::cout<< "������������ ����"; break;
                    };
                    break;
            case 2: if(flag !=2)
                    {
                        std::cout<<"�� ������� ����� 1 (�������������)\n";
                        getchar();
                        break;
                    };
                    std::cout<<"1. ������\n";
                    std::cout<<"2. ������-�������������\n";
                    std::cout<<"3. ���������� �����\n";
                    std::cout<<"4. ������ ��������\n";
                    std::cin>> menu;
                    getchar();
                    switch(menu)
                    {
                        case 1: std::cout<<"1. ������\n";
                                std::cout<<"2. ����� ������\n";
                                std::cout<<"3. ���\n";
                                std::cout<<"4. ���-�� �����������\n";
                                std::cin>> menu;
                                getchar();
                                if(menu>0 && menu<5)
                                    for(i=0; i<countString; i++)
                                    {
                                        switch(menu)
                                        {
                                            case 1: p[numbers[0][i]]->print(); break;
                                            case 2: std::cout<<p[numbers[0][i]]->strLenght()<<"\n"; break;
                                            case 3: std::cout<<p[numbers[0][i]]->getType()<<"\n"; break;
                                            case 4: p[numbers[0][i]]->printCopyCount(); break;
                                        };
                                    }
                                else
                                    std::cout<< "������������ ����\n";
                                break;
                        case 2: std::cout<<"1. ������\n";
                                std::cout<<"2. ����� ������\n";
                                std::cout<<"3. ���\n";
                                std::cout<<"4. ���-�� �����������\n";
                                std::cout<<"5. � ������� ��������\n";
                                std::cin>> menu;
                                getchar();
                                if(menu>0 && menu<6)
                                    for(i=0; i<countIdentifier; i++)
                                    {
                                        std::cout<<"������� "<<numbers[1][i]+1<<": ";
                                        switch(menu)
                                        {
                                            case 1: p[numbers[1][i]]->print(); break;
                                            case 2: std::cout<<p[numbers[1][i]]->strLenght()<<"\n"; break;
                                            case 3: std::cout<<p[numbers[1][i]]->getType()<<"\n"; break;
                                            case 4: p[numbers[1][i]]->printCopyCount(); break;
                                            case 5: (static_cast<Identifier*>(p[numbers[1][i]])->toLowerCase()).print(); break;
                                        };
                                    }
                                else
                                    std::cout<< "������������ ����\n";
                                break;
                        case 3: std::cout<<"1. ������\n";
                                std::cout<<"2. ����� ������\n";
                                std::cout<<"3. ���\n";
                                std::cout<<"4. ���-�� �����������\n";
                                std::cout<<"5. ������� ����\n";
                                std::cout<<"6. ����������� � Long?\n";
                                std::cin>> menu;
                                getchar();
                                if(menu>0 && menu<7)
                                    for(i=0; i<countDecimal; i++)
                                    {
                                        std::cout<<"������� "<<numbers[2][i]+1<<": ";
                                        switch(menu)
                                        {
                                            case 1: p[numbers[2][i]]->print(); break;
                                            case 2: std::cout<<p[numbers[2][i]]->strLenght()<<"\n"; break;
                                            case 3: std::cout<<p[numbers[2][i]]->getType()<<"\n"; break;
                                            case 4: p[numbers[2][i]]->printCopyCount(); break;
                                            case 5: (static_cast<Decimal*>(p[numbers[2][i]])->makeNegative()).print(); break;
                                            case 6: std::cout<<(static_cast<Decimal*>(p[numbers[2][i]])->isLong())<<"\n"; break;
                                        };
                                    }
                                else
                                    std::cout<< "������������ ����\n";
                                break;
                        case 4: std::cout<<"������-�������������\n";
                                for(i=0; i<countIdentifier; i++)
                                {
                                    std::cout<<"������� "<<numbers[1][i]+1<<": ";
                                    p[numbers[1][i]]->print();
                                };
                                std::cout<<"���������� �����\n";
                                for(i=0; i<countDecimal; i++)
                                {
                                    std::cout<<"������� "<<numbers[2][i]+1<<": ";
                                    p[numbers[2][i]]->print();
                                };
                                std::cout<<"������ �������. ������� ����� ��������: ";
                                std::cin>> operand1;
                                getchar();
                                system("cls");
                                std::cout<<"������\n";
                                for(i=0; i<countString; i++)
                                {
                                    std::cout<<"������� "<<numbers[0][i]+1<<": ";
                                    p[numbers[0][i]]->print();
                                };
                                std::cout<<"������-�������������\n";
                                for(i=0; i<countIdentifier; i++)
                                {
                                    std::cout<<"������� "<<numbers[1][i]+1<<": ";
                                    p[numbers[1][i]]->print();
                                };
                                std::cout<<"���������� �����\n";
                                for(i=0; i<countDecimal; i++)
                                {
                                    std::cout<<"������� "<<numbers[2][i]+1<<": ";
                                    p[numbers[2][i]]->print();
                                };
                                std::cout<<"������ �������. ������� ����� ��������: ";
                                std::cin>> operand2;
                                getchar();
                                std::cout<<"������� ��������: ";
                                std::cin>> operator1;
                                getchar();
                                system("cls");
                                if(operand1<0 || operand1>count || operand2<0 || operand2>count )
                                {
                                    std::cout<<"������������ ����\n";
                                    break;
                                };
                                typeOperand1=p[--operand1]->getType();
                                typeOperand2 =p[--operand2]->getType();
                                if((typeOperand1 == 2 && (operator1 == '+' || operator1 == '*')) || (operator1!='+' && operator1!='-' && operator1!='*' && operator1!='='))
                                {
                                    std::cout << "�������� " <<'"'<<operator1<<'"'<<" �� ��������� ��� �������� �1\n";
                                    break;
                                };
                                p[operand1]->print();
                                std::cout<< operator1<<"\n";
                                p[operand2]->print();
                                std::cout<<"=\n";
                                if(typeOperand1 == 2)
                                {
                                    if(typeOperand2 == 1)
                                        switch(operator1)
                                        {
                                            case '-': (*static_cast<Identifier*>(p[operand1]) - *p[operand2]).print(); break;
                                            case '=': (*static_cast<Identifier*>(p[operand1]) = *p[operand2]).print(); break;
                                        };

                                    if(typeOperand2 == 2)
                                        switch(operator1)
                                        {
                                            case '-': (*static_cast<Identifier*>(p[operand1]) - *static_cast<Identifier*>(p[operand2])).print(); break;
                                            case '=': (*static_cast<Identifier*>(p[operand1]) = *static_cast<Identifier*>(p[operand2])).print(); break;
                                        };
                                    if(typeOperand2 == 3)
                                        switch(operator1)
                                        {
                                            case '-': (*static_cast<Identifier*>(p[operand1]) - *static_cast<Decimal*>(p[operand2])).print(); break;
                                            case '=': (*static_cast<Identifier*>(p[operand1]) = *static_cast<Decimal*>(p[operand2])).print(); break;
                                        };
                                }
                                else
                                {
                                    if(typeOperand2 == 1)
                                        switch(operator1)
                                        {
                                            case '+': (*static_cast<Decimal*>(p[operand1]) + *p[operand2]).print(); break;
                                            case '-': (*static_cast<Decimal*>(p[operand1]) - *p[operand2]).print(); break;
                                            case '*': (*static_cast<Decimal*>(p[operand1]) * *p[operand2]).print(); break;
                                            case '=': (*static_cast<Decimal*>(p[operand1]) = *p[operand2]).print(); break;
                                        };
                                    if(typeOperand2 == 2)
                                        switch(operator1)
                                        {
                                            case '+': (*static_cast<Decimal*>(p[operand1]) + *static_cast<Identifier*>(p[operand2])).print(); break;
                                            case '-': (*static_cast<Decimal*>(p[operand1]) - *static_cast<Identifier*>(p[operand2])).print(); break;
                                            case '*': (*static_cast<Decimal*>(p[operand1]) * *static_cast<Identifier*>(p[operand2])).print(); break;
                                            case '=': (*static_cast<Decimal*>(p[operand1]) = *static_cast<Identifier*>(p[operand2])).print(); break;
                                        };
                                    if(typeOperand2 == 3)
                                        switch(operator1)
                                        {
                                            case '+': (*static_cast<Decimal*>(p[operand1]) + *static_cast<Decimal*>(p[operand2])).print(); break;
                                            case '-': (*static_cast<Decimal*>(p[operand1]) - *static_cast<Decimal*>(p[operand2])).print(); break;
                                            case '*': (*static_cast<Decimal*>(p[operand1]) * *static_cast<Decimal*>(p[operand2])).print(); break;
                                            case '=': (*static_cast<Decimal*>(p[operand1]) = *static_cast<Decimal*>(p[operand2])).print(); break;
                                        };
                                };
                                break;
                        default: std::cout<< "������������ ����"; break;
                    }; getchar(); break;
            case 3 : break;
        };
    }while(menu1 !=3);
    for(i=0; i<count; i++)
        delete p[i];
    delete [] p;
    return 0;
}
