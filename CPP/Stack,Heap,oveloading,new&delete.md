# 스택, 힙, 오버로딩, friend키워드 new/delete, const

### 스택

예약된 로컬 메모리 공간 (일반적으로 1MB 이하) 컴파일 옵션으로 설정가능

함수 호출과 반환이 스택에서 일어남.

단순히 스택포인터를 옮기면서 동작

- 메모리를 할당 및 해제할 필요가 없음
- 스택에 할당된 메모리는 범위를 벗어나면 사라짐
- 변수와 매개변수를 위해 필요한 크기는 컴파일 도중에 알 수 있음

스택에 큰 개체를 많이 넣으면..

- 스택 오버플로우 발생가능.
- 성능이 느려질 수 있음
    - 1MB 할당한다고해서 실제 물리적으로 컴파일하자말자 전부 할당하는게 아니라 OS 단에서 필요할때마다 페이징파일로 디스크에 올려놓고 필요한 부분만 꺼내쓸수있다.

```cpp
void PrintVectors(const Vector& a, const Vector& b)
{
	Vector* result = new Vector; //-> 힙에 할당
	result->mX = a.mX + b.mX;
	result->mY = a.mY + b.mY;
	//... 기타 코드들..
	delete result;
}

void Foo()
{
	PrintVectors(a, b);
}
```

함수안에서 new 키워드로 힙에 생성하는건 안좋은습관.

because

1. 로컬변수로 만들면 데이터 처리도 더 빠름.
2. RAII 원칙에 위배해서 작성할경우 메모리누수가 쉽게 일어날 수 있음.

### 개체 배열

```cpp
vector[] list = new Vector[10]; //java 코드
vector* list = new Vector[10]; //c++코드
```

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/65b967c2-3721-477d-a876-bd39c2d217a4/Untitled.png)

자바는 10개의 벡터포인터가 생성되고 그 포인터배열의 첫번째 주소를 list 가 가리키게 된다.

c++ 은 힙에 정말 10개의 벡터공간이 할당되고 list 는 첫번째 벡터의 주소를 가리키게됨.

### 개체 소멸

```cpp
//java code 
Vector a = new Vector();
//...
// 즉시 메모리를 해제하진않음. 나~중에 가비지컬렉터가 해제함
a = null;
```

```cpp
//c++ code
Vector* a = new Vector;
Vector* list = new Vector[10];
//...

delete a; //메모리가 즉시 해제됨
a = NULL; // 안해도됨
// 하지만  minishell 프로젝트 당시 특정 포인터가 할당되었는 확인할때 
// 위쪽코드에서 할당하고 해제했으나 밑코드에서 if(a) 로만 메모리 할당여부를 판별하면 큰일날 수는 있음.

delete[] list; // []<- 꼭 넣어야됨.
list = NULL;
```

### 멤버변수 초기화

java, c# 은 클래스 초기화시 멤버변수 0으로 알아서 초기화함.

c++ 은 초기화 안함. →성능중시.

### new/delete, malloc()/free() 차이점은 뭘까

1. malloc은 리턴값 자료형이 (void *) 형이다. 하지만 new 는 type safe로 해당 객체에 맞는 포인터로 반환해준다.
2. new 는 초기값 지정이 가능하다,즉 생성자 호출이 가능하다.
3. new 를 통해 객체 생성시 에러가 발생하면 예외처리가 가능하지만 malloc 은 NULL값을 반환한다.
4. malloc 은 realloc 으로 메모리크기를 재조정가능하지만 new 는 이미 할당된크기에 대한 메모리 재조정이 불가능하다.
5. delete 는 소멸자를 호출하지만 free 는 그런 기능이없다.
6. new/delete는 기본적으로 연산자고 malloc/free 는 함수이다, 그러므로 new/delete 는 오버로딩이가능하다.

### 생성자(Constructor)

```cpp
class X
{
	const int mNameSize;
	AnotherClass& mAnother;
	X(AnotherClass& another)
		: mNameSize(20)
		, mAnother(another)
	{
	}
};
```

초기화 리스트

- 멤버 변수를 대입 없이 초기화
- 상수나 참조 변수도 초기화 가능
- 생성과 동시에 초기화

```cpp
class Vector
{
private:
	int mX;
	int mY;
};

void Foo()
{
	Vector a;                
	Vector b(10, 2);//컴파일 에러
}
```

```cpp
class Vector
{
private:
	int mX;
	int mY;
public:
	Vector(int x, int y);
};

void Foo()
{
	Vector a;        //컴파일 에러        
	Vector b(10, 2);//ok
}
```

c++ 은 생성자가 정의되어있을때 기본생성자를 제공하지않음.

### 소멸자

- 개체가 지워질때 호출됨
- java : 자동으로 가비지를 수집하기 때문에 소멸자 없음
- c++ : c++ 클래스는 그 안에서 동적으로 메모리를 할당할 수도 있음
  그런경우 필히 소멸자에서 메모리를 직접 해제해 줘야 한다.

