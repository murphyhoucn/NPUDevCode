#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
public:
	Entity()
	{
		m_Name = "Unknow";
	}
	Entity(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& GetName() const
	{
		return m_Name;
	}
};
int main()
{
	const Entity e0;
	std::cout << e0.GetName() << std::endl;

	const Entity e1("Cherno");
	std::cout << e1.GetName() << std::endl;

	std::cin.get();
}