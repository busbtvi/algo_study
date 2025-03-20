// https://www.acmicpc.net/problem/8972
#include <iostream>
#include <utility>
#include <map>

using namespace std;
using intp = pair<int, int>;

int r,c, x = 0, ended = 0;
intp me;

int move_toward(int target, int cur){
    if(target == cur) return cur;
    return target > cur ? cur+1 : cur-1;
}
map<intp, int> moveR(map<intp, int> prev){
    map<intp, int> next, collision;  // value is not important

    for(auto m: prev){  // move R
        intp a = m.first;
        a.first  = move_toward(me.first,  a.first);
        a.second = move_toward(me.second, a.second);

        if(a == me){
            ended = 1;
            return next;
        }
        if(next.find(a) != next.end())
            collision[a] = 1;
        else next[a] = 1;
    }

    for(auto m: collision)  // remove collisioned R
        next.erase(m.first);
    
    return next;
}
void print_board(map<intp, int> crazy){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            intp cur = make_pair(i,j);

            if(crazy.find(cur) != crazy.end()) cout << 'R';
            else if(me == cur) cout << 'I';
            else cout << '.';
        }
        cout << endl;
    }
}
int main(){
    int moveI[10][2] = {  // row, colum
        { 0, 0}, { 1,-1}, { 1, 0}, { 1, 1}, { 0,-1}, 
        { 0, 0}, { 0, 1}, {-1,-1}, {-1, 0}, {-1, 1}
    };
    map<intp, int> crazy;
    string steps;

    cin >> r >> c;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++){
            char in;
            cin >> in;
            if(in == 'R') crazy[make_pair(i,j)] = 1;
            if(in == 'I') me = make_pair(i,j);
        }
    cin >> steps;

    for(char c: steps){
        int dir = c - '0';
        x++;

        me = make_pair(me.first+moveI[dir][0], me.second+moveI[dir][1]);
        if(crazy.find(me) != crazy.end()){
            cout << "kraj " << x << endl;
            return 0;
        }

        crazy = moveR(crazy);
        if(ended){
            cout << "kraj " << x << endl;
            return 0;
        }
    }

    print_board(crazy);

    return 0;
}

/*
    -- 생각 과정 --
    음.. 뭔가 트릭이 있는 문제 보다는 시뮬레이션 문제인듯?
    R을 queue나 vector에 담아두고 순회하면 되나?
        R끼리 충돌, I가 R에 가는거 어떻게 판단하지?
    map<pair<int,int>, int> 사실 value는 중요하지 않음
*/