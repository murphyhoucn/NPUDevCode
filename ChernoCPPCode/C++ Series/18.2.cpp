#include <iostream>
using namespace std;

class Player
{
public: // 公有，表示允许在类外访问这些变量
  int x, y;
  int speed;

  // 在类内定义函数
  void Move(int xa, int ya) // 类内的函数我们叫它为"方法"（methods）
  {
    x += xa * speed;
    y += ya * speed;
  }
};


int main()
{
  Player player1;

  player1.x = 0;
  player1.y = 0;
  player1.speed = 10;

  player1.Move(1, -1);

  cout << " x = " << player1.x << endl;
  cout << " y = " << player1.y << endl;

  cin.get();
}