// https://www.acmicpc.net/problem/2342
#include <iostream>
#include <vector>
#define MAX 123456789
using namespace std;

int cost[5][5] = {  // cost[from][to]
    {0, 2, 2, 2, 2},
    {0, 1, 3, 4, 3},
    {0, 3, 1, 3, 4},
    {0, 4, 3, 1, 3},
    {0, 3, 4, 3, 1}
};

int main(){
    vector<vector<int>> dp(100000, vector<int>(25, MAX));
    int n, k=0, ans = MAX;

    cin >> n;
    dp[0][n*5] = cost[0][n];  // 왼발을 옮기거나
    dp[0][n]   = cost[0][n];  // 오른발을 옮기거나

    while(true){  // 처음부터 0이 들어오는 경우?
        cin >> n;
        if(n == 0) break;
        k++;

        for(int i=0; i<5; i++){  // 왼발
            for(int j=0; j<5; j++){  // 오른발
                if(i == j) continue;
                
                int prev = i*5 + j;
                if(dp[k-1][prev] != MAX){
                    dp[k][n*5 + j] = min(dp[k][n*5 + j], dp[k-1][prev] + cost[i][n]);
                    dp[k][i*5 + n] = min(dp[k][i*5 + n], dp[k-1][prev] + cost[j][n]);
                }
            }
        }
    }

    // cout << endl;
    // for(int i=0; i<=k; i++){
    //     for(int j=0; j<25; j++){
    //         if(dp[i][j] == MAX) cout << ". ";
    //         else cout << dp[i][j] << ' ';
    //         if(j%5 == 4) cout << '|';
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    for(int i=0; i<25; i++) ans = min(ans, dp[k][i]);
    cout << ans << endl;
}

/*
    -- 생각 과정 --
    모든 경우 다 해보기(DP)
    두 발이 있을 수 있는 경우: 5*5

    -- 틀린 이유 --
    다른 경로로 동일한 위치에 접근해 올 수 있는데(34, 35번 line)
    그때 최소의 경우를 택해야 하는데 그러지 않았음
    https://www.acmicpc.net/board/view/59839
*/