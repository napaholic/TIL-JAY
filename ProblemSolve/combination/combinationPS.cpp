//
// Created by jaewkim on 2023/05/19.
//

#include "combinationPS.h"
#include <bits/stdc++.h>

using namespace std;

int n = 5, k = 3, a[5] = {1, 2, 3, 4, 5};
void print(vector<int> b){
	for (int i : b)
		cout << i << " ";
	cout << '\n';
}

void combi(int start, vector<int> b){
	if (b.size() == k) {
		print(b);
		return;
	}
	for (int i = start + 1; i < n; i++) {
		b.push_back(i);
		combi(i, b);
		b.pop_back();
	}
	return;
}



int main() {
	vector<int> b;

//
//	do {
//		for (int i : b) {
//			cout << i << " ";
//		}
//		cout << "\n";
//	} while (next_permutation(b.begin(), b.end()));
	
	combi(-1, b);
	return 0;
}