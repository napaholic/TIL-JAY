# 예외, STL1[Vector]

| OS “Exception” | std::exception |
| --- | --- |
| 비동기적 | 동기적 |
| 윈도우 : 구조적예외처리
리눅스 : POSIX 신호 Faults, Traps, Aborts | C++STL |
| 플랫폼마다 다름 | 모든 플랫폼에 공통 |
| 오버헤드 비교적 많음, 더 느림 | 오버헤드가 비교적 적음 |
- 대부분의 예외는 불필요한경우가 많다
- 하지만 생성자의 경우에는 유용할 수 있다.

```cpp
Inventory::Inventory(int count)
{
	mSlots = new int[count];
}
//mSlots가 NULL이라면 생성자는 반환값이 없기때문에
//생성자는 문제가 있을때 외부에 문제가있다고 알릴방법이 없음.
```

```cpp
//Exceptions.h
#incldue <exception>

struct SlotNullException : public std::exception
{
	const char* what() const throw()
	{
		return "Slot is NULL";
	}
};

//Inventory.cpp

Inventory::Inventory(int slotCount)
{
	mSlots = new int[slotCount];
	if (mSlots == NULL)
	{
		throw SlotNullException();
	}
}
```

예외처리 예시 : 웹 요청 방식

```cpp
//Error.h
enum EError
{
	SUCCESS,
	ERROR,
};

struct ErrorCode
{
	EError Status;
	int Code;
};

template <typename T> struct Result
{
	ErrorCode Error;
	T Value;
};

//Main.cpp
Result<const char*> result;

result = record.GetStudentIDByName("Pope Kim");

if (result.Error.Status == ERROR)
{
	cout << "Error Code " << result.Error.Code << endl;
}
else
{
	cout << "Student ID is " << result.Value << endl;
}
```

### 적절한 예외 처리 전략

1. 유효성 검사/예외는 오직 경계에서만
    1. 밖에서 오는 데이터를 제어할 수 없기 때문
    2. 예) 외부에서 들어오는 웹 요청, 파일 읽기/쓰기, 외부 라이브러리
2. 일단 시스템에 들어온 데이터는 다 올바르다고 간주할 것
    1. assert를 사용해서 개발 중 문제를 잡아내고 고칠 것
3. 예외 상황이 발생할 때는 NULL을 능동적으로 사용할 것
    1. 하지만 기본적으로 함수가 NULL을 반환하거나 받는 일은 없어야 함
    2. 코딩표준: 만약 NULL을 반환하거나 받는다면 함수의 이름을 잘 지을 것


```cpp
//경계에서의 예외 처리
//c#방식
string ReadFileOrNull(string filename)
{
	if (!File.Exists(filename))
	{
		return null;
	}
	try
	{
		return File.LoadAllText(filename);
	}
	catch (Exception e)
	{
		return null;
	}
}
```

```cpp
//일단 시스템에 들어온 데이터는 다 올바르다고 간주
//assert 사용해서 개발줄 문제를 잡아내고 고칠 것
int ConverToHumanAge(const Animal* pet)
{
	Assert(pet != NULL);
	//...
}
```

### 코딩표준

1. 매개변수가 NULL이 될 수 있으면 매개변수 이름 뒤에 OrNull을 붙인다.

    ```cpp
    const char* GetCoolName(const char* startWithOrNull) const;
    ```

2. 함수가 NULL을 반환할 수 있으면 이름뒤에 OrNull을 붙인다

```cpp
const char* GetHobbyOrNull() const;
```



### STL Container  목록

- 벡터
- 맵
- 셋
- 스택
- 큐
- 리스트
- 덱
- ...

### STL 컨테이너의 목적

- 템플릿 기반
- 모든 컨테이너에 적용되는 표준 인터페이스
- 메모리 자동 관리

### 벡터

- 어떤 자료형도 넣을 수 있는 동적 배열
    - 기본 데이터
    - 클래스
    - 포인터
- 그 안에 저장된 모든 요소들이 연속된 메모리 공간에 위치
- 요소 수가 증가함에 따라 자동으로 메모리를 관리해 줌
- 어떤 요소에도 임의로 접근 가능

