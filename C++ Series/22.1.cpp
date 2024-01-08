#include <iostream>
using namespace std;

struct Entity
{
	int num;

	void Print()
	{
		cout << num << endl;
	}
};

int main()
{
	Entity e1;
	e1.num = 2;

	Entity e2;
	e2.num = 5;

	cout << e1.num << endl; // 2
	cout << e2.num << endl; //5

	cout << &(e1.num) << endl; // 008FFBC4
	cout << &(e2.num) << endl; // 008FFBB8

	cin.get();
}