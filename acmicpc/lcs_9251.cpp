// https://www.acmicpc.net/problem/9251
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int lcs[1001][1001] = {0,};
    string a,b;
    cin >> a >> b;

    for(int i=0,aLen=a.length(); i<aLen; i++){
        for(int j=0,bLen=b.length(); j<bLen; j++){
            if(a[i] == b[j]){
                lcs[i+1][j+1] = lcs[i][j] + 1;
            }
            else{
                lcs[i+1][j+1] = max(lcs[i][j+1], lcs[i+1][j]);
            }
        }
    }
    cout << lcs[a.length()][b.length()];
    return 0;
}