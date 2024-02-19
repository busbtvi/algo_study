// https://www.acmicpc.net/problem/9248
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	int lookBack = 0;
	string s;
	cin >> s;

	// suffix
	vector<int> suffix(s.size()), rank(s.size(), 0);
	for(int i=0; i<s.size(); i++){
		suffix[i] = i;
		rank[i] = s[i];
	}

	while(lookBack < s.size()){
		sort(suffix.begin(), suffix.end(), [&rank, &s, lookBack](const int& a, const int& b){
			if(rank[a] != rank[b]) return rank[a] < rank[b];
			if(a+lookBack >= s.length() || b+lookBack >= s.length()) return a > b;
			return rank[a+lookBack] < rank[b+lookBack];
		});

		vector<int> newRank(s.size(), 0);
		for(int i=1, j,k; i<s.size(); i++){
			// if(rank[suffix[i-1]] != rank[suffix[i]] || rank[suffix[i-1]+lookBack] != rank[suffix[i]+lookBack]){
			// 	newRank[suffix[i]] = newRank[suffix[i-1]] + 1;
			// }
			// else newRank[suffix[i]] = newRank[suffix[i-1]];
			j = suffix[i-1];
			k = suffix[i];
			if(rank[j]==rank[k] && (k+lookBack)<s.size() && (j+lookBack)<s.size() && rank[k+lookBack]==rank[j+lookBack])
				newRank[k] = newRank[j];
			else newRank[k] = newRank[j] + 1;
		}
		for(int i=0; i<s.size(); i++) rank[i] = newRank[i];

		lookBack = (lookBack == 0) ? 1 : lookBack*2;
	}

	// lcp
	vector<int> lcp(s.size());
	for(int i=0, j, c; i<s.length(); i++){
		c = 0;
		j = suffix[rank[i]-1];
		while(j+c<s.size() && s[i+c]==s[j+c]) c++;
		
		lcp[rank[i]] = c;
	}

	for(auto c: suffix) cout << c+1 << ' ';
	cout << "\nx ";
	for(int i=1; i<lcp.size(); i++) cout << lcp[i] << ' ';

	return 0;
}

// https://m.blog.naver.com/jqkt15/222035128595