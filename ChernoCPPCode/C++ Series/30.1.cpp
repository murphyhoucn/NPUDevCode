#include <iostream>
#include <string>
using namespace std;

class Entity
{
	// int X, Y; // 如果类中定义的变量没有指定visibility，则默认就是private。
private:
	int X;
public:
	Entity()
	{
		X = 0; // right!
	}
};

class Player : public Entity
{
public:
	Player()
	{
		// X = 10; // error!
	}
};
int main()
{
	Entity e;
	// e.X = 10; // error!
	cin.get();
}