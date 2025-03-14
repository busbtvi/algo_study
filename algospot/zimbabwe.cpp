// https://www.algospot.com/judge/problem/read/ZIMBABWE
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory.h>
#include <cmath>
#include <cassert>
// #define MOD 23
#define MOD 1000000007
using namespace std;

/*
    key: 0 ~ 9의 각 숫자가 몇개 있는지를 16진수(4bit)씩 표현
        0(13개), 1(2개), 나머지 다 0개  -> 0x00...02D
    value: 주어진 key로 조합할 수 있는 숫자 중m으로 나눈 나머지의 갯수
*/
unordered_map<long long, vector<long long>> cache;
long long e, m;
long long convert(const vector<int>& digits){
    long long ret = 0;
    for(int i=0; i<10; i++)
        ret = (ret << 4) | digits[i];
    return ret;
}
/*
    남은 수들을 활용해 만들 수 있는 모든 경우에서, m으로 나눈 나머지의 갯수를 cache에 저장
    (i * 10^k) % m    의 나머지와 
    i를 제외한 나머지의 숫자들로 만들 수 있는 조합 % m
    의 합이 0 이거나 m이면 나눠 떨어지는 것임
*/
void recursive(vector<int>& digits, int k){
    long long cur_key = convert(digits);
    long long power_10 = pow(10, k);

    // cout << "k = " << k << ", digits = ";
    // for(int i=0; i<5; i++) cout << digits[i] << ' ';
    // cout << endl;

    // return with cache;
    if(cache.find(cur_key) != cache.end()) return;

    vector<long long> ans(m, 0);  // initialize;
    if(k == 0){  // only one digit
        for(int i=0; i<10; i++){
            if(digits[i]){
                ans[ i%m ] = 1;
                cache[cur_key] = ans;

                return;  // no other digit
            }
        }
    }

    for(int i=0; i<10; i++){
        if(digits[i]){
            digits[i]--;  // 해당 숫자를 사용

            recursive(digits, k-1);  // 이 다음 경우의 cache를 계산

            long long cur_rmd = (i * power_10) % m;
            vector<long long>& next = cache[convert(digits)];
            for(int next_rmd=0, cur_index; next_rmd<m; next_rmd++){
                cur_index = (next_rmd + cur_rmd) % m;
                ans[cur_index] =  (ans[cur_index] + next[next_rmd]) % MOD;
                // ans[cur_index] += next[next_rmd];
            }

            digits[i]++;
        }
    }

    cache[cur_key] = ans;
}
long long reconstruct(vector<int>& digits, int k, long long acc){
    if(k < 0){  // no digits
        return static_cast<long long>((acc < e) && (acc % m == 0));
    }
    // cout << "digits: ";
    // for(int i=0; i<10; i++) cout << digits[i] << ' ';
    // cout << "\nk = " << k << ", acc = " << acc << endl;

    long long power_10 = static_cast<long long>(pow(10, k));
    long long ans = 0;

    for(int i=0; i<10; i++){
        if(digits[i]){
            /*
                사용 가능한 숫자 i 보다 1 높은걸 넣어도 e보다 작다
                = 현재 i, 이후에 어떤 조합으로도 e보다 작다
                i == 9인 경우는 올림으로 되기때문에 큰 상관 없음
            */
            if((i+1) * power_10 + acc <= e){
                acc += i * power_10;
                digits[i]--;

                int cur_rmd = acc % m;
                int next_rmd = (m - cur_rmd) % m;
                ans = (ans + cache[convert(digits)][next_rmd]) % MOD;
                // ans += cache[convert(digits)][next_rmd];

                digits[i]++;
                acc -= i * power_10;
            }
            else {
                acc += i * power_10;
                digits[i]--;
                return (ans + reconstruct(digits, k-1, acc)) % MOD;
                // return ans + reconstruct(digits, k-1, acc);
            }
        }
    }

    return ans;
}
void solve(){
    cin >> e >> m;

    cache.clear();
    vector<int> digits(10);
    int k = 0;
    for(long long temp=e; temp>0; temp/=10){
        digits[temp%10]++;
        k++;
    }
    // for(int i=0; i<digits.size(); i++)
    //     cout << digits[i] << ' ';
    // cout << endl;
    // cout << k << endl;

    recursive(digits, k-1);
    cout << reconstruct(digits, k-1, 0) << endl;
    // vector<int>& result = cache[convert(digits)];

    // cout << endl;
    // for(auto i: result) cout << i << ' ';
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
    1 <= e <= 10^14: 15자리 숫자   -> 최악의 경우 15! 가지 경우의 수
        - long long으로 담을 순 있음
        - 15! = 1.3 * 10^12 = 13000 * 10^8
    기본 아이디어: 제일 앞 숫자 하나와, 뒤의 나머지로 나눠서 생각
        (a * 10^k + b) % m == 0
        나눠 떨어지는 경우
            (a * 10^k) % m == 0 && b % m == 0
            (a * 10^k) % m != 0 && b % m != 0  중 일부
        그럼 a*10^k + b가 m 으로 나눠 떨어진다는 것을 어떻게 찾을 수 있나
        나머지의 합이 m과 같은것만 찾으면 될듯
    파라미터 넘기는거랑, max(원래 값) 이하인걸 어떻게 보장하지?
        vector<int>로 각 index에 해당하는 숫자가 몇개 있는지 넘기기
        caching은 vector<int>를 long long으로 바꿔서 map에 key로 사용

    -- 코딩 과정 --
    recursive: 처음에는 acc와 digits로 수를 만들어서 e 이하의 수 중, m으로 나눠
        떨어지는 갯수를 반환 하려고 했으나, 함수가 너무 복잡해짐
        그냥 크기 상관하지 않고, 반환값 없이
        "현재 digits들로 만들 수 있는 모든 경우에서 m으로 나눈 나머지의 갯수를 캐시에 저장"
    convert: cache의 key로 사용해야할 값이 vector<int>이기 때문에 
        이를 고유한 값으로 변환 해주는 함수
        최악의 경우 동일한 숫자가 10개 이상이 될 수도 있기 때문에 4bit씩 사용
    reconstruct: 캐시를 활용해서 크기 비교를 하며 나누어 떨어지는 갯수를 반환
        숫자를 골랐다고 해도, 10^k을 곱해서 더해야 겨우 비교가 가능하기 때문에
        적절히 비교해서 경우의 수를 더하는 로직을 작성하기 어려웠음
        (i+1) * power_10 + acc 의 방식으로, 일부러 고른 숫자보다 1 큰 숫자를 해당 자리에 대입해
        e와 비교. 그래도 e가 크다면 i로 만들 수 있는 모든 경우는 다 e보다 작음
        그게 아니라면 e의 해당 자리는 i와 동일 => 다음 재귀에게 판단 보류

    -- 생각해 볼 점 --
    나눠 떨어지는 지를 계산할때, {(앞 자리의 나머지 * 10) + 현재 자리 } % m
    이런 앞에서 부터 숫자를 하나씩 선택해 만들어 가는 방식도 가능함
*/