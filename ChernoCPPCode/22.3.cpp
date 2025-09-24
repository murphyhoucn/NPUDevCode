#include <iostream>
using namespace std;

struct Entity
{
	static int num;

	void Print()
	{
		cout << num << endl;
	}
};

int Entity::num;

int main()
{
	Entity e1;
	Entity::num = 2;

	Entity e2;
	Entity::num = 5;

	cout << Entity::num << endl; // 5
	cout << Entity::num << endl; // 5

	cout << &(Entity::num) << endl; // 00BCA138
	cout << &(Entity::num) << endl; // 00BCA138

	cin.get();
}