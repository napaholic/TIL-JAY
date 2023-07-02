#include <bits/stdc++.h>

#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
void printV(vector<int> &v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "\n";
}

int main(){
	int a[3] = {1, 2, 3};
	vector<int> v;
	for(int i = 0; i < 3; i++)v.push_back(a[i]);
//1, 2, 3부터 오름차순으로 순열을 뽑습니다.
	do{
		printV(v);
	}while(next_permutation(v.begin(), v.end()));
	cout << "-------------" << '\n';
	v.clear();
	for(int i = 2; i >= 0; i--)v.push_back(a[i]);
//3, 2, 1부터 내림차순으로 순열을 뽑습니다.
	do{
		printV(v);
	}while(prev_permutation(v.begin(), v.end()));
	return 0;
}