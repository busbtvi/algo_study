// https://www.algospot.com/judge/problem/read/TILING2
#include <iostream>
#include <memory.h>
#include <cassert>
#define MOD 1000000007
using namespace std;

long long cache[100];
long long recursive(int len){
    if(len == 0) return 1;
    if(len <= 3) return len;

    long long& ans = cache[len];
    if(ans) return ans;
    
    int front = len/2, back = len/2 - !(len%2);
    ans =        (recursive(front  ) * recursive(back  ))%MOD;
    ans = (ans + (recursive(front-1) * recursive(back  ))%MOD) % MOD;
    ans = (ans + (recursive(front  ) * recursive(back-1))%MOD) % MOD;
    // ans = (recursive(front) * recursive(back))
    //     + (recursive(front-1) * recursive(back))
    //     + (recursive(front) * recursive(back-1));

    return ans;
}
void solve(){
    memset(cache, 0, sizeof(cache));
    int n;
    cin >> n;

    cout << recursive(n) << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    세로로 세워서 배치를 하거나, 가로로 뉘어서 2개를 배치하는 2가지 선택지를 고르고
    남은 길이를 넘겨서 재귀 호출
        - 일단 이렇게 생각했는데, 가로 길이를 기준으로 동일한 부분 문제이기 때문에 분할 정복 방식으로 변경
    주어진 길이의 가운데 index가
        1. 세로로 배치 recur[beg, index), recur[index+1, end)
        2. 가로 앞으로 배치 recur[beg, index-1), recur[index+1, end)
        3. 가로 뒤로 배치 recur[beg, index), recur[index+2, end)
    그리고 [beg,end)가 아니라 그냥 recur(remain_len)으로 처리하면 될듯?
*/