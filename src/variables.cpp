#include "variables.hpp"
#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <map>

std::map<std::string, big_number> variable_map;

void set_variable(const std::string name, big_number value){
    variable_map.insert({name, value});
}
void set_variable(const char *name, big_number value){
    variable_map.insert({std::string(name), value});
}

big_number get_variable(const std::string name){
    std::map<std::string, big_number>::iterator iter = variable_map.find(name);
    if (iter == variable_map.end()){
        throw VARIABLE_DO_NOT_FIND;
    }
    else{
        return iter->second;
    }
}

big_number get_variable(const char *name){
    return get_variable(std::string(name));
}