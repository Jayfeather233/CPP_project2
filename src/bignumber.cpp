#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <cmath>

const big_number k2_PI = big_number("6.2831853071795864769252867664");
const big_number kPI   = big_number("3.1415926535897932384626433832");
const big_number kPI_2 = big_number("1.5707963267948966192313216916");
const big_number kPI_4 = big_number("0.7853981633974483096156608458");
const big_number kE    = big_number("2.7182818284590452353602874713");
const big_number k0    = big_number("0");
const big_number k1    = big_number("1");

// create a new big_number
big_number::big_number(){
    memset(data,0,sizeof(data));
    int_len = frac_len = is_negative = 0;
}

// create a new big_number with value number(int)
big_number::big_number(int number){
    memset(data,0,sizeof(data));
    int_len = frac_len = is_negative = 0;
    if(number <= 0){
        number = -number;
        is_negative = 1;
    }
    while(number){
        data[int_len + kFracLen] = number % 10;
        number /= 10;
        int_len++;
    }
}

// create a new big_number with value number(double)
big_number::big_number(double dnumber){
    memset(data,0,sizeof(data));
    int_len = frac_len = is_negative = 0;
    if(dnumber <= 0){
        dnumber = -dnumber;
        is_negative = 1;
    }
    int number = (int)(dnumber + 1e-11);
    dnumber -= number;
    while(number){
        data[int_len + kFracLen] = number % 10;
        number /= 10;
        int_len ++;
    }
    while(dnumber>=1e-9 && frac_len < kFracLen){
        data[kFracLen - frac_len - 1] = (int)(dnumber * 10);
        dnumber = dnumber * 10 - data[kFracLen - frac_len - 1];
        frac_len ++;
    }
}

void big_number::datacpy(int u){
    if(u < 0){
        u = -u;
        for(int i=std::max(u,kFracLen - frac_len); i <= kFracLen + int_len; i++){
            data[i-u] = data[i];
        }
        for(int i=std::max(0,kFracLen + int_len - u); i <= kFracLen + int_len; i++){
            data[i] = 0;
        }
        int_len -= u;
        int_len = std::max(0,int_len);
        frac_len += u;
        while(data[kFracLen - frac_len]==0&&frac_len>0){
            frac_len --;
        }
    } else {
        if(kFracLen + int_len + u >= kMaxn){
            throw (std::string)"Number too big.(Up to 10^500) at 1";
        }
        for(int i=kFracLen + int_len; i >= std::max(0,kFracLen - 1 - frac_len); i--){
            data[i+u] = data[i];
        }
        for(int i=kFracLen - 1 - frac_len + u; i >= std::min(0,kFracLen - 1 - frac_len); i--){
            data[i] = 0;
        }
        int_len += u;
        frac_len -= u;
        frac_len = std::max(frac_len, 0);
        while(data[kFracLen + int_len - 1]==0 && int_len>0){
            int_len --;
        }
    }
}

void big_number::floor(){
    for(int i=kFracLen-1;i>=kFracLen - frac_len;i--){
        data[i]=0;
    }
    frac_len =0;
}

//create a new big_number with value number(string)
big_number::big_number(std::string number)
{
    memset(data,0,sizeof(data));
    int_len = frac_len = is_negative = 0;
    
    int stage = 0;
    int exp_part = 0;//to store something like e5

    // Is the number negative or not. 1 for positive, -1 for negative
    int exp_negative = 1;

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
                data[int_len + kFracLen] = ch - '0';
                int_len ++;
                if(int_len + kFracLen >= kMaxn){
                    throw (std::string)"Number too big.(Up to 10^500) at 2";
                }
            }
            else if (stage <= 4)
            {
                stage = 4;
                data[kFracLen - frac_len - 1] = ch - '0';
                frac_len ++;
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
    for(int i=0;i<int_len/2;i++){
        std::swap(data[i+kFracLen],data[int_len-i-1+kFracLen]);
    }
    while(data[int_len+kFracLen-1]==0 && int_len >0) int_len--;
    datacpy(exp_part * exp_negative);
}

void big_number::output(){
    if(is_negative) printf("-");
    if(int_len == 0){
        printf("0");
    }
    if(int_len < 20){
        for(int i=int_len + kFracLen - 1; i >= kFracLen - std::min(frac_len,30); i --){
            if(i==kFracLen - 1&& frac_len){
                printf(".");
            }
            printf("%d",data[i]);
        }
    } else {
        for(int i=int_len + kFracLen - 1; i >= int_len + kFracLen - 50; i --){
            if(i==int_len + kFracLen - 2){
                printf(".");
            }
            printf("%d",data[i]);
        }
        printf("e%d",int_len-1);
    }
}

