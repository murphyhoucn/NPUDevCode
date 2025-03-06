#include <iostream>
#include <array>

// 用模板传入std::array的size，避免显式调用
template<int T>
void PrintArray(std::array<int, T>& array)
{
    for (int i = 0; i < T; i++)
    {
        std::cout << array[i] << std::endl;
    }
}

int main()
{
	std::array<int, 5> data;

    for (std::array<int, data.size()>::iterator it = data.begin(); it != data.end(); it++)
    {
        *it = 0;
    }

    PrintArray(data);

	std::cin.get();
}