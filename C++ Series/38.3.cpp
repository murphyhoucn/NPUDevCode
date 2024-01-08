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
	Entity* e;

	{
		Entity* entity = new Entity("Cherno");
		e = entity; // 这里只是复制的entity对象的地址
		std::cout << "1. " << entity->GetName() << std::endl;
	}

	std::cout << "2. " << e->GetName() << std::endl;

	std::cin.get();
	delete e;
}

/*
程序输出内容如下：
1. Cherno
2. Cherno
*/