//
// Created by jaewkim on 2023/07/07.
//

#include <bits/stdc++.h>

using namespace std;



int is_palindrome(string &s) {
	int len = s.size();
	cout << "\n len/2 = " << len / 2;
	for (int i = 0; i < len / 2; ++i) {
		if (s[i] != s[len - i - 1]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	string s;
	
	cin >> s;
	is_palindrome(s) ? cout << "true\n" : cout << "false\n";
	cout << s.size();
}
