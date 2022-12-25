#include <iostream>
#include <math.h>
#define PrintMethodName 1
class ComplexNumber
{
private:
    double realCoefficient;
    double imaginateCoefficient;
public:
    ComplexNumber(double a = 0, double b = 0);
    ComplexNumber(ComplexNumber& number);
    void setRealCoefficient(double num);
    void setImaginateCoefficient(double num);
    void readRealCoefficient();
    void readImaginateCoefficient();
    double getRealCoefficient();
    double getImaginateCoefficient();
    void exponent(int n);
    void print(const char a[] = "");
    void printRealCoefficient();
    void printImaginateCoefficient();
    int operator==(ComplexNumber &num);
    int operator!=(ComplexNumber &num);
    void operator+=(ComplexNumber &num);
    void operator+=(double num);
    ~ComplexNumber();
};

ComplexNumber::ComplexNumber(double a, double b)
{
    if(PrintMethodName)
        std::cout << "constructor ComplexNumber(double, double)\n";
    realCoefficient = a;
    imaginateCoefficient = b;
}

ComplexNumber::ComplexNumber(ComplexNumber& number)
{
    if(PrintMethodName)
        std::cout << "constructor ComplexNumber(ComplexNumber&)\n";
    realCoefficient = number.realCoefficient;
    imaginateCoefficient = number.imaginateCoefficient;
}

void ComplexNumber::setRealCoefficient(double num)
{
    if(PrintMethodName)
        std::cout << "method setRealCoefficient\n";
    realCoefficient = num;
}

void ComplexNumber::setImaginateCoefficient(double num)
{
    if(PrintMethodName)
        std::cout << "method setImaginateCoefficient\n";
    imaginateCoefficient = num;
}

void ComplexNumber::readRealCoefficient()
{
    if(PrintMethodName)
        std::cout << "method readRealCoefficient\n";
    std::cin >> realCoefficient;
}

void ComplexNumber::readImaginateCoefficient()
{
    if(PrintMethodName)
        std::cout << "method readImaginateCoefficient\n";
    std::cin >> imaginateCoefficient;
}

double ComplexNumber::getRealCoefficient()
{
    if(PrintMethodName)
        std::cout << "method getRealCoefficient\n";
    return realCoefficient;
}

double ComplexNumber::getImaginateCoefficient()
{
    if(PrintMethodName)
        std::cout << "method getImaginateCoefficient\n";
    return imaginateCoefficient;
}

void ComplexNumber::exponent(int n)
{
    if(PrintMethodName)
        std::cout << "method exponent\n";
    double argument;
    double modul = sqrt(realCoefficient*realCoefficient + imaginateCoefficient*imaginateCoefficient);
    modul = pow(modul, n);
    if (realCoefficient > 0)
        argument = atan(imaginateCoefficient/realCoefficient);
    else
        if (imaginateCoefficient > 0)
            argument = M_PI + atan(imaginateCoefficient/realCoefficient);
        else
            argument = -M_PI + atan(imaginateCoefficient/realCoefficient);
    realCoefficient = modul*cos(n*argument);
    imaginateCoefficient = modul*sin(n*argument);
}

void ComplexNumber::print(const char a[])
{
    if(PrintMethodName)
        std::cout << "method print\n";
    std::cout << a << realCoefficient << " + " << imaginateCoefficient << "*i\n";
}

void ComplexNumber::printRealCoefficient()
{
    if(PrintMethodName)
        std::cout << "method printRealCoefficient\n";
    std::cout << realCoefficient <<"\n";
}

void ComplexNumber::printImaginateCoefficient()
{
    if(PrintMethodName)
        std::cout << "method printImaginateCoefficient\n";
    std::cout << imaginateCoefficient <<"\n";
}

int ComplexNumber::operator==(ComplexNumber &num)
{
    if(PrintMethodName)
        std::cout << "operator==\n";
    return realCoefficient == num.realCoefficient && imaginateCoefficient == num.imaginateCoefficient;
};

int ComplexNumber::operator!=(ComplexNumber &num)
{
    if(PrintMethodName)
        std::cout << "operator!=\n";
    return realCoefficient != num.realCoefficient || imaginateCoefficient != num.imaginateCoefficient;
};

void ComplexNumber::operator+=(ComplexNumber &num)
{
    if(PrintMethodName)
        std::cout << "operator+=(ComplexNumber)\n";
    realCoefficient += num.realCoefficient;
    imaginateCoefficient += num.imaginateCoefficient;
};

void ComplexNumber::operator+=(double num)
{
    if(PrintMethodName)
        std::cout << "operator+=(double)\n";
    realCoefficient += num;
};

ComplexNumber::~ComplexNumber()
{
    if(PrintMethodName)
        std::cout << "~ComplexNumber";
}
