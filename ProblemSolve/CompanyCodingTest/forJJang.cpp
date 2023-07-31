//
// Created by jaewkim on 2023/07/30.
//
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> results;

int solution(vector<vector<int>> users, int fp_cost, int fn_cost) {
	int result = 0;
	for (int i = 0; i < users.size(); ++i) {
		for (int j = 0; j < users[i][0] + 2; ++j) {
			result = 0;
			for (int k = 0; k < users.size(); ++k) {
				if (users[k][0] >= j && users[k][1] == 0)
					result += fp_cost;
				else if (users[k][0] < j && users[k][1] == 1)
					result += fn_cost;
			}
			results.push_back({result, j});
		}
	}
	std::sort(results.begin(), results.end());
	return results[0][1];
}

int main() {
	int result = 0;
	vector<vector<int> > adj = {
			{998, 1},
			{999, 1},
			{1000, 1}
	};
	int fp_cost = 1;
	int fn_cost = 1;
	
	cout << solution(adj, fp_cost, fn_cost) << "\n";
	
	return 0;
}