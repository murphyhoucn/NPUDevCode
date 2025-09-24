#include <iostream>
#include <string>

class Solution
{
public:
    std::string toLowerCase(std::string s)
    {
        for (char &ch : s)
        {
            if (ch >= 'A' && ch <= 'Z')
                ch |= 32;
        }

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
大写字母 A - Z 的 ASCII 码范围为 [65,90]：
小写字母 a - z 的 ASCII 码范围为 [97,122]。


时间复杂度：O(n)
空间复杂度：O
*/