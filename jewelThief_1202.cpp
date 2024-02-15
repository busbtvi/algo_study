// https://www.acmicpc.net/problem/1202
#include <iostream>
#include <set>
using namespace std;

int main(){
    multiset<pair<int,int>> jewel;
    multiset<int> bag;
    long long cost = 0;
    int n, k;

    cin >> n >> k;
    for(int i=0,m,v; i<n; i++){
        cin >> m >> v;
        jewel.insert(make_pair(v,m));
    }
    for(int i=0,c; i<k; i++){
        cin >> c;
        bag.insert(c);
    }

    for(auto i=jewel.rbegin(); i!=jewel.rend(); i++){
        auto search = bag.lower_bound(i->second);
        if(search != bag.end()){
            cost += i->first;
            bag.erase(search);
        }
    }
    cout << cost;

    return 0;
}