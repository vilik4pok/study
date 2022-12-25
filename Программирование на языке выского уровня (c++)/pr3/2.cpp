#include <iostream>
#include "queue1.cpp"
#include "queue2.cpp"
template<template<typename> class T, typename C>
void menu(T<C> *object)
{
    setlocale(LC_ALL, "rus");
    int menu;
    C num;
    do
    {
        system("cls");
        std::cout<<"1. �������� � �������.\n";
        std::cout<<"2. ������������� ������\n";
        std::cout<<"3. ������ �� �������\n";
        std::cout<<"4. ��������� �� �������\n";
        std::cout<<"5. ��������� �� �������������\n";
        std::cout<<"6. �����\n";
        std::cin>>menu;
        getchar();
        switch(menu)
        {
            case 1: if(object->isFull())
                        std::cout<<"������� ���������\n";
                    else
                    {
                        std::cin>>num;
                        getchar();
                        object->EnQueue(num);
                    };
                    break;
            case 2: if(object->isEmpty())
                        std::cout<<"������� �����\n";
                    else
                        std::cout<<object->Front();
                    break;
            case 3: if(object->isEmpty())
                        std::cout<<"������� �����\n";
                    else
                        std::cout<<object->DeQueue();
                    break;
            case 4: std::cout<<object->isEmpty();
                    break;
            case 5: std::cout<<object->isFull();
                    break;
            case 6: break;
            default: std::cout<<"������������ ����\n";
                     break;
        }; getchar();
    }
    while(menu!=6);
};

int main()
{
    system("chcp 1251");
    system("cls");
    int choice, choice2;
    std::cout << "1. ��������� �������\n";
    std::cout << "2. ������� �������\n";
    std::cin >> choice;
    std::cout << "1. ��� int\n";
    std::cout << "2. ��� float\n";
    std::cin >> choice2;
    if(choice != 1 && choice != 2 || choice2 != 1 && choice2 != 2)
    {
        std::cout << "������������ ����";
        return 0;
    };
    if (choice == 1)
    {
        if(choice2 == 1)
        {
            Queue<int> a;
            menu<Queue, int>(&a);
        }
        else
        {
            Queue<float> a;
            menu<Queue, float>(&a);
        }
    }
    else
    {
        if(choice2 == 1)
        {
            Queue2<int> a;
            menu<Queue2, int>(&a);
        }
        else
        {
            Queue2<float> a;
            menu<Queue2, float>(&a);
        }
    };
    return 0;
}
