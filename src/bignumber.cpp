#include "bignumber.hpp"
#include "exception.hpp"

#include <iostream>
#include <cstring>
#include <cmath>

// create a new big_number
big_number::big_number()
{
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    memset(exp_part, 0, sizeof(exp_part));
    frac_length = int_length = exp_length = exp_negative = is_negative = 0;
}

// create a new big_number with value number(int)
big_number::big_number(int number)
{
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    memset(exp_part, 0, sizeof(exp_part));
    frac_length = int_length = exp_length = exp_negative = is_negative = 0;
    if (number < 0)
    {
        number = -number;
        is_negative = 1;
    }
    while (number != 0)
    {
        integer_part[int_length++] = number % 10;
        number /= 10;
    }
}

// create a new big_number with value number(double)
big_number::big_number(double dnumber)
{
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    memset(exp_part, 0, sizeof(exp_part));
    frac_length = int_length = exp_length = exp_negative = is_negative = 0;
    if (dnumber < 0)
    {
        dnumber = -dnumber;
        is_negative = 1;
    }
    int inumber = floor(dnumber);
    dnumber = dnumber - inumber + 1e-9;
    while (inumber != 0)
    {
        integer_part[int_length++] = inumber % 10;
        if (int_length >= MAXN)
            throw (m_exception){0,"Too long (length:1000) for big_number"};
        inumber /= 10;
    }
    while (dnumber >= 1e-10)
    {
        frac_part[frac_length] = int(dnumber * 10);
        dnumber = dnumber * 10 - frac_part[frac_length++];
        if (frac_length >= MAXN) break;
    }
}
big_number::big_number(std::string number)
{
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    memset(exp_part, 0, sizeof(exp_part));
    frac_length = int_length = exp_length = exp_negative = is_negative = 0;

    int stage = 0;

    // stage:0 1  2  3  4  5 6  7
    // value:  - 123 . 456 e - 789

    for (int pos = 0; pos < number.length(); pos++)
    {
        char ch = number[pos];
        if (ch == 'e' || ch == 'E')
        {
            if (stage != 2 && stage != 4)
            {
                throw (m_exception){pos,"This is not a number"};
            }
            stage = 5;
        }
        else if (ch == '.')
        {
            if (stage != 2)
            {
                throw (m_exception){pos,"This is not a number"};
            }
            stage = 3;
        }
        else if (ch == '-')
        {
            if (stage != 0 && stage != 5)
            {
                throw (m_exception){pos,"This is not a number"};
            }
            if (stage == 0)
            {
                is_negative = 1;
                stage = 1;
            }
            else
            {
                exp_negative = 1;
                stage = 6;
            }
        }
        else if ('0' <= ch && ch <= '9')
        {
            if (stage <= 2)
            {
                stage = 2;
                integer_part[int_length++] = ch - '0';
            }
            else if (stage <= 4)
            {
                stage = 4;
                frac_part[frac_length++] = ch - '0';
            }
            else if (stage <= 7)
            {
                stage = 7;
                exp_part[exp_length++] = ch - '0';
            }
            else
                throw (m_exception){pos,"This is not a number"};
        }
        else
            throw (m_exception){pos,"This is not a number"};
    }

    for (int i = 0; i < int_length / 2; i++)
    {
        std::swap(integer_part[i], integer_part[int_length - i - 1]);
    }
    for (int i = 0; i < exp_length / 2; i++)
    {
        std::swap(exp_part[i], exp_part[exp_length - i - 1]);
    }
}

big_number big_number::to_int()
{
}

void big_number::output()
{

}
void big_number::output(int)
{

}

big_number operator+(const big_number v1, const big_number v2)
{
}
big_number operator-(const big_number v1, const big_number v2)
{
}
big_number operator*(const big_number v1, const big_number v2)
{
}
big_number operator/(const big_number v1, const big_number v2)
{
}
big_number operator<(const big_number v1, const big_number v2)
{
}
big_number operator>(const big_number v1, const big_number v2)
{
}
big_number operator==(const big_number v1, const big_number v2)
{
}
big_number operator<=(const big_number v1, const big_number v2)
{
}
big_number operator>=(const big_number v1, const big_number v2)
{
}