// https://www.algospot.com/judge/problem/read/OCR
#include <iostream>
#include <memory.h>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<string> words(500);
vector<int> input;
double first_prob[500], next_prob[500][500], classify[500][500];
double prob_cache[100][500];  // [cur_index][prev_word]: 현재 위치가 cur_index이고, 이전 단어가 prev_word일 때, 이후의 최대 확률
int word_cache[100][500];  // [cur_index][prev_word]: 현재 위치가 cur_index이고, 이전 단어가 prev_word일 때 현재의 단어
int m, q, n;

// 이전이 정해졌을 때, 현재 뒤로의 최소 확률
double recursive(int cur){  // cur: [0, n]
    if(cur == input.size()) return 1;

    int prev_word = (cur == 0) ? 0 : input[cur-1];  // input의 범위를 위해 cur == 0을 확인
    int orig_word = input[cur];  // 현재 문자를 바꿔볼 것이기 때문에, 백업
    double& ans = prob_cache[cur][prev_word];
    if(ans) return ans;
    
    double temp;
    for(int change=0; change<m; change++){
        // orig_word를 읽어서 change로 분류 하고, prev_word 다음에 있을 확률
        temp = ((cur == 0) ? first_prob[change] : next_prob[prev_word][change]) 
            * classify[change][orig_word];
        
        if(ans <= temp){
            input[cur] = change;
            temp *= recursive(cur+1);
        }
        if(ans < temp){
            ans = temp;
            word_cache[cur][prev_word] = change;
        }
    }
    input[cur] = orig_word;  // 다시 원래대로 돌려놓기

    return ans;
}
void read_input_data(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> m >> q;
    for(int i=0; i<m; i++) cin >> words[i];
    for(int i=0; i<m; i++) cin >> first_prob[i];
    for(int i=0; i<m; i++) for(int j=0; j<m; j++) cin >> next_prob[i][j];
    for(int i=0; i<m; i++) for(int j=0; j<m; j++) cin >> classify[i][j];
}
void reconstruct(){
    int prev = 0;
    for(int i=0; i<n; i++){
        cout << words[word_cache[i][prev]] << ' ';
        prev = word_cache[i][prev];
    }
    cout << endl;
}
void solve(){
    string in;

    cin >> n;

    // clear caches
    input.clear();  input.reserve(n);
    memset(word_cache, 0, sizeof(word_cache));
    for(int i=0; i<m; i++) for(int j=0; j<m; j++) prob_cache[i][j] = 0.0;

    // convert input words, into word index
    for(int j=0; j<n; j++){
        cin >> in;
        input.push_back(
            find(words.begin(), words.end(), in) - words.begin()
        );
    }

    recursive(0);
    reconstruct();
}
int main(){
    read_input_data();
    for(int i=0; i<q; i++) solve();
    return 0;
}

/*
    -- 생각 과정 --
    현재 위치 cur가 주어졌을 때, cur를 다른 단어들로 다 바꿔보기
    이전 단어 다음에 있을 확률 * 바꿀 단어를 실수로 현재 단어로 잘못읽을 확률 * 이 다음 문자열의 확률

    -- 생각해 볼 것 --
    답을 재구성 하는 cache와, 메모이제이션에서 사용할 cache가 구조가 같음
    timeout인데... 어디서 줄이지
*/
/*
5 3

I am a boy buy

1.0 0.0 0.0 0.0 0.0

0.1 0.6 0.1 0.1 0.1
0.1 0.1 0.6 0.1 0.1
0.1 0.1 0.1 0.6 0.1
0.2 0.2 0.2 0.2 0.2
0.2 0.2 0.2 0.2 0.2

0.8 0.1 0.0 0.1 0.0
0.1 0.7 0.0 0.2 0.0
0.0 0.1 0.8 0.0 0.1
0.0 0.0 0.0 0.5 0.5
0.0 0.0 0.0 0.5 0.5

4 I am a buy
4 I I a boy
4 I am am boy
*/