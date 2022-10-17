#include "calcRPN.hpp"
#include "variables.hpp"

#include <stack>
#include <iostream>
#include <vector>

/// @brief To check if the input's brackets are correct
/// @param input 
/// @param l left bound
/// @param r right bound [l,r]
void bracket_match(std::string input, int l, int r)
{
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
            if (pre_bracket.empty()){//There is no '(' to matchh this ')'
                std::string msg(input);
                msg+='\n';
                for(int j=0;j<i;j++) msg+=' ';
                msg+="^\nBracket matching failed.";
                throw msg;
            }
            int u = pre_bracket.top();
            pre_bracket.pop();
        }
    }
    if (!pre_bracket.empty())// There are extra '('
    {
        int u = pre_bracket.top();
        std::string msg(input);
        msg+='\n';
        for(int j=0;j<u;j++) msg+=' ';
        msg+="^\nBracket matching failed.";
        throw msg;
    }
}

/// @brief To check if is an operator
/// @param a 
/// @return 1 for an operator
inline int is_operator(const char& a){
    return (a=='+' || a=='-' || a=='*' || a=='/' || a=='^' ||
            a=='(' || a==')' || a=='<' || a=='>' || a=='=' || a=='!');
}

/// @brief To check if is a function
/// @param a 
/// @return 1 for a function
inline int is_function(const std::string a){
    return a=="sqrt" || a=="sin" || a=="cos" || a=="tan" || a=="ln";
}

/// @brief To compare which operator should be calculate first
/// @param a 
/// @return the priority of the operator
inline int get_priority(const char& a){
    if(a=='(') return 0;
    else if(a=='=' || a=='<' || a=='>' || a=='!') return 1;
    else if(a=='+' || a=='-') return 2;
    else if(a=='*' || a=='/') return 3;
    else return 4;
}

/// @brief To convert char* input to vector<string>. Example:"abc+sin(y)" to ["abc","+","sin","(","y",")"]
/// @param input 
/// @param l left bound
/// @param r right bound [l,r]
/// @return the vector<string>
std::vector<std::string> convert_input(std::string input, int l, int r){
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
            if(str == "-"){
                try{
                    if(result.size()==0) throw std::string("");
                    try{
                        big_number(result.back());
                    }catch(std::string e){
                        get_variable(result.back());
                    }
                }catch(std::string e){
                    result.push_back("0");
                }
            }
            result.push_back(str);
        } else {
            str="";
            while(i<=r && (!is_operator(input[i]) || 
                            (input[i-1]=='e' && input[i]=='-'))){
                if(input[i]=='-' && input[i-1]=='e'){
                    int flg = 0;
                    try{
                        big_number ex = big_number(str);
                    } catch (std::string e){
                        flg=1;
                    }
                    if(flg) break;
                }
                str+=input[i];
                i++;
            }
            --i;
            result.push_back(str);
        }
    }
    return result;
}



/// @brief Convert infix expressionn to suffix expresssion. Example: ["abc","+","sin","(","y",")"] to ["abc","y","sinnn","+"]
/// @param input_ori Original input like "abs+sin(y)"
/// @param l left bound
/// @param r right bound
/// @return Suffix expression
std::vector<std::string> build_RPN(std::string input_ori, int l, int r){
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

            // After matching '()', to see if the next is a function name
            if(tmp.size() && is_function(tmp.top())){
                result.push_back(tmp.top());
                tmp.pop();
            }
        }else if(is_operator(op[0])){
            // pop all operators that has lower priority to get correct calculate order
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


/// @brief Compute a suffix expression
/// @param expression 
/// @return the value of this expression
big_number calc_RPN(std::vector<std::string> expression){
    std::stack<big_number> result;
    big_number t1,t2;
    for(std::string op : expression){
        if(is_operator(op[0])){//Binary operators
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
            }else if(op[0]=='=' && op[1]=='='){
                result.push(t2==t1);
            }else if(op[0]=='!' && op[1]=='='){
                result.push(t2!=t1);
            }
        }else if(is_function(op)){//functions
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
        }else{//Just a number or error
            try{
                result.push(big_number(op));
            } catch (std::string e){
                try{
                    result.push(get_variable(op));
                } catch (std::string e2){
                    throw e;
                }
            }
        }
    }
    if(result.size()>=2){
        throw std::string("Expression error.");
    }
    return result.top();
}