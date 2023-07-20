//
// Created by jaewkim on 2023/07/17.
//

#include <bits/stdc++.h>

using namespace std;

int n, cnt;
int v[2];
string s;

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		stack<char> stk;
		for (char l : s) {
			if (stk.size() && stk.top() == l)
				stk.pop();
			else
				stk.push(l);
		}
		if (stk.size() == 0)
			cnt++;
	}
	cout << cnt << "\n";
}