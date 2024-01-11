#include <iostream>

class Base
{
public:
	Base() { std::cout << "Base Constructor\n"; }
	~Base() { std::cout << "Base Destructor\n"; }
};

class Derived :public Base
{
public:
	Derived() { std::cout << "Derived Constructor\n"; }
	~Derived() { std::cout << "Derived Destructor\n"; }
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
Base Destructor
*/