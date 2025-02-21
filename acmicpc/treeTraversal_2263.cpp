// https://www.acmicpc.net/problem/2263
#include <iostream>
#include <map>
using namespace std;

int in[100000], post[100000], n;
int inIndex[100001], postIndex[100001];
void dfs(int inBeg, int inEnd, int poBeg, int poEnd){
    if(poBeg == poEnd) return;

    // post의 가장 뒤에 있는 원소는 Root
    cout << post[poEnd - 1] << ' ';
    if(poBeg+1 == poEnd) return;

    int inRoot = inIndex[post[poEnd-1]];  // inOrder의 root 앞쪽은 left, 뒤쪽은 right
    int leftLen = inRoot - inBeg;  // inOrder의 left 길이를 이용해 postOrder의 위치 계산
    dfs(inBeg, inRoot, poBeg, poBeg+leftLen);  //left
    dfs(inRoot+1, inEnd, poBeg+leftLen, poEnd-1); // right
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> in[i];
        inIndex[in[i]] = i;
    }
    for(int i=0; i<n; i++){
        cin >> post[i];
        postIndex[post[i]] = i;
    }

    dfs(0,n, 0,n);

    return 0;
}