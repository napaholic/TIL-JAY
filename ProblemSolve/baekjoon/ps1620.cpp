//
// Created by jaewkim on 2023/07/13.
//

#include <bits/stdc++.h>

using namespace std;

void solve(string &s, map<int, string> &datais, map<string, int> &datasi) {
	if (isalpha(s[0])) {
		cout << datasi[s] << "\n";
		return ;
	} else {
		cout << datais[stoi(s)] << "\n";
		return ;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	map<int, string> datais;
	map<string, int> datasi;
	string s;
	
	cin >> n >> m;
	for (int i = 1; i < n + 1; ++i) {
		cin >> s;
		datais[i] = s;
		datasi[s] = i;
	}
	for (int i = 0; i < m; ++i) {
		cin >> s;
		solve(s, datais, datasi);
	}
}
