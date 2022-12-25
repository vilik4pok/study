#include <iostream>
//#include "menu.cpp"
typedef double DataType;
struct element
{
    DataType data;
    struct element *next, *prev;
};
class Deque2 : public Menu
{
    struct element *left, *right;
    int sizeOfDeque, maxsize;
public:
    Deque2(int );
    ~Deque2();
    int isEmpty();
    int isFull();
    int inRight (DataType x);
    DataType readLeft();
    DataType readRight();
    DataType outLeft();
    DataType outRight();
};

Deque2::Deque2(int size)
{
    left = right = NULL;
    sizeOfDeque = 0;
    maxsize = size;
}

Deque2::~Deque2()
{
    while (left)
        this->outLeft();
}

int Deque2::isEmpty()
{
    if(left)
        return 0;
    return 1;
}

int Deque2::isFull()
{
    return sizeOfDeque == maxsize;
}

int Deque2::inRight(DataType x)
{
    struct element *temp;
    if (!(temp = new struct element))
        return 0;
    temp->data = x;
    temp->next = NULL;
    temp->prev = right;
    if(right)
        right->next = temp;
    else
        left = temp;
    right = temp;
    sizeOfDeque++;
    return 1;
}

DataType Deque2::outRight()
{
    struct element *temp = right;
    DataType data = temp->data;
    right = right->prev;
    if (!right)
        left = NULL;
    delete temp;
    sizeOfDeque--;
    return data;
}

DataType Deque2::outLeft()
{
    struct element *temp = left;
    DataType data = temp->data;
    left = left->next;
    if (!left)
        right = NULL;
    delete temp;
    sizeOfDeque--;
    return data;
}

DataType Deque2::readRight()
{
    return right->data;
}

DataType Deque2::readLeft()
{
    return left->data;
}
