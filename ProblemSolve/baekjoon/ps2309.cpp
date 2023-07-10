//
// Created by jaewkim on 2023/07/06.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > ans;
vector<int> nine;

void combi(int start, vector<int> b, int n, int k) {
	if (b.size() == k) {
		if (std::accumulate(b.begin(),b.end(), 0.0) == 100)
			ans.push_back(b);
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	vector<int> b;
	int a;
	
	for (int i = 0; i < 9; ++i) {
		cin >> a;
		nine.push_back(a);
	}
	sort(nine.begin(), nine.end());
	combi(-1, b, 9, 7);
	for (int i = 0; i < ans.size(); ++i) {
		for (int j = 0; j < ans[i].size(); ++j) {
			cout << ans[i][j] << "\n";
		}
	}
}
