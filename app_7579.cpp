// https://www.acmicpc.net/problem/7579
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){
    int n, m, costSum=0;
    cin >> n >> m;

    vector<int> mem(n), cost(n);
    for(int i=0; i<n; i++) cin >> mem[i];
    for(int i=0; i<n; i++){
        cin >> cost[i];
        costSum += cost[i];
    }

    vector<vector<int>> dp(n, vector<int>(costSum+1, 0));
    for(int j=cost[0]; j<=costSum; j++) dp[0][j] = mem[0];
    for(int i=1; i<n; i++){
        for(int j=0; j<=costSum; j++){
            if(cost[i] > j){
                dp[i][j] = dp[i-1][j];
                continue;
            }

            dp[i][j] = max(
                dp[i-1][j],
                dp[i-1][j-cost[i]] + mem[i]
            );
        }
    }
    
    for(int j=0; j<=costSum; j++){
        if(dp[n-1][j] >= m){
            cout << j;
            break;
        }
    }

    return 0;
}
// https://hackids.tistory.com/113