#include "pch.h"
#include "SquareNegative.h"
#include <iostream>



void SquareNegative(double* arr, int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i] < 0)
            arr[i] *= arr[i];
}

void ReadArray(double* arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = getValue();
}

double getValue()
{

    double a;
    while (true)
    {
        system("cls");
        std::cin >> a;

        if (std::cin.fail()) 
        {
            std::cout << "wrong input\n";
            std::cin.clear(); 
            std::cin.ignore(32767, '\n'); 
            system("pause");
        }
        else 
            return a;
    }
}


void PrintArray(double* arr, int size)
{
    for (int i = 0; i < size; i++)
        std::cout<< arr[i] <<" ";
    std::cout <<"\n";
}