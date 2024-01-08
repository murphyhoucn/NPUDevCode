#include <iostream>
using namespace std;

class Entity
{
public:
	float X, Y;

	void Print()
	{
		cout << X << ", " << Y << endl;
	}

	void Init()
	{
		X = 0.0f;
		Y = 0.0f;
	}
};

int main()
{
	Entity e;
	e.Init();
	cout << e.X << ", " << e.Y << endl;
	e.Print();

	cin.get();
}