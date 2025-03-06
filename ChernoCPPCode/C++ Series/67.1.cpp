#include <iostream>

int main()
{
	struct Union
	{
		union
		{
			float a;
			int b;
		};
	};

	Union u;
	u.a = 2.0f;

	std::cout << u.a << ", " << u.b << std::endl; // 2, 1073741824

	std::cin.get();
}