//
// Created by jaewkim on 2023/07/08.
//

#include <bits/stdc++.h>

using namespace std;

int is_pandigital(string s) {
	int arr[10] = {0,};
	for (int i = 0; i < s.size(); ++i) {
		arr[s[i] - '0']++;
	}
	for (int i = 1; i <= s.size(); ++i) {
		if (arr[i] != 1)
			return 0;
	}
	return 1;
}

int main() {
	//1. 조건을 모두 만족하는 숫자를 "멋쟁이 팬디지털" 이라고 한다.
	//2. 길이가 N인 substring을 10진수로 읽은 숫자입니다. (1 <= N <= 9)
	//3. 1부터 N까지의 숫자를 하나씩 사용하여 만든 N자리 숫자입니다.
	//4. 문자열 s와 길이 N을 입력받아서 멋쟁이 팬디지털을 반환하는 함수를 만드세요, 만약 멋쟁이 팬디지털이 여러 개 존재하는 경우라면 가장 큰 수를 반환해주세요, 멋쟁이 팬디지털이 존재하지않는 경우에는 -1 을 반환해주세요
	string s;
	int n;
	vector<string> v;
	
	cin >> s >> n;
	
	if (s.size() < 0 || s.size() > 1000 || n < 1 || n > 9) {
		cout << -1;
		return -1;
	}
	
	if (s.size() < n) {
		cout << -1;
		return -1;
	}
	
	if (s.size() == n) {
		if (is_pandigital(s)) {
			cout << s;
		} else {
			cout << -1;
		}
		return 0;
	}
	for (int i = 0; i < s.size() - n + 1; ++i) {
		string tmp = s.substr(i, n);
		if (is_pandigital(tmp)) {
			v.push_back(tmp);
		}
	}
	if (v.empty()) {
		cout << -1;
	} else {
		sort(v.begin(), v.end());
		cout << stoi(v.back());
	}
}