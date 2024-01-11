#include <iostream>
using namespace std;

class Entity
{
public:
	float X, Y;

	void Move(float xa, float ya)
	{
		X += xa;
		Y += ya;
	}
};

class Player : public Entity
{
public:
	const char* Name;

	void PrintName()
	{
		cout << Name << endl;
	}
};


int main()
{
	Player player;

	player.Name = "Tom";

	player.X = 0;
	player.Y = 0;
	player.Move(5, 5);

	player.PrintName();

	cin.get();
}