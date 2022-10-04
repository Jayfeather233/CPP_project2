#include "calcRPN.hpp"
#include "variables.hpp"

#include <stack>
#include <iostream>
#include <vector>

const int MAXM = 1000000;

int bracket_nxt[MAXM];
int bracket_pre[MAXM];

void bracket_match(char *input, int l, int r)
{
    for(int i=l;i<=r;i++){
        bracket_nxt[i]=bracket_pre[i]=0;
    }
    std::stack<int> pre_bracket;
    while (!pre_bracket.empty())
        pre_bracket.pop();
    for (int i = l; i <= r; i++)
    {
        if (input[i] == '(')
        {
            pre_bracket.push(i);
        }
        else if (input[i] == ')')
        {
            if (pre_bracket.empty()){
                std::string msg(input);
                msg+='\n';
                for(int j=0;j<i;j++) msg+=' ';
                msg+="^\nBracket matching failed.";
                throw msg;
            }
            int u = pre_bracket.top();
            bracket_nxt[u] = i;
            bracket_pre[i] = u;
            pre_bracket.pop();
        }
    }
    if (!pre_bracket.empty())
    {
        int u = pre_bracket.top();
        std::string msg(input);
        for(int j=0;j<u;j++) msg+=' ';
        msg+="^\nBracket matching failed.";
        throw msg;
    }
}

inline int is_operator(const char& a){
    return (a=='+' || a=='-' || a=='*' || a=='/' || a=='^' ||
            a=='(' || a==')' || a=='<' || a=='>' || a=='=' || a=='!');
}
inline int is_function(const std::string a){
    return a=="sqrt" || a=="sin" || a=="cos" || a=="tan" || a=="ln";
}
inline int get_priority(const char& a){
    if(a=='=' || a=='<' || a=='>' || a=='!') return 0;
    else if(a=='(') return 1;
    else if(a=='+' || a=='-') return 2;
    else if(a=='*' || a=='/') return 3;
    else return 4;
}

std::vector<std::string> convert_input(char *input, int l, int r){
    std::vector<std::string> result;
    std::string str;
    for(int i=l;i<=r;i++){
        if(is_operator(input[i])){
            str="";
            str+=input[i];
            if(i<r && input[i+1]=='='){
                str+=input[i+1];
                i++;
            }
            result.push_back(str);
        } else {
            str="";
            while(i<=r && !is_operator(input[i])){
                str+=input[i];
                i++;
            }
            --i;
            result.push_back(str);
        }
    }
    return result;
}
std::vector<std::string> build_RPN(char *input_ori, int l, int r){
    std::vector<std::string> result;
    std::stack<std::string> tmp;
    std::vector<std::string> input = convert_input(input_ori,l,r);

    for(std::string op : input){
        if(op[0]=='('){
            tmp.push(op);
        }else if(op[0]==')'){
            while(tmp.top()[0]!='('){
                result.push_back(tmp.top());
                tmp.pop();
            }
            tmp.pop();
            if(tmp.size() && is_function(tmp.top())){
                result.push_back(tmp.top());
                tmp.pop();
            }
        }else if(is_operator(op[0])){
            while(tmp.size() && (get_priority(op[0]) <= get_priority(tmp.top()[0]))){
                result.push_back(tmp.top());
                tmp.pop();
            }
            tmp.push(op);
        }else if(is_function(op)){
            tmp.push(op);
        }else{
            result.push_back(op);
        }
    }
    while(tmp.size()){
        result.push_back(tmp.top());
        tmp.pop();
    }
    return result;
}
big_number calc_RPN(std::vector<std::string> expression){
    std::stack<big_number> result;
    big_number t1,t2;
    for(std::string op : expression){
        if(is_operator(op[0])){
            if(result.size()<2){
                throw "Expression error.";
            }
            t1=result.top();result.pop();
            t2=result.top();result.pop();

            if(op[0]=='+'){
                result.push(t2+t1);
            }else if(op[0]=='-'){
                result.push(t2-t1);
            }else if(op[0]=='*'){
                result.push(t2*t1);
            }else if(op[0]=='/'){
                result.push(t2/t1);
            }else if(op[0]=='^'){
                result.push(bpow(t2,t1));
            }else if(op[0]=='<' && op[1]!='='){
                result.push(t2<t1);
            }else if(op[0]=='>' && op[1]!='='){
                result.push(t2>t1);
            }else if(op[0]=='<' && op[1]=='='){
                result.push(t2<t1);
            }else if(op[0]=='>' && op[1]=='='){
                result.push(t2>=t1);
            }else if(op[0]=='=' && op[1]!='='){
                result.push(t2==t1);
            }else if(op[0]=='!' && op[1]!='='){
                result.push(t2!=t1);
            }
        }else if(is_function(op)){
            if(result.size()<1){
                throw "Expression error.";
            }
            t1=result.top();result.pop();

            if(op=="sqrt"){
                result.push(bsqrt(t1));
            }else if(op=="sin"){
                result.push(bsin(t1));
            }else if(op=="cos"){
                result.push(bcos(t1));
            }else if(op=="tan"){
                result.push(btan(t1));
            }else if(op=="ln"){
                result.push(bln(t1));
            }
        }else{
            try{
                result.push(big_number(op));
            } catch (std::string e){
                try{
                    result.push(get_variable(op));
                } catch (std::string e2){
                    throw e2;
                }
            }
        }
    }
    if(result.size()>=2){
        throw "Expression error.";
    }
    return result.top();
}