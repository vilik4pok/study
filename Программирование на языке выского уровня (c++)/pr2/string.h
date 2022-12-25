#ifndef STRING_H
#define STRING_H

class Decimal;
class Identifier;
class String
{
    static int copyCount;
protected:
    char *str;
    int size;
public:
    String();
    String(char c);
    String(char *strSource);
    String(const char *strSource) : String((char*) strSource){};
    String(const String& object);
    virtual ~String();
    String operator=(const String& object);
    String operator=(char *strSource);
    String operator=(const char *strSource);
    virtual void printCopyCount();
    virtual void print();
    int strLenght();
    virtual int getType();
    friend Decimal;
    friend Identifier;

};

#endif // STRING_H



