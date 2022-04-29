# 인라인함수, static 키워드
### 인라인 함수의 동작 원리

- 사실상 복붙과 비슷
    - 함수 호출하는 대신에

```cpp
//Animal.h
class Animal
{
//...
public:
	Animal(int age);
	
	inline int GetAge() const;//인라인 함수 정의
}

int Animal::GetAge() const
{
	return mAge;//함수단에서 public private 권한체크는 함.
}
//Main.cpp
Cat* myCat = new Cat(2, "Coco");
int age = myCat->GetAge();//이 코드를
int age = myCat.mAge;//이렇게 컴파일러가 바꿔줌
```

```cpp
//매크로와 매우 비슷한 개념
#define SQUARE(x) (x)*(x)

int main()
{
	int result = SQUARE(3)
// -> int result = (3)*(3); 코드로 전처리기가 바꿔줌
}
```

매크로 대신 인라인함수를 쓰는 이유

- 매크로는 디버깅하기 힘듬
    - 콜스택에 함수이름이 안 보임
    - 중단점도 설정 불가능
- 매크로는 범위를 준수하지않음(매크로는 글로벌)

inline 함수 사용시 주의점

- 실제로는 인라인 안될수도있다.
- 컴파일러가 자기 맘대로 아무 함수나 인라인 할 수도 있음.
- 인라인 함수 구현이 헤더파일에 위치해야 함
    - 복붙하려면 컴파일러가 그 구현체를 볼 수 있어야 하기에..
    - 각 cpp 파일은 따로 컴파일 됨
- 간단한 함수에 적합
    - 특히 getter, setter에..

### Vector 클래스 inline 함수 사용하기

```cpp
#pragma once

namespace samples
{
	class Vector
	{
	public:
		Vector();
		Vector(int x, int y);

		inline int GetX() const;//getter setter 인라인하기좋음.
		inline void SetX(int x);

		inline int GetY() const;
		inline void SetY(int y);

		inline bool IsEqual(const Vector& v) const;
		inline Vector Multiply(const Vector& v) const;
		inline Vector Multiply(int multiplier) const;

		inline void Scale(const Vector& v);
		inline void Scale(int multiplier);
//IsEqual, Multiply Scale 등 간단한 수학적인 함수들
//인라인하기 좋은 함수들임.

	private:
		int mX;
		int mY;
	};
//함수 정의부는 Inline 키워드 안붙여도됨.
//함수 정의 역시 컴파일러가 알아야 하기때문에 헤더파일에 있음.
	int Vector::GetX() const
	{
		return mX;
	}

	void Vector::SetX(int x)
	{
		mX = x;
	}

	void Vector::SetY(int y)
	{
		mY = y;
	}

	int Vector::GetY() const
	{
		return mY;
	}

	bool Vector::IsEqual(const Vector& v) const
	{
		return (mX == v.mX && mY == v.mY);
	}

	Vector Vector::Multiply(const Vector& v) const
	{
		Vector result(mX * v.GetX(), mY * v.GetY());

		return result;
	}

	Vector Vector::Multiply(int multiplier) const
	{
		Vector result(mX * multiplier, mY * multiplier);

		return result;
	}

	void Vector::Scale(const Vector& v)
	{
		mX *= v.mX;
		mY *= v.mY;
	}

	void Vector::Scale(int multiplier)
	{
		mX *= multiplier;
		mY *= multiplier;
	}
}
```

# Static 키워드

- 범위(scope)의 제한을 받는 전역 변수

### extern 키워드

- 다른 파일의 전역변수에 접근을 가능케 해 줌

```cpp
//ExternTest.h
extern int globalValue;

void IncreaseValue();

//Main.c
#include "ExternTest.h"

int main()
{
	printf("%d", globalValue);
	//...
}
```

### C 스타일 static

```cpp
//StaticTest.h
extern int globalValue;

void IncreaseValue();

//StaticTest.cpp
#include "StaticTest.h"

static int globalValue = 2;

void IncreaseValue()
{
	globalValue++;
}

//Main.cpp
#include "StaticTest.h"

int main()
{
	//링커 에러
	printf("%d", globalValue);
	return 0;
}
```

### 정적 멤버 변수

- 클래스당 하나의 copy 만 존재
- 개체의 메모리 레이아웃의 일부가 아님
- 클래스 메모리 레이아웃에 포함
- exe파일 안에 필요한 메모리가 잡혀있음
    - 컴파일러가 이 변수의 인스턴스가 몇 개 존재해야하는지 알기에..

### 정적 멤버 변수 베스트 프랙티스

- 함수안에서 정적 변수를 넣지 말 것
    - 클래스 안에 넣을 것
- 전역변수 대신 정적 멤버변수를 쓸 것
    - 범위를 제한하기 위해
- C스타일의 정적변수를 쓸 이유가 이제 없음
    - c++ 식으로 클래스안에만 정적변수를 넣을경우 필요x

### 정적 멤버 함수

- 논리적인 범위에 제한 된 전역 함수
- 해당 클래스의 정적 멤버에만 접근 가능
- 개체가 없이도 정적 함수를 호출할 수 있음.

정적멤버함수 예시

```cpp
#pragma once

namespace samples
{
	class Math
	{
	public:
		static int Ceil(float value);
		static int Floor(float value);
		static float Power(float value, float power);
		static int Round(float value);
		static float Square(float value);

	private:
		Math() {};
//누군가 Math 개체를 만들지 못하게 하기 위해서 private에정의하면
new Math 하더라도 컴파일에러가남

	};
}
```

```cpp
#include <iostream>
#include "Math.h"

namespace samples
{
	int Math::Ceil(float value)
	{//static_cast float to int 는 소수점을 버림.
		int intValue = static_cast<int>(value);
		if (value == static_cast<float>(intValue))
		{
			return intValue;
		}
		
		return intValue + 1;	
	}

	int Math::Floor(float value)
	{
		return static_cast<int>(value);
	}

	float Math::Power(float value, float power)
	{
		return pow(value, power);
	}

	int Math::Round(float value)
	{
		return static_cast<int>(value + 0.5f);
	}

	float Math::Square(float value)
	{
		return value * value;
	}
}
```