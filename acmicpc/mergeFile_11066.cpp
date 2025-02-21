// https://www.acmicpc.net/problem/11066
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;

    for(int ti=0, k; ti<t; ti++){
        cin >> k;
        vector<vector<int>> dp(k, vector<int>(k, 0));
        vector<int> cumulativeSum(k+1), nums(k);
        for(int i=0; i<k; i++){
            cin >> nums[i];
            cumulativeSum[i+1] = cumulativeSum[i] + nums[i];
        }

        for(int ijGap=1; ijGap<k; ijGap++){
            for(int diaCount=0; diaCount+ijGap<k; diaCount++){
                int i=diaCount, j=diaCount+ijGap;
                int curCost = ~(1<<31);

                for(int l=i; l<j; l++){
                    curCost = min(curCost, 
                        dp[i][l] + dp[l+1][j] + 
                        (cumulativeSum[l+1] - cumulativeSum[i]) + 
                        (cumulativeSum[j+1] - cumulativeSum[l+1])
                    );
                }
                dp[i][j] = curCost;
            }
        }

        cout << dp[0][k-1] << '\n';
    }

    return 0;
}