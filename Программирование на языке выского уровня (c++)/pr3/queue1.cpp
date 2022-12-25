#include <iostream>
#include <cstdlib>
template<class T> class Queue
{
    int head, tail;
    int maxLength;
    T *data;
public:
    Queue(int n=10);
    ~Queue();
    bool isEmpty(void);
    bool isFull(void);
    T Front(void);
    bool EnQueue(T x);
    T DeQueue(void);
};

template<class T>
Queue<T>::Queue(int n)
{
    maxLength = n;
    data=new T[maxLength];
    head=0;
    tail=maxLength-1;
}

template<class T>
Queue<T>::~Queue()
{
    delete[] data;
}

template<class T>
bool Queue<T>::isEmpty(void)
{
    return (tail+1)%maxLength == head;
}

template<class T>
bool Queue<T>::isFull(void)
{
    return (tail+2)%maxLength == head;
}

template<class T>
T Queue<T>::Front (void)
{
    return data[head];
}

template<class T>
bool Queue<T>::EnQueue (T x)
{
    if (this->isFull()) return false;
    tail = (tail+1)%maxLength;
    data[tail] = x;
    return true;
}

template<class T>
T Queue<T>::DeQueue (void)
{
    int temp = head;
    head = (head+1)%maxLength;
    return data[temp];
}
