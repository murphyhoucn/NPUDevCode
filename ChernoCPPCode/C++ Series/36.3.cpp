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
	{
		m_Name = std::string("Unknown");
		m_Example = Example(100);
	}
};
int main()
{
	const Entity e0;

	std::cin.get();
}

// 输出结果是以下两行
// Created Example!
// Created Example with 100!
// 为什么会分别调用了默认构造函数和有参数的构造函数呢？ 明明在Entity类的构造函数中只使用了m_Example = Example(100);
// 这是因为Example m_Example;调用了一次Example的默认构造函数
// 因此这就相当于把Example实例化了一次然后又实例化了一次，这就造成了性能的浪费。
// 为了解决这个问题，可以使用成员列表的方式来解决。