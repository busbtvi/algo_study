// https://www.acmicpc.net/problem/1197
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

vector<int> vertex;

int getRoot(int i){
    if(vertex[i] != i) vertex[i] = getRoot(vertex[i]);
    return vertex[i];
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    using intt = tuple<int,int,int>;
    int v, e, ans = 0;

    cin >> v >> e;
    vector<intt> edge;
    edge.reserve(e);
    vertex.reserve(v+1);
    for(int i=0; i<=v; i++) vertex.push_back(i);
    for(int i=0, beg, end, cost; i<e; i++){
        cin >> beg >> end >> cost;
        edge.push_back(make_tuple(beg, end, cost));
    }
    sort(edge.begin(), edge.end(), [](const intt& a, const intt& b){
        return get<2>(a) < get<2>(b);
    });

    for(auto e: edge){
        int i, j, c;
        tie(i, j, c) = e;
        if(getRoot(i) != getRoot(j)){
            if(vertex[i] < vertex[j])
                vertex[vertex[j]] = vertex[i];
            else vertex[vertex[i]] = vertex[j];
            
            ans += c;
        }
    }

    cout << ans;
    return 0;
}