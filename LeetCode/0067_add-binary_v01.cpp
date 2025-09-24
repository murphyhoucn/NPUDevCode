#include <iostream>
#include <string>

class Solution
{
public:
	std::string addBinary(std::string a, std::string b)
	{
		std::string ans;
		int carry = 0;
		int i = (int)a.length() - 1;
		int j = (int)b.length() - 1;

		while (i >= 0 || j >= 0 || carry)
		{
			if (i >= 0) { carry += a[i--] - '0'; }
			if (j >= 0) { carry += b[j--] - '0'; }

			ans += carry % 2 + '0';
			carry /= 2;
		}
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
};

int main()
{
	std::string A = "1010";
	std::string B = "1011";
	
	Solution solu;

	std::cout << solu.addBinary(A, B) << std::endl;

}