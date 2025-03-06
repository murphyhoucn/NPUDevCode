#include <iostream>
using namespace std;

void Function()
{
	int i = 0;
	i++;
	cout << "i = " << i << endl;
}

int main()
{
	Function();
	Function();
	Function();

	// cout << "main: i = " << i << endl; // Compilation error
	cin.get();
}
//i = 1
//i = 1
//i = 1

// i是定义在函数Function中的变量，其作用域和生存时间都是在函数Function内部，从main函数中就是访问不到变量i了。