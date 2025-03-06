#include <iostream>
#include <string>

template<typename T, int N>
class Array
{
private:
	T m_Array[N];
public:
	int GetSize() const { return N; }
};


int main()
{
	Array<int, 5> array1;
	std::cout << array1.GetSize() << std::endl;

	std::cin.get();
}