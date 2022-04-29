# STL2[Map, Set]

# 맵 Map, Set

- 키 와 값 들의 쌍을 저장
- 키는 중복될 수 없음
- c++ 맵은 키를 기준으로 자동 정렬되는 컨테이너...
- 이진탐색 트리기반

```cpp
int main()
{
	std::map<std::string, int> simpleScoreMap;
	
	simpleScoreMap.insert(std::pair<std::string, int>("Mocha", 100));

	simpleScoreMap["Mocha"] = 0; // Mocha 라는 키에 value 를 0 으로 초기

	std::cout << "Current size: " << simpleScoreMap.size() << std::endl;
	//map.size() 요소의 갯수 반환
	return 0;
}
```

### 맵 생성

```cpp
map<<key_type>, <value_type>><name>
//빈 맵을 생성한다

map<<key_type>, <value_type>><name>(const map& x)
//x 라는 map 의 복사 생성자
//ex
std::map<std::string, int> simpleScoreMap;
std::map<StudentInfo, int> complexScoreMap;//StudendInfo 라는 클래스 혹은 구조체로도 생성 가능.

std::map<std::string, int> copiedSimpleScoreMap(simpleScoreMap);
```

### std::pair<key, value>

- 두 데이터를 한 단위로 저장하는 구조

pair.first, pair.second 가능........

```cpp
std::pair<std::string, int> student1("Coco", 10);

simpleScoreMap.insert(std::pair<std::string, int>("Mocha", 100));
```

### insert()

```cpp
std::pair<iterator, bool> insert(const value_type& value)
```

- 새 요소를 map 에 삽입한다.
- 반복자와 bool 값을 한 쌍으로 반환
    - 반복자(iterator) 는 요소를 가리키고
    - bool 값은 삽입 결과를 알려줌
- 키를 중복으로 삽입할 수 없음

```cpp
simpleScoreMap.insert(std::pair<std::string, int>("Mocha", 100));

simpleScoreMap.insert(std::pair<std::string, int>("Mocha", 0)); // false 반환
```

### operator[]

```cpp
mapped_type& operator[](const Key& key);
```

- key에 대응하는 값을 “참조"로 반환한다
- map에 키가 없으면 새 요소를 삽입
- map 에 키가 이미 있으면 그 값을 덮어씀

```cpp
std::map<std::string, int> simpleScoreMap;

simpleScoreMap["Coco"] = 10; //새 요소를 삽입한다
simpleScoreMap["Coco"] = 50; //기존 요소에 덮어쓴다.

//문제가  일어날 수 있는 상황들..
//simpleScoreMap 에는 "Coco" 만 들어있는 상황에서 다른 함수에서 "Moca" 를 읽으려고 하는경우

int somefunction(const map& x)
{
	return (map["moca"]);
}
//simpleScoreMap 안에 "moca", 0 인 페어를 생성함..
```

### find()

```cpp
iterator find(const Key& key);
```

- map에서 key 를 찾으면 그에 대응하는 값을 가리키는 반복자를 반환
- 못찾으면 end() 를 반환

예시

```cpp
int main()
{
	std::map<std:string, int> simpleScoreMap;
	simpleScoreMap.insert(std::pair<std::string, int>("Mocha", 100));

	std::map<std::string, int>::iterator it = simpleScoreMap.find("Mocha");
	if (it != simpleScoreMap.end())
	{
		it->second = 80;
	}

	return 0;
}
```

### swap(), clear()

```cpp
void swap(map& other);//두 map의 키와 값을 서로 맞바꾼다.

void clear();//map을 비운다
```

### erase()

```cpp
void erase(iterator position);
size_type erase(const key_type& key);
void erase(iterator first, iterator last);

std::map<std::string, int>::iterator foundIt = simpleScoreMap.find("Coco");
simpleScoreMap.erase(foundIt);//이터레이터로 지우는법

simpleScoreMap.erase("Coco"); //키받아서 지우는법
```

### 개체를 키로 사용하기

```cpp
//StudentInfo.h
class StudentInfo
{
public:
	//생성자들
private:
	std::string mName;
	std::string mStudentID;
};

//Main.cpp
int main()
{
	std::map<StudentInfo, int> scores;
	scores.insert(std::pair<StudentInfo, int>(
		StudentInfo("Poppy", "a556"), 30));
	scores.insert(std::pair<StudentInfo, int>(
		StudentInfo("Lulu", "a112"), 70));
	//,,,
}
//오류발생
//Code : C2678 
//Description : binary '<': no operator found which takes a left-hand operand of type 'const StudentInfo'...
```

STL맵은 항상 정렬된다.

- 반드시 두 키를 비교하는 함수를 만들어야함
    - operator<()

```cpp
bool StudentInfo::operator<(const StudentInfo& other) const
{
	if (mName == other.mName)
	{
		return mStudentID < other.mStudentID;
	}

	return mName < other.mName;
}
//위 함수를 studentInfo 클래스에 정의해야된다.
```

### 맵 장점

- std::list, std::vector 보다 탐색 속도가 더 빠름

맵 단점

- 자동으로 정렬됨
- 해쉬맵이 아님

# Set

- 정렬되는 컨테이너
- 중복되지 않는 키를 요소로 저장함
- 역시 이진 탐색 트리기반
    - 오름차순
- 셋은 맵과 거의 같다.(맵에서 값(value)를 없앤 개념)

```cpp
#include <set>

int main()
{
	std::set<int> scores;
	scores.insert(20);
	scores.insert(100);

	for (std::set<int>::iterator it = scores.begin(); it !- scores.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
```