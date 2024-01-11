#include <iostream>
#include <string>

struct Vector3
{
	float x, y, z;

	Vector3()
		:x(10.0f), y(11.0f), z(12.0f) {}
};

int main()
{
	int value = 5;
	int array[5];
	for (int i = 0; i < 5; i++)
	{
		array[i] = i;
	}
	Vector3 vector;

	int* hvalue = new int;
	*hvalue = 5;
	int* harray = new int[5];
	for (int i = 0; i < 5; i++)
	{
		harray[i] = i;
	}
	Vector3* hvector = new Vector3();

	delete hvalue;
	delete[] harray;
	delete hvector;

	std::cin.get();
}