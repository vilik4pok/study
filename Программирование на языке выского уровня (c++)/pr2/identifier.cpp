#include "identifier.h"
#include <cstring>
#include <iostream>
#define PrintMethodName2 1

int checkPossibility(char *tmp);

int Identifier::copyCount = 0;

Identifier::Identifier(const Identifier& object) : String(object)
{
    copyCount++;
}

Identifier::Identifier(const String& object) : Identifier(object.str)
{
    copyCount++;
}
Identifier::Identifier(const Decimal& object) : String()
{
   copyCount++;
}

int Identifier::getType()
{
    if(PrintMethodName2)
        std::cout << "Identifier::getType()\n";
    return 2;
}

void Identifier::printCopyCount()
{
    if(PrintMethodName2)
        std::cout << "Identifier::printCopyCount()\n";
    std::cout<<copyCount;
}

int checkPossibility(char *tmp)
{
    if(PrintMethodName2)
        std::cout << "friend Identifier int checkPossibility()\n";
    if(strcmp(tmp, "alignas") == 0 || strcmp(tmp, "alignof") == 0 || strcmp(tmp, "and") == 0 || strcmp(tmp, "and_eq") == 0 || strcmp(tmp, "asm") == 0 || strcmp(tmp, "auto") == 0 || strcmp(tmp, "bitand") == 0 || strcmp(tmp, "bitor") == 0 || strcmp(tmp, "bool") == 0 || strcmp(tmp, "break") == 0 || strcmp(tmp, "case") == 0 || strcmp(tmp, "catch") == 0 || strcmp(tmp, "char") == 0 || strcmp(tmp, "char16_t") == 0 || strcmp(tmp, "char32_t") == 0 || strcmp(tmp, "class") == 0 || strcmp(tmp, "compl") == 0 || strcmp(tmp, "const") == 0 || strcmp(tmp, "constexpr") == 0 || strcmp(tmp, "const_cast") == 0 || strcmp(tmp, "continue") == 0 || strcmp(tmp, "decltype 	") == 0 || strcmp(tmp, "default") == 0 || strcmp(tmp, "delete") == 0 || strcmp(tmp, "do") == 0 || strcmp(tmp, "double") == 0 || strcmp(tmp, "dynamic_cast") == 0 || strcmp(tmp, "else") == 0 || strcmp(tmp, "enum") == 0 || strcmp(tmp, "explicit") == 0 || strcmp(tmp, "export") == 0 || strcmp(tmp, "extern") == 0 || strcmp(tmp, "false") == 0 || strcmp(tmp, "float") == 0 || strcmp(tmp, "for") == 0 || strcmp(tmp, "friend") == 0 || strcmp(tmp, "goto") == 0 || strcmp(tmp, "if") == 0 || strcmp(tmp, "inline") == 0 || strcmp(tmp, "int") == 0 || strcmp(tmp, "long") == 0 || strcmp(tmp, "mutable") == 0 || strcmp(tmp, "namespace 	") == 0 || strcmp(tmp, "new") == 0 || strcmp(tmp, "noexcept") == 0 || strcmp(tmp, "not") == 0 || strcmp(tmp, "not_eq") == 0 || strcmp(tmp, "nullptr") == 0 || strcmp(tmp, "operator") == 0 || strcmp(tmp, "or") == 0 || strcmp(tmp, "or_eq") == 0 || strcmp(tmp, "private") == 0 || strcmp(tmp, "protected") == 0 || strcmp(tmp, "public") == 0 || strcmp(tmp, "register") == 0 || strcmp(tmp, "reinterpret_cast") == 0 || strcmp(tmp, "return") == 0 || strcmp(tmp, "short") == 0 || strcmp(tmp, "signed") == 0 || strcmp(tmp, "sizeof") == 0 || strcmp(tmp, "static") == 0 || strcmp(tmp, "static_assert") == 0 || strcmp(tmp, "static_cast") == 0 || strcmp(tmp, "struct") == 0 || strcmp(tmp, "switch") == 0 || strcmp(tmp, "template") == 0 || strcmp(tmp, "this") == 0 || strcmp(tmp, "thread_local") == 0 || strcmp(tmp, "throw") == 0 || strcmp(tmp, "true") == 0 || strcmp(tmp, "try") == 0 || strcmp(tmp, "typedef") == 0 || strcmp(tmp, "typeid") == 0 || strcmp(tmp, "typename") == 0 || strcmp(tmp, "union") == 0 || strcmp(tmp, "unsigned") == 0 || strcmp(tmp, "using") == 0 || strcmp(tmp, "virtual") == 0 || strcmp(tmp, "void") == 0 || strcmp(tmp, "volatile") == 0 || strcmp(tmp, "wchar_t") == 0 || strcmp(tmp, "while") == 0 || strcmp(tmp, "xor") == 0 || strcmp(tmp, "xor_eq") == 0)
        return 0;
    if (*tmp != '_' && (*tmp<'A' || *tmp>'Z') && (*tmp<'a' || *tmp>'z'))
        return 0;
    while(*++tmp)
        if(*tmp != '_' && (*tmp<'A' || *tmp>'Z') && (*tmp<'a' || *tmp>'z') && (*tmp<'1' || *tmp>'9'))
            return 0;
    return 1;
}

Identifier::~Identifier()
{
    if(PrintMethodName2)
        std::cout << "Identifier::~Identifier()\n";
    delete[] str;
    str = NULL;
}

Identifier::Identifier(char *strSource)
{
    if(PrintMethodName2)
        std::cout << "Identifier::Identifier(char *strSource)\n";
    if(checkPossibility(strSource))
    {
        delete[] str;
        size = strlen(strSource)+1;
        str = new char[size];
        strcpy(str, strSource);
    };
}

Identifier Identifier::toLowerCase()
{
    if(PrintMethodName2)
        std::cout << "Identifier::toLowerCase()\n";
    for(int i=0; str[i]!='\0'; i++)
        if((str[i]<'0' || str[i]>'9') && str[i]!='_')
            str[i] = std::tolower(str[i]);
    return *this;
}

Identifier Identifier::operator-(const Identifier& object)
{
    if(PrintMethodName2)
        std::cout << "Identifier::operator-(const Identifier& object)\n";
    char *p, *tmp = new char[size];
    strcpy(tmp, str);
    for(int i=0; object.str[i]; i++)
        if((p = strchr(tmp, object.str[i])) != NULL)
            for(; *p; *p=*(p+1), p++);
    return Identifier(tmp);
}
