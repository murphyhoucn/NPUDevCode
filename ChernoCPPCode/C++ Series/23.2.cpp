#include <iostream>
using namespace std;

int i = 0;

void Function()
{
  i++;
  cout << "i = " << i << endl;
}

int main()
{
  Function();
  Function();
  Function();

  cout << "main: i = " << i << endl;
  cin.get();
}

// i = 1
// i = 2
// i = 3
// main: i = 3

// i定义在了函数外部，所以是个全局变量，其作用域和生存时间都是在整个程序中，这样就可以在main函数中访问到了i。