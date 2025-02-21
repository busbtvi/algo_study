// https://www.acmicpc.net/problem/1918
#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;

int main(){
    map<char, int> pri = {{'*', 1}, {'/', 1}, {'+', 0}, {'-', 0}};
    stack<char> operand, op;
    stack<int> opPri;
    int curPriority = 0;
    string infixStr, posfixStr = "";

    cin >> infixStr;

    for(auto c: infixStr){
        if('A'<=c && c<='Z') operand.push(c);
        else if(c == '(') curPriority += 10;
        else if(c == ')') curPriority -= 10;
        else{
            while(!opPri.empty() && opPri.top() >= curPriority+pri[c]){
                operand.push(op.top());
                op.pop(); opPri.pop();
            }

            op.push(c);
            opPri.push(curPriority + pri[c]);
        }
    }
    
    for(; !operand.empty(); operand.pop())
        posfixStr = operand.top() + posfixStr;
    for(; !op.empty(); op.pop())
        posfixStr += op.top();

    cout << posfixStr;

    return 0;
}