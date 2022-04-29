# 정렬안된 맵, 어레이, 범위기반 for 반복문

### 새로 추가된 STL

- std::unordered_map ( and unordered_multimap)
- std::unordered_set (and unordered_multiset)
- std::array

# 정렬 안된 맵(unordered_map)

- c++ 은 기본이 자동정렬되는 맵임

### std::unordered_map

- 키와 값의 쌍(pair) 들을 저장
- 키는 중복 불가
- 자동으로 정렬되지 않는 컨테이너
    - 요소는 해쉬 함수가 생성하는 색인 기반의 버킷들로 구성됨
    - 해쉬맵 이라고도 함

std::map

- 자동으로 정렬되는 컨테이너
- 키-값 쌍들을 저장
- 이진탐색트리
- 탐색시간 : O(logN)
- 삽입과 제거가 빈번하면 느림

std::unordered_map

- 자동으로 정렬되지 않는 컨테이너
- 키-값  쌍들을 저장
- 해쉬테이블
- 탐색시간:
    - O(1), 해쉬 충돌이 없을 경우
    - O(n), 최악의 경우
- 버킷 때문에 메모리 사용량 증가

```cpp
//SpeedTestExample.hpp
#pragma once

namespace samples
{
	void SpeedTestExample();
}

//SpeedTestExample.cpp
#include <iostream>
#include <set>
#include <unordered_set>
#include <chrono>
#include "SpeedTestExample.h"

using namespace std;

namespace samples
{
	void SpeedTestExample()
	{
		// RUN THIS EXAMPLE IN RELEASE CONFIG

		// initialize test
		set<int> orderedSet;
		unordered_set<int> unorderedSet; //정렬된 set과 정렬되지않은 set이 있음

		const int NUMBER_TO_INSERT_LATER = 1023;
		const int MAX_NUMBER_IN_SET = 100000;

		unorderedSet.reserve(MAX_NUMBER_IN_SET); //unoredered Set 의 경우 reserve함수 있음.

		static_assert(MAX_NUMBER_IN_SET > NUMBER_TO_INSERT_LATER, "MAX_NUMBER_IN_SET should be greater than NUMBER_TO_INSERT");

		for (int i = 0; i < MAX_NUMBER_IN_SET; i++)
		{
			if (i == NUMBER_TO_INSERT_LATER)
			{
				continue;
			}

			orderedSet.insert(i);
			unorderedSet.insert(i);
		}

		auto start = chrono::high_resolution_clock::now(); //시간측정함수

		orderedSet.insert(NUMBER_TO_INSERT_LATER);

		auto end = chrono::high_resolution_clock::now();

		auto elapsedNanoSeconds = end - start;

		cout << "Inserting into orderedSet: " << elapsedNanoSeconds.count() << " ns" << endl;

		start = chrono::high_resolution_clock::now();

		unorderedSet.insert(NUMBER_TO_INSERT_LATER);

		end = chrono::high_resolution_clock::now();

		elapsedNanoSeconds = end - start;

		cout << "Inserting into unorderedSet: " << elapsedNanoSeconds.count() << " ns" << endl;

		// Uncomment this when you run it with Release configuration
		// system("pause"); 
	}
}
```

### std::array

- 요소 수를 기억하지 않음
- 더 나은 방법이 있어서 잘 쓰이지는 않음
- FixedVector랑 비슷함

### 범위 기반 for 반복문

```cpp
int scores[3] = {10, 20, 30};

for (int i = 0; i < 3; ++i)
{
	std:: cout << scores[i] << " " << std::endl;
}

for (int score : scores)
{
	std::cout << score << " " << std::endl;
}

std::map<std::string, int> scoreMap;

scoreMap["Lulu"] = 10;
scoreMap["Coco"] = 50;
scoreMap["Mocha"] = 100;

for (auto& score : scoreMap)
//score 변수를 scoreMap범위 안에서 참조로 가져올 수도 있음
//&문자 빼서 참조로 안가져오면 복사로 가져옴 (원본안바뀜)
{
	//...
}
```

- for 반복문을 더 간단하게 쓸 수 있음
- 이전의 for 반복보다 가독성이 더 높음
- STL컨테이너와 c스타일 배열 모두에서 작동함
- auto 키워드를 범위 기반 for 반복에 쓸 수 있음
- 컨테이너/배열을 역순회 할 수 없음

/