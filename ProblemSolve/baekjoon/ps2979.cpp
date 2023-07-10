//
// Created by jaewkim on 2023/07/06.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int one, two, three;
	int arive, leave;
	int cnt[100] = {0,};
	int ret = 0;
	
	cin >> one >> two >> three;
	
	for (int i = 0; i < 3; ++i) {
		cin >> arive >> leave;
		for (int j = arive; j < leave; ++j) {
			cnt[j]++;
		}
	}
	for (int k = 0; k < 100; ++k) {
		if (cnt[k]) {
			if (cnt[k] == 1) {
				ret += one * cnt[k];
			} else if (cnt[k] == 2) {
				ret += two * cnt[k];
			} else if (cnt[k] == 3){
				ret += three * cnt[k];
			}
		}
	}
	cout << ret << "\n";
	return 0;
}
