// https://www.acmicpc.net/problem/9248
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int lookBack = 0, sLen;
	string s;
	cin >> s;
	sLen = s.length();

	// suffix
	vector<int> suffix(sLen), rank(sLen, 0), newRank(sLen, 0);
	for(int i=0; i<sLen; i++){
		suffix[i] = i;
		rank[i] = s[i];
	}

	while(lookBack < sLen){
		sort(suffix.begin(), suffix.end(), [&rank, sLen, lookBack](const int& a, const int& b){
			if(rank[a] != rank[b]) return rank[a] < rank[b];
			if(a+lookBack >= sLen || b+lookBack >= sLen) return a > b;
			return rank[a+lookBack] < rank[b+lookBack];
		});

		newRank[0] = 0;
		for(int i=1, j,k; i<sLen; i++){
			j = suffix[i-1];
			k = suffix[i];
			if(rank[j]==rank[k] && (k+lookBack)<sLen && (j+lookBack)<sLen && rank[k+lookBack]==rank[j+lookBack])
				newRank[k] = newRank[j];
			else newRank[k] = newRank[j] + 1;
		}
		
		for(int i=0; i<sLen; i++) rank[i] = newRank[i];

		lookBack = (lookBack == 0) ? 1 : lookBack*2;
	}

	// lcp
	vector<int> lcp(sLen);
	for(int i=0, j, c; i<sLen-1;){
		c = 0;
		j = suffix[rank[i]-1];
		while(j+c<sLen && s[i+c]==s[j+c]) c++;

		do{
			lcp[rank[i]] = c;
			i++;
			j++;
			c--;
			// lcp를 구할 때, 자기 자신과(s[i+c]) suffix array의 이전(s[j+c])을 비교해 겹치는 길이를 찾는다
			// 그런다음 하나씩 앞에서 한글자씩 떼면 c-1씩 겹친다.
			// 그런데 첫 글자를 하나씩 뗀 문자열이 suffix array상에서 이웃한다는 보장이 없다(abbaba를 생각해봐라)
			// 그래서 첫 글자를 떼면서 동시에 suffix array 상에서 이웃한지 아닌지를 같이 탐색
		}while(c > 0 && rank[i] == rank[j]+1);
	}

	for(auto c: suffix) cout << c+1 << ' ';
	cout << "\nx ";
	for(int i=1; i<sLen; i++) cout << lcp[i] << ' ';

	return 0;
}

// https://m.blog.naver.com/jqkt15/222035128595