// https://www.acmicpc.net/problem/1708
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define POW(x) (x)*(x)
using namespace std;

int main(){
    using llp = pair<long long, long long>;
    long long n, hullI = 0, startI;

    cin >> n;
    vector<llp> convexHull(n+1), dots(n);
    llp start = {50000, 50000};

    for(int i=0,x,y; i<n; i++){
        cin >> dots[i].first >> dots[i].second;

        if(dots[i].first < start.first || (dots[i].first == start.first && dots[i].second < start.second)){
            start = dots[i];
            startI = i;
        }
    }

    swap(dots[startI], dots[0]);
    sort(dots.begin()+1, dots.end(), [&start](const llp& a, const llp& b){
        long long temp = (a.first-start.first)*(b.second-a.second) - (a.second-start.second)*(b.first-a.first);
        if(temp != 0) return temp > 0;
        return (POW(a.first-start.first) + POW(a.second-start.second)) < (POW(b.first-start.first) + POW(b.second-start.second));
    });

    for(auto dot: dots){
        while(hullI > 1){
            llp ab = {convexHull[hullI-1].first - convexHull[hullI-2].first, convexHull[hullI-1].second - convexHull[hullI-2].second};
            llp bc = {dot.first - convexHull[hullI-1].first, dot.second - convexHull[hullI-1].second};
            
            if(ab.first*bc.second <= ab.second*bc.first) hullI--;
            else break;
        }
        convexHull[hullI++] = dot;
    }

    cout << hullI;
    return 0;
}