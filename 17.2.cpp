#include <iostream>
using namespace std;

void IncreaseValue(int value)
{
  value++;
}
int main()
{
  int a = 5;
  IncreaseValue(a);
  cout << "a = " << a << endl;
  cin.get();
}

// a = 5

// value的数值增加了，但这里的value只是形式参数，value的值的改变并不会影响实际参数a的数值。