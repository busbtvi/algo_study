// https://www.acmicpc.net/problem/2504
#include <iostream>
#include <stack>
using namespace std;

int main(){
    string str;
    stack<char> brackets;
    stack<int> values;
    int sum;
    
    cin >> str;
    for(auto c: str){
        if(c == '(' || c == '['){
            brackets.push(c);
            values.push(0);
        }
        else if(c == ')'){
            if(brackets.empty() || brackets.top() != '('){
                cout << 0;
                return 0;
            }
            brackets.pop();

            for(sum=0; !values.empty() && values.top()!=0; values.pop())
                sum += values.top();
            values.pop();
            values.push(sum ? sum*2 : 2);
        }
        else{  // ]
            if(brackets.empty() || brackets.top() != '['){
                cout << 0;
                return 0;
            }
            brackets.pop();

            for(sum=0; !values.empty() && values.top()!=0; values.pop())
                sum += values.top();
            values.pop();
            values.push(sum ? sum*3 : 3);
        }
    }

    sum = 0;
    if(brackets.empty()){
        while(!values.empty()){
            sum += values.top();
            values.pop();
        }
    }
    cout << sum;

    return 0;
}