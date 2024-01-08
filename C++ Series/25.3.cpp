#include <iostream>
using namespace std;

class Entity
{
public:
	float X, Y;

	Entity() //Constructor method的名字和类名相同，没有返回值
	{
		X = 0.0f;
		Y = 0.0f;
	}
	void Print()
	{
		cout << X << ", " << Y << endl;
	}
};

int main()
{
	Entity e;
	cout << e.X << ", " << e.Y << endl;
	e.Print();

	cin.get();
}