// https://www.algospot.com/judge/problem/read/PI
#include <iostream>
#include <memory.h>
#include <string>
#define OOS 10000000  // out of scope
using namespace std;

string num;
int difficurty[10000][5];  // index, length
int cache[10000];
int get_difficulty(int cur, int len){
    if(cur+len > num.size()) return OOS;
    
    int& ret = difficurty[cur][len];
    if(ret != 0) return ret;

    if(len == 3){  // no cache
        if(num[cur] == num[cur+1] && num[cur] == num[cur+2]) ret = 1;
        // only possilbe when, -1 * -1 or 1 * 1
        else if((num[cur+1]-num[cur]) * (num[cur+2]-num[cur+1]) == 1) ret = 2;
        else if(num[cur] == num[cur+2]) ret = 4;
        else if(num[cur+1]-num[cur] == num[cur+2]-num[cur+1]) ret = 5;
        else ret = 10;
    } else {  // use cache
        int last = cur + len - 1;

        if(difficurty[cur][len-1] == 1 &&
            num[last] == num[last-1]) 
            ret = 1;
        else if(difficurty[cur][len-1] == 2 &&
            num[last]-num[last-1] == num[last-1]-num[last-2])
            ret = 2;
        else if(difficurty[cur][len-1] == 4 &&
            num[last] == num[last-2])
            ret = 4;
        else if(difficurty[cur][len-1] == 5 &&
            num[last]-num[last-1] == num[last-1]-num[last-2])
            ret = 5;
        else ret = 10;
    }

    // cout << cur << ' ' << len << ' ' << ret << endl;
    return ret;
}
int recursive(int cur){
    if(cur == num.size()) return 0;

    int& ans = cache[cur];
    if(ans != 0) return ans;

    ans = OOS;
    for(int len=3; len<6; len++){
        if(cur + len <= num.size())
            ans = min(ans, get_difficulty(cur, len) + recursive(cur+len));
    }
    return ans;
}
void solve(){
    memset(difficurty, 0, sizeof(difficurty));
    memset(cache, 0, sizeof(cache));

    cin >> num;
    cout << recursive(0) << endl;
}

int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    일단 그냥 3,4,5개의 원소를 택하고 다음으로 넘기기

    -- 생각해 볼 것 --
    문자열의 길이가 7을 쪼개면 (3,4), (4,3) 2가지 경우가 가능한데,
    10,000개의 문자열에는 길이가 7인 자열이 1,428개가 있어서
    완전 탐색으로 무식하게 하면 2^1,428 이상이 걸린다
        - 단순하게는 불가능
*/