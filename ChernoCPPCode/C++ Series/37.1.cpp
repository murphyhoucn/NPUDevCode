#include <iostream>
#include <string>

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
	// method 1
	if (s_Level > 5)
		s_Speed = 10;
	else
		s_Speed = 5;

	// method 2
	s_Speed = s_Level > 5 ? 10 : 5;
	std::string rank = s_Level > 10 ? "Master" : "Beginner";

	s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
	// 尽量不要做三运运算符的嵌套，易读性可能会大大降低

	std::cin.get();
}