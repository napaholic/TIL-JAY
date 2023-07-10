//
// Created by jaewkim on 2023/07/10.
//

#include <bits/stdc++.h>

using namespace std;
int sum_que(deque<int> &ref) {
	int sum = 0;
	for (int i = 0; i < ref.size(); ++i) {
		sum += ref[i];
	}
	return sum;
}

int main() {
	int n, k, idx;
	deque<int> que;
	cin >> n >> k;
	int result = 0;
	int max;
	for (int i = 0; i < n; ++i) {
		cin >> idx;
		que.push_front(idx);
		if (que.size() > k)
			que.pop_back();
		max = sum_que(que);
		if (result < max)
			result = sum_que(que);
	}
	cout << result;
	return 0;
}
//위 코드는 복잡도가 2n^2 임


//두번째

int main() {
	int psum[100001] = {0, };
	int ret = -100004;
	int n, k;
	int tmp = 0;
	
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> tmp;
		psum[i] = psum[i - 1] + tmp;
	}
	for (int i = k; i <= n; ++i) {
		ret = max(ret, psum[i] - psum[i - k]);
	}
	cout << ret;
	return 0;
}