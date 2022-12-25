#include "menu.cpp"
#include "deque1.cpp"
#include "deque2.cpp"
int main()
{
    system("chcp 1251");
    int choice;
    std::cout << "1. Векторный дек\n";
    std::cout << "2. Связной дек\n";
    std::cin >> choice;
    if(choice != 1 && choice != 2)
    {
        std::cout << "Неправильный ввод";
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
