//
// Created by jaewkim on 2023/07/14.
//

#include <bits/stdc++.h>

using namespace std;

string s, ret;
int a[26];
int flag, mid;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> s;
	for (int i = 0; i < s.size(); ++i) {
		a[s[i] - 65]++;
	}
	for (int i = 25; i >= 0; --i) {
		if (a[i]) {
			if ((a[i] & 1) == 1) {
				mid = i;
				flag++;
			}
			if (flag == 2) {
				break;
			}
			
		}
	}
	if (flag == 2) {
		cout << "I'm Sorry Hansoo\n";
		return 0;
	}
	cout << ret << "\n";
}
