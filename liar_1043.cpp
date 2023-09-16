// https://www.acmicpc.net/problem/1043
#include <iostream>
#include <vector>
using namespace std;

bool know[51] = {0,};
int parents[51];

int findRoot(int i, bool knowTrue){
    know[i] |= knowTrue;

    if(parents[i] != i)
        return parents[i] = findRoot(parents[i], know[i]);
    return i;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> partyStartMember;
    int n, m, knowCount, ans = 0;
    cin >> n >> m >> knowCount;

    partyStartMember.reserve(m);
    for(int i=0; i<=n; i++) parents[i] = i;

    for(int i=0, j; i<knowCount; i++){
        cin >> j;
        know[j] = true;
    }
    for(int i=0, count, root1,root2; i<m; i++){
        cin >> count;
        for(int j=0, in; j<count; j++){
            cin >> in;

            if(j == 0){
                partyStartMember.push_back(in);
                root1 = findRoot(in, know[in]);
            }
            else{
                root2 = findRoot(in, know[in]);
                parents[root2] = root1;
                know[root1] |= know[root2];
            }
            // findRoot(in, know[in]);
        }
    }

    // for(int i=0; i<=n; i++) cout << know[i] << ' ';
    // cout << '\n';
    // for(int i=0; i<=n; i++) cout << parents[i] << ' ';
    // cout << '\n';
    // for(int i=0; i<m; i++) cout << partyStartMember[i] << ' ';
    // cout << '\n';
    for(auto i: partyStartMember){
    //     // if(!know[i]) cout << i << " know\n";
        ans += !know[findRoot(i, know[i])];
    }
    cout << ans;
}