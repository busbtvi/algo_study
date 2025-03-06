// https://www.algospot.com/judge/problem/read/FANMEETING
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

// return a * 10^k + b
vector<int> add(int k, const vector<int>& a, const vector<int>& b){
}
// return a - b
vector<int> sub(const vector<int>& a, const vector<int>& b){
	vector<int> ans;

	int i=0, underflow = 0;
	while(i < b.size()){
		if((underflow + a[i]) >= b[i]){
			ans.push_back(underflow + a[i] - b[i]);
			underflow = 0;
		}
		else {
			ans.push_back(10 + a[i] - b[i]);
			assert(i+1 < a.size());
			underflow = -1;
		}
		i++;
	}
	while(i < a.size()){
		ans.push_back(underflow + a[i]);
		underflow = 0;
		i++;
	}

	reverse(ans.begin(), ans.end());
	return ans;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	if(a.size() == 1 || b.size() == 1){
	}

	// a0 * 10^half + a1, b0 * 10^half + b1
	int half = min(a.size(), b.size()) / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + half);
	vector<int> b1(b.begin() + half, b.end());

	vector<int> half_power2 = karatsuba(a0, a1);
	vector<int> half_power0 = karatsuba(b0, b1);
	vector<int> half_power1 = karatsuba(add(0, a0, a1), add(0, b0, b1));  // (a0 + a1)(b0 + b1)
		half_power1 = sub(
			sub(half_power1, half_power2),  // -b0b1
			half_power0						// -a0a1
		);

	vector<int> ans = add(half*2, half_power2, half_power0);
	ans = add(half, half_power1, ans);
	return ans;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case--){
	}
	return 0;
}

/*
	-- 생각 과정 --
	일단 단순하게, O({팬의수 - 멤버 수} * 맴버 수 * 테스트 케이스)
		max -> 10^10 * 20 = 2,000 * 10^8
	bit를 활용해서 남자(1)끼리 악수하는지를 & 로 판단해서 모든 경우가 0인 경우를 찾기
		팬과, 멤버를 정수로 표현해서 shift 시켜가며 &로 판단
		max -> 10^5 * (20만 / 64bit) * 20 = 62.5 * 10^8
	분할 정복...
		ab | cd 로 나누기?
		 abcd
		012345    가운데 매칭을 기준으로 이전, 이후 나누기?
	재귀 함수가 뭘 반환해야 두 부분을 활용해서 현재의 반환값을 정할 수 있을까
	base 케이스가 뭘까? (에초에 어떻게 나누느냐에 따라 base 케이스가 바뀌긴 함)
		멤버수와, 팬의 수가 동일할 때?
		멤버수가 1명일때?

	-- 생각해 볼 것 --
	...이게 뭐지...
	곱셈은 근본적으로 모든 경우를 다 처리한다(음.. 슬라이딩 윈도우를 처음부터 끝까지 처리한다?)
				a0b0	a1b0	...		aNb0
		a0b1	a1b1	...		aNb1
		-> 이런 느낌으로?
	곱셈의 한 항은 X 형태로 곱해진 항목들의 합이다(필요에 따라 곱하는 값을 뒤집는것이 유용함)
	bit의 & 연산은 정수의 곱하기와 비슷하다
	
	https://www.acmicpc.net/problem/1067 비슷하게 풀 수 있는 문제
	FFT
*/