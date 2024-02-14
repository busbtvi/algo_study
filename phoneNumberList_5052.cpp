// https://www.acmicpc.net/problem/5052
#include <iostream>
#include <set>
using namespace std;

int main(){
    int t;

    cin >> t;
    for(int i=0, n; i<t; i++){
        cin >> n;

        set<string> suffixs, phoneNums;
        string in, result = "YES\n";
        for(int j=0; j<n; j++){
            cin >> in;

            if(result == "YES\n"){
                if(suffixs.find(in) != suffixs.end()) result = "NO\n";
                else for(int k=1; k<=in.length(); k++){
                    suffixs.insert(in.substr(0,k));
                    if(phoneNums.find(in.substr(0,k)) != phoneNums.end()){
                        result = "NO\n";
                        break;
                    }
                }
            }
            phoneNums.insert(in);
        }

        cout << result;
    }
    return 0;
}