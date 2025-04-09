// https://www.algospot.com/judge/problem/read/RESTORE
#include <iostream>
#include <vector>
#include <string>
#include <memory.h>
using namespace std;

vector<string> strings;
// strings[i] 뒤에 strings[j]를 놓았을 때 겹치는 최대 길이
int overlap[15][15], k;
int dp[15][1<<15];
vector<int> next_best, _next;

void calc_overlap(){
    for(int i=0; i<strings.size(); i++){
        for(int j=0; j<strings.size(); j++){
            if(i == j) continue;

            int& overlap_len = overlap[i][j];
            string &a = strings[i], &b =strings[j];
            for(int len=0; len<min(a.length(), b.length()); len++){
                if(a.substr(a.length() - len) == b.substr(0, len)){
                    overlap_len = len;
                }
            }
        }
    }
}
void remove_contain(){
    vector<string> removed;
    for(int i=0, j; i<k; i++){
        for(j=0; j<k; j++){
            if(i == j) continue;
            if(strings[j].find(strings[i]) != string::npos)
                break;
        }

        // 끝까지 와도 겹치는거 없었음
        if(j == k) removed.push_back(strings[i]);
    }
    strings = removed;
}
int bools_to_int(bool* arr){
    int result=0;
    for(int i=14; i>=0; i--) result = (result << 1) | arr[i];
    return result;
}
int calc_max_overlap(int cur, bool* visited, int count){
    if(count == strings.size()) return -1;
    if(cur == -1){
        int ans = -1;
        for(int i=0; i<strings.size(); i++){
            _next = vector<int>(strings.size(), -100);
            visited[i] = true;
            int temp = calc_max_overlap(i, visited, 1);
            if(ans < temp){
                ans = temp;
                next_best = _next;
            }
            visited[i] = false;
        }
        return ans;
    }
    
    int& ans = dp[cur][bools_to_int(visited)];
    if(ans == -1){
        for(int i=0; i<strings.size(); i++){
            if(!visited[i]){
                visited[i] = true;
                int temp = calc_max_overlap(i, visited, count+1) + overlap[cur][i];
                if(ans < temp){
                    _next[cur] = i;
                    ans = temp;
                }
                visited[i] = false;
            }
        }
    }

    return ans;
}
void reconstruct(int prev, bool* visited, int overlab_sum){
    for(int i=0; i<strings.size(); i++){
        if(!visited[i]){
            visited[i] = true;

            int prev_overlab = (prev == -1) ? 0 : overlap[prev][i];
            if(dp[i][bools_to_int(visited)]+prev_overlab == overlab_sum){
                cout << strings[i].substr(prev_overlab);
                reconstruct(i, visited, overlab_sum - prev_overlab);
                return;
            }

            visited[i] = false;
        }
    }
}
void solve(){
    memset(overlap, 0, sizeof(overlap));
    memset(dp, -1, sizeof(dp));

    cin >> k;
    strings = vector<string>(k);
    for(int i=0; i<k; i++) cin >> strings[i];
    remove_contain();
    calc_overlap();

    bool visited[15] = {0, };
    int max_overlab = calc_max_overlap(-1, visited, -1);

    reconstruct(-1, visited, max_overlab);
    cout << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    노가다: 최악의 경우 600(겹치는게 하나도 없을 때 길이) ^ 15
        이런 경우는 어떻게 처리하지? cde, abc, efg
    알파벳 소문자로만 이루어져 있다는 점을 활용한다면? ...
    k * k 배열을 만들어서 겹치는 부분의 길이가 가장 긴것부터 하나씩 합쳐 나가는 방식?
        k*k 배열을 받아 가장 겹치는 부분의 길이가 긴 문자열 2개 합치기
        (k-1)*(k-1) 배열을 계산해서 다음
        그리디가 되나..?  abaca caba
            -> c(aba)ca, aba(ca)ba 두가지 경우로 겹칠 수 있음,

    -- 생각해 볼 것 --
    한번에 겹치는 것을 어떻게 할지 생각하지 말고, 나눠서 생각해보기
    1. **string간에 겹치는 부분 길이 계산해보기**
    2. 완전 탐색으로 겹치는 부분의 길이가 최대인 경우 찾기
    3. dp 적용
    4. 2번의 결과를 활용해서, string의 순회 순서 찾기
    5. 4번에서 substring만 출력하여 전체 정답 완성

    ... 솔직히 해설을 보고나서 왜 못풀었는지를 좀 까먹어버림..
    이것 저것 하다가 시간이 걸리기도 했고..
*/
