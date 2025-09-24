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

int Entity::num; // 定义这些静态变量，让链接器能连接到这些变量

int main()
{
	Entity e1;
	e1.num = 2;

	Entity e2;
	e2.num = 5;

	cout << e1.num << endl; // 5
	cout << e2.num << endl; // 5

	cout << &(e1.num) << endl; // 00BCA138
	cout << &(e2.num) << endl; // 00BCA138

	cin.get();
}