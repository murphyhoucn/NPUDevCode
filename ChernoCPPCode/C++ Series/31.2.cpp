#include <iostream>
#include <array>
using namespace std;

int main()
{
	array<int, 5> array1;

	for (int i = 0; i < array1.size(); i++)
	{
		array1[i] = i;
	}

	cin.get();
}