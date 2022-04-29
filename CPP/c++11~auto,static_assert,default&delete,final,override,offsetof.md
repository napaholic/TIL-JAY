# c++11~ auto키워드, static_assert, default/delete 키워드, final 키워드 override키워드, offsetof매크로

# auto

- 자료형을 추론
- 자바스크립트등의 언어에 있는 동적인 형과는 다름
- 실제 자료형은 컴파일하는 동안 결정됨
- 따라서, 반드시 auto변수를 초기화해야 됨

```cpp
auto x;          //에러
auto x = "Chris";//올바름
```

JavaScript vs C++

```cpp
//JavaScript
var x;
x = "Chris";
x = 50 
//컴파일 ok

//C++
auto x = "Chris"; // x = const char*
x = 50; //에러
```

auto로 포인터와 참조 받기

- auto를 사용하여 포인터와 참조를 받을 수 있음
    - 포인터를 받을 때 : auto 또는 auto*
    - 참조를 받을 때 : auto&

ex: auto로 포인터받기

```cpp
//Main.cpp

cat* myCat = new Cat("Coco", 2);
auto myCatPtr = myCat;
//myCatPtr 은 myCat 과 동일한 포인터다.
```

auto 가동성문제

```cpp
auto a = 3;
auto b = ptr; //ptr 은 char*
//그러나 이건 포인터일까 아닐까?
auto name = object.GetName();
//가독성에 좋지않음 
//포인터형을 받을때는 auto* 를 쓰자
auto* name = object.GetName();
```

auto 참조형

```cpp
Cat myCat("Coco", 2);
Cat& myCatRef = myCat;
auto& anotherMyCatRef = myCatRef;
```

- auto형에 참조를 적용하려면 &연산자를 써야함.
- auto 형은 기본적으로는 대입이나 복사다.
- &연산자를 붙이면 참조형

auto로 const 받기

```cpp
const int b = 1;
auto& a = b;
```

const 를 이어받는다.

→ 컴파일러가 const 를 알아낼 수 있기 때문

```cpp
auto& name = object.GetName();//name 이 const 인지 아닌지 알 수 있을까?
```

- 가독성에 좋지는 않다
- const 참조를 받을때는 const auto& 를 쓰자

```cpp
const auto& name = object.GetName();
```

auto 는 엄청나게 좋은건가?

- auto 키워드가 타이핑을 좀 줄여 줌
- 허나 가독성을 떨어뜨림
    - 아래에서 minValue는 음수가 될 수 있을까?

    ```cpp
    auto minValue = object.GetMinValue();
    if (minValue < -3)//minValue가 만약 unsigned int 라면 음수와 비교하는게 말이될까?
    {
    	//...
    }
    ```

- 아직 auto에 관한 모두가 동의하는 코딩 표준이 없다
- pocu 코딩 표준에서는 auto보다 실제 자료형을 선호한다.
- 단, 몇 가지 예외가 있다.

### auto와 반복자

- 반복자에는 auto키워드가 매우 유용

```cpp
for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
{
	//...
}
//위와 같은 정형화된 상황에서는 auto키워드를 사용해서 코드양을 줄일 수 있음.
```

상기코드를 아래 코드로 변경가능

```cpp
for (auto it = v.begin(); it != v.end(); ++it)
{
	//...
}
```

이런코드 역시 auto 키워드로 변경가능

```cpp
for (std::map<std::string, std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
{
	//...
}
//이코드를
```

```cpp
//auto 키워드로 이렇게..
for (auto it = v.begin(); it != v.end(); ++it)
{
	//...
}
```

auto로 템플릿 형 받기

- 일부 템플릿 형의 경우에도 마찬가지

```cpp
MyArray<int>* a = new MyArray<int>(10);

auto* a = new MyArray<int>(10);
```

### 베스트 프랙티스

업계 전반의 코딩 표주은 아님

- 명시적이어야함
    - auto보다 실제 자료형 사용을 권장
    - 예외: 템플릿 매개변수와 반복자에는 auto사용
    - auto보다 auto* 를 사용
    - auto& 보다  const auto& 사용
- 전부 가독성과 관련된 것
- 런타임 성능은 동일

# static_assert

### assert 기본 동작

```cpp
//Class.cpp
#include <cassert>
const Student* Class::GetStudentInfo(const char* name)
{
	assert(name != NULL);// 조건이 false 면 실행을 멈춤
	//...
}
//Assertion failed: name != NULL, file c:\...\Class.cpp, line 21
```

### Assert

- 실행중에 가정(assertion) 이 맞는 지 평가
- 오직 디버그 빌드에서만 작동
- 실패한 assert를 보려면 반드시 프로그램을 실행해야 함
    - 모든 코드 경로가 실행되었다고 어떻게 장담할까?
    - 일부 어서션은 프로그램을 실행하기도 전에 알 수 있음
- “모든 곳에 assert를 쓰자”
    - 여전히 유효한 조언

### static_assert

- 컴파일 중에 어서션 평가
- 컴파일러가 assert조건이 참인지 아닌지 앎
- 실패하면 컴파일러는 컴파일 에러를 뱉음
- 많은 경우에 유용함

```cpp
//Class.h
struct Student
{
	char name[64];
	char id[10];
	int currentSemester;
};

class Class
{
public:
	//..
	const Student* GetStudentInfo(const char* name);
};

//Class.cpp
const Student* Class::GetStudentInfo(const char * name)
{
	static_assert(sizeof(Student) == 74, "Student structure size mismatch");
}

//static assertion failed with "Student structure size mismatch" 에러 발생확인가능
```

### default 키워드

예시

