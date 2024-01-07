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
	explicit Entity(int age)
		: m_Name("Uknown"), m_Age(age) {}
};

int main()
{
	Entity a("Cherno");
	Entity b(22);

	Entity c = Entity("Cherno");
	Entity d = Entity(22);

	Entity e = std::string("Cherno");
	Entity f = (Entity)22;

	std::cin.get();
}