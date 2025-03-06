#include <iostream>

class Base
{
public:
	Base() { std::cout << "Base Constructor\n"; }
	virtual ~Base() { std::cout << "Base Destructor\n"; } // 标价为virtual
};

class Derived :public Base
{
private:
	int* m_Array;
public:
	Derived() { m_Array = new int[5]; std::cout << "Derived Constructor\n"; } // 只调用构造函数，不调用析构函数的话，就会导致内存泄露
	~Derived() { delete[] m_Array; std::cout << "Derived Destructor\n"; }
};

int main()
{
	std::cout << "-----First:Base" << std::endl;
	Base* base = new Base();
	delete base;

	std::cout << "-----Second:Derived Inherited from Base" << std::endl;
	Derived* derived = new Derived();
	delete derived;
	
	std::cout << "-----Third:Polymorphic" << std::endl;
	Base* poly = new Derived();
	delete poly;

	std::cin.get();
}

/*
-----First:Base
Base Constructor
Base Destructor
-----Second:Derived Inherited from Base
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor
-----Third:Polymorphic
Base Constructor
Derived Constructor
Derived Destructor
Base Destructor
*/