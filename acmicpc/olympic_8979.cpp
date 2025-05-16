// https://www.acmicpc.net/problem/8979
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

using ilpair = pair<int, long long>;

int main(){
    ilpair contry[1000];
    long long g,s,b, score;
    int n, k;

    cin >> n >> k;
    for(int i=0, num; i<n; i++){
        cin >> num >> g >> s >> b;
        score = (g << 40) + (s << 20) + b;
        contry[i] = make_pair(num, score);
    }

    sort(contry, contry + n, [](const ilpair& a, const ilpair& b) -> bool {
        return a.second > b.second;
    });

    // for(int i=0; i<n; i++)
    //     cout << contry[i].first << ' ' << contry[i].second << endl;
    for(int i=0; i<n; i++){
        if(contry[i].first == k){
            while(i>0 && contry[i-1].second == contry[i].second)
                i--;
            
            cout << i+1 << endl;
            break;
        }
    }

    return 0;
}