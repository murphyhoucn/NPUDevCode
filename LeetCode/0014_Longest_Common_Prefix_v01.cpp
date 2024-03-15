#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
	std::string longestCommonPrefix(std::vector<std::string>& strs)
	{
		std::string CommonPrefix = "";

		int MinSize = strs[0].size();
		for (int i = 1; i < strs.size(); i++)
		{
			MinSize = MinSize < strs[i].size() ? MinSize : strs[i].size();
		}

		// std::cout << MinSize << std::endl;
		// std::cout << strs.size() << std::endl;

		int i, j;
		for (j = 0; j < MinSize; j++) //字符串中的每个字符
		{
			for (i = 1; i < strs.size(); i++) //vector中的每个元素
			{
				// std::cout << strs[0][j] << "  " << strs[i][j] << std::endl;
				if (strs[0][j] != strs[i][j]) { return CommonPrefix; }
			}
			CommonPrefix += strs[0][j];
		}
		return CommonPrefix;
	}
};

int main()
{
	std::vector<std::string> Strs = { "flower", "flow", "flight" };
	// std::vector<std::string> Strs = { "dog", "racecar", "car" };
	Solution solution;

	std::cout << solution.longestCommonPrefix(Strs);
}