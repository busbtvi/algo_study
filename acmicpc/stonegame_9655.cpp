// https://www.acmicpc.net/problem/9655
#include <iostream>
#include <memory.h>
using namespace std;

char dp[1001] = {0, };
bool win(int n){
    if(n == 3 || n == 1) return true;
    if(n == 2) return false;

    // more than 3
    char& ans = dp[n];
    if(ans == -1){
        if(!win(n-3) || !win(n-1))
            ans = 1;
        else ans = 0;
    }
    return static_cast<bool>(ans);
}
int main(){
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;

    cout << (win(n) ? "SK" : "CY");

    return 0;
}