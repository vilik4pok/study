#include <iostream>
typedef double DataType;
class Menu
{
public:
    Menu(){};
    ~Menu(){};
    void print();
    virtual int isEmpty()=0;
    virtual int isFull()=0;
    virtual int inRight (DataType x)=0;
    virtual DataType readLeft()=0;
    virtual DataType readRight()=0;
    virtual DataType outLeft()=0;
    virtual DataType outRight()=0;
};

void Menu::print()
{
    double milk, bottle, rand;
    std::cout << "������� ���-�� ������ � ����: ";
    std::cin >> milk;
    std::cout << "������� ����������� ����� �������: ";
    std::cin >> bottle;
    if(bottle<0 || milk<0)
    {
        std::cout << "������������ ����";
        return;
    };
    while(milk>=bottle || !this->isEmpty())
    {
        rand = (double)(std::rand()%21-10)/100+1;
        if(!this->isFull() && milk>=bottle*rand)
        {
            milk-=rand*bottle;
            this->inRight(rand*bottle);
            std::cout << "������ " << this->readRight() << " ������\n";
            if(this->readRight() < bottle)
            {
                milk+=this->outRight();
                std::cout <<"������� - ������� ��������, ������ ���������� � ���\n";
            }
            else
                if(milk < bottle)
                    std::cout << "� ���� �������� "<<milk<<" ������\n";
        }
        else
            if(!this->isEmpty())
                std::cout << "������� " << this->outLeft() << " ������ ���������� �� �����\n";
    };
    std::cout << "��� ������� ���������� �� �����\n";
}
