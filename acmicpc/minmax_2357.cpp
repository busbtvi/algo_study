// https://www.acmicpc.net/problem/2357
#include <iostream>
#include <utility>
using namespace std;

using intp = pair<int,int>;
intp minMaxSegment[(1<<18)];
int n, m ,nums[100000];
void setUpSegmentTree(int i, int beg, int end){
    if(beg+1 == end) minMaxSegment[i] = {nums[beg], nums[beg]};
    else{
        int middle = (beg+end) / 2;
        setUpSegmentTree(i*2, beg, middle);
        setUpSegmentTree(i*2+1, middle, end);

        minMaxSegment[i] = {
            min(minMaxSegment[i*2].first, minMaxSegment[i*2+1].first), 
            max(minMaxSegment[i*2].second, minMaxSegment[i*2+1].second), 
        };
    }
}
// i, l, r is related to minMaxSegment
intp searchSegmentTree(int beg, int end, int i, int l, int r){
    if(beg == l && end == r) return minMaxSegment[i];

    int c = (l + r) / 2;
    if(end <= c) return searchSegmentTree(beg, end, i*2, l, c);
    else if(c <= beg) return searchSegmentTree(beg, end, i*2+1, c, r);
    else{
        intp f = searchSegmentTree(beg, c, i*2, l, c);
        intp b = searchSegmentTree(c, end, i*2+1, c, r);

        return {min(f.first, b.first), max(f.second, b.second)};
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> nums[i];

    setUpSegmentTree(1, 0, n);
    for(int i=0,a,b; i<m; i++){
        cin >> a >> b;
        intp result = searchSegmentTree(a-1, b, 1, 0, n);
        cout << result.first << ' ' << result.second << '\n';
    }

    return 0;
}