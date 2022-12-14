#ifndef _INC_CALCRPN_HPP
#define _INC_CALCRPN_HPP 1

#include "bignumber.hpp"

#include <iostream>
#include <vector>

//Some functions used to convert and calculate input
void bracket_match(std::string, int, int);
std::vector<std::string> build_RPN(std::string,int,int);
big_number calc_RPN(std::vector<std::string>);

#endif