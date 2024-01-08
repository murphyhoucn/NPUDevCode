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
};

int main()
{
	Entity e;
	cout << e.X << ", " << e.Y << endl;  // linking error
	e.Print();

	cin.get();
}
// error C4700: uninitialized local variable 'e' used