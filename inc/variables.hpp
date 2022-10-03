#ifndef _INC_VARIABLES_HPP
#define _INC_VARIABLES_HPP 1

#define VARIABLE_DO_NOT_FIND 1

#include "bignumber.hpp"

#include <iostream>
#include <cstring>

void set_variable(const std::string, big_number);
void set_variable(const char *, big_number);
big_number get_variable(const std::string);
big_number get_variable(const char *);

#endif