### const란?

```cpp
// const 메서드. 해당 개체 안의 어떠한 것도 바꾸지않음
int GetX() const;
```

### 구조체 vs 클래스

- c++ 에서는 구조체를 클래스처럼 쓸 수 있음
    - 하지만 절대 그러지 말 것
    - 구조체는 c 스타일로 쓰자..

- struct는 순수하게 데이터 뿐이여야 함
    - 사용자가 선언한 생성자나 소멸자 x
    - static이 아닌 private/protected 멤버변수 x
    - 메모리 카피가 가능함
        - memcpy()를 사용해서 struct 를 char[] 로 복사가능


차이는 private public 접근제어자 유무.

### 복사생성자

```cpp
class Vector
{
public:
	Vector(const Vector& other);
private:
	int mX;
	int mY;
};
Vector::Vector(const Vector& other)
	: mX(other.mX)
	, mY(other.mY) // private 멤버변수이지만 같은클래스이기때문에 접근가능
{
}
```

다른 개체를 이용해서 새로운 개체를 초기화

### 암시작 복사 생성자

- 코드에 복사 생성자가 없는경우, 컴파일러가 암시적 복사생성자를 자동생성

```cpp
class Vector
{
private:
	int mX;
	int mY;
};
```

위 코드 컴파일시

```cpp
class Vector
{
public:
	Vector() {}
	Vector(const Vector& other)
		: mX(other.mX)
		, mY(other.mY)
{
}
private:
	//...
};
```

위와같이 컴파일러가 암시적 복사 생성자를 자동생성

### 암시적 복사 생성자

- 암시적 복사 생성자는 얕은복사를 수행.
    - 멤버 별 복사
    - 각 멤버의 값을 복사 함
    - 개체인 멤버변수는 그 개체의 복사 생성자가 호출됨


### 포인터는 얕은 복사

```cpp
ClassRecord::ClassRecord(const int *scores, int count)
	: mCount(count)
{
	mScores = new int[mCount];
	memcpy(mScores, scores, mCount * sizeof(int));
}

//암시적 복사 생성자
ClassRecord::ClassRecord(const ClassRecord& other)
	: mCount(other.mCount)
	, mScores(other.mScores)
{
}

//Main.cpp
ClassRecord classRecord(scores, 5);
ClassRecord* classRecordCopy = new ClassRecord(classRecord);
delete classRecordCopy;
```

위 코드에서 암시적 복사생성자 수행시

메모리상황을 같이 보자면

먼저 classRecordCopy 라는 스택 포인터 공간에 new ClassRecord 주소가 할당된다.(실제 생성된 ClassRecord 클래스는 힙공간에있음.)

새로 생성된 ClassRecord 에 int mCount, int *scores 데이터를 그대로 복사해버리므로 두개의개체가 같은 포인터공간을 가리키게됨

### 사용자가 만든 복사 생성자

- 직접 복사 생성자를 만들어서 깊은 복사를 할 것
    - 포인터 변수가 가리키는 실제 데이터까지도 복사

```cpp
ClassRecord::ClassRecord(const ClassRecord& other)
	:mCount(other.mCount)
{
	mScores = new int[mCount];
	memcpy(mScores, other.mScores, mCount * sizeof(int));
}
```

데이터는 memcpy 로 복사하는것 좋은것같음..

## 함수 오버로딩

```cpp
Vector result = vector1 + vector2;
Vector result = vector1.operator+(vector2);
```

```cpp
Vector Vector::operator+(const Vector& other) const
{
	Vector sum;
	sum.mX = mX + other.mX;
	sum.mY = mY + other.mY;

	return sum;
}
```

### friend  클래스

```cpp
// X.h
class X
{
	friend class Y;
private:
	int mPrivateInt;
};

...
// Y.h
class Y
{
public:
	void Foo(X& x);
};

...
//Y.cpp
void Y::Foo(X& x)
{
	xmPrivateInt += 10;

```

### friend 함수

```cpp
//X.h
class X
{
	friend void Foo(X& x);
private:
	int mPrivateInt;
};

//GlobalFunction.cpp
void Foo(X& x)
{
	x.mPrivateInt += 10;//Ok
}
```

```cpp
//Vector.h
class Vector
{
	friend std::ostream& operator<<(const std::ostream& os, const Vector& rhs);
public:
	//....
private:
//....
};

//Vector.cpp
std::ostream& operator<<(std::ostream& os, const Vector& rhs)
{
	os << rhs.mX << ", " << rhs.mY;
	return os;
}
```

```cpp
Vector operator+(const Vector& rhs) const;
//& 사용이유 : 굳이 클래스 복사를 할 이유가 없기때문.
//const 사용 이유: 클래스의 멤버변수가 바뀌는것도 방지
std::ostream& operator<<(const std::ostream& os, const Vector& rhs);
//ostream이 변경되기때문에 위 상황은 const 빼야됨.
```