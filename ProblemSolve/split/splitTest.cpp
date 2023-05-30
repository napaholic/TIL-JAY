//
// Created by jaewkim on 2023/04/02.
//
#include <bits/stdc++.h>

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



int main(){
	//7개를 임의로 뽑는다.
	//7개의 난쟁이 합이 100인지 확인한다
	//100이면 출력
}
