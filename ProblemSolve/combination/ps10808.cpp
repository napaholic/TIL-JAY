//
// Created by jaewkim on 2023/07/06.
//

#include <bits/stdc++.h>

using namespace std;


int main() {
	map<char, int> cnt;
	map<char, int> test;
	
	string s;
	cin >> s;
	
	for (int i = 0; i < s.size(); ++i) {
		cnt[s[i] - 'a']++;
	}
	
	for (int i = 0; i < 26; ++i) {
		cout << cnt[i] << " ";
	}
	cout << "\n--------------------\n";
	cout << test.size() << "\n";
	cout << test['a'] << "\n";
	cout << test['b'] << "\n";
	cout << test.size() << "\n";
	
}