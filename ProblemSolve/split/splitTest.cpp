//
// Created by jaewkim on 2023/04/02.
//
#include <bits/stdc++.h>

using namespace std;
vector<int> v;
vector<vector<int> > ans;
int sum;
int size;
vector<int> nine;

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

void combi(int start, vector<int> b, int n, int k) {
	if (b.size() == k) {
		if (sum - b[0] - b[1] == 100) {
			ans.push_back(b);
			exit(0);
		}
		return;
	}
	for (int i = start + 1; i < n; ++i) {
		b.push_back(nine[i]);
		combi(i, b, n, k);
		
		b.pop_back();
	}
	return ;
}



int main() {
	vector<int> b;
	int a;
	
	for (int i = 0; i < 9; ++i) {
		cin >> a;
		nine.push_back(a);
	}
	sum = accumulate(nine.begin(), nine.end(), 0.0);
	sort(nine.begin(), nine.end());
	combi(-1, b, 9, 2);
	for (int i = 0; i < ans.size(); ++i) {
		for (int j = 0; j < ans[i].size(); ++j) {
			cout << ans[i][j];
		}
	}
}

