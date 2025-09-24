#include <iostream>
#include <vector>

class Solution
{
public:
    int xorOperation(int n, int start)
    {
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans ^= (start + i * 2); // 任何数与0进行异或操作，结果都是该数本身。
        }
        return ans;
    }
};

int main()
{
    int n = 5, start = 0;
    Solution solu;
    std::cout << solu.xorOperation(n, start) << std::endl;

    return 0;
}

/*
时间复杂度：O(n)。这里用一重循环对 n 个数字进行异或。
空间复杂度：O(1)。这里只是用了常量级别的辅助空间。
*/