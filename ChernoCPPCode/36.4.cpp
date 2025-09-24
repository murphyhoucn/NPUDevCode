#include <iostream>
#include <string>

class Example
{
public:
	Example()
	{
		std::cout << "Created Example!" << std::endl;
	}
	
	Example(int x)
	{
		std::cout << "Created Example with " << x << "!" << std::endl;
	}
};
class Entity
{
private:
	std::string m_Name;
	Example m_Example;
public:
	Entity()
		: m_Name("Unkonwn"), m_Example(Example(100)) // m_Example(100)，写成这样的效果也是一样的。
	{
	}
};
int main()
{
	const Entity e0;

	std::cin.get();
}


// 输出结果
// Created Example with 100!