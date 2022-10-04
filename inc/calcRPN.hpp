#ifndef _INC_CALCRPN_HPP
#define _INC_CALCRPN_HPP 1

#include "bignumber.hpp"

#include <iostream>
#include <vector>

void bracket_match(char *, int, int);
std::vector<std::string> build_RPN(char*,int,int);
big_number calc_RPN(std::vector<std::string>);

#endif