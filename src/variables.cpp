#include "variables.hpp"
#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <map>

std::map<std::string,big_number> variable_map;

inline void set_variable(std::string name, const big_number value){
    variable_map.insert({name,value});
}

inline big_number get_variable(std::string name){
    std::map<std::string,big_number>::iterator iter = variable_map.find(name);
    if(iter == variable_map.end()){
        throw VARIABLE_DO_NOT_FIND;
    }else{
        return iter->second;
    }
}