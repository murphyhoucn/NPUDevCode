#include <iostream>
using namespace std;

class Player
{
public: // 公有，表示允许在类外访问这些变量
  int x, y;
  int speed;
};

// 类外的函数
void Move(Player& player, int xa, int ya)
{
  player.x += xa * player.speed;
  player.y += ya * player.speed;
}

int main()
{
  Player player1;

  player1.x = 0;
  player1.y = 0;
  player1.speed = 10;

  Move(player1, 1, -1);

  cout << " x = " << player1.x << endl;
  cout << " y = " << player1.y << endl;

  cin.get();
}

