#include <iostream>
using namespace std;

void Function()
{
  static int i = 0;
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
//i = 2
//i = 3

// static声明的i是静态变量，这样的效果和全局变量类似，但是并不能在所有函数中访问到i，i的作用域仅在其所定义的函数内部。