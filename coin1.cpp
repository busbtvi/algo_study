// https://www.acmicpc.net/problem/2293
#include <algorithm>
#include <iostream>
using namespace std;

int main(){
    int n, k, coins[101] = {0,}, cases[10001] = {1,};
    cin >> n >> k;

    for(int i=1; i<=n; i++) cin >> coins[i];
    sort(coins, coins+n);
    // fill(cases, cases+10001, 1);

    for(int i=1; i<=n; i++){
        for(int j=coins[i]; j<=k; j++){
            cases[j] += cases[j - coins[i]];
        }
    }

    cout << cases[k];
    return 0;
}