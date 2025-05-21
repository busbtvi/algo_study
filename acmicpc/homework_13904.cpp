// https://www.acmicpc.net/problem/13904
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using intp = pair<int, int>;

class Cmp {
    public: bool operator()(const intp& a, const intp& b){
        if(a.second == b.second) return a.first > b.first;
        return a.second < b.second;
    }
};
int main(){
    priority_queue<intp, vector<intp>, Cmp> q;
    vector<int> result(1001, 0);
    int n, d, w, ans = 0;

    cin >> n;
    for(int i=0; i<n; i++){
        cin >> d >> w;
        q.push({d, w});
    }

    while(!q.empty()){
        auto [day, score] = q.top();
        q.pop();

        while(day>0 && result[day] != 0) day--;

        if(day) result[day] = score;
        // cout << day << ' ' << score << '\n';
    }
    
    for(int i: result) ans += i;
    cout << ans;

    return 0;
}