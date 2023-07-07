//
// Created by jaewkim on 2023/07/07.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
	int cnt = 0;
	string pattern;
	string s;
	string head, tail;
	int pos;
	
	cin >> cnt;
	cin >> pattern;
	pos = pattern.find('*');
	head = pattern.substr(0, pos);
	tail = pattern.substr(pos + 1);
	
	for (int i = 0; i < cnt; ++i) {
		cin >> s;
		if (head.size() + tail.size() > s.size()) {
			cout <<"NE\n";
		} else {
			if (head == s.substr(0,head.size()) && tail == s.substr(s.size() - tail.size()))
				cout << "DA\n";
			else {
				cout << "NE\n";
			}
		}
	}
	return 0;
}