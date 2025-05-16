// https://www.acmicpc.net/problem/15989
#include <iostream>
using namespace std;

int dp[10001] = {0, 1, 2, 3, 4, };
int main(){
    int t, n, dp_max = 4;
    cin >> t;

    for(int i=5; i<=10000; i++){
        dp[i] = dp[i-1];  // 이전 모든 경우 + '1'

        // 2, 3으로만 조합되는 경우
        if(i%2) dp[i] += (i-3)/6 + 1;  // 홀수이면 3을 제외하고 생각
        else dp[i] += i/6 + 1;         // 짝수면 그냥 생각
    }

    for(int i=0; i<t; i++){
        cin >> n;
        cout << dp[n] << endl;
    }

    return 0;
}

/*
    -- 생각해 볼 것 --
    https://velog.io/@dhelee/%EB%B0%B1%EC%A4%80-15989%EB%B2%88-123-%EB%8D%94%ED%95%98%EA%B8%B0-4-Python-%EB%8B%A4%EC%9D%B4%EB%82%98%EB%AF%B9-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8DDP
    1만 써서 만들 수 있는 경우  => 모두 1가지
    2를 추가로 쓸 수 있는 경우  => dp[i] += dp[i-2]
    3을 추가로 쓸 수 있는 경우  => dp[i] += dp[i-3]

    dp를 수평이 아니라 수직으로 생각해 보기
*/