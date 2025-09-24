#include <iostream>

class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        return n > 0 && (n & (-n)) == n;
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

位运算
负数n的二进制，把n的二进制按位取反，然后+1

Dec:  4  Bin: (前面全是0)0100
Dec: -4  Bin: (前面全是1)1100
*/