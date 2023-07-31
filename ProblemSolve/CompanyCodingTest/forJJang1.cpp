//
// Created by jaewkim on 2023/07/30.
//
#include <bits/stdc++.h>

using namespace std;

//주 5일제인 회사의 직원이 휴가를 내고 n일간 여행을 가려고 합니다. 이 때 여행 기간에 포함되는 휴일(토요일과
//일요일)의 숫자는 무슨 요일부터 여행을 시작하는지에 따라 달라질 수 있습니다.
//예를 들어 6일간 여행을 간다고 했을때
//월요일부터 여행을 간다면 월-화-수-목-금-토로 휴일이 하루만 포함됩니다.
//화요일부터 여행을 간다면 화-수-목-금-토-일로 휴일이 이틀 포함됩니다.
//무슨 요일에 여행을 시작하더라도 휴일이 1보다 적게포함되거나, 2보다 많이 포함될 수는 없습니다.
//여행을 가려는 기간 n일이 주어질 때, 해당 기간중에 포함되는 휴일(토요일, 일요일)의 최솟값과 최대값을 return 하도록 solution 함수를 완성해주세요.
//n 은 10^15 이하의 자연수입니다.
//return 하는 배열의 첫 번째 원소는 최솟값, 두 번째 원소는 최댓값이어야 합니다.
vector<long long> solution(long long n) {
	vector<long long> answer;
	
	long long w = n / 7;
	long long r = n % 7;
	
	if (r == 0) {
		answer.push_back(w * 2);
		answer.push_back(w * 2);
		return answer;
	}
	else if (r == 1) {
		answer.push_back(w * 2);
		answer.push_back(w * 2 + 1);
	}
	else if (r == 6) {
		answer.push_back(w * 2 + 1);
		answer.push_back(w * 2 + 2);
	}
	else {
		answer.push_back(w * 2);
		answer.push_back(w * 2 + 2);
	}
	
	return answer;
}

int main() {
	long long n = 7;
	cout << solution(n)[0] << "\n";
	cout << solution(n)[1] << "\n";
}