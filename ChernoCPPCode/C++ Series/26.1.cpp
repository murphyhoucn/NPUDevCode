#include <iostream>
using namespace std;

class Entity
{
public:
	float X, Y;

	Entity() // 构造函数
	{
		X = 0.0f;
		Y = 0.0f;
		cout << "Created Entity!" << endl;
	}

	~Entity() // 析构函数
	{
		cout << "Destroyed Entity!" << endl;
	}


	void Print()
	{
		cout << X << ", " << Y << endl;
	}
};

void Function()
{
	Entity e;
	e.Print();
}
int main()
{
	Function();
	cin.get();
}


/*
Created Entity!
0, 0
Destroyed Entity!


E:\userDoc\ChernoDevCPP\NewProject\bin\Win32\Debug\NewProject.exe (process 22128) exited with code 0.
Press any key to close this window . . .
*/