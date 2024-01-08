#include <iostream>
#include <string>

class Entity
{
private:
	std::string m_Name;
	int m_Score;
public:
	Entity()
		: m_Name("Unknown"), m_Score(0)
	{
	}

	Entity(const std::string& name, const int score)
		: m_Name(name), m_Score(score)
	{
		m_Name = name;
	}

	const std::string& GetName() const
	{
		return m_Name;
	}

	const int& GetScore() const
	{
		return m_Score;
	}
};
int main()
{
	const Entity e0;
	std::cout << e0.GetName() << ", " << e0.GetScore() << std::endl;

	const Entity e1("Cherno", 10);
	std::cout << e1.GetName() << ", " << e1.GetScore() << std::endl;

	std::cin.get();
}