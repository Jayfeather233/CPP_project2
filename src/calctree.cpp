#include "calctree.hpp"
#include "exception.hpp"

#include <stack>

int my_cmp(const char* str1, const char* str2, const int len){
    for(int i=0;i<len;i++){
        if(str1[i]!=str2[i]){
            return 0;
        }
    }
    return 1;
}

const int MAXM = 1000000;

calc_tree tree_node[MAXM];
int node_num=1;

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
            if (pre_bracket.empty())
                throw (m_exception){i,"Bracket matching failed."};
            int u = pre_bracket.top();
            bracket_nxt[u] = i;
            bracket_pre[i] = u;
            pre_bracket.pop();
        }
    }
    if (!pre_bracket.empty())
    {
        throw (m_exception){pre_bracket.top(),"Bracket matching failed."};
    }
}

int build_calc_tree(char *input, int l, int r){
    try{
        for(int i=r;i>=l;i--){//== != < > <= >=
            if(input[i]==')'){
                i=bracket_pre[i];
            }
            else if(((input[i]=='=' || input[i]=='!' || input[i]=='<' || input[i]=='>') && input[i+1]=='=')){
                int u = node_num++;
                tree_node[u].op[0]=input[i];
                tree_node[u].op[1]=input[i+1];
                tree_node[u].ch[0]=build_calc_tree(input,l,i-1);
                tree_node[u].ch[1]=build_calc_tree(input,i+1,r);
                return u;
            }
            else if(input[i]=='<' || input[i]=='>'){
                int u = node_num++;
                tree_node[u].op[0]=input[i];
                tree_node[u].ch[0]=build_calc_tree(input,l,i-1);
                tree_node[u].ch[1]=build_calc_tree(input,i+1,r);
                return u;
            }
        }
        for(int i=r;i>=l;i--){//+ -
            if(input[i]==')'){
                i=bracket_pre[i];
            }
            else if(input[i]=='+' || input[i]=='-'){
                int u = node_num++;
                tree_node[u].op[0]=input[i];
                tree_node[u].ch[0]=build_calc_tree(input,l,i-1);
                tree_node[u].ch[1]=build_calc_tree(input,i+1,r);
                return u;
            }
        }
        for(int i=r;i>=l;i--){//* /
            if(input[i]==')'){
                i=bracket_pre[i];
            }
            else if(input[i]=='*' || input[i]=='/'){
                int u = node_num++;
                tree_node[u].op[0]=input[i];
                tree_node[u].ch[0]=build_calc_tree(input,l,i-1);
                tree_node[u].ch[1]=build_calc_tree(input,i+1,r);
                return u;
            }
        }
        for(int i=r;i>=l;i--){//^
            if(input[i]==')'){
                i=bracket_pre[i];
            }
            else if(input[i]=='^'){
                int u = node_num++;
                tree_node[u].op[0]=input[i];
                tree_node[u].ch[0]=build_calc_tree(input,l,i-1);
                tree_node[u].ch[1]=build_calc_tree(input,i+1,r);
                return u;
            }
        }
        
        for(int i=l;i<=r;i++){
            if(input[i]=='('){
                if(my_cmp(input+l,"sqrt",4)){
                    int u = node_num ++;
                    tree_node[u].op[0]='s';
                    tree_node[u].op[1]='q';
                    tree_node[u].ch[0]=build_calc_tree(input,i+1,bracket_nxt[i]-1);
                }
            }
        }
    } catch (m_exception e){
        throw e;
    }


}
big_number calc_calc_tree(int node){

}