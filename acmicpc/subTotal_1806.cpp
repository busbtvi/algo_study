// https://www.acmicpc.net/problem/1806
#include <iostream>
using namespace std;

int main(){
    int ans = ~(1<<31);
    int nums[100001] = {0,};
    int n, s;

    cin >> n >> s;
    for(int i=0; i<n; i++) cin >> nums[i];

    for(int i=0,j=0,sum=0; j<=n;){
        if(sum < s){
            sum += nums[j];
            j++;
        }
        else{
            if(j-i < ans) ans = j-i;
            sum -= nums[i];
            i++;
        }
    }

    if(ans == ~(1<<31)) cout << 0;
    else cout << ans;

    return 0;
}