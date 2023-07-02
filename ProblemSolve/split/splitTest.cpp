//
// Created by jaewkim on 2023/04/02.
//
#include <bits/stdc++.h>

using namespace std;

vector<int> v;
int size;

void printV(vector<int> &v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "\n";
}

std::vector<std::string> split(std::string input, std::string delimiter) {
	std::vector<std::string> ret;
	long long pos = 0;
	std::string token = "";
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		ret.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
	ret.push_back(input);
	return ret;
}

void makePermutation(int n, int r, int dep) {
	cout << n << " : " << r << " : " << dep << '\n';
	if (dep == r) {
		printV(v);
		size++;
		return;
	}
	for (int i = dep; i < n; ++i) {
		swap(v[i], v[dep]);
		makePermutation(n, r, dep + 1);
		swap(v[i], v[dep]);
	}
}

int main(){
	for (int i = 1; i <= 10; ++i) {
		v.push_back(i);
	}
	makePermutation(10, 3, 0);
	cout << "last size = " << size << '\n';
	//7개를 임의로 뽑는다.
	//7개의 난쟁이 합이 100인지 확인한다
	//100이면 출력
	next_permutation(v.begin(), v.end());
}
