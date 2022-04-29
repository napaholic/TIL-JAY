# 큐 Queue, 스택 Stack, 기타 컨테이너, STL컨테이너의 목적

- 선입 선출 자료구조(First in First out, FIFO)

```cpp
// 큐 예시
std::queue<int> studentIDQueue;
std::queue<std::string> studentNameQueue;
std::queue<StudentInfo> studentInfoQueue;
```

### 요소 삽입, 제거

```cpp
void push(const value_type& val);
void pop();//c++은 pop이 뭔가를 반환하지않는다. 그래서 맨 앞 요소를 front() 함수로 쓰고 pop으로 제거해야됨.
```

### front(), back()

```cpp
value_type& front();//가장 먼저 삽입되었던 요소를 "참조"로 반환
value_type& back();//가장 마지막에 삽입되었던 요소를 참조로 반환

//"Coco", "Mocha" 를 넣었을 경우.
std::string front = studentNameQueue.front(); // "Coco"
std::string back = studentNameQueue.back(); // "Mocha"
```

### size(), empty()

```cpp
size_type size();
bool empty();
```

# 스택 Stack

- 후입 선출 (Last in first out, LIFO) 자료구조
- 스택은 top 이외에 아래에 있는 요소에 대해서는 접근을 못하게하는게 원칙인 자료구조다.
  필요하다면 다른 자료구조를 쓰는게 옳을듯..

```cpp
#include <stack>

int main()
{
	std::stack<std::string> studentNameStack;
	studentNameStack.push("Coco");
	studentNameStack.push("Mocha");

	while (!studentNameStack.empty())
	{
		std::cout << studentNameStack.top() << std::endl;
		tudentNameStack.pop();
	}
	return 0;
}
```

### top()

```cpp
value_type& top(); //stack에 가장 마지막에 저장된 요소를 참조로 반환한다.
```

### size(), empty()

```cpp
size_type size();
bool empty();
```

### 리스트

- 탐색느림
- 위치를 알고 있다면 O(1)

### 멀티셋

- 중복 키를 허용
- 요소를 수정하면 안됨

### 멀티맵

- 중복 키를 허용

### 덱(디큐, deque)

- Double ended queue의 약자
- 양쪽 끝에서 요소 삽입과 삭제가 모두 가능

### 우선순위 큐

- 자동 정렬되는 큐

# STL 컨테이너의 목적

- 모든 컨테이너에 적용되는 표준 인터페이스
- std 알고리즘은 많은 컨테이너에서 작동
- 템플릿 프로그래밍 기반
- 메모리 자동 관리

과연 이런 것들이 더 좋은 기능일까 라는 물음을 할 수 있다.

단점을 살펴 보자면

### 모든 컨테이너에 알맞은 표준 인터페이스라는 환상

- 모든 컨테이너에 같은 인터페이스가 적용되는 것은 이상하다
    - 극단적으로 oop를 추구한 사례

```cpp
std::vector<int> scores;
scores.push_back(10);

std::list<int> ages;
ages.push_back(100);

//둘다 스택같아 보일 수 도 있음.
```

### 메모리 단편화

- 빈번한 메모리 재할당은 메모리 단편화를 초래함
- 메모리 단편화는 엄청난 문제가 될 수 있음. 특히 가상 메모리를 지원하지 않는 플랫폼에서 프로그램을 실행할 때...
- 메모리 단편화 때문에 애플리케이션이 뻗어 버릴 수 있음
    - 즉, 총 여유 공간은 충분하나 충분히 큰 연속되는 메모리가 없는 경우
- 디버깅 및 고치는 게 쉽지 않음.

### 회사 내부에서 만든 STL 대체품들..

- 많은 회사들이 자신만의 컨테이너를 만들어 STL을 대체
    - EA
        - EASTL
        - STL과 호환 됨. 메모리 문제 등을 고친 컨테이너
    - Epic Games (언리얼 엔진4)
        - TArray, TMap, TMultiMap, TSet
        - STL보다 나은 인터페이스로 구현한 언리얼 만의 컨테이너
- EA STL과 언리얼엔진 4는 모두 오픈소스니 한 번 살펴볼것
- 또한 직접 컨테이너를 만들어 보면 메모리 관리에 대한 이해를 높일 수 있을것임