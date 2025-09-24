#include <iostream>

class Solution
{
public:
    int subtractProductAndSum(int n)
    {
        int add = 0, mul = 1;

        while (n)
        {
            add += n % 10;
            mul *= n % 10;
            n /= 10;
        }
        return (mul - add);
    }
};

int main()
{
    int n = 234;
    Solution solu;
    std::cout << solu.subtractProductAndSum(n) << std::endl;

    return 0;
}

/*
时间复杂度：O(logn)，其中 n 为题目给定的数字。
空间复杂度：O(1)，仅使用常量空间。
*/