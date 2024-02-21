// https://www.acmicpc.net/problem/7579

// 전부 다 비활성화한다고 생각 -> 하나씩 덜 비활성화
// 덜 비활성화 하는 m가 쌓여서 (∑m - M) 이하가 되게 : 가방 중량 제한
// 추가 비용 c의 감소 = 가치↑

// ==> m이 gap 이하가 되게, c는 최대가 되게
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){
    int n, m, memSum=0, costSum=0, memGap;
    cin >> n >> m;

    vector<int> mem(n), cost(n);
    for(int i=0; i<n; i++){
        cin >> mem[i];
        memSum += mem[i];
    }
    for(int i=0; i<n; i++){
        cin >> cost[i];
        costSum += cost[i];
    }
    memGap = memSum - m;

    vector<vector<int>> dp(memGap+1, vector<int>(n, 0));
    for(int i=mem[0]; i<=memGap; i++) dp[i][0] = cost[0];
    for(int i=0; i<=memGap; i++){
        for(int j=1; j<n; j++){
            if(mem[j] > i) continue;

            dp[i][j] = max(
                max(dp[i-1][j], dp[i][j-1]), 
                dp[i-mem[j]][j-1] + cost[j]
            );
            // dp[i][j] = max(
            //     max(dp[i-1][j], j==0 ? 0 : dp[i][j-1]), 
            //     (j == 0) ? cost[j] : dp[i-mem[j]][j-1] + cost[j]
            // );
        }
    }

    // cout << '\n';
    // for(int i=0; i<=memGap; i++){
    //     for(int j=0; j<n; j++)
    //         cout << dp[i][j] << ' ';
    //     cout << '\n';
    // }
    // cout << '\n';

    cout << costSum - dp[memGap][n-1];

    return 0;
}