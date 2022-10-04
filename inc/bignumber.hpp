#ifndef _INC_BIGNUMBER_HPP
#define _INC_BIGNUMBER_HPP 1

#include <iostream>
#include <cstring>

const int MAXN = 1010;
class big_number{
public:
    int integer_part[MAXN], frac_part[MAXN];
    int int_length, frac_length, exp_part;
    bool is_negative;

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
big_number operator <= (const big_number, const big_number);
big_number operator >= (const big_number, const big_number);
big_number pow (const big_number, const big_number);
big_number pow (const big_number, const double);
big_number sqrt (const big_number);
big_number ln (const big_number);
big_number sin (const big_number);
big_number cos (const big_number);
big_number tan (const big_number);

#endif