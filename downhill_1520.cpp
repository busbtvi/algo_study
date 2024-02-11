// https://www.acmicpc.net/problem/1520
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

map<int, map<int,int>> dp;
int n, m, mapData[500][500];
int recursive(int i, int j){
    if(dp[i].find(j) == dp[i].end()){
        if(i>0 && mapData[i][j]<mapData[i-1][j])
            dp[i][j] += recursive(i-1, j);
        if(i+1<n && mapData[i][j]<mapData[i+1][j])
            dp[i][j] += recursive(i+1, j);
        if(j>0 && mapData[i][j]<mapData[i][j-1])
            dp[i][j] += recursive(i, j-1);
        if(j+1<m && mapData[i][j]<mapData[i][j+1])
            dp[i][j] += recursive(i, j+1);
    }

    return dp[i][j];
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++) cin >> mapData[i][j];
    
    dp[0][0] = 1;
    cout << recursive(n-1, m-1);

    return 0;
}