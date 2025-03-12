// https://www.algospot.com/judge/problem/read/DRAGON
#include <iostream>
#include <memory.h>
#include <limits>
#define LIMIT 1000000000
using namespace std;

int cache[51];
int n, p ,l;
int recursive(int remain, char prev, int cur){  // remain: [0, n]
    int end = p+l;
    if(remain == 0){
        if(p <= cur && cur < end) cout << prev;
        // cout << prev;
        return 1;
    }

    /*
        캐시가 없거나 / 캐시o 범위x / 캐시o 범위o
        출력 x: 캐시o 범위x
    */
    int& ans = cache[remain];
    if(ans != 0 && (cur+ans< p || end <= cur))  // 캐시o 범위x
        return ans;

    int acc = 0;  // 캐시x(어짜피 cache 계산), 캐시o 범위o(출력해야됨)
    if(prev == 'Y'){
        if(p <= cur && cur < end) cout << 'F';
        acc += recursive(remain - 1, 'X', cur+1);
        if(p <= cur+acc+1 && cur+acc+1 < end) cout << '-';
        acc += recursive(remain - 1, 'Y', cur+acc+2);
    } else {
        acc += recursive(remain - 1, 'X', cur);
        if(p <= cur+acc && cur+acc < end) cout << '+';
        acc += recursive(remain - 1, 'Y', cur+acc+1);
        if(p <= cur+acc+1 && cur+acc+1 < end) cout << 'F';
    }
    
    if(ans == 0){
        ans = acc + 2;  // F,- / +,F
        if(ans > LIMIT) ans = LIMIT;
    }
    return ans;
}
void solve(){
    cin >> n >> p >> l;

    p--;  // to use as start index
    memset(cache, 0, sizeof(cache));

    if(p == 0) cout << 'F';
    recursive(n, 'X', 1);
    cout << endl;

    // cout << endl;
    // for(int i=0; i<=n; i++) cout << cache[i] << ' ';
    // cout << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    이것저것 생각해 보다가, 그냥 일단 단순하게 n세대 문자열 출력하는 재귀부터 생각
    F출력, 현재가 마지막 세대면 X출력/아니면 재귀
        파라미터를 현재 몇세대가 아니라, 몇세대 남았는지
        반환값을 해당 세대의 출력 문자수
        로 한다면 캐싱 + skip이 가능할듯
    시간 초과...(범위보다 큰 값의 빠른 return을 빼먹었음)

    -- 생각해 볼 것 --
    max 값을 정할때, A_n+1 = 2*A_n + 2 이기 때문에
    2배를 곱해도 overflow가 나지 않을 정도의 크기를 잘 정해야 한다

    n세대 문자열에서 p번째 문자를 출력하는 함수 * l번 반복  도 가능한 방식이다
    길이의 점화식을 찾았기 때문에, 따로 길이의 계산해 놓고 활용할 수도 있다.
*/