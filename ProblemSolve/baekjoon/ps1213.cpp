//
// Created by jaewkim on 2023/07/14.
//

#include <bits/stdc++.h>

using namespace std;

string s, ret;
int c[200];
int flag;
char mid;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	for (char loop : s) {
		c[loop]++;
	}
	for (int i = 'Z'; i >= 'A'; i--) {
		if (c[i]) {
			if (c[i] & 1) {
				mid = char(i);
				flag++;
				c[i]--;
			}
			if (flag == 2)
				break;
			for (int j = 0; j < c[i]; j += 2) {
				ret = char(i) + ret + char(i);
			}
		}
	}
	if (mid)
		ret.insert(ret.begin() + ret.size() / 2, mid);
	if (flag == 2) {
		cout << "I'm Sorry Hansoo\n";
	} else {
		cout << ret << "\n";
	}
}
