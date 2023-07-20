//
// Created by jaewkim on 2023/07/17.
//
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int cnt, sumVal, result;
//
//void print(vector<int> b) {
//	int sum = b[0] + b[1];
//	if (sum == sumVal) {
//		result++;
//	}
//	return ;
//}
//
//void combi(int start, vector<int> &b, vector<int> &v) {
//	if (b.size() == 2) {
//		print(b);
//		return ;
//	}
//	for (int i = start + 1; i < v.size(); ++i) {
//		b.push_back(v[i]);
//		combi(i, b, v);
//		b.pop_back();
//	}
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
//	vector<int> v;
//	vector<int> b;
//	int tmp = 0;
//
//	cin >> cnt >> sumVal;
//	for (int i = 0; i < cnt; ++i) {
//		cin >> tmp;
//		v.push_back(tmp);
//	}
//	combi(-1, b, v);
//
////	for (int i = 0; i < v.size(); ++i) {
////		for (int j = i + 1; j < v.size(); ++j) {
////			if (v[i] + v[j] == sumVal)
////				result++;
////		}
////	}
//	cout << result << "\n";
//	return (0);
//}

#include <stdio.h>
int N, M;
int x[10010000];
int y;
int z;
int main()
{
	scanf("%d%d", &N, &M);
	int i;
	for (i = 0; i < N; i++)
	{
		scanf("%d", &y);
		x[y]++;
	}
	for (i = 0; i <= M; i++)
	{
		z += x[i] * x[M - i];
	}
	printf("%d", z/2);
}