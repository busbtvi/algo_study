// https://www.acmicpc.net/problem/2473
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int main(){
    long long n, ans[4] = {LONG_MAX,}, solutions[5000];
    
    cin >> n;
    for(int i=0; i<n; i++) cin >> solutions[i];
    sort(solutions, solutions+n);

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            long long sum  = solutions[i] + solutions[j];
            int inversI = lower_bound(solutions+j+1, solutions+n, -sum) - solutions;

            if(inversI < n){
                if(ans[0] > abs(sum + solutions[inversI])){
                    ans[0] = abs(sum + solutions[inversI]);
                    ans[1] = solutions[i]; ans[2] = solutions[j]; ans[3] = solutions[inversI];
                }
            }
            if(inversI-1 > j){
                if(ans[0] > abs(sum + solutions[inversI-1])){
                    ans[0] = abs(sum + solutions[inversI-1]);
                    ans[1] = solutions[i]; ans[2] = solutions[j]; ans[3] = solutions[inversI-1];
                }
            }
        }
    }

    cout << ans[1] << ' ' << ans[2] << ' ' << ans[3];

    return 0;
}