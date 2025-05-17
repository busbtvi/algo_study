// https://www.acmicpc.net/problem/20437
#include <iostream>
#include <memory.h>
#include <vector>
#include <utility>
#define IMAX 987654321
using namespace std;

void solve(){
    vector<int> indexs[26];
    string w;
    int k, len1 = IMAX, len2 = -1;

    cin >> w >> k;
    for(int i=0; i<w.length(); i++)
        indexs[w[i] - 'a'].push_back(i);
    
    for(int i=0; i<26; i++){
        if(indexs[i].size() < k) continue;

        for(int j=k-1; j<indexs[i].size(); j++){
            len1 = min(len1, indexs[i][j] - indexs[i][j-k+1]);  // 이거 맞나?
            len2 = max(len2, indexs[i][j] - indexs[i][j-k+1]);
        }
    }

    if(len1 == IMAX) cout << -1 << '\n';
    else cout << len1+1 << ' ' << len2+1 << '\n';
}
int main(){
    string w;
    int t, k;

    cin >> t;
    while(t--) solve();

    return 0;
}

/*
    -- 접근 방식 --
    무식하게, 불가능(10,000^2 * 1,000)
    리버스 인덱스?
*/