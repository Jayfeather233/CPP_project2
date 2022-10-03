#include "bignumber.hpp"
#include "variables.hpp"

#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

const int MAXM = 100000;

int bracket_nxt[MAXM];
int bracket_pre[MAXM];
void bracket_match(char *input, int l, int r)
{
    stack<int> pre_bracket;
    while (!pre_bracket.empty())
        pre_bracket.pop();
    for (int i = l; i < r; i++)
    {
        if (input[i] == '(')
        {
            pre_bracket.push(i);
        }
        else if (input[i] == ')')
        {
            if (pre_bracket.empty())
                throw i;
            int u = pre_bracket.top();
            bracket_nxt[u] = i;
            bracket_pre[i] = u;
            pre_bracket.pop();
        }
    }
    if (!pre_bracket.empty())
    {
        throw pre_bracket.top();
    }
}
char input[MAXM];
int main(int argc, char **argv)
{
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
            puts("    and functions: pow sqrt sin cos tan ln");
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
    set_variable("E",C_E);
    set_variable("PI",C_PI);
    while (true)
    {
        scanf("%[^\n]", input);
        scanf("%*c");
        if(strcmp(input,"quit")==0){
            break;
        }
        if(strcmp(input,"exit")==0){
            puts("Use \'quit\' to quit");
            continue;
        }
        int lt = strlen(input), nlt = 0;
        // delete empty space in input
        for (int i = 0; i < lt; i++)
        {
            if (input[i] != ' ')
            {
                input[nlt++] = input[i];
            }
        }
        lt = nlt;
        input[lt] = 0;
        for (int i = 0; i < lt; i++)
        {
            bracket_nxt[i] = bracket_pre[i] = 0;
        }
        try
        {
            bracket_match(input, 0, nlt);
        }
        catch (int e)
        {
            printf("Cannot do bracket matching. Please check your input.\nAT %s\n", input);
            printf("   ");
            for (int i = 0; i < e; i++)
                printf(" ");
            printf("^\n");
        }
        
    }
    return 0;
}