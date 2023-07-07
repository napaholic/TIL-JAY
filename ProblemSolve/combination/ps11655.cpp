//
// Created by jaewkim on 2023/07/07.
//

#include <bits/stdc++.h>

using namespace std;

int ft_isalpha(char c) {
	if (c >= 65 && c <= 90)
		return 1;
	else if (c >= 97 && c <= 122)
		return 2;
	return 0;
}

int main() {
	string s;
	
	getline(cin, s);
	for (int i = 0; i < s.size(); ++i) {
		if (ft_isalpha(s[i]) == 1) {
			s[i] = ((s[i] - 'A' + 13) % 26) + 'A';
		} else if (ft_isalpha(s[i]) == 2) {
			s[i] = ((s[i] - 'a' + 13) % 26) + 'a';
		}
	}
	cout << s;
}