```cpp
//Dog.h
class Dog
{
public:
	Dog() = default;
	Dog(std::string name);
private:
	std::string mName;
};

//Dog.cpp
#include "Dog.h"
//컴파일러가 Dog() 대신만들어냄

Dog::dog(std::string name)
{
	//이하 코드 생략
}
```

default 키워드

- default 키워드를 사용하면, 컴파일러가 특정한 생성자, 연산자 및 소멸자를 만들어 낼 수 있음
- 그래서, 비어 있는 생성자나 소멸자를 구체화할 필요가 없음
- 또한 기본 생성자, 연산자 및 소멸자를 더 분명하게 표시할 수 있음
    - 명확하게 표현하는 것은 항상 좋다

컴파일러가 만든 생성자를 삭제하는 방법은?

```cpp
//Dog.h
class Dog
{
public:
	Dog() = default;
	Dog(const Dog& other) = delete;
	//...
};

//Main.cpp
#include "Dog.h"
int main()
{
	Dog myDog;
	Dog copiedMyDog(myDog);//에러
	//...
}
//C2280 'Dog::Dog(const Dog &)':attempting to reference a deleted function
```

delete 키워드

- 컴파일러가 자동으로 생성자를 만들어 주길 원치 않는다면 delete 키워드 사용
- private 접근 제어자로 빈 생성자를 만드는 트릭은 이제 그만
- 올바른 에러 메시지도 나옴

# final/override

## final

해결책 1. final 키워드로 클래스 상속 막기

```cpp
//Animal.h
class Animal final
{
public:
	virtual void SetWeight(int weight);
	//...
};

//Dog.h
#include "Animal.h"
class Dog : public Animal // 에러
{
public:
	virtual void SetWeight(int weight);
	//..
};
```

해결책 2. final 키워드로 클래스 상속 막기

```cpp
//Dog.h
#include "Animal.h"

//Animal 클래스는 final이 아님

class Dog final : public Animal // Animal 클래스를 상속받은 Dog 클래스는 상속 불가능
{
public:
	virtual void SetWeight(int weight) override;
	//...
};

//Corgi.h
#include "Dog.h"
class Corgi : public Dog // 에러
{
public:
	//..
};
```

해결책 2. final 키워드로 함수 상속 막기

```cpp
//Animal.h
class Animal
{
public:
	virtual void SetWeight(float weight) final;//더이상 오버라이드 불가능하도록.지정
	//...
};

//Dog.h
#include "Animal.h"
class Dog :public Animal
{
public:
	virtual void SetWeight(int weight) override;//에러
	Dog();
	~Dog();
};
```

- 클래스나 가상함수를 파생 클래스에서 오버라이딩 못 하도록 하려면 final 키워드 사용
- 컴파일 도중에 확인함
- 당연히 가상 함수가 아니면 쓸 수 없음

### override 키워드

- 잘못된 가상 함수 오버라이딩을 막으려면 override 키워드를 사용
- 당연히 가상 함수가 아니면 쓸 수 없음
- 이것도 컴파일 도중에 검사

```cpp
//human.h
#pragma once
#include <string>

namespace samples
{
	class Human
	{
	public:
		Human() = delete; //이름없는 사람은 생성 불가하도록 기본생성자 제거
		Human(const char* name);

		virtual ~Human() = default; //기본 소멸자 지정
//defualt 키워드로 기본소멸자를 지정한다는 소리는 이 클래스 안에서 메모리할당 안하겠다는 이야기다.

		virtual void SayMyName() const;

	protected:
		std::string mName;
	};
}

//pope.h
#pragma once

#include "Human.h"

namespace samples
{
	class Pope final : public Human //상속 불가
	{
	public:
		Pope();
		Pope(const Pope& otherPope) = delete;//복제 불가능

		virtual ~Pope() override = default; 
//override 하는 이유는 부모의 소멸자가 가상함수라는것을 보장할 수 있다.

		virtual void SayMyName() const override;

		// Compile error
		// void Scream() const override;//Scream 은 human 클래스에 없는 함수이기때문에 에러
	};
}

//pope.cpp
#include <iostream>
#include "Pope.h"

using namespace std;

namespace samples
{
	Pope::Pope()
		: Human::Human("Pope")//자식단에서 기본생성자 만들면서 부모생성자에 바로 이름을 넣어주게되면
//이미 pope 라는 이름이 있기때문에 pope 인스턴스를 만들 때 다른 이름을 줄 수 없음.
	{
	}

	void Pope::SayMyName() const
	{
		cout << "I'm " << mName << "!!" << endl;
	}
}
```

### offsetof

offset : 어떤걸 기준으로해서 얼마나 차이가 나는지.

예시 : 멤버들의 상대적위치(offset) 구하기

```cpp
//Main.cpp
struct Student
{
	const char* ID;
	const char* Name;
	int CurrentSemester;
};

int main()
{
	std::cout << "ID offset: " << offsetof(Student, ID) << std::endl;
//student 구조체로부터 ID 는 어느정도 거리(차이 : offset)에 있는지 -> 0출력됨
	std::cout << "Name offset: " << offsetof(Student, Name) << std::endl;
//student 구조체로부터 Name 은 어느정도 거리(차이 : offset)에 있는지 -> 4 출력됨
	std::cout << "CurrentSemester offset: " << offsetof(Student, CurrentSemester) << std::endl;
//student 구조체로부터 CurrentSemester 은 어느정도 거리(차이 : offset)에 있는지 -> 8 출력됨
```

offsetof 매크로

```cpp
#define offset(type, member)
```

- 매크로의 일종
- 특정 멤버가 본인을 포함한 자료구조의 시작점에서부터 몇 바이트만큼 떨어져 있는지 알려줌
- 직렬화, 역직렬화를 할 때 꽤나 유용