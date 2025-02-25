// https://www.algospot.com/judge/problem/read/QUADTREE
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

// string에서 시작 index를 주면 quad-tree를 파싱해서 한 블럭의 끝을 return
int find_end(int beg);
// block [0,1), [1,2), [2,3), [3,end) 를 인자로 받아서
// 1234 -> 3412 순서로 in-memory flip
void in_memory_flip(int indexs[5]);
/*
	sudo code

	recursion(beg,end){
		if(beg+1 == end) return;

		int gaps[5] = {beg+1, };
		for 4 times
			int cur_end = find_end(gaps[i]);
			recursion(gaps[i], cur_end);
			gaps[i+1] = cur_end;
		
		in_memory_flip(gaps);
	}
*/

string original;
int find_end(int beg){
	if(original[beg] != 'x') return beg+1;

	// x(?)(?)(?)(?)
	int end = beg+1;
	for(int i=0; i<4; i++){
		if(original[end] == 'x'){
			end = find_end(end);
		} else end++;
	}
	return end;
}
void in_memory_flip(int indexs[5]){
	string flipped = 
		original.substr(indexs[2], indexs[4] - indexs[2]) +
		original.substr(indexs[0], indexs[2] - indexs[0]);
	original.replace(indexs[0], indexs[4]-indexs[0], flipped);
}
void recursion(int beg, int end){
	if(beg+1 == end) return;

	assert(original[beg] == 'x');
	int gaps[5] = {beg+1,};
	for(int i=0; i<4; i++){
		gaps[i+1] = find_end(gaps[i]);
		recursion(gaps[i], gaps[i+1]);
	}

	in_memory_flip(gaps);
}
string book_code(string::iterator& it){
	char head = *it;
	++it;
	if(head != 'x') return string(1, head);

	string upper_left  = book_code(it);
	string upper_right = book_code(it);
	string lower_left  = book_code(it);
	string lower_right = book_code(it);
	return string("x") + lower_left + lower_right + upper_left + upper_right;
}
int main(){
	int test_case;
	cin >> test_case;

	while(test_case > 0){
		cin >> original;
		// mycode -> recursion
		// recursion(0, original.length());
		// cout << original << endl;
		string::iterator it = original.begin();
		cout << book_code(it) << endl;

		test_case--;
	}
	return 0;
}

/*
	-- 생각 과정 --
	1234 -> 3412로 뒤집는 재귀(or 분할 정복)
	log_4(1000) ~ 5이고, 최악의 경우(격자무늬?)도 시간안에 풀 수 있을 듯

	x를 활용해서 어디서 끊어야 할지 판단하는 parser
		- 흠 한방에 짜기 어렵네

	이렇게 sudo 코드를 짰는데, recursion을 어떻게 넣지?
		-> 이거 전체를 recursion에 넣고, 반복문 내부에 한 블럭에 해당하는 곳에 recursion을 호출하면 될듯?
	```cpp
		int gaps[5] = {beg, };
			for 4 times
				int cur_end = find_end(gaps[i]);
				gaps[i+1] = cur_end;
			
		in_memory_flip(gaps);
	```

	-- 잘못 본것 --
	원본 그림의 크기를 20 * 20 칸이라고 잘못 생각함
		- 압축을 풀지않고 바로 뒤집어서 상관은 없었다만..

	-- 생각해볼 점 --
	전체를 뒤집고, 각 부분을 어떻게 뒤집을까(top-down)으로 생각을 했었는데,
	각 부분을 뒤집고, 전체를 뒤집는걸 생각 못함
	
	iterator를 reference로 넘기면 다른 곳에서도 상태가 변경됨
	in_memory_flip을 제외하고, 탐색 자체에는 string을 한번 순회하기 때문에 
	시간 복잡도는 O(N)
*/