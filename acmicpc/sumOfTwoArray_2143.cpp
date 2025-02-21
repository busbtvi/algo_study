// https://www.acmicpc.net/problem/2143
#include <iostream>
#include <map>
using namespace std;

int main(){
    // 이렇게 푸는건 아니겠지만...
    // 어짜피 배열의 최대 길이는 1000 -> 생길 수 있는 모든 합의 경우는 n^2이라 해도 1,000,000
    map<int, int> subSumAB[2];
    int t, n, ab[2][1000];
    long long ans=0;
    cin >> t;

    for(int i=0; i<2; i++){
        cin >> n;
        for(int j=0; j<n; j++) cin >> ab[i][j];

        for(int j=0; j<n; j++){
            for(int k=j, sum=0; k<n; k++){
                sum += ab[i][k];
                subSumAB[i][sum]++;
            }
        }
    }

    for(auto a=subSumAB[0].begin(); a!=subSumAB[0].end(); a++){
        if(subSumAB[1].find(t - a->first) != subSumAB[1].end())
            ans += (long long)a->second * (long long)subSumAB[1][t - a->first];
    }

    cout << ans;
    return 0;
}