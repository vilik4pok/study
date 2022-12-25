#include <iostream>
#include <queue>
template<class T> class Queue
{
    std::queue<T> object;
public:
    Queue(){};
    ~Queue(){std::queue<T> empty; std::swap(object, empty);};
    bool isEmpty(){return object.empty();};
    T Front(){return object.front();};
    void EnQueue(T x){object.push(x);};
    T DeQueue(){T num = Front(); object.pop(); return num;};
};

template<class T>
void menu(Queue<T> *object)
{
    setlocale(LC_ALL, "rus");
    int menu;
    T num;
    do
    {
        system("cls");
        std::cout<<"1. Добавить в очередь\n";
        std::cout<<"2. Неразрушающее чтение\n";
        std::cout<<"3. Убрать из очереди\n";
        std::cout<<"4. Проверить на пустоту\n";
        std::cout<<"5. Выйти\n";
        std::cin>>menu;
        getchar();
        switch(menu)
        {
            case 1: std::cin>>num;
                    object->EnQueue(num);
                    break;
            case 2: if(object->isEmpty())
                        std::cout<<"Очередь пуста\n";
                    else
                        std::cout<<object->Front();
                    break;
            case 3: if(object->isEmpty())
                        std::cout<<"Очередь пуста\n";
                    else
                        std::cout<<object->DeQueue();
                    break;
            case 4: std::cout<<object->isEmpty();
                    break;
            case 5: break;
            default: std::cout<<"Неправильный ввод\n";
                     break;
        }; getchar();
    }
    while(menu!=5);
};

int main()
{
    Queue<int> a;
    Queue<float> b;
    int choice;
    setlocale(LC_ALL, "rus");
    std::cout << "1. Тип int\n";
    std::cout << "2. Тип float\n";
    std::cin >> choice;
    if(choice != 1 && choice != 2)
    {
        std::cout << "Неправильный ввод";
        return 0;
    };
    if (choice == 1)
        menu(&a);
    else
        menu(&b);
    return 0;
}
