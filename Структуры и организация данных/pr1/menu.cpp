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
    std::cout << "Введите кол-во молока в баке: ";
    std::cin >> milk;
    std::cout << "Введите номинальный объем бутылки: ";
    std::cin >> bottle;
    if(bottle<0 || milk<0)
    {
        std::cout << "Неправильный ввод";
        return;
    };
    while(milk>=bottle || !this->isEmpty())
    {
        rand = (double)(std::rand()%21-10)/100+1;
        if(!this->isFull() && milk>=bottle*rand)
        {
            milk-=rand*bottle;
            this->inRight(rand*bottle);
            std::cout << "Налито " << this->readRight() << " молока\n";
            if(this->readRight() < bottle)
            {
                milk+=this->outRight();
                std::cout <<"Недолив - бутылка извечена, молоко возвращено в бак\n";
            }
            else
                if(milk < bottle)
                    std::cout << "В баке осталось "<<milk<<" молока\n";
        }
        else
            if(!this->isEmpty())
                std::cout << "Бутылка " << this->outLeft() << " объема отправлена на склад\n";
    };
    std::cout << "Все бутылки отправлены на склад\n";
}
