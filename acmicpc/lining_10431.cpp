// https://www.acmicpc.net/problem/10431
#include <iostream>
using namespace std;

void sort(){
    int test_case, nums[20], count = 0;
    cin >> test_case;
    for(int i=0; i<20; i++) cin >> nums[i];

    for(int i=1; i<20; i++){
        for(int j=0; j<i; j++){
            if(nums[i] < nums[j]){
                int temp = nums[i];
                for(int k=i; k>j; k--){
                    nums[k] = nums[k-1];
                    count++;
                }
                nums[j] = temp;

                break;
            }
        }
    }

    cout << test_case << ' ' << count << '\n';
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int p;

    cin >> p;
    for(int i=0; i<p; i++) sort();

    return 0;
}