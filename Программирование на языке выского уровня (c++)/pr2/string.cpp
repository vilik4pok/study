#include "string.h"
#include <iostream>
#include <cstring>
#define PrintMethodName1 1



String::String()
{
    if(PrintMethodName1)
        std::cout << "String::String()\n";
    str = new char[1];
    *str = '\0';
    size = 1;
}

String::String(char c)
{
    if(PrintMethodName1)
        std::cout << "String::String(char c)\n";
    str = new char[2];
    *str = c;
    *(str+1) = '\0';
    size = 2;
}


String::String(char *strSource)
{
    if(PrintMethodName1)
        std::cout << "String::String(char *strSource)\n";
    size = strlen(strSource)+1;
    str = new char[size];
    strcpy(str, strSource);
}

String::String(const String& object)
{
    if(PrintMethodName1)
        std::cout << "String::String(const String& object)\n";
    size = object.size;
    str = new char[size];
    strcpy(str, object.str);
    copyCount++;
}

String::~String()
{
    if(PrintMethodName1)
        std::cout << "String::~String()\n";
    delete[] str;
    str = NULL;
}

String String::operator=(const String& object)
{
    if(PrintMethodName1)
        std::cout << "String::operator=(const String& object)\n";
    delete[] str;
    size = object.size;
    str = new char[size];
    strcpy(str, object.str);
    return *this;
}

String String::operator=(char *strSource)
{
    if(PrintMethodName1)
        std::cout << "String::operator=(char *strSource)\n";
    delete[] str;
    if(strSource)
    {
        size = strlen(strSource);
        str = new char[size];
        strcpy(str, strSource);
    }
    else
    {
        str = new char[1];
        *str = '\0';
        size = 1;
    };
    return *this;
}

String String::operator=(const char *strSource)
{
    if(PrintMethodName1)
        std::cout << "String::operator=(const char *strSource)\n";
    delete[] str;
    size = strlen(strSource)+1;
    str = new char[size];
    strcpy(str, strSource);
    return *this;
}

void String::print()
{
    if(PrintMethodName1)
        std::cout << "String::print()\n";
    if(str)
        std::cout << str <<"\n";
}

int String::strLenght()
{
    if(PrintMethodName1)
        std::cout << "String::strLenght()\n";
    if(str)
        size = strlen(str)+1;
    return size-1;
}

int String::getType()
{
    if(PrintMethodName1)
        std::cout << "String::getType()\n";
    return 1;
}

int String::copyCount=0;

void String::printCopyCount()
{
    if(PrintMethodName1)
        std::cout << "String::printCopyCount()\n";
    std::cout<<copyCount;
};



