#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
public:
	Entity() : m_Name("Unkown") {}
	Entity(const std::string name) : m_Name(name) {}

	const std::string& GetName() const { return m_Name; }
};

int main()
{
	Entity entity;
	std::cout << entity.GetName() << std::endl;

	Entity entity1("Cherno");
	// Entity entity1 = Entity("Cherno"); // 类型 实例名 = 构造函数(参数)
	std::cout << entity1.GetName() << std::endl;

	std::cin.get();
}