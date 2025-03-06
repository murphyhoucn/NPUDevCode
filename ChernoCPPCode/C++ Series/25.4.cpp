#include <iostream>
using namespace std;

class Entity
{
public:
	float X, Y;

	Entity(float x, float y)
	{
		X = x;
		Y = y;
	}
	void Print()
	{
		cout << X << ", " << Y << endl;
	}
};

int main()
{
	Entity e(5.0f, 6.0f);
	cout << e.X << ", " << e.Y << endl;
	e.Print();

	cin.get();
}