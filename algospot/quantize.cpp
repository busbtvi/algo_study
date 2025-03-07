// https://www.algospot.com/judge/problem/read/QUANTIZE
#include <iostream>
#include <algorithm>
#include <cassert>
#include <memory.h>
#define INF 987654321;
using namespace std;

int num[100], sums[100][100];  // sum in range of [beg, end]
int n, s, cache[100][10];
void calc_sums(){
    sums[0][0] = num[0];
    for(int j=1; j<n; j++) sums[0][j] = sums[0][j-1] + num[j];
    for(int i=1; i<n; i++){
        for(int j=i; j<n; j++)
            sums[i][j] = sums[i-1][j] - num[i-1];
    }
}
int recursive(int cur, int remain){  // cur: [0, n], remain: [0, s]
    if(cur == n || n <= cur + remain) return 0;
    if(remain == 0) return INF;

    assert(remain > 0);
    assert(cur < n);
    int& ans = cache[cur][remain-1];
    if(ans) return ans;

    ans = INF;
    for(int i=cur; i<n; i++){
        // [cur, i]까지의 평균 계산
        int cur_avr = round(static_cast<double>(sums[cur][i]) / (i-cur+1));
        int error = 0;
        for(int j=cur; j<=i; j++) 
            error += (cur_avr-num[j])*(cur_avr-num[j]);
        
        // cout << "error " << cur_avr << ' ' << cur << ' ' << i << ' ' << error << endl;
        ans = min(ans, error + recursive(i+1, remain-1));
    }
    return ans;
}
void solve(){
    memset(num, 0, sizeof(num));
    memset(sums, 0, sizeof(sums));
    memset(cache, 0, sizeof(cache));

    cin >> n >> s;
    for(int i=0; i<n; i++) cin >> num[i];

    sort(num, num + n);
    calc_sums();

    cout << recursive(0, s) << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    정렬 + 
    부분합[시작][끝]을 가지고 있으면, 평균 계산하기 편할듯?
    recursive(현재 위치, 남은 집합 수): 현재 위치 뒤로 나올 수 있는 최소 오차 제곱 합

    -- 생각해 볼 것 --
    각 함수에, input의 범위를 작성해보기
    범위가 애매할 때는 assert로 확인 해보기

    sums로 [beg, end]의 합을 구할필요 없이, 부분합으로 계산했어도 됬었다
    마찬가지로 제곱의 부분합을 미리 구해놓았어도 [beg, end]의 제곱합에서
    해당 구간의 평균 제곱을 뺐어도 오차 제곱합을 구할 수 있었다.
*/