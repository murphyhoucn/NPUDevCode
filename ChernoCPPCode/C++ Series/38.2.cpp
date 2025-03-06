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

void Function()
{
	Entity entity("Cherno");
	int a = 10;
	// a和entity的生命周期仅存在函数function之内，函数结束了之后，变量所占用的内存也就被释放了。
}

int main()
{
	Function();
	// 但我们调用function的时，就为这个函数创建了一个栈结构

	std::cin.get();
}
