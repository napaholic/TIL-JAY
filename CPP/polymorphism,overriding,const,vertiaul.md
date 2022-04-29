# 연산자 오버로딩,const, 암시적함수 제거방법, 상속, 다형성, 바인딩, 가상함수

### 연산자 오버로딩 제한사항

1. 오버로딩된 연산자는 최소한 하나의 사용자 정의 형을 가져야함

    ```cpp
    Vector operator+(const Vector& rhs) const;
    ```

2. 오버로딩된 연산자는 피연산자 수를 동일하게 유지해야 함

    ```cpp
    Vector vector1;
    
    +vector1; //불가능. + 연산자는 2개의 피연한자를 가짐.
    					// 단, 단항 + 연산자를 오버로딩할 순 있음.
    ```

3. 새로운 연산자 부호를 만들 수 없음

    ```cpp
    Vector operator@(const Vector& rhs) const;//불가능
    ```

4. 오버로딩 불가능한 연산자도 존재 (검색해보면 여러가지있음..)

### 연산자 오버로딩을 남용하지 말 것

```cpp
Vector vector = vector1 << vector2;

Vector Vector::operator<<(const Vector& rhs) const
{
	Vector cross;
	cross.mX = mY * rhs.mZ - mZ * rhs.mY;
	//... 외적계산을 하고앉아있음...
	return cross;
}

이렇게 자신만 알 수 있는(코드를 까봐야지만 알 수 있는동작) 연산자 오버로딩을 만들지말자.. 차라리 함수를 만들자..
```

### 암시적 복사생성자를 없애는 방법

1. 클래스에 딸려오는 기본 함수들
    1. 매개변수 없는 생성자
    2. 복사생성자
    3. 소멸자
    4. 대입(=) 연산자

   위 함수들이 암시적으로 생성안해도 c++언어가 만들어주는 함수임.(그리고 전부 얕은복사..)


a. 암시적 매개변수 없는 생성자 지우는법

```cpp
class Vector
{
public:

private:
	Vector() {}; //예전에는 이런식으로 지웠다고함..
	int mX;
	int mY;
};
//main.cpp
Vector v1; //컴파일에러
```

b. 암시적 복사 생성자 지우는법

```cpp
class Vector
{
public:

private:
	Vector(const Vector& other) {};
	int mX;
	int mY;
};
//main.cpp
Vector v1;
Vector v2(v1); //컴파일 에러
```

c. 암시적 소멸자 지우는법

```cpp
class Vector
{
public:

private:
	~Vector() {};
	int mX;
	int mY;
};
//main.cpp
Vector v1; // 컴파일 에러
Vector* v2 = new Vector();
delete v2; //컴파일에러
```

d. 암시적 operator= 지우는법

```cpp
class Vector
{
public:

private:
	const Vector& operator=(const Vector& rhs);

	int mX;
	int mY;
};

//Main.cpp
Vector v1;
Vector v2 = v1; //컴파일에러
```

### 상속

```cpp
// Animal.cpp
Animal::Animal(int age) : mAge(age) {}

// Cat.cpp
Cat::Cat(int age, const string& name) : Animal(age)
{
	size_t size = strlen(name) + 1;
	mName = new char[size];
	strcpy(mName, name);
}

// main.cpp
Cat* myCat = new Cat(2, "Mew");
```

위와 같은 코드 작성시 메모리는

스택에 mycat 포인터에 주소가 담기고 그 값은 Animal 클래스의 주소 그다음 연이어서 Cat 클래스의 주소가 할당됨

- mycat 변수의 자식 데이터에 접근시 컴파일러가 상속구조를 이미 알기때문에 부모 클래스의 데이터만큼 뛰어넘어서 접근함.
- 부모클래스가 자식클래스보다 앞에 위치하기에 생성자 역시 부모클래스가 먼저 호출되는것.

만약 자식생성자에서 부모생성자를 명시안해주면 부모의 암시적 생성자가 호출되는데 사용자가 특정 생성자만 정의했을경우..

```cpp
// Animal.cpp
Animal::Animal(int age) : mAge(age) {}

// Cat.cpp
Cat::Cat(int age, const string& name)
//암시적으로 Animal()호출하나 Animal.cpp 에는 
//int 값을 매개변수로 받는 생성자만 정의되어있을경우 컴파일에러발생.
{
	size_t size = strlen(name) + 1;
	mName = new char[size];
	strcpy(mName, name);
}

// main.cpp
Cat* myCat = new Cat(2, "Mew");
```

# 다형성

### 다형성을 배우기 전에...

### 멤버함수의 메모리

멤버함수는 컴파일 시에 딱 한번만 메모리에 “할당"됨.(코드섹션)

```jsx
//for example
//main.cpp
myCat->GetName();
	//mov   ecx, dword ptr[myCat] //ecx레지스터에 myCat 포인터를 저장
	//call  Cat::GetName(0A16C7h)

yourCat->GetName();

//Cat.cpp Cat클래스
const char* GetName(Cat* ptr) const  //함수 주소는 0x0A16C7
{
	return ptr->mName;
}
```

### 함수 오버라이딩

c++은 기본적으로 정적바인딩을 한다.

```jsx
//main.cpp
Cat* myCat = new Cat();
myCat->Speak();

mov  ecx, dword ptr[myCat] // myCat 주소를 저장
call Cat::Speak(0AA16C2h)

Animal* yourCat = new Cat();
yourCat->Speak();

mov  ecx, dword ptr[yourCat] // myCat 주소를 저장
call Cat::Speak(0AA16BDh)
```

```jsx
void Speak(Animal* ptr) const //기본주소 0x0AA16BD
{
	//...
}
```

```jsx
void Speak(Cat* ptr) const //기본주소 0x0AA16C2
{
	//...
}
```

c++은 현재 데이터의 형대로 참조

→ virtual 키워드로 해결가능

Java는 모든 것이 기본적으로 가상함수

→ Java 는 final 키워드 통해서 조금 빠르게 가능

c++에서는 자식마다 다르게 동작하게 하고싶다면 virtual 함수를 넣자.

### 가상함수

- 자식 클래스의 멤버함수가 언제나 호출됨
    - 부모의 포인터 또는 참조를 사용 중이더라도
- 동적바인딩
    - 실행 중에 어떤 함수를 호출할지 결정한다
    - 당연히 정적 바인딩보다 느림
- 이를 위해 가상 테이블이 생성됨
    - 모든 가상 멤버함수의 주소를 포함
    - 클래스마다 하나의 가상테이블이 생성됨 //룩업테이블 혹은 점프테이블로도 불림
    - 개체를 생성할 때, 해당 클래스의 가상 테이블 주소가 함께 저장됨

### 동적바인딩 - 가상 멤버함수

run time 에서 Cat = new MyCat(”Coco”) 할당시

| “Coco”의 포인터 |
| --- |
| 2 |
| 가상테이블 주소 : a |

아래 가상테이블, 코드섹션은 컴파일시 생성

| Cat가상 테이블 (주소는 a) | Animal가상테이블 |
| --- | --- |
| Cat::Move()주소 | Animal::Move()주소 |
| Cat::Speak()주소 | Animal::Speak()주소 |

각각 Cat 가상테이블, Animal가상테이블

```jsx
//메모리 코드섹션

//Animal class
void Move(Animal* ptr) const {}
void Speak(Animal* ptr) const {}

//Cat 클래스
void Move(Cat* ptr) const {}  /0xa
void Speak(Cat* ptr) const {}
```