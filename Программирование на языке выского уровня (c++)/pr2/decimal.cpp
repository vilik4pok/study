#include "decimal.h"
#include <cstring>
#include <iostream>

#define PrintMethodName3 1

int Decimal::copyCount = 0;

int Decimal::getType()
{
    if(PrintMethodName3)
        std::cout << "Decimal::getType()\n";
    return 3;
}

Decimal::Decimal(const String& object):  Decimal(object.str)
{
    copyCount++;
}

Decimal::Decimal(const Identifier& object): Decimal()
{
    copyCount++;
}

void Decimal::printCopyCount()
{
    if(PrintMethodName3)
        std::cout << "Decimal::printCopyCount()\n";
    std::cout<<copyCount;
}

void checkPossibilityDecimal(Decimal* obj, char *strSource)
{
    if(PrintMethodName3)
        std::cout << "friend checkPossibilityDecimal(Decimal* obj, char *strSource)\n";
    int i;
    delete[] obj->str;
    obj->size = 2;
    obj->str = new char[obj->size];
    *obj->str = '0';
    *(obj->str+1) = '\0';
    obj->sign = 1;
    if(*strSource!='+' && *strSource!='-' && (*strSource<'0' || *strSource>'9'))
        return;
    if (*strSource == '-')
    {
        obj->sign = -1;
        strSource++;
    }
    else if (*strSource == '+')
        strSource++;
    while(*strSource=='0'&&*(strSource + 1))
        strSource++;
    for(i=0; strSource[i]; i++)
        if(strSource[i]=='+' || strSource[i]=='-' || strSource[i]<'0' || strSource[i]>'9')
            return;
    delete[] obj->str;
    obj->size = strlen(strSource)+1;
    obj->str = new char[obj->size];
    strcpy(obj->str, strSource);

}

Decimal::Decimal()
{
    if(PrintMethodName3)
        std::cout << "Decimal::Decimal()\n";
    delete[] str;
    size = 2;
    str = new char[size];
    *str = '0';
    *(str+1) = 0;
    sign = 1;
}

Decimal::Decimal(char* strSource)
{
    if(PrintMethodName3)
        std::cout << "Decimal::Decimal(char* strSource)\n";
    checkPossibilityDecimal(this, strSource);
}


Decimal::Decimal(const Decimal& object) : String(object)
{
    if(PrintMethodName3)
        std::cout << "Decimal::Decimal(const Decimal& object)\n";
    sign = object.sign;
    copyCount++;
}

Decimal::~Decimal()
{
    if(PrintMethodName3)
        std::cout << "Decimal::~Decimal()\n";
    delete[] str;
    str = NULL;
}

Decimal Decimal::operator=(const Decimal& object)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator=(const Decimal& object)\n";
    delete[] str;
    size = object.size;
    str = new char[size];
    strcpy(str, object.str);
    sign = object.sign;
    return *this;
}


Decimal Decimal::operator=(char *strSource)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator=(char *strSource)\n";
    checkPossibilityDecimal(this, strSource);
    return *this;
}

Decimal Decimal::operator=(const char *strSource)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator=(char *strSource)\n";
    checkPossibilityDecimal(this, (char*)strSource);
    return *this;
}

Decimal Decimal::operator+(const Decimal& object)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator+(const Decimal& object))\n";
    int i, j;
    Decimal *obj1 = this;
    const Decimal *obj2 = &object;
    if((obj1->size == obj2->size && strcmp(obj1->str, obj2->str)<0) || obj1->size < obj2->size)
    {
        obj1 = (Decimal*)&object;
        obj2 = this;
    };

    if(obj1->sign == 1 && obj2->sign == -1) return (Decimal)*obj1 - Decimal(*obj2).makeNegative();
    if(obj1->sign == -1 && obj2->sign == 1) return (Decimal)*obj2 - Decimal(*obj1).makeNegative();

    char *result = new char[obj1->size+1];
    strcpy(result, obj1->str);
    for(i = obj1->size; i>0; result[i] = result[i-1], i--);
    result[0] = '0';
    for(i=obj1->size-1, j=obj2->size-2; j>=0; j--, i--)
        if ((result[i]  = (result[i]-'0') + (obj2->str[j] - '0') + '0') > '9')
        {
            result[i]-=10;
            result[i-1]++;
        };
    for(; i>=0; i--)
        if (result[i] > '9')
        {
            result[i]-=10;
            result[i-1]++;
        }
        else
            break;
    Decimal res (result);
    res.sign = obj1->sign;
    delete[] result;
    return res;
}

