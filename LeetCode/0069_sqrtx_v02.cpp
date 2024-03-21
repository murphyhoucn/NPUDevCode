#include <iostream>
#include <algorithm>

class Solution
{
public:
	int mySqrt(int x)
	{
		if (x == 0 || x == 1) { return x; }
		long int left = 0;
		long int right = x;

		while (left <= right)
		{
			long int mid = left + (right - left) / 2;
			if (mid * mid == x) { return mid; }
			else if (mid * mid < x) { left = mid + 1; }
			else { right = mid - 1; }
		}
		return std::min(left, right);
	}
};

int main()
{
	int x = 2147395600;
	Solution solu;
	std::cout << solu.mySqrt(x);
}