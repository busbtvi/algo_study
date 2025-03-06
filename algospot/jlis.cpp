// https://www.algospot.com/judge/problem/read/JLIS
#include <iostream>
#include <cassert>
#include <memory.h>
using namespace std;


int cache[101][101];
int a[100], b[100], a_len, b_len;
int recursive(int ai, int bi) {
	if(ai == a_len && bi == b_len) return 0;

	int& ans = cache[ai][bi];
	if(ans != 0) return ans;


	ans = 1;
	if(ai < a_len){
		// select a[ai]
		for(int n_ai=ai+1; n_ai<=a_len; n_ai++){
			for(int n_bi=bi; n_bi<=b_len; n_bi++){
				// 다음으로 넘기는 조건을 확인하는게 너무 복잡해서, 넘기지 않는 조건으로 탐색
				if( (n_ai < a_len && a[n_ai] <= a[ai]) ||
					(n_bi < b_len && b[n_bi] <= a[ai])) continue;
				else ans = max(ans, 1+recursive(n_ai, n_bi)); 
			}
		}
	}
	if(bi < b_len){
		// select b[bi]
		for(int n_bi=bi+1; n_bi<=b_len; n_bi++){
			for(int n_ai=ai; n_ai<=a_len; n_ai++){
				if( (n_ai < a_len && a[n_ai] <= b[bi]) ||
					(n_bi < b_len && b[n_bi] <= b[bi])) continue;
				else ans = max(ans, 1+recursive(n_ai, n_bi)); 
			}
		}
	}

	return ans;
}
void solve(){
	memset(cache, 0, sizeof(cache));

	cin >> a_len >> b_len;
	for(int i=0; i<a_len; i++) cin >> a[i];
	for(int i=0; i<b_len; i++) cin >> b[i];
	
	int ans = 1;
	for(int i=0; i<a_len; i++){
		for(int j=0; j<b_len; j++)
			ans = max(ans, recursive(i,j));
	}
	cout << ans << endl;
}

int main(){
	int test_case;
	cin >> test_case;

	while(test_case--) solve();
	return 0;
}

/*
	-- 생각 과정 --
	A나 B에서 숫자 하나 고르고, 다음 가능한 A_i, B_i로 재귀 호출
	recursive(ai, bi): 현재 a[ai], b[bi] 둘 중 아무거나 선택가능할 때의 최대 길이
		- 한참 고생했는데, 시간 초과(N^4 인듯...)
		- N^2(cache 크기) * N^2(캐시가 없을 때 2중 for loop)
	a[ai], b[bi] 둘중에 작은걸 고르면

	
	음... 책에 코드에서 a[indexA] != b[indexB]를 가정하고 푸는데
	문제에서 해당 조건을 보장하지 않는다..
*/