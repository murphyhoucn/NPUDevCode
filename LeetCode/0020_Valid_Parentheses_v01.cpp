#include <iostream>
#include <string>
#include <stack>

class Solution
{
public:
	bool isValid(std::string s)
	{
		std::stack<char> StackofS;
		char right = '\0';
		char left = '\0';

		for (std::string::iterator it = s.begin(); it != s.end(); it++)
		{
			switch (*it)
			{
			case '(':StackofS.push(*it); break;
			case '{':StackofS.push(*it); break;
			case '[':StackofS.push(*it); break;
			case ')':left = '('; right = *it; break;
			case '}':left = '{'; right = *it; break;
			case ']':left = '['; right = *it; break;
			default:
				break;
			}
			// std::cout << *it << std::endl;

			if (right == *it)
			{
				if (StackofS.empty()) { return false; }
				else
				{
					char tmp = StackofS.top();
					StackofS.pop();
					if (tmp != left) { return false; }
				}
			}

		}
		if (StackofS.empty()) { return true; }
		else { return false; }
	}
};

int main()
{
	std::string S = "()[]{}";
	Solution solution;
	std::cout << solution.isValid(S);

}