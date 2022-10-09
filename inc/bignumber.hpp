#ifndef _INC_BIGNUMBER_HPP
#define _INC_BIGNUMBER_HPP 1

#include <iostream>
#include <cstring>

const int kMaxn = 1010;
const int kFracLen = 500;
class big_number{
public:
    int data[kMaxn];  //The number
    int int_len;      //integer part length
    int frac_len;     //fraction part length
    int is_negative;  //if is negative

    //constructors
    big_number();
    big_number(int);
    big_number(double);
    big_number(std::string);

    //left or right shift data. (=*10^u)
    void datacpy(int);
    //delete fraction part
    void floor();
    //output the data
    void output();
};

//redefine operators
big_number operator + (const big_number, const big_number);
big_number operator - (const big_number, const big_number);
big_number operator * (const big_number, const big_number);
big_number operator / (const big_number, const big_number);
int operator < (const big_number, const big_number);
int operator > (const big_number, const big_number);
int operator == (const big_number, const big_number);
int operator != (const big_number, const big_number);
int operator <= (const big_number, const big_number);
int operator >= (const big_number, const big_number);
//math functions
big_number bpow (const big_number, const big_number);
big_number bpow (const big_number, double);
big_number bsqrt (const big_number);
big_number bexp (const big_number);
big_number bln (const big_number);
big_number bsin (const big_number);
big_number bcos (const big_number);
big_number btan (const big_number);

#endif