Decimal Decimal::operator-(const Decimal& object)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator-(const Decimal& object)\n";
    int i, j,flag=1;
    Decimal *obj1 = this;
    const Decimal *obj2 = &object;
    if(obj1->size == obj2->size && strcmp(obj1->str, obj2->str)==0 && obj1->sign == obj2->sign)
        return Decimal();
    if((obj1->size == obj2->size && strcmp(obj1->str, obj2->str)<0) || obj1->size < obj2->size)
    {
        obj1 = (Decimal*)&object;
        obj2 = this;
        flag = -1;
    };
    if(obj1->sign != obj2->sign)
    {
        if(flag==-1)
            return (Decimal)Decimal(*obj1).makeNegative() + *obj2;
        else
            return *obj1 + Decimal(*obj2).makeNegative();
    };
    char* result = new char[obj1->size];
    strcpy(result, obj1->str);
    for(i=obj1->size-2, j=obj2->size-2; j>=0; j--, i--)
        if ((result[i] = (result[i]-'0') - (obj2->str[j] - '0') + '0') < '0')
        {
            result[i]+=10;
            result[i-1]--;
        };
    for(; i>=0; i--)
        if (result[i] < '0')
        {
            result[i]+=10;
            result[i-1]--;
        }
        else
            break;
    Decimal res (result);
    res.sign = obj1->sign*flag;
    delete[] result;
    return res;
}

void Decimal::print()
{
    if(PrintMethodName3)
        std::cout << "Decimal::print()\n";
    char c;
    if (sign == 1) c='+';
    if (sign == -1) c='-';
    if(c=='-')
        std::cout << c << str <<"\n";
    else
        std::cout << str <<"\n";
}

Decimal Decimal::makeNegative()
{
    if(PrintMethodName3)
        std::cout << "Decimal::makeNegative()\n";
    sign*=-1;
    return *this;
}

Decimal Decimal::operator*(const Decimal& object)
{
    if(PrintMethodName3)
        std::cout << "Decimal::operator*(const Decimal& object)\n";
    int i, j, k, tmp, c=0, maxsize = size + object.size - 1, offset = maxsize - 2;
    unsigned char *str3 = new unsigned char[maxsize];
    str3[maxsize-1] = 0;
    Decimal res;
    for(i = object.size-2; i>=0; c++, offset = maxsize-2-c, i--)
    {
        for(k=0; k<maxsize-1; k++)
            str3[k] = '0';
        for(j=size-2; j>=0; j--, offset--)
        {
            if ((str3[offset] = str3[offset] + (str[j]-'0') * (object.str[i]-'0')) > '9')
            {
                tmp = str3[offset] - '0';
                str3[offset] = tmp%10 + '0';
                str3[offset-1] += tmp/10;
            };
        };
        for(;offset>0; offset--)
            if (str3[offset] > '9')
            {
                tmp = str3[offset]-'0';
                str3[offset] = tmp%10+'0';
                str3[offset-1]+= tmp/10;
            }
            else
                break;
        res = res + Decimal((char*)str3);
    };
    delete[] str3;
    res.sign = sign*object.sign;
    return res;
}

int Decimal::isLong()
{
    if(PrintMethodName3)
        std::cout << "Decimal::isLong()\n";
    char longMax[30], longMin[30];
    sprintf(longMax, "%ld%c", LONG_MAX, 0);
    sprintf(longMin, "%ld%c", LONG_MIN, 0);
    if(sign<0)
        if((*this - Decimal(longMin)).sign>0)
            return 1;
    if(sign>0)
        if((Decimal(longMax) - *this).sign>0)
            return 1;
    return 0;
}
