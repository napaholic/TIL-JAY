# 가상소멸자, 다중상속, 추상클래스, 인터페이스, 캐스팅

# 비 가상 소멸자

```cpp
//Animal.h
class Animal
{
public:
	~Animal();
private:
	int mAge;
};

//Cat.h
class Cat : public Animal
{
public:
	~Cat();
private:
	char* mName;
};

//ex1 Cat
Cat* myCat = new Cat(2, "Coco"); //Cat.h 의 소멸자 호출 다음 부모 소멸자 호출 이상없음
delete myCat;

//ex2 업캐스팅 Cat
Animal* yourCat = new Cat(5, "Mocha"); //현재의 데이터 형이 Animal클래스이기때문에
delete yourCat;                        //바로 Animal class 소멸자만 호출.
																			 //자식클래스 소멸자 호출안되므로 mName 메모리누수
```

## 가상 소멸자

```c++
//Animal.h
class Animal
{
public:
	virtual ~Animal();
private:
	int mAge;
};

//Cat.h
class Cat : public Animal
{
public:
	virtual ~Cat();//여기는 virtual 키워드 생략해도됨. 혹시나 Cat 을 다시 상속받을수도있으니..
private:
	char* mName;
};

//Cat.cpp
Cat::~Cat()
{
	delete mName;
}
```

- 모든 소멸자에는 언제나 virtual  키워드를 넣을것.
    - because. 협업시에 내가만든 클래스를 누군가 상속해서 쓸 수도 있는데 그럴경우 일일이 컨트롤할 수 없기때문에..

  ### 다형성

    - 업캐스팅으로 다양한 클래스들을 하나의 배열로 컨트롤하는데에 유용함


# 다중 상속

```c++
//Animal.h
class Animal
{
};
//Tiger.h
class Tiger : virtual public Animal
{
};
//Lion.h
class Lion : virtual public Animal
{
};

//Liger.h
class Liger : public Tiger, public Lion
{
};
//가상 베이스클래스로 상속받으면 해결 가능하지만 한번에 이런 구조를 만들지 않는이상 해결하기 어려운점이 있음.
//해결책은 인터페이스를 통해서 해결가능.

```

# 추상(abstract) 클래스

- 순수 가상함수를 가지고 있는 베이스 클래스를 추상클래스라 함.
    - 추상 클래스에서 개체를 만들 수 없음
    - 추상 클래스를 포인터나 참조 형으로는 사용가능

```c++
//Animal.h
class Animal
{
public:
	virtual ~Animal();
	virtual void Speak() = 0;//순수 가상함수 : 구현체가 없는 멤버함수, 파생클래스가 구현해야함.
private:
	int mAge;
};
//Cat.h
class Cat : public Animal
{
public:
	~Cat();
	void Speak();
private:
	char* mName;
};
```

# 인터페이스

- c++은 자체적으로 인터페이스를 지원하지않음
- 순수 추상 클래스를 사용해서 Java의 인터페이스 흉내
    - 순수 가상 함수만 가짐
    - 멤버 변수는 없음//회사에따라서 멤버변수 안겹치게 선언하는곳도있음.

```c++
// IFlyable.h
class IFlyable
{
public:
	virtual void Fly() = 0;
};
//IWalkable.h
class IWalkable
{
public:
	virtual void Walk() = 0;
};
class Bat : public IFlyable, public IWalkable
{
public:
	void Fly();
	void Walk();
};
class Cat : public IWalkable
{
public:
	void Walk();
};
```

# 명시적(Explicit) 캐스팅

- c++ 캐스팅
    - static_cast
    - const_cast
    - dynamic_cast
    - reinterpret_cast

### static_cast

```c++
Animal* myPet = new Cat(2, "Coco");

Cat* myCat = static_cast<Cat*>(myPet);

Dog* myDog = static_cast<Dog*>(myPet);   //컴파일되지만 위험, Dog 클래스 멤버를
myDog->GetDogHouseName();                //가지고있지 않기때문에 크래시가 날 수 있다.
```

for example(static_cast cat to dog)

```c++
//animal.cpp
#include "Animal.h"

namespace samples
{
	Animal::Animal(int age)
		: mAge(age)
	{
	}
}

//cat.cpp
#include <iostream>
#include "Cat2.h"

namespace samples
{
	const char* Cat2::mAnimalType = "Cat";

	Cat2::Cat2(int age, const char* name)
		: mAge(age)
	{
		mName = new char[strlen(name) + 1];
		memcpy(mName, name, strlen(name) + 1);
	}

	Cat2::~Cat2()
	{
		delete[] mName;
	}

	// static function
	const char* Cat2::GetType()
	{
		return mAnimalType;
	}
}

//dog.cpp
#include <cstring>

#include "Dog.h"

namespace samples
{
	Dog::Dog(int age, const char* address)
		: Animal(age)
	{
		mHomeAddress = new char[strlen(address) + 1];
		memcpy(mHomeAddress, address, strlen(address) + 1);
	}

	Dog::~Dog()
	{
		delete[] mHomeAddress;
	}

	const char* Dog::GetAddress() const
	{
		return mHomeAddress;
	}
}

//static casting ex
#include <iostream>

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "ObjectPointerCastingExample.h"

using namespace std;

namespace samples
{
	void ObjectPointerCastingExample()
	{
		Animal* pet1 = new Cat(2, "Lulu");
		Animal* pet2 = new Dog(2, "Burnaby");
	
		Cat* cat = static_cast<Cat*>(pet1);
		Dog* dog1 = static_cast<Dog*>(pet2);
		Dog* dog2 = static_cast<Dog*>(pet1);//이부분 cat to dog static casting

		cout << "cat's name : " << cat->GetName() << endl;
		cout << "dog1's address :" << dog1->GetAddress() << endl;

		// prints cat's name instead
		cout << "dog2's address : " << dog2->GetAddress() << endl;
		//함수 리스트 테이블에서 상대적 위치가 같기때문에 이 함수들은 4바이트만큼 떨어진 곳에 있는 
		//const char* 멤버 변수를 반환 즉 두 클래스의 변수 접근 위치가 같은 형태였기때문에 접근가능

		delete pet1;
		delete pet2;
	}
}
```

### reinterpret_cast

비트패턴은 바꾸지않으나 컴파일러가 해석하는 데이터형이 바뀜.

reinterpret_cast 사용법

```jsx

```

### const_cast

```jsx
void WriteLine(char* ptr);//뭔가 별로인 외부 라이브러리

void MyWriteLine(const char* ptr) //우리프로그램
{
	WriteLine(const_cast<char*>(ptr));
}
//써드파티 라이브러리가 const를 제대로 사용하지 않을때
```

### dynamic_cast

RTTI가 꺼져있다면 static_cast 와 똑같이 작동함.

보통 c++ 프로젝트에서는 RTTI를 끄는것이 보통.(성능때문..)

## 캐스팅 규칙

1. 기본적으로 static_cast 를 쓸 것
    1. reinterpret_cast<Cat*> 대신 static_cast<Cat*>
        1. 만약 Cat 이 Animal 이 아니라면 컴파일러가 에러를 뱉음.
2. reinterpret_cast를 쓸 것
    1. 포인터와 비포인터 사이의 변환
        1. 정말 해야될 때가 있음(데이터직렬화)
    2. 서로 연관이 없는 포인터 사이의 변환은 그 데이터형이 맞다고 정말 확실할 때만 할것
3. 내가 변경 권한이 없는 외부 라이브러리를 호출할 때만 const_cast를 쓸 것