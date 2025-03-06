#include <iostream>

int main()
{
	// 1-d array
	int* array = new int[50];

	delete[] array;


	// 2-d array (50*10)
	int** a2d = new int* [50];
	for (int i = 0; i < 50; i++)
		a2d[i] = new int[10];

	for (int i = 0; i < 50; i++)
		delete[] a2d[i];
	delete[] a2d;

	// 3-d array (50*10*3)
	int*** a3d = new int** [50];
	for (int i = 0; i < 50; i++)
	{
		a3d[i] = new int* [10];

		for (int j = 0; j < 10; j++)
		{
			a3d[i][j] = new int[3];
		}
	}

	std::cin.get();
}