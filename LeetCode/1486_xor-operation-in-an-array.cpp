#include <iostream>
#include <vector>

class Solution
{
public:
    int xorOperation(int n, int start)
    {
        std::vector<int> nums(n);
        for (int i = 0; i < n; i++)
        {
            nums[i] = start + 2 * i;
        }

        int res = nums[0];
        for (int i = 1; i < n; i++)
        {
            res ^= nums[i];
        }
        return res;
    }
};

int main()
{
    int n = 5, start = 0;
    Solution solu;
    std::cout << solu.xorOperation(n, start) << std::endl;

    return 0;
}