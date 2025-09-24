#include <iostream>

class Solution {
public:
    int smallestEvenMultiple(int n) {
        return n % 2 == 0 ? n : 2 * n;
    }
};

int main()
{
    int num = 6;
    Solution solu;
    std::cout << solu.smallestEvenMultiple(num) << std::endl;

    return 0;
}

/*
时间复杂度：O(1)。仅需要判断一次 n 的奇偶性。
空间复杂度：O(1)。
*/