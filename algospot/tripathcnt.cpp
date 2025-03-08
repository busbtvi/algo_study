// https://www.algospot.com/judge/problem/read/TRIPATHCNT
#include <iostream>
#include <cassert>
#include <memory.h>
using namespace std;

void solve(){
    int nums[100][100], sums[100][100], cases[100][100];
    int n;

    // input
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<=i; j++) cin >> nums[i][j];
    
    // calc cases & sums
    sums[0][0] = nums[0][0];
    cases[0][0] = 1;
    for(int i=1; i<n; i++){
        sums[i][0] = sums[i-1][0] + nums[i][0];
        cases[i][0] = 1;

        for(int j=1; j<i; j++){
            if(sums[i-1][j-1] == sums[i-1][j]){
                sums[i][j] = sums[i-1][j] + nums[i][j];
                cases[i][j] = cases[i-1][j-1] + cases[i-1][j];
            } else if(sums[i-1][j-1] < sums[i-1][j]){
                sums[i][j] = sums[i-1][j] + nums[i][j];
                cases[i][j] = cases[i-1][j];
            } else {
                sums[i][j] = sums[i-1][j-1] + nums[i][j];
                cases[i][j] = cases[i-1][j-1];
            }
        }

        sums[i][i] = sums[i-1][i-1] + nums[i][i];
        cases[i][i] = 1;
    }

    int max_num=0, count=0;
    for(int j=0; j<n; j++){
        if(max_num == sums[n-1][j]) count += cases[n-1][j];
        else if(max_num < sums[n-1][j]){
            count = cases[n-1][j];
            max_num = sums[n-1][j];
        }
    }
    cout << count << endl;
}
int nums[100][100], sums[100][100], cases[100][100], n;
void recursive(int i, int j){  // i:[0, ??
    if(i == n-1){
        sums[i][j] = nums[i][j];
        cases[i][j] = 1;
        return;
    }
    if(sums[i][j]) return;
    recursive(i+1, j); recursive(i+1, j+1);

    if(sums[i+1][j] == sums[i+1][j+1]){
        sums[i][j] = sums[i+1][j] + nums[i][j];
        cases[i][j] = cases[i+1][j] + cases[i+1][j+1];
    } else if(sums[i+1][j] < sums[i+1][j+1]){
        sums[i][j] = sums[i+1][j+1] + nums[i][j];
        cases[i][j] = cases[i+1][j+1];
    } else {
        sums[i][j] = sums[i+1][j] + nums[i][j];
        cases[i][j] = cases[i+1][j];
    }
}
void solve2(){  // solve with recursive version
    memset(nums, 0, sizeof(nums));
    memset(sums, 0, sizeof(sums));
    memset(cases, 0, sizeof(cases));
    
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<=i; j++) cin >> nums[i][j];

    recursive(0,0);
    cout << cases[0][0] << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    // while(test_case--) solve();
    while(test_case--) solve2();
    return 0;
}

/*
    -- 생각 과정 --
    위에서 부터 아래로 내려오면서 누적합 구하기 + 경우의 수 계산
    경우의 수[i][j] = (sum[i-1][j-1] == sum[i-1][j]) ?
        두 경우의 수 합 : 둘중 큰 수의 경우의 수
    sum과 경우의 수를 훓으며, 최대값과 sum이 같으면 경우의 수 누적

    -- 생각해 볼 것 --
    지금은 재귀가 아니라 반복문으로 풀었는데, 
    반복문과 재귀가 기본적으로 답을 계산해 나가는 과정이 반대인듯
        - 반복문은 앞에서 뒤로, 재귀는 뒤에서 앞으로
*/