#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <cmath>

// create a new big_number
big_number::big_number(){
    data = 0;
}

// create a new big_number with value number(int)
big_number::big_number(int number){
    data = number;
}

// create a new big_number with value number(double)
big_number::big_number(double dnumber)
{
    data = dnumber;
}

//create a new big_number with value number(string)
big_number::big_number(std::string number)
{
    data = 0;
    
    int stage = 0;
    int exp_part = 0;//to store something like e5

    // Is the number negative or not. 1 for positive, -1 for negative
    int num_nagetive = 1;
    int exp_negative = 1;
    double expr=0.1;

    // stage point to where the number is
    // stage:0 1  2  3  4  5 6  7
    // value:  - 123 . 456 e - 789

    for (int pos = 0; pos < number.length(); pos++)
    {
        char ch = number[pos];
        if (ch == 'e' || ch == 'E')
        {
            if (stage != 2 && stage != 4)// format like -123.e5 and -e5
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 5;
        }
        else if (ch == '.')
        {
            if (stage != 2)// format like -. and 123.123.123
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 3;
        }
        else if (ch == '-')
        {
            if (stage != 0 && stage != 5)// format like 12-3 and 1e12-3
            {
                throw "AT " + number + ": This is not a number";
            }
            if (stage == 0)
            {
                num_nagetive = 1;
                stage = 1;
            }
            else
            {
                exp_negative = -1;
                stage = 6;
            }
        }
        else if ('0' <= ch && ch <= '9')
        {
            if (stage <= 2)
            {
                stage = 2;
                data = data * 10 + ch - '0';
            }
            else if (stage <= 4)
            {
                stage = 4;
                data += (ch - '0')*expr;
                expr*=0.1;
            }
            else if (stage <= 7)
            {
                stage = 7;
                exp_part = exp_part * 10 + ch - '0';
            }
            else
                throw "AT " + number + ": This is not a number";
        }
        else
                throw "AT " + number + ": This is not a number";
    }
    data *= pow(10, exp_part*exp_negative);
}

void big_number::output(){
    printf("%0.8lf",data);
}

// Below are some operators ///
big_number operator+(const big_number v1, const big_number v2){
    return big_number(v1.data+v2.data);
}
big_number operator-(const big_number v1, const big_number v2){
    return big_number(v1.data-v2.data);
}
big_number operator*(const big_number v1, const big_number v2){
    return big_number(v1.data*v2.data);
}
big_number operator/(const big_number v1, const big_number v2){
    return big_number(v1.data/v2.data);
}
big_number operator<(const big_number v1, const big_number v2){
    return big_number(v1.data<v2.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}
big_number operator>(const big_number v1, const big_number v2){
    return big_number(v1.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6)>v2.data);
}
big_number operator==(const big_number v1, const big_number v2){
    return big_number(abs(v1.data-v2.data)<=std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}
big_number operator!=(const big_number v1, const big_number v2){
    return big_number(!(abs(v1.data-v2.data)<=std::max(1e-9,std::min(v1.data,v2.data)*1e-6)));
}
big_number operator<=(const big_number v1, const big_number v2){
    return big_number(v1.data<=v2.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}
big_number operator>=(const big_number v1, const big_number v2){
    return big_number(v1.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6)>=v2.data);
}
//////

// Below are some math functions ///
big_number bpow (const big_number v1, const big_number v2){
    return big_number(pow(v1.data,v2.data));
}
big_number bpow (const big_number v1, const double v2){
    return big_number(pow(v1.data,v2));
}
big_number bsqrt (const big_number v){
    return big_number(sqrt(v.data));
}
big_number bln (const big_number v){
    return big_number(log(v.data));
}
big_number bsin (const big_number v){
    return big_number(sin(v.data));
}
big_number bcos (const big_number v){
    return big_number(cos(v.data));
}
big_number btan (const big_number v){
    return big_number(tan(v.data));
}