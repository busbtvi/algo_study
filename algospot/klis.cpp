// https://www.algospot.com/judge/problem/read/KLIS
#include <iostream>
#include <vector>
#include <memory.h>
#include <limits>
using namespace std;

int nums[500], cache[500];  // cache: 현재 index를 포함해 가능한 lis 최대 길이
int case_cache[500];  // 현재 위치 뒤에 모든 가능한 경우의 수
int n, k, lis_len;
int recursive(int cur){
    if(cur == n) return 0;
    
    int& ans = cache[cur];
    if(ans == 0){
        ans = 1;
        for(int i=cur+1; i<=n; i++){
            if(i == n || nums[cur] < nums[i])
                ans = max(ans, 1 + recursive(i));
        }
    }

    return ans;
}
int calc_possiblecase(int cur, int len){  // cur 뒤로(cur 포함x) 생길 수 있는 모든 조합
    // cache값이 같은 자리 끼리는 무조건 내림 차순임
    // 원소 하나라도 내림차순이 아니었다면, 해당 원소는 다른 길이의 cache값이 됬을것
    if(len == 0){
        case_cache[cur] = 1;
        return 1;
    }
    if(cur == n) return 0;

    int& ans = case_cache[cur];
    if(ans == -1){
        ans = 0;
        for(int i=n-1; i>cur; i--)
            if(cache[i] == len && nums[cur] < nums[i]){
                ans += calc_possiblecase(i, len-1);
                
                // overflow
                if(ans < 0) ans = numeric_limits<int>::max();
            }
    }
    return ans;
}
void output(){
    int skip = k, prev_num = 0;

    for(int len=lis_len; len>0; len--){
        int front = -1;
        for(int i=n-1; i>front; i--){
            if(cache[i] == len && prev_num < nums[i]){
                if(skip <= case_cache[i]){
                    cout << nums[i] << ' ';
                    prev_num = nums[i];
                    front = i;
                    break;
                } else skip -= case_cache[i];
            }
        }
    }
    cout << endl;
}
void solve(){
    cin >> n >> k;
    for(int i=0; i<n; i++) cin >> nums[i];

    memset(cache, 0, sizeof(cache));
    memset(case_cache, -1, sizeof(case_cache));
    lis_len = 0;

    for(int i=0; i<n; i++)
        lis_len = max(lis_len, recursive(i));
    for(int i=0; i<n; i++)
        if(cache[i] == lis_len) calc_possiblecase(i, lis_len-1);

    cout << lis_len << endl;
    output();
    // for(int i=0; i<n; i++) cout << cache[i] << ' ';
    // cout << endl;
    // // cout << calc_possiblecase(0, lis_len) << endl;
    // for(int i=0; i<n; i++) cout << case_cache[i] << ' ';
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
    재귀로 최대 길이를 찾아가기, 최대 길이와 동일하면 count를 세서, k 번째와 같으면 출력
    정답을 맞추긴 했는데, 깔끔하다기 보다는 정말로 하나하나씩 풀어가긴 했음
    1. lis 길이 찾기
    2. 해당 위치 이후에 생길 수 있는 경우의 수 계산
    3. 경우의 수를 보며 skip or 출력으로 답을 계산

        - 책도 똑같이 풀었네.. ㅋㅋㅋ
*/