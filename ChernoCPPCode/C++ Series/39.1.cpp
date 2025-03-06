#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
	int m_Age;
public:
	Entity(const std::string& name)
		: m_Name(name), m_Age(-1) {}
	Entity(int age)
		: m_Name("Uknown"), m_Age(age) {}
};

int main()
{
	Entity a("Cherno");
	Entity b(22);

	Entity c = Entity("Cherno");
	Entity d = Entity(22);

	Entity e = std::string("Cherno"); // 隐式类型转换
	Entity f = 22; // 隐式类型转换

	std::cin.get();
}