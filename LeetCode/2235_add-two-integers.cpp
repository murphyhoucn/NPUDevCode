#include <iostream>

class Solution
{
public:
    int sum(int num1, int num2)
    {
        return num1 + num2;
    }
};

int main()
{
    int num1 = 12, num2 = 5;
    Solution solu;
    std::cout << solu.sum(num1, num2) << std::endl;

    return 0;
}

/*
时间复杂度：O(1)。
空间复杂度：O(1)。
*/