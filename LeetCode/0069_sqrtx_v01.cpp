#include <iostream>

class Solution 
{
public:
	int mySqrt(int x) 
	{
		if (x == 0 || x == 1) { return x; }

		long int n = 1;
		while (n * n <= x) { n++; }
		return n - 1;
	}
};

int main()
{
	int x = 2147395600;
	Solution solu;
	std::cout << solu.mySqrt(x);
}