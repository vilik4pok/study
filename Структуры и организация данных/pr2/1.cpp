#include "graph1.cpp"
#include "graph2.cpp"
#include <fstream>
#include <iostream>
#include <locale.h>
#include <string.h>
int main(int argc, char* files[])
{

    int num, i=0, j=0;
    char filename[80], c;

    Graph1 a;
    Graph2 b;
    setlocale(LC_ALL, "rus");
    if(argc<2)
    {
        std::cout << "Имя файла:";
        std::cin.getline(filename, 80);
    }
    else
        strcpy(filename,files[1]);
    std::fstream f(filename);
    if(!f.is_open())
    {
        std::cout<<"Не удалось открыть файл";
        return 0;
    };
    while(f>>num)
    {
        if(i==0)
        {
            a.addNode();
            b.addNode();
        };
        a.addEdge(i,j, num);
        b.addEdge(i,j, num);
        j++;
        while(f.get(c))
        {
            if(c>='0' && c<='9' || c=='-')
            {
                f.unget();
                break;
            }
            if(c=='\n')
            {
                i++;
                j=0;
                break;
            };
        };
    };
    f.close();
    std::cout<<"Матрица смежности:\n";
    a.print();
    std::cout<<"Списки вершин смежности:\n";
    b.print();
    std::cout<<"Диаметр:\n";
    a.getDiameter();
    b.getDiameter();
    return 0;
}
