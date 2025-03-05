// https://www.algospot.com/judge/problem/read/LIS
#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;

// void solve(){
//     vector<int> sub_seq[501];
//     int n, nums[500] = {0,};

//     cin >> n;
//     for(int i=0; i<n; i++) cin >> nums[i];

//     /*
//         길이 1 ~ N-1 까지 subseq 탐색
//         if nums[N] > sub_seq[Len] 
//             if nums[N] > sub_seq[Len + 1].last  continue
//             else memcpy(sub_seq[Len+1]의 위치에 sub_seq[Len] + nums[N])
//         else 교체???
//     */
//     sub_seq[1].push_back(nums[0]);
//     for(int i=1; i<n; i++){  // nums를 순회
//         for(int sub_len=1; sub_len<=i && !sub_seq[sub_len].empty(); sub_len++){  // sub_seq의 길이는 i 이하
//             auto& cur = sub_seq[sub_len];
//             auto& next = sub_seq[sub_len+1];

//             if(nums[i] == cur.back()) break;
//             if(nums[i] > cur.back()){
//                 if(next.empty() || nums[i] < next.back()){
//                     next.assign(cur.begin(), cur.end());
//                     next.push_back(nums[i]);

//                     break;
//                 } else {
//                 }
//             } else if(sub_len == 1) {  // nums[i] < sub_seq[sub_len].back()
//                 sub_seq[1].back() = nums[i];
//                 break;
//             }
//         }
//     }

//     for(int i=500; i>0; i--){
//         if(!sub_seq[i].empty()){
//             cout << i << endl;
//             break;
//         }
//     }
// }

int n, nums[500] = {0,}, cache[500] = {0,};
int recursive(int cur){
    int& val = cache[cur];
    if(val != 0) return val;

    val = 1;
    for(int next=cur+1; next<n; next++)
        if(nums[cur] < nums[next])
            val = max(val, 1+recursive(next));
    return val;
}
void book(){
    cin >> n;
    for(int i=0; i<n; i++) cin >> nums[i];

    memset(cache, 0, sizeof(cache));
    cache[n-1] = 1;

    int max_num = 1;
    for(int i=0; i<n; i++) max_num = max(max_num, recursive(i));
    cout << max_num << endl;
    
    // for(int i=0; i<n; i++) cout << cache[i] << ' ';
    // cout << endl;
}
int main(){
    int test_case;
    cin >> test_case;

    while(test_case--) book();
    // while(test_case--) solve();
    return 0;
}

/*
    -- 생각 과정 --
    무식하게 재귀 2^500 * 50
        -> 불가능
    해당 위치 n에서, n 이전까지 원소들로 구성된 길이 1 ~ n-1의 subsequence를 비교하면서
    해당 원소를 추가(가능하면)해서 다음 길이의 subsequence와 비교
    cache[길이] = vector<int>{ 해당 길이의 sequence를 구성하는 원소들, 증가 순서 }
        -> 50 * N(새로운 숫자) * (해당 숫자 이전의 subsequence 탐색)
    
    -- 생각해 볼 것 --
    무식하게 안되서, 앞에서 부터 답을 찾아가려고 해서 복잡한 코드가 되어버림
    뒤에서 부터 답이 완성되는 것으로 접근했다면, 쉽게 풀 수 있었음
        재귀는 다음의 순서로 결과가 나옴
        재귀(0) -> 재귀(1) ... -> 재귀(n) -> 답(n) -> 답(n-1) ... 답(0)
    내가 짠 알고리즘에서 `해당 길이의 가장 작은 subsequence`를 저장하는 벡터 대신에
    `해당 길이의 가장 작은 마지막 원소`만 저장해서 풀어도 됨
        O(N * k)
        여기서 k를 이진탐색으로 접근하면 O(N logk) 까지 내릴 수 있음
*/