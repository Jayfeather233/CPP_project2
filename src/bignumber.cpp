#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <cmath>

// create a new big_number
big_number::big_number()
{/*
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    frac_length = int_length = exp_part = is_negative = 0;*/
    data=0;
}

// create a new big_number with value number(int)
big_number::big_number(int number)
{/*
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    frac_length = int_length = exp_part = is_negative = 0;
    if (number < 0)
    {
        number = -number;
        is_negative = 1;
    }
    while (number != 0)
    {
        integer_part[int_length++] = number % 10;
        number /= 10;
    }*/
    data = number;
}

// create a new big_number with value number(double)
big_number::big_number(double dnumber)
{/*
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    frac_length = int_length = exp_part = is_negative = 0;
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
            throw "Too long (length:1000) for big_number";
        inumber /= 10;
    }
    while (dnumber >= 1e-10)
    {
        frac_part[frac_length] = int(dnumber * 10);
        dnumber = dnumber * 10 - frac_part[frac_length++];
        if (frac_length >= MAXN) break;
    }*/
    data = dnumber;
}
big_number::big_number(std::string number)
{/*
    memset(frac_part, 0, sizeof(frac_part));
    memset(integer_part, 0, sizeof(integer_part));
    frac_length = int_length = exp_part = is_negative = 0;

    int stage = 0;

    int exp_negative = 1;

    // stage:0 1  2  3  4  5 6  7
    // value:  - 123 . 456 e - 789

    for (int pos = 0; pos < number.length(); pos++)
    {
        char ch = number[pos];
        if (ch == 'e' || ch == 'E')
        {
            if (stage != 2 && stage != 4)
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 5;
        }
        else if (ch == '.')
        {
            if (stage != 2)
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 3;
        }
        else if (ch == '-')
        {
            if (stage != 0 && stage != 5)
            {
                throw "AT " + number + ": This is not a number";
            }
            if (stage == 0)
            {
                is_negative = 1;
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
                exp_part = exp_part * 10 + ch - '0';
            }
            else
                throw "AT " + number + ": This is not a number";
        }
        else
                throw "AT " + number + ": This is not a number";
    }

    for (int i = 0; i < int_length / 2; i++)
    {
        std::swap(integer_part[i], integer_part[int_length - i - 1]);
    }

    exp_part *= exp_negative;*/

    data = 0;
    
    int stage = 0;
    int exp_part = 0;

    int num_nagetive = 1;
    int exp_negative = 1;
    double expr=0.1;

    // stage:0 1  2  3  4  5 6  7
    // value:  - 123 . 456 e - 789

    for (int pos = 0; pos < number.length(); pos++)
    {
        char ch = number[pos];
        if (ch == 'e' || ch == 'E')
        {
            if (stage != 2 && stage != 4)
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 5;
        }
        else if (ch == '.')
        {
            if (stage != 2)
            {
                throw "AT " + number + ": This is not a number";
            }
            stage = 3;
        }
        else if (ch == '-')
        {
            if (stage != 0 && stage != 5)
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

void big_number::to_int()
{/*
    if(exp_part < 0){
        for(int i=0;i<int_length+exp_part;i++){
            integer_part[i]=integer_part[i-exp_part];
        }
        for(int i=int_length+exp_part;i<int_length;i++){
            integer_part[i]=0;
        }
        exp_part = 0;
    }
    for(int i=exp_part;i<frac_length;i++){
        frac_part[i]=0;
    }
    frac_length = exp_part;*/
    data = int(data);
}

void big_number::output()
{/*
    if(abs(exp_part)<6){
        for(int i=int_length-1;i>=0;i--){
            printf("%d",integer_part[i]);
            if(i==-exp_part){
                printf(".");
            }
        }
        for(int i=0;i<frac_length;i++){
            if(i==exp_part && i){
                printf(".");
            }
            printf("%d",frac_part[i]);
        }
    } else {
        for(int i=int_length-1;i>=0;i--){
            printf("%d",integer_part[i]);
        }
        printf(".");
        for(int i=0;i<frac_length;i++){
            printf("%d",frac_part[i]);
        }
        printf("e%d",exp_part);
    }*/
    printf("%0.8lf",data);
}

big_number operator+(const big_number v1, const big_number v2)
{
    return big_number(v1.data+v2.data);
}
big_number operator-(const big_number v1, const big_number v2)
{
    return big_number(v1.data-v2.data);
}
big_number operator*(const big_number v1, const big_number v2)
{
    return big_number(v1.data*v2.data);
}
big_number operator/(const big_number v1, const big_number v2)
{
    return big_number(v1.data/v2.data);
}
big_number operator<(const big_number v1, const big_number v2)
{
    return big_number(v1.data<v2.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}
big_number operator>(const big_number v1, const big_number v2)
{
    return big_number(v1.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6)>v2.data);
}
big_number operator==(const big_number v1, const big_number v2)
{
    return big_number(abs(v1.data-v2.data)<=std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}big_number operator!=(const big_number v1, const big_number v2)
{
    return big_number(!(abs(v1.data-v2.data)<=std::max(1e-9,std::min(v1.data,v2.data)*1e-6)));
}
big_number operator<=(const big_number v1, const big_number v2)
{
    return big_number(v1.data<=v2.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6));
}
big_number operator>=(const big_number v1, const big_number v2)
{
    return big_number(v1.data+std::max(1e-9,std::min(v1.data,v2.data)*1e-6)>=v2.data);
}
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