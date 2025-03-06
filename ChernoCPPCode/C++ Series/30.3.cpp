#include <iostream>
#include <string>
using namespace std;

class Entity
{
public:
	int X;
	void Print() {}
public:
	Entity()
	{
		X = 0; // right!
		Print(); // right!
	}
};

class Player : public Entity
{
public:
	Player()
	{
		X = 10; // right!
		Print(); // right!
	}
};


int main()
{
	Entity e;
	e.X = 10; // right!
	e.Print(); // right!
	cin.get();
}