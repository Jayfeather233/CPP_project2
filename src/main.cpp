#include "bignumber.hpp"
#include "variables.hpp"
#include "calcRPN.hpp"

#include <iostream>
#include <cstring>
#include <stack>
#include <vector>

// To call functions in calcRPN
big_number calc(std::string input, int l, int r){
    bracket_match(input, l, r);
    std::vector<std::string> RPN_exp = build_RPN(input, l, r);
    return calc_RPN(RPN_exp);
}
std::string input;
int main(int argc, char **argv){
    if(argc != 1){// Below are documents
        if(argc > 2){
            puts("Too many parameters! Please use -h or --help to see the documents.");
            return 1;
        }
        if(strcmp(argv[1],"-h")==0||strcmp(argv[1],"--help")==0){
            puts("Usage: bc [-h | --help] [-v | --version]");
            puts("");
            puts("You should directly run ./bc to calculate expressions.");
            puts("Support: + - * / ^ () and < > <= >= == !=");
            puts("    and functions: sqrt sin cos tan ln");
            puts("    and [variable name] = [expressions]");
            puts("");
            puts("Built in variables: PI = 3.14... E = 2.718...");
            puts("");
            puts("Options meaning:");
            puts("  -h or --help:    Show this information.");
            puts("  -v or --version: Show the version information.");
            puts("");
        } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            puts("better calc(C++ project 2) by jayfeather233 version 1.0.0");
        } else {
            puts("Unknown command. Try -h for help.");
            return 1;
        }
        return 0;
    }
    puts("Welcome to better calculator. please input your expressions.");
    // const number e and pi
    big_number C_E("2.71828182845904523536028747135");
    big_number C_PI("3.1415926535897932384626433832");
    set_const_variable("E",C_E);
    set_const_variable("PI",C_PI);
    while (true){
        input="";
        getline(std::cin,input);
        int lt = input.length(), nlt = 0;
        if(lt==0) continue;//No input
        if(input=="quit" || input=="exit"){
            break;
        }
        // delete empty space in input
        for (int i = 0; i < lt; i++){
            if (input[i] != ' '){
                input[nlt++] = input[i];
            }
        }
        lt = nlt;
        input[lt] = 0;

        int flg_var = 0;
        for(int i=0;i<nlt;i++){
            if(input[i]=='=' && input[i-1]!= '<' && input[i-1]!= '>' && input[i-1]!= '!' && input[i-1]!= '=' &&
                input[i+1]!= '<' && input[i+1]!= '>' && input[i+1]!= '!' && input[i+1]!= '='){
                // A single '=', means variable assignment.
                std::string var_name="";
                for(int j=0;j<i;j++){
                    var_name+=input[j];
                }
                if(var_name.length()==0){
                    std::cout<<"Lack of variable name."<<std::endl;
                }else{
                    try{
                        big_number result = calc(input, i+1, nlt-1);
                        set_variable(var_name, result);
                        std::cout<<"set "<<var_name<<" to ";
                        result.output();
                        std::cout<<std::endl;
                    } catch (std::string e){
                        std::cout<<e<<std::endl;
                    } catch (const char* e){
                        std::cout<<e<<std::endl;
                    }
                }
                flg_var = 1;
                break;
            }
        }

        if(!flg_var){//otherwise is a expression with output result
            try
            {
                big_number u = calc(input,0,nlt-1);
                u.output();
                set_const_variable("ans",u);
                std::cout<<std::endl;
            } catch (std::string e){
                std::cout<<e<<std::endl;
            } catch (const char* e){
                std::cout<<e<<std::endl;
            }
        }
    }
    return 0;
}