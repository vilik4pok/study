#include <iostream>
template<class T, class Tnumber>
T maxNegative(T *arr, Tnumber n)
{
    T max;
    Tnumber i;
    for(i = 0; i<n; i++)
        if(arr[i] < 0)
        {
            max = arr[i++];
            break;
        };
    for(; i<n; i++)
        if(arr[i]>max && arr[i]<0)
            max = arr[i];
    return max;
}

int main()
{
    int *arr1, choice, count;
    float *arr2;
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
        arr1 = new int[count];
        std::cout<<"Введите "<<count<<" элементов: ";
        for(int i = 0; i<count; i++)
            std::cin>>arr1[i];
        std::cout<<"Если 0, значит нет отрицательных\nНаибольший из отрицательных: " << maxNegative(arr1, count);
        delete[] arr1;
    }
    else
        {
            arr2 = new float[count];
            std::cout<<"Введите "<<count<<" элементов: ";
            for(int i = 0; i<count; i++)
                std::cin>>arr2[i];
            std::cout<<"Если 0, значит нет отрицательных\nНаибольший из отрицательных: " << maxNegative(arr2, count);
            delete[] arr2;
        };
    return 0;
}
