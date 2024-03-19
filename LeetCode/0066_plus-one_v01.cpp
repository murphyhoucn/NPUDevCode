#include <iostream>
#include <vector>

class Solution
{
public:
	std::vector<int> plusOne(std::vector<int>& digits)
	{
		for (int i = (int)digits.size() - 1; i >= 0; --i)
		{
			if (digits[i] < 9)
			{
				++digits[i];
				return digits;
			}
			digits[i] = 0;
		}
		digits.insert(digits.begin(), 1);
		return digits;
	}
};

int main()
{
	std::vector<int> Digits = {4, 3, 2, 9};

	Solution solu;
	solu.plusOne(Digits);

	for (int i = 0; i < (int)Digits.size(); i++)
	{
		std::cout << Digits[i] << std::endl;
	}
}