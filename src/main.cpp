#include "bignumber.hpp"
#include "variables.hpp"
#include "calcRPN.hpp"

#include <iostream>
#include <cstring>
#include <stack>
#include <vector>

big_number calc(char *input, int l, int r){
    bracket_match(input, l, r);
    std::vector<std::string> RPN_exp = build_RPN(input, l, r);
    return calc_RPN(RPN_exp);
}
char input[1000000];
int main(int argc, char **argv){
    if(argc != 1){
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
    big_number C_E("2.7182818284590452353602874713526624977572470936999595749669676277240766303535");
    big_number C_PI("3.141592653589793238462643383279502884197169399375105820974944592307816406286");
    set_variable("e",C_E);
    set_variable("pi",C_PI);
    while (true){
        input[0]=0;
        scanf("%[^\n]", input);
        scanf("%*c");
        int lt = strlen(input), nlt = 0;
        if(lt==0) continue;
        for(int i=0;i<lt;i++){
            if('A'<=input[i] && input[i]<='Z'){
                input[i]+='a'-'A';
            }
        }
        if(strcmp(input,"quit")==0){
            break;
        }
        if(strcmp(input,"exit")==0){
            puts("Use \'quit\' to quit");
            continue;
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
                
                std::string var_name="";
                for(int j=0;j<i;j++){
                    var_name+=input[j];
                }
                try{
                    big_number result = calc(input, i+1, nlt-1);
                    set_variable(var_name, result);
                } catch (std::string e){
                    std::cout<<e<<std::endl;
                }
                flg_var = 1;
                break;
            }
        }

        if(!flg_var){
            try
            {
                big_number u = calc(input,0,nlt-1);
                u.output();
                std::cout<<std::endl;
            } catch (std::string e){
                std::cout<<e<<std::endl;
            }
        }
    }
    return 0;
}