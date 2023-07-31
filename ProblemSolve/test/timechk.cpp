//
// Created by jaewkim on 2023/07/25.
//

#include <bits/stdc++.h>

using namespace std;


//for time check 10000000 * 10000000 vector<int>
int fortimechk() {
	vector<int> v;
	for (int i = 0; i < 10000; ++i) {
		v.push_back(i);
	}
	for (int i = 0; i < 10000; ++i) {
		for (int j = 0; j < 10000; ++j) {
			v[i] = v[j];
		}
	}
}

//foreach time check 10000000 * 10000000 vector<int>
int forEachtimechk() {
	vector<int> v;
	for (int i = 0; i < 10000; ++i) {
		v.push_back(i);
	}
	for (auto &i : v) {
		for (auto &j : v) {
			v[i] = v[j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	clock_t start, end;
	
	start = clock();
	fortimechk();
	end = clock();
	cout << "for time check: " << (double)(end - start) / CLOCKS_PER_SEC << "\n";
	
	start = clock();
	forEachtimechk();
	end = clock();
	cout << "forEach time check: " << (double)(end - start) / CLOCKS_PER_SEC << "\n";
	
	return 0;
}