// Below are some operators ///
big_number operator+(const big_number v1, const big_number v2){
    if(v1.is_negative ^ v2.is_negative){
        if(v1.is_negative){
            big_number c(v1);
            c.is_negative = 0;
            return v2-c;
        } else {
            big_number c(v2);
            c.is_negative = 0;
            return v1-c;
        }
    } else {
        big_number c(v1);
        c.frac_len = std::max(v1.frac_len,v2.frac_len);
        c.int_len = std::max(v1.int_len,v2.int_len);
        for(int i=kFracLen - c.frac_len;i<kFracLen + c.int_len;i++){
            c.data[i]+=v2.data[i];
            c.data[i+1]+=c.data[i]/10;
            c.data[i]%=10;
        }
        while(c.data[kFracLen + c.int_len]){
            c.data[kFracLen + c.int_len +1] += c.data[kFracLen + c.int_len]/10;
            c.data[kFracLen + c.int_len]%=10;
            c.int_len ++;
            if(c.int_len + kFracLen >= kMaxn){
                throw (std::string)"Number too big.(Up to 10^500) at 3";
            }
        }
        return c;
    }
}
big_number operator-(const big_number v1, const big_number v2){
    if(v1.is_negative ^ v2.is_negative){
        if(v1.is_negative){
            big_number c(v2);
            c.is_negative = 1;
            return v1+c;
        } else {
            big_number c(v1);
            c.is_negative = 1;
            return c+v2;
        }
    } else if(v1.is_negative){
        big_number c1(v1),c2(v2);
        c1.is_negative = 0;
        c2.is_negative = 0;
        c1 = c1-c2;
        c1.is_negative ^= 1;
        return c1;
    } else if(v1<v2){
        big_number c = v2 - v1;
        c.is_negative ^= 1;
        return c;
    } else {
        big_number c(v1);
        c.frac_len = std::max(v1.frac_len,v2.frac_len);
        c.int_len = std::max(v1.int_len,v2.int_len);
        for(int i=kFracLen - c.frac_len;i<kFracLen + c.int_len;i++){
            c.data[i]-=v2.data[i];
            if(c.data[i]<0){
                c.data[i]+=10;
                c.data[i+1]--;
            }
        }
        while(c.data[kFracLen + c.int_len - 1]==0 && c.int_len > 0){
            c.int_len --;
        }
        return c;
    }
}
big_number operator*(const big_number v1, const big_number v2){
    big_number c = big_number();
    c.frac_len = std::max(c.frac_len, v1.frac_len + v2.frac_len);
    c.int_len = std::max(c.int_len, v1.int_len+v2.int_len-1);
    c.frac_len = std::min(c.frac_len,kFracLen-1);
    c.is_negative = v1.is_negative ^ v2.is_negative;
    for(int i=kFracLen - v1.frac_len;i<kFracLen + v1.int_len;i++){
        for(int j=kFracLen - v2.frac_len;j<kFracLen + v2.int_len;j++){
            if(i+j - kFracLen<0) continue;
            if(i+j - kFracLen>kMaxn){
                throw (std::string)"Number too big.(Up to 10^500) at 4";
            }
            c.data[i+j - kFracLen] += v1.data[i]*v2.data[j];
        }
    }
    for(int i=kFracLen - c.frac_len;i<kFracLen + c.int_len;i++){
        c.data[i+1]+=c.data[i]/10;
        c.data[i]%=10;
    }
    while(c.data[kFracLen + c.int_len]){
        c.data[kFracLen + c.int_len +1] += c.data[kFracLen + c.int_len]/10;
        c.data[kFracLen + c.int_len]%=10;
        c.int_len ++;
        if(c.int_len + kFracLen >= kMaxn){
            throw (std::string)"Number too big.(Up to 10^500) at 5";
        }
    }
    return c;
}
big_number operator/(const big_number v1, const big_number v2){
    big_number ans = big_number();
    big_number c1(v1);
    big_number c2(v2);
    int i_len = v1.int_len-v2.int_len;
    ans.is_negative = v1.is_negative ^ v2.is_negative;
    c2.datacpy(v1.int_len-v2.int_len);
    while(i_len >= 0){
        while(c1>c2 && c2 != k0){
            c1=c1-c2;
            ans.data[i_len + kFracLen]++;
            ans.int_len = std::max(ans.int_len,i_len+1);
        }
        c2.datacpy(-1);
        i_len --;
    }
    while(i_len >= -100){
        while(c1>c2 && c2 != k0){
            c1=c1-c2;
            ans.data[i_len + kFracLen]++;
            ans.frac_len = std::max(ans.frac_len,-i_len);
        }
        c2.datacpy(-1);
        i_len --;
    }
    return ans;
}
int operator<(const big_number v1, const big_number v2){
    if(v1.is_negative ^ v2.is_negative){
        return v1.is_negative;
    } else {
        if(v1.int_len != v2.int_len){
            return v1.int_len < v2.int_len;
        }
        for(int i=v1.int_len+kFracLen -1;i>=kFracLen - std::max(v1.frac_len,v2.frac_len);i--){
            if(v1.data[i]!=v2.data[i]){
                return v1.data[i]<v2.data[i];
            }
        }
        return 0;
    }
}
int operator>(const big_number v1, const big_number v2){
    return !(v1<v2);
}
int operator==(const big_number v1, const big_number v2){
    if(v1.is_negative ^ v2.is_negative){
        return 0;
    } else {
        if(v1.int_len != v2.int_len){
            return 0;
        }
        for(int i=v1.int_len+kFracLen -1;i>=300;i--){
            if(v1.data[i]!=v2.data[i]){
                return 0;
            }
        }
        return 1;
    }
}
int operator!=(const big_number v1, const big_number v2){
    return !(v1==v2);
}
int operator<=(const big_number v1, const big_number v2){
    return v1<v2 || v1==v2;
}
int operator>=(const big_number v1, const big_number v2){
    return v1>v2 || v1==v2;
}
//////

// Below are some math functions ///
big_number bpow (const big_number v1, const big_number v2){
    return bexp(v2*bln(v1));
}
big_number bpow (const big_number v1, double v2){
    return bexp(big_number(v2)*bln(v1));
}
big_number bsqrt (const big_number v){
    return bpow(v,0.5);
}
big_number bln (const big_number v){
    big_number ans = big_number();
    big_number c(v);
    while(c>kE){
        c = c / kE;
        ans = ans + k1;
    }
    big_number p("0.5");
    big_number k1_2("0.5");
    while(p!=k0){
        c = c*c;
        if(c>kE){
            c=c/kE;
            ans=ans+p;
        }
        p=p*k1_2;
    }
    return ans;
}
big_number bexp (const big_number v){
    big_number upd(v);
    if(v.is_negative){
        upd.is_negative = 0;
        return big_number(1) / bexp(upd);
    }
    big_number ans(1);
    for(int i=1;i<=700;i++){//Taylor expression for exp
        upd=upd/i;
        ans=ans+upd;
        upd=upd*v;
    }
    return ans;
}
big_number bsin (const big_number v){
    big_number c(v);
    big_number x = c / k2_PI;
    x.floor();
    c=c-x*k2_PI;
    if(c>kPI){
        big_number ans = bsin(c-kPI);
        ans.is_negative = 1;
        return ans;
    } else if(c>kPI_2){
        return bsin(kPI - c);
    } else {
        big_number ans = big_number();
        big_number upd(c);
        for(int i=1;i<=499;i+=2){//Taylor expression for sin
            if(i%4==1) ans = ans + upd;
            else ans = ans - upd;
            upd=upd/(big_number(i+1)*big_number(i+2));
            upd=upd*c*c;
        }
        return ans;
    }
}
big_number bcos (const big_number v){
    big_number c(v);
    big_number x = c / k2_PI;
    x.floor();
    c=c-x*k2_PI;
    if(c>kPI){
        return bcos(k2_PI - c);
    } else if(c>kPI_2){
        big_number ans = bcos(kPI - c);
        ans.is_negative = 1;
        return ans;
    } else {
        big_number ans = big_number(1);
        big_number upd(c*c);
        upd = upd / big_number(2);
        for(int i=2;i<=500;i+=2){//Taylor expression for cos
            if(i%4==2) ans = ans - upd;
            else ans = ans + upd;
            upd=upd/(big_number(i+1)*big_number(i+2));
            upd=upd*c*c;
        }
        return ans;
    }
}
big_number btan (const big_number v){
    return bsin(v)/bcos(v);
}