// https://www.acmicpc.net/problem/10942
#include <iostream>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, nums[2001];
    bool dp[2001][2001];
    cin >> n;
    for(int i=1; i<=n; i++) cin >> nums[i];
    cin >> m;

    for(int r=1; r<=n; r++){
        for(int c=1; c<=r; c++){
            if(r == c) dp[r][c] = true;
            else if(r-1 == c) dp[r][c] = (nums[r]==nums[c]);
            else dp[r][c] = (dp[r-1][c+1] && nums[r]==nums[c]);
        }
    }    

    for(int i=0,s,e; i<m; i++){
        cin >> s >> e;
        cout << dp[e][s] << '\n';
    }
}