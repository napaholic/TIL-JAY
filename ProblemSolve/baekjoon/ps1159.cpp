//
// Created by jaewkim on 2023/07/07.
//

#include <bits/stdc++.h>

using namespace std;
int player_cnt;
string s;

int main() {
	int at_least  = 0;
	int a[26] = {0, };
	
	cin >> player_cnt;
	for (int i = 0; i < player_cnt; ++i) {
		cin >> s;
		a[s[0] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {
		if (a[i] > 5) {
			cout << (char)('a' + i);
			at_least = 1;
		}
	}
	
	if (at_least == 0)
		cout << "PREDAJA";
}