```cpp
scores.push_back(30); //vector 의 맨 뒤에 요소를 추가한다
scores.pop_back();// vector의 맨 뒤에 있는 요소를 제거한다.
scores.capacity(); // vector에 할당된 요소 공간 수, byte반환이아니라 실제 몇개 공간 담을수있는지 반환
scores.size(); //현재 실제로 vector에 들어 있는 요소 수
```

### vector의 용량 늘리기

```cpp
scores.reserve(10); // 만약 기존 capacity 보다 작으면 아무 동작 안함.
//새로운 저장공간 재할당 뒤 기존 요소들을 모두 새 공간으로 복사.
vector<int> scores;
scores.reserve(5); //컴파일러는 이런 코드 두줄을 보면 최적화를한다. 즉, 초기용량이 5인 vector 생성
```

- 만약 처음 벡터를 생성시 16개의 capacity 가 있다고 할때, 이 벡터에 100개의 요소를 넣는다면 컴파일러의 순서는 어떻게될까..
    - 보통 capacity 가 2배씩 증가한다고함.. 그래서 16 개의 요소 push 이후 32를 할당하고 다차면 또 64를 할당, 다 할당되면 128을 할당.. 불필요한 재할당이 발생함.
- 불필요한 재할당을 막기위해 vector 생성한 직후에 reserve 함수를 꼭 호출해서 불필요한 재할당을 막자...

### 특정 위치에 요소 삽입하기

```cpp
std::vector<int> scores;

scores.reserve(4);
scores.push_back(10);
scores.push_back(20);
scores.push_back(30);
scores.push_back(40);

std::vector<int>::iterator it = scores.begin();

it = scores.insert(it, 80); //실행 결과는  80, 10, 20, 30, 40 
```

### 재할당 + 복사 문제

```cpp
std::vector<int> scores;
scores.reserve(4);
//10, 50, 38, 100 을 넣는다면..

std::vector<int>::iterator it;
it = scores.begin();

it = scores.insert(it, 80);
/*
스택에 기존의 vector capacity 를 초과해서 삽입하므로 재할당이 일어나면서 동시에
요소를 하나씩 뒤로 복사해서 할당하는 문제가 일어남.. 배열의 고질적인문제..
*/
```

### 요소대입

```cpp
vector<int> anotherScores;
anotherScores.assign(7, 100); //100, 100, 100, 100, 100, 100, 100
```

### 두 벡터 교환하기

```cpp
vector<int> anotherScores;//1, 2, 3, 4
vector<int> scores;//5, 6, 7

scores.swap(anotherScores);  //scores: 1, 2, 3, 4  //anotherScores: 5, 6, 7
//swap 은 서로 포인터만 교환하면 되지않을까..
```

### 벡터의 크기 변경하기

```cpp
scores.resize(10);
```

- 벡터의 크기 변경.
- 새 크기가 벡터의 기존 크기(size)보다 작으면, 초과분이 제거됨
- 새 크기가 벡터의 기존 용량(capacity)보다 크면 재할당이 일어남

### 벡터의 모든 요소 제거하기

```cpp
scores.clear();
```

- vector를 싹 지운다.
- 크기(size)는 0이되고 용량은 그대로.

개체를 직접 보관하는 벡터의 문제점

- 사이즈가 큰 오브젝트의 경우 벡터재할당이 일어나거나 다른 함수로 복사에 의해서 전달하는경우 메모리를 어마어마하게 쓸 수도 있음.
- 해결책 → 포인터벡터.

### 포인터벡터

```cpp
int main()
{
	vector<Score*> scores;

	scores.reserve(2);
	scores.push_back(new Scores(30, "C++"));
	scores.push_back(new Scores(87, "Java"));
	//...

	for( vector<Score>*::iterator iter = scores.begin(); iter!= scores.end(); ++iter)
	{
		delete *iter;
	} // 개체의 힙영역 할당공간 delete 해주는것 잊지말기.. scores 는 "포인터" 벡터일뿐..
	scores.clear();
	return 0;
}
```

### 벡터의 장점

- 순서에 상관 없이 요소에 임의적으로 접근 가능
- 제일 마지막 위치에 요소를 빠르게 삽입 및 삭제

### 벡터의 단점

- 중간에 요소 삽입 및 삭제는 느림
- 재할당 및 요소 복사에 드는 비용