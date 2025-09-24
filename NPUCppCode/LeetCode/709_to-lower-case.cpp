#include <iostream>
#include <string>
#include <cctype>

class Solution
{
public:
    std::string toLowerCase(std::string s)
    {
        for (char &ch : s)
            ch = std::tolower(ch);

        return s;
    }
};

int main()
{
    std::string s = "Hello";

    Solution solu;

    std::cout << solu.toLowerCase(s) << std::endl;

    return 0;
}

/*
直接使用API
时间复杂度：O(n)
空间复杂度：O
*/