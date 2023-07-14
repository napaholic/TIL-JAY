//
// Created by jaewkim on 2023/07/14.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	string a, b;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		map<string, int> _map;
		cin >> m;
		for (int j = 0; j < m; ++j) {
			cin >> a >> b;
			_map[b]++;
		}
		long long ret = 1;
		for (auto loop : _map)
			ret *= ((long long)loop.second + 1);
		ret--;
		cout << ret << "\n";
	}
}
