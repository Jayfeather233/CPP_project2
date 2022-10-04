#ifndef _INC_BIGNUMBER_HPP
#define _INC_BIGNUMBER_HPP 1

#include <iostream>
#include <cstring>

const int MAXN = 1010;
class big_number{
public:/*
    int integer_part[MAXN], frac_part[MAXN];
    int int_length, frac_length, exp_part;
    bool is_negative;
*/
    double data;
    big_number();
    big_number(int);
    big_number(double);
    big_number(std::string);
    void to_int();
    void output();
};
big_number operator + (const big_number, const big_number);
big_number operator - (const big_number, const big_number);
big_number operator * (const big_number, const big_number);
big_number operator / (const big_number, const big_number);
big_number operator < (const big_number, const big_number);
big_number operator > (const big_number, const big_number);
big_number operator == (const big_number, const big_number);
big_number operator != (const big_number, const big_number);
big_number operator <= (const big_number, const big_number);
big_number operator >= (const big_number, const big_number);
big_number bpow (const big_number, const big_number);
big_number bpow (const big_number, const double);
big_number bsqrt (const big_number);
big_number bln (const big_number);
big_number bsin (const big_number);
big_number bcos (const big_number);
big_number btan (const big_number);

#endif