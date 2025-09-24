#include <iostream>

class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

int main()
{
    int num = 16;
    Solution solu;
    std::cout << solu.isPowerOfTwo(num) << std::endl;

    return 0;
}

/*
T: O(1)
S: O(1)
*/

// 位运算