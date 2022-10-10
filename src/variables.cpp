#include "variables.hpp"
#include "bignumber.hpp"

#include <iostream>
#include <cstring>
#include <map>

std::map<std::string, big_number> variable_map;

/// @brief Insert value into a variable
/// @param name 
/// @param value 
void set_variable(const std::string name, big_number value){
    if(name=="ans" || name=="E"||name=="PI"){
        throw std::string("You cannot set const variable "+name+".");
    }
    variable_map.insert({name, value});
}
void set_const_variable(const std::string name, big_number value){
    variable_map.insert({name, value});
}
void set_variable(const char *name, big_number value){
    set_variable(std::string(name), value);
}

/// @brief Get value from a variable
/// @param name 
/// @return 
big_number get_variable(const std::string name){
    std::map<std::string, big_number>::iterator iter = variable_map.find(name);
    if (iter == variable_map.end()){
        throw "AT " + name + "\n   ^\nVariable not find";
    }
    else{
        return iter->second;
    }
}

big_number get_variable(const char *name){
    return get_variable(std::string(name));
}