//
// Created by jaewkim on 2023/05/29.
//
#include <bits/stdc++.h>

#include "makePermutation.h"

using namespace std;

int v[] = {1, 2, 3};

void printVec(vector<int> &v) {
	for (int i : v) {
		cout << i << " ";
	}
	cout << "\n";
}

void printArr() {
	int size = sizeof(v)/sizeof(*v);
	for (int i = 0; i < size; ++i) {
		cout << v[i] << " ";
	}
	cout << "\n";
}


void f(int n, int r, int depth) {
	cout << n << " : " << r << " : " << depth << '\n';
	if (r == depth) {
		printArr();
		return;
	}
	for (int i = depth; i < n; ++i) {
		swap(v[i], v[depth]);
		f(n, r, depth + 1);
		swap(v[i], depth);
	}
	return ;
}

int main() {
	f(3, 3, 0);
	return 0;
}