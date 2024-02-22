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
		}while(c > 0 && rank[i] == rank[j]+1);
	}

	for(auto c: suffix) cout << c+1 << ' ';
	cout << "\nx ";
	for(int i=1; i<sLen; i++) cout << lcp[i] << ' ';

	return 0;
}

// https://m.blog.naver.com/jqkt15/222035128595