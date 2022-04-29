# nullptr, 고정 폭 정수형, enum class

# nullptr

### NULL 문제

- NULL을 쓰면 가끔 뭔가 굉장히 이상한 일이 벌어짐

```cpp
//Class.h
float GetSore(const char* name);
float GetScore(int id);

//Main.cpp
Class* myClass = new Class("COMP3100");
//...
int score = myClass->GetScore(NULL); <- 어떤 함수가 호출될까?
```

NULL vs nullptr

```cpp
int number = NULL;
int* ptr = NULL;

int anotherNumber = nullptr;
int* anotherPtr = nullptr;
```

c에서는 NULL 이랑 0이랑 구분이 불가했는데 c++ 에서는  nullptr이라는 자료형이 새로 생겼다.

```cpp
nullptr
typedef decltype(nullptr) nullptr_t;
```

예시: nullptr 사용하기

```cpp
//Main.cpp
Class* myClass = new Class("COMP3200");

const Student* student = myClass->GetStudent("Coco");
if (student != nullptr)
{
	std::cout << student->GetID() << ":" << student->GetName() << std::endl;
}
```

- 포인터에는 언제나 nullptr 을 쓰자
- 더이상 NULL이 있을곳이 없음.

### 고정 폭 정수형

기본 자료형과 바이트 크기

- 아래 자료형들의 바이트 크기는 얼마일까?
    - char
    - short
    - long
    - longlong
    - int
- 사실 int 가 4바이트라는건 표준이아니라 많은 플랫폼이 4바이트를 쓰는것 뿐이다.
- 드디어 c++11에서 지원됨.

[Fixed width integer types (since C++11)](http://en.cppreference.com/w/cpp/types/integer)

- 가독성 향상을 위해 낡은 기존 자료형보다 이것들을 쓰자

```cpp
int8_t score = student->GetScore();
```

### Enum Class

문제: C 스타일 Enum

```cpp
//Main.cpp
enum eScoreType
{
	Assignment1,
	Assignment2,
	Assignment3,
	Midterm,
	Count,
};

enum eStudyType
{
	Fulltime,
	Parttime,
};

int main()
{
	eScoreType type = Midterm;
	eStudyType studyType = Fulltime;
	
	int num = Assignment3; //->에러안나는건 문제임
	if (type == Fulltime) //->이 구문도 에러나야됨 왜냐
//eScoreType eStudyType 둘간에 비교하는것 자체가 말이안됨
	{
		//...
	}
	return 0;
}
```

해결책

```cpp
//Main.cpp
enum class eScoreType
{
	Assignment1,
	Assignment2,
	Assignment3,
	Midterm,
	Count,
};

enum class eStudyType
{
	Fulltime,
	Parttime,
};

int main()
{
	eScoreType type = Midterm;
	eStudyType studyType = Fulltime;
	
	int num = Assignment3; //에러 initializing: cannot convert from 'eScoreType' to int
	if (type == Fulltime) //->이 구문도 에러
	{
		//...
	}
	return 0;
}
```

- 정수형으로의 암시적 캐스팅이 없음
- 자료형 검사
- enum class 저장공간도 지정가능

```cpp
//Class.h
#incldue cstdint>

enum class eScoreType : uing8_t
{
	Assignment1,
	Assignment2,
	Assignment3,
	Midterm,
	Final = 0x100, //경고! 256 대입하려고함, 
};
```

바뀌면서 안되는것

```cpp
for(int i = eScoreType::Assignment1; i < eScoreType::Count; ++i)
{
	//...
} //이제 이런식으로 컴파일안됨
```

```cpp
for(int i = static_cast<int>(eScoreType::Assignment1);
			 i < static_cast<int>(eScoreType::Count);
			++i)
{
	//...
} //이제 이런식으로 컴파일안됨
```

enum class 예시

```cpp
//Ecolor.h
#pragma once

namespace samples
{
	enum class eColor
	{
		Red,
		Green,
		Blue
	};
}
//Ball.h
#pragma once

#include "EColor.h"

namespace samples
{
	class Ball
	{
	public:
		Ball(eColor color);
		Ball() = delete;
		~Ball() = default;

		eColor GetColor() const;
		void SayColor() const;

	private:
		eColor mColor;
	};
}

//ball.cpp
#include <iostream>
#include "Ball.h"

using namespace std;

namespace samples
{
	Ball::Ball(eColor color)
		: mColor(color)
	{
	}
	
	eColor Ball::GetColor() const
	{
		return mColor;
	}

	void Ball::SayColor() const
	{
		switch (mColor)
		{
		case eColor::Red:
			cout << "I'm RED!!" << endl;
			break;

		case eColor::Green:
			cout << "I'm GREEN!!" << endl;
			break;

		case eColor::Blue:
			cout << "I'm BLUE!!" << endl;
			break;

		default:
			cout << "I DON'T KNOW WHAT COLOR I AM!!" << endl;
			break;
		}
	}
}

//EnumExample.cpp
#include "EColor.h"
#include "Ball.h"

using namespace std;

namespace samples
{
	void EnumExample()
	{
		Ball ball1(eColor::Red);
		Ball ball2(eColor::Blue);
		Ball ball3(eColor::Green);

		ball1.SayColor();
		ball2.SayColor();
		ball3.SayColor();
	}
}
```