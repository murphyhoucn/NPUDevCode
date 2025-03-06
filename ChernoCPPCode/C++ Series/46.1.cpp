#include <iostream>
#include <string>

class Entity
{
public:
	void Print() const{ std::cout << "Hello!" << std::endl; }
};

int main()
{
	Entity e;
	e.Print();

	Entity* ptr = &e;
	(*ptr).Print(); // 考虑运算符优先级

	Entity* ptr1 = &e;
	Entity& entity = *ptr1;
	entity.Print();

	Entity* ptr2 = &e;
	ptr2->Print();

	std::cin.get();
}