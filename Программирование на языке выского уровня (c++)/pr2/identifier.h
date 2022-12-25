#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include "string.h"
int checkPossibility(char *tmp);

class Identifier: public String
{
    static int copyCount;
    friend int checkPossibility(char *tmp);
public:
    Identifier(char *strSource);
    Identifier(const char *strSource) : Identifier((char*) strSource){};
    Identifier(const Identifier& object);
    Identifier(const String& object);
    Identifier(const Decimal& object);
    Identifier toLowerCase();
    ~Identifier();
    Identifier operator-(const Identifier& object);
    int getType();
    void printCopyCount();
};


#endif // IDENTIFIER_H
