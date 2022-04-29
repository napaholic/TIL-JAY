# 템플릿 프그래밍, STL알고리듬의 유형

### 함수 템플릿

```cpp
template <class <type_name>> <function_declaration>;
template <typename <type_name>> <function_declaration>;

template <class T>
T Add(T a, T b)
{
	//...
}

template <typename T>
T Add(T a, T b)
{
	//...
}
```

- 함수 템플릿을 호출할 때 템플릿 매개변수를 생략할 수 있음

```cpp
Add<int>(3, 10);

Add(3, 10);
```

### typename vs class

- 차이가 없다..(미묘한 차이가 있는데 거의 없다..)
    - [https://stackoverflow.com/questions/213121/use-class-or-typename-for-template-parameters](https://stackoverflow.com/questions/213121/use-class-or-typename-for-template-parameters)
- 그냥 typename 을 사용하자

### 템플릿은 어떻게 작동할까?

- 템플릿을 인스턴스화 할때마다 컴파일러가 내부적으로 코드를 생성

```cpp
//MyMath.h
template<typename T>
T Add(T a, T b)
{
	return a + b;
}

//Main.cpp
#incldue "MyMath.h"

//2. 컴파일러가 MyMath.h를 보고 생성한 코드
int Add(int a, int b)
{
	return a + b;
}
//4. 컴파일러가 MyMath.h를 보고 생성한 코드
float Add(float a, float b)
{
	return a + b;
}

int main()
{
	int resultInt = Add<int>(3, 10);// <-- 1. 컴파일러가 이 인스턴스를 볼때 코드 생성  
	float resultFloat = Add<float>(3.14f, 10.14f); // <-- 3. 컴파일러가 이 구문을 보고 또 생성

	return 0;
}
```

### 이런 방식이 어떤 의미를 가질까?

- 템플릿에 넣는 자료형 가짓수에 비례해서 exe 파일 크기 증가 → 컴파일시간 증가
- 컴파일 타임에 어느 정도 다형성을 부여할 수 있음
    - 그래서 많이 잘못 사용했음..
    - 이에 대해서는 나중에 ..

### 클래스템플릿

```cpp
//MyArray.h
#pragma once

namespace samples
{
	template<typename T>
	class MyArray
	{
	public:
		MyArray();

		bool Add(const T& data);
		size_t GetSize() const;

	private:
		enum { MAX = 3 };//enum형으로 이렇게 정의하면 메모리도 안잡아먹고 매직넘버 문제도 해결가능

		size_t mSize;
		T mArray[MAX];
	};
//템플릿 프로그래밍은 구현체가 헤더파일에 있어야한다.
//인라인함수와 동일하게 컴파일러가 cpp파일을 컴파일할때 해당 함수에 대한 내용을 알아야하기 때문
//컴파일러가 해당 함수 내용을 알아야 cpp파일에 각 자료형 별로 함수를 복제함.
	template<typename T>
	MyArray<T>::MyArray()
		: mSize(0)
	{
	}

	template<typename T>
	size_t MyArray<T>::GetSize() const
	{
		return mSize;
	}

	template<typename T>
	bool MyArray<T>::Add(const T& data)
	{
		if (mSize >= MAX)
		{
			return false;
		}

		mArray[mSize++] = data;

		return true;
	}
}
```

### 괜찮은 트릭

처음 인스턴스로 배열을 만들때 배열의 크기를 강요받는방식.

```cpp
//FixedVector.h

template<typename T, size_t N>//size_t형을 받음으로써 초기화시 배열크기를 고정하는방식
class FixedVector
{
public:
	//...
private:
	T mArray[N];
};

//main.cpp
FixedVector<int, 16> numbers;
```

### 템플릿 특수화

*특정한 템플릿 매개변수를 받도록 템플릿 코드를 커스터마이즈할 수 있음

- std::vector에 좋은 예가 있음
-

```cpp
template <class T, class Allocator>
class std::vector<T, Allocator> {} //모든 형을 받는 제네릭 vector

template <class Allocator>
class std::vector<bool, Allocator> //bool을 받도록 특수화된 vector
```

- bool을 왜 따로 만들까?
    - 이렇게 생각해보자
        - 제네릭 템플릿이 어느 형에나 적용됨
        - 단 특정 형에 특수화된 템플릿이 있다면 그 특수화된 템플릿이 적용됨
    - 그렇게 자주 쓰이지는 않음
- 전체 템플릿 특수화
    - 템플릿 매개변수 리스트가 비어있음

```cpp
template<typename VAL, typename EXP>
VAL Power(const VAL value, EXP exponent) {} //모든 형을 받는 제네릭 power()

template <>
float Power(float value, float exp) //float을 받도록 특수화된 power()
```

- 부분 템플릿 특수화

```cpp
template <class T, class Allocator>
class std::vector<T, Allocator> {} // 모든 형을 받는 제네릭 vector

template <class Allocator>
class std::vector<bool, Allocator> //bool을 받도록 특수화된 vector

```

# 템플릿 프로그래밍의 장점과 단점

- 컴파일러가 컴파일 도중에 각 템플릿 인스턴스에 대한 코드를 만들어줌
    - 컴파일 타임은 비교적 느림
    - 템플릿 매개변수를 추가할수록 더 느려짐

    ```cpp
    std::pair<std::string, int>
    std::pair<std::string, std::string>
    std::pair<float, std::string>
    ...
    ```

    - 하지만 런타임 속도는 더 빠를지도 모름
    - 실행 파일 크기가 커지기 때문에 항상 그런 것은 아님
    - c#과 Java도 어느 정도 해당되는 말(그래서 ArrayList를 쓰지 말라는것)
- 자료형만 다른 중복 코드를 없애는 훌륭한 방법
    - 최대한 제네릭 함수를 짧게 유지할 것
    - 제네릭이 아니어도 되는 부분은 별도의 함수로 옮기는 것도 방법. 이 함수가 인라인 될 수도 있음
- 컨테이너의 경우 매우 적합
    - 아주 다양한 형들을 저장할 수 있음
    - 그런 이유로 Java와 C#제네릭이 주로 컨테이너에 쓰이는 것
- 컨테이너가 아닌 경우
    - 각기 다른 서넛 이상의 자료형을 다룬다면 템플릿을 쓰자
    - 두 가지 정도라면 그냥 클래스를 2개 만들자

    ```cpp
    class Math;
    class FloatMath;
    ```


### STL 알고리듬이란?

- 요소 범위에서 쓸 수 있는 함수들
- 배열 또는 몇몇 STL 컨테이너에 쓸 수 있음
- 반복자를 통해 컨테이너에 접근
- 컨테이너의 크기를 변경하지 않음(따라서 추가 메모리 할당도 없음)

예제 vector 를 다른 vector로 복사하기

```cpp
#include <algorithm>
//...

int main()
{
	std::vector<int> scores;

	scores.push_back(10);
	scores.push_back(70);
	scores.push_back(40);

	std::vector<int> copiedScores;
	copiedScores.resize(scores.size());

	std::copy(scores.begin(), scores.end(), copiedScores.begin());
	//algorithm
	for (std::vector<int>::iterator it = copiedScores.begin();
	it != copiedScores.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
```

- copy()

```cpp
template<class _InIt, class _OutIt>
_OutIt copy(_InIt _First, _InIt _Last, _OutIt _Dest);
```

```cpp
//std::vector<int> scores;
//std::vector<int> copiedScores;
//std::vector<std::string> names;
//std::vector<std::string> copiedNames;

//int vector
std::copy(scores.begin(), scores.end(), copiedscores.begin());

//string vector
std::copy(names.begin(), names.begin() + 2, copiedNames.begin());
```

- copy() 구현
    - template<class _ ← 밑줄 하나있는건 템플릿 이 구현 안에서만 쓰려고 표시해놓는것.

```cpp
template<class _InIt, class _OutIt>
_OutIt copy(_InIt _First, _InIt _Last, _OutIt _Dest)
{
	for (; _First != _Last; ++_Dest, (void)++_First)
		{
			*_Dest = *_First;
		}

		return (_Dest);
}
```

- find() 함수 구현
```cpp
#include <iostream>

#pragma once

namespace samples
{
	namespace Algorithm
	{
		template <typename ITER, typename T>
		const ITER* Find(const ITER* begin, const ITER* end, const T& value)
		{
			const ITER* p = begin;
			while (p != end)
			{
				if (*p == value)
				{
					break;
				}
				++p;
			}

			return p;
		}
	};
};
```