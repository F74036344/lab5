#include "HugeInt.h"



HugeInt::HugeInt()
{


}

HugeInt::~HugeInt()
{


}

HugeInt::HugeInt(int initializeValue)
{
    int singleDigit;
    if(initializeValue!=0)
    {
        do
        {
            singleDigit = initializeValue % 10;
            pushFront(digit,singleDigit+'0');
            initializeValue/=10;
        }
        while(initializeValue>0);
    }
    else
        digit.push_back('0');


}

HugeInt::HugeInt(const char *initChar)
{
    int index = 0;
    while((*(initChar+index)>='0') && (*(initChar+index)<='9'))
    {
        digit.push_back(*(initChar+index));
        index++;
    }
}



istream &operator>>(istream &in, HugeInt &num)
{
    int index = 0;
    char *initChar;
    in >> initChar;
    while((*(initChar+index)>='0') && (*(initChar+index)<='9'))
    {
        num.digit.push_back(*(initChar+index));
        index++;
    }

    return in;
}

ostream &operator<<(ostream &out, const HugeInt &num)
{
    for(int i=0;i<num.digit.size();i++)
        out << num.digit.at(i);
    return out;
}

HugeInt HugeInt::operator+(HugeInt hugeIntToAdd)
{
    HugeInt calResult;
    HugeInt hugeIntToAdd2 = *this;
    int sizeDifference;
    if(hugeIntToAdd.digit.size() >= hugeIntToAdd2.digit.size())
    {
        sizeDifference = hugeIntToAdd.digit.size() - hugeIntToAdd2.digit.size();
        for(int i=0;i<sizeDifference;i++)
            pushFront(hugeIntToAdd2.digit,'0');
        //Now 1 and 2 have the same size
    }

    else
    {
        sizeDifference = hugeIntToAdd2.digit.size() - hugeIntToAdd.digit.size();
        for(int i=0;i<sizeDifference;i++)
            pushFront(hugeIntToAdd.digit,'0');
        //Now 1 and 2 have the same size
    }


    pushFront(calResult.digit,'0');
    for(int i=hugeIntToAdd.digit.size()-1;i>=0;i--)
    {
        pushFront(calResult.digit,'0');
        calResult.digit.at(1) += hugeIntToAdd.digit.at(i) + hugeIntToAdd2.digit.at(i);
        if(calResult.digit.at(1)>'9')
        {
            calResult.digit.at(0)++;
            calResult.digit.at(1) -= 10;

        }
    }
    //At last, examine whether the first digit is 0 or not.
    //If is, remove the 0
    if(calResult.digit.at(0)=='0')
        popFront(calResult.digit);

    return calResult;
}

HugeInt HugeInt::operator-(HugeInt hugeIntToMinus)
{
    HugeInt calResult;
    HugeInt hugeIntToMinus2 = *this;
    if(hugeIntToMinus.digit.size()==hugeIntToMinus2.digit.size())
    {
        //ensure that hugeIntToAdd is bigger
        for(int i=0;i<hugeIntToMinus.digit.size();i++)
        {
            if(hugeIntToMinus.digit.at(i)==hugeIntToMinus2.digit.at(i))
                continue;
            else if(hugeIntToMinus.digit.at(i)>hugeIntToMinus2.digit.at(i))
                break;
            else    //hugeIntToAdd.digit.at(i)<hugeIntToAdd2.digit.at(i)
            {
                //exchange 1 and 2
                HugeInt tmp;
                tmp = hugeIntToMinus;
                hugeIntToMinus = hugeIntToMinus2;
                hugeIntToMinus2 = tmp;
                break;
            }
        }

    }
    else if(hugeIntToMinus.digit.size()>hugeIntToMinus2.digit.size())
    {
        int sizeDifference = hugeIntToMinus.digit.size()-hugeIntToMinus2.digit.size();
        for(int i=0;i<sizeDifference;i++)
            pushFront(hugeIntToMinus2.digit,'0');
    }
    else    //hugeIntToAdd.digit.size()<hugeIntToAdd2.digit.size()
    {
        //exchange
        HugeInt tmp;
        tmp = hugeIntToMinus;
        hugeIntToMinus = hugeIntToMinus2;
        hugeIntToMinus2 = tmp;

        int sizeDifference = hugeIntToMinus.digit.size()-hugeIntToMinus2.digit.size();
        for(int i=0;i<sizeDifference;i++)
            pushFront(hugeIntToMinus2.digit,'0');
    }

    pushFront(calResult.digit,'0');
    for(int i=hugeIntToMinus.digit.size()-1;i>=0;--i)
    {
        pushFront(calResult.digit,'0');
        calResult.digit.at(1) += hugeIntToMinus.digit.at(i)-hugeIntToMinus2.digit.at(i);
        if(calResult.digit.at(1)<'0')
        {
            calResult.digit.at(1) += 10;
            --calResult.digit.at(0);
        }

    }
    if(calResult.digit.at(0)=='0')    //If the first element of the result vector is 0, then remove it
        popFront(calResult.digit);

    return calResult;

}



void HugeInt::pushFront(vectorChar &vtr, char ch)
{
    vtr.push_back(0);
    for(int i=vtr.size()-1;i>=1;i--)
        vtr.at(i) = vtr.at(i-1);
    vtr.at(0) = ch;
}

void HugeInt::popFront(vectorChar &vtr)
{
    for(int i=0;i<vtr.size()-1;i++)
        vtr.at(i) = vtr.at(i+1);
    vtr.pop_back();
}


