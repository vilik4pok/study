//#include "menu.cpp"
#include <iostream>
typedef double DataType;
class Deque: public Menu
{
    int left, right, sizeOfDeque;
    DataType* data;
public:
    Deque(int size);
    ~Deque();
    int isEmpty();
    int isFull();
    int inRight (DataType x);
    DataType readLeft();
    DataType readRight();
    DataType outLeft();
    DataType outRight();
};

Deque::Deque(int size)
{
    sizeOfDeque = size+1;
    data = new DataType[sizeOfDeque];
    left = 0;
    right = sizeOfDeque-1;
}

Deque::~Deque()
{
    delete[] data;
}

int Deque::isEmpty()
{
    return (right+1)%sizeOfDeque == left;
}

int Deque::isFull()
{
    return (right+2)%sizeOfDeque == left;
}

DataType Deque::readLeft()
{
    return data[left];
}

DataType Deque::readRight()
{
    return data[right];
}

int Deque::inRight(DataType x)
{
    if(this->isFull())
        return 0;
    right = (right+1)%sizeOfDeque;
    data[right] = x;
    return 1;
}

DataType Deque::outRight()
{
//    if(this->isEmpty())
//        return NULL;
    int temp = right;
    right = right ? right-1 : sizeOfDeque-1;
    return data[temp];
}

DataType Deque::outLeft()
{
    int temp = left;
    left = (left+1)%sizeOfDeque;
    return data[temp];
}
