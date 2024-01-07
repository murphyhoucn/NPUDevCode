#include <iostream>
using namespace std;

void IncreaseValue(int& value) 
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

// a = 6

// int& value = a; 所以value的变化等价于a的变化。