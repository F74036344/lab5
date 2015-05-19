#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> vectorChar;


class HugeInt{
//overloaded <<, >>, and + operators
    friend istream & operator>>(istream &, HugeInt &);
    friend ostream & operator<<(ostream &, const HugeInt &);

public:
    HugeInt operator+(HugeInt);
    HugeInt operator-(HugeInt);
    HugeInt();
    HugeInt(int);
    HugeInt(const char *);
    ~HugeInt();

    void pushFront(vectorChar &,char);
    void popFront(vectorChar &);

private:
    vectorChar digit;

};



#endif // HUGEINT_h

