//
// Created by jaewkim on 2023/07/20.
//
#include <bits/stdc++.h>

using namespace std;
int n;
long long num;
int i;

int main() {
	ios_base::sync_with_stdio(false);
	
	while (!cin.eof()) {
		cin >> n;
		num = 1;
		i = 1;
		while(1) {
			if (num % n == 0) {
				cout << i << "\n";
				break;
			}
			else {
				num = (num * 10)%n + 1;
				++i;
			}
		}
	}
	return 0;
}