#include <vector>
#include <iostream>
template<class T>
T maxNegative(std::vector<T> &arr)
{
    T max;
    int i;
    for(i=0; i<arr.size(); i++)
        if(arr[i]<0)
        {
            max = arr[i++];
            break;
        }
   for(; i<arr.size(); i++)
        if(arr[i]>max && arr[i]<0)
            max = arr[i];
    return max;
}

int main()
{
    int choice, count;
    std::vector<int> arr1;
    std::vector<float> arr2;
    setlocale(LC_ALL, "rus");
    std::cout << "1. Тип int\n";
    std::cout << "2. Тип float\n";
    std::cin >> choice;
    std::cout << "Введите кол-во элементов массива: ";
    std::cin >> count;
    if(choice!=1 && choice != 2 || count<0)
    {
        std::cout<<"Неправильный ввод\n";
        return 0;
    };
    if(choice == 1)
    {
        int num;
        std::cout<<"Введите "<<count<<" элементов: ";
        for(int i = 0; i<count; i++)
        {
            std::cin>>num;
            arr1.push_back(num);

        };
        std::cout<<"Если 0, значит нет отрицательных\nНаибольший из отрицательных: " << maxNegative(arr1);
        std::vector<int> empty;
        std::swap(arr1, empty);
    }
    else
        {
            float num;
            std::cout<<"Введите "<<count<<" элементов: ";
            for(int i = 0; i<count; i++)
            {
                std::cin>>num;
                arr2.push_back(num);
            };
            std::cout<<"Если 0, значит нет отрицательных\nНаибольший из отрицательных: " << maxNegative(arr2);
            std::vector<float> empty;
            std::swap(arr2, empty);
        };
    return 0;
}
