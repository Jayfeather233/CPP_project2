#ifndef _INC_BIGNUMBER_HPP
#define _INC_BIGNUMBER_HPP 1

#define ARITHMETIC_ERROR 2
#define NOT_A_NUMBER 4

#include <iostream>
#include <cstring>

const int MAXN = 1010;
class big_number{
public:
    int integer_part[MAXN], frac_part[MAXN], exp_part[MAXN];
    int int_length, frac_length, exp_length;
    bool is_negative, exp_negative;

    big_number();
    big_number(int);
    big_number(double);
    big_number(std::string);
    big_number to_int();
};
big_number operator + (const big_number, const big_number);
big_number operator - (const big_number, const big_number);
big_number operator * (const big_number, const big_number);
big_number operator / (const big_number, const big_number);
big_number operator < (const big_number, const big_number);
big_number operator > (const big_number, const big_number);
big_number operator == (const big_number, const big_number);
big_number operator <= (const big_number, const big_number);
big_number operator >= (const big_number, const big_number);

#endif