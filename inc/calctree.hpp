#ifndef _INC_CALCTREE_HPP
#define _INC_CALCTREE_HPP 1

#include "bignumber.hpp"

struct calc_tree{
    char op[2];     //operation like + - * / or a function
    int ch[2];      //do operation for two number
};

void bracket_match(char *, int, int);
int build_calc_tree(char*,int,int);
big_number calc_calc_tree(int);

#endif