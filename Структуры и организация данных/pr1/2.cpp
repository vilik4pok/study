#include "menu.cpp"
#include "deque1.cpp"
#include "deque2.cpp"
int main()
{
    system("chcp 1251");
    int choice;
    std::cout << "1. ��������� ���\n";
    std::cout << "2. ������� ���\n";
    std::cin >> choice;
    if(choice != 1 && choice != 2)
    {
        std::cout << "������������ ����";
        return 0;
    };
    if (choice == 1)
    {
        Deque a(10);
        a.print();
    }
    else
    {
        Deque2 a(10);
        a.print();
    };
    return 0;
}
