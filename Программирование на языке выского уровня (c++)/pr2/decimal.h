#ifndef DECIMAL_H
#define DECIMAL_H
#include "string.h"
int checkPossibilityDecimal(char *str);

class Decimal : public String
{
    static int copyCount;
    int sign;
public:
    Decimal();
    Decimal(char* strSource);
    Decimal(const char* strSource) : Decimal((char*)strSource){};
    Decimal(const Decimal& object);
    Decimal(const String& object);
    Decimal(const Identifier& object);
    ~Decimal();
    int isLong();
    Decimal operator-(const Decimal& object);
    Decimal operator*(const Decimal& object);
    Decimal operator+(const Decimal& object);
    Decimal operator=(char* strSource);
    Decimal operator=(const char *strSource);
    Decimal operator=(const Decimal& object);
    Decimal makeNegative();
    void print();
    friend void checkPossibilityDecimal(Decimal* obj, char *strSource);
    int getType();
    void printCopyCount();
};

#endif //DECIMAL_H
