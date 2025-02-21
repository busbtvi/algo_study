// https://www.acmicpc.net/problem/5582
#include <iostream>
#include <string>
using namespace std;

int main(){
    string a,b;
    int ans = 0;
    cin >> a >> b;

    int i = a.length()-1, j=0;
    for(int rep=1; rep<a.length()+b.length(); rep++){
        int ti=i, tj=j, count=0;
        while(ti<a.length() && tj<b.length()){
            if(a[ti] != b[tj]){
                if(ans < count) ans = count;
                count = 0;
            }
            else count++;

            ti++; tj++;
        }
        if(ans < count) ans = count;

        if(i > 0) i--;
        else j++;
    }

    cout << ans;
    return 0;
}