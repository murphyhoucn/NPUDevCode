#include <iostream>
using namespace std;

void IncreaseValue(int* value)
{
  (*value)++; // 这里要考虑多个运算符号的运算先后顺序
}
int main()
{
  int a = 5;
  IncreaseValue(&a);
  cout << "a = " << a << endl;
  cin.get();
}

// a = 6

// 使用指针的方法，传到IncreaseValue函数中的不是变量a的值，而是变量a的地址。
// 使用*value解引用，把改内存地址上的数值增加，从而改变了变量a的值。