// https://www.algospot.com/judge/problem/read/ASYMTILING
#include <iostream>
#include <memory.h>
#include <cassert>
#define MOD 1000000007
using namespace std;

long long cache[101];
long long recursive(int n){
    if(n == 0) return 1;
    if(n <= 3) return n;

    long long& ans = cache[n];
    if(ans == 0){
        int front = n/2, back = n/2 - !(n%2);

        ans =        (recursive(front  ) * recursive(back  ))%MOD;
        ans = (ans + (recursive(front-1) * recursive(back  ))%MOD) % MOD;
        ans = (ans + (recursive(front  ) * recursive(back-1))%MOD) % MOD;
    }
    
    return ans;
}
long long calc_sym(int n){
    if(n <= 2) return n;
    if(n == 3) return 1;

    int half = n/2;
    long long ans = recursive(half);  // ()|() & ()()
    if(n % 2 == 0)  // ()=()
        ans = (ans + recursive(half-1)) % MOD;

    return ans;
}
void solve(){
    memset(cache, 0, sizeof(cache));
    int n;
    cin >> n;

    long long all_case = recursive(n);
    long long sym_case = calc_sym(n);
    if(all_case < sym_case) all_case += MOD;

    // cout << all_case << ' ' << sym_case << endl;
    cout << all_case - sym_case << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    비슷한 문제를 풀었응니, 그냥 전체 경우의 수 - 좌우 대칭인 경우의 수
        - 대칭인 경우: ()|(), ()=(), ()()
    % 연산에서 - 가 나왔을 때, 음수의 경우를 생각해야함
*/