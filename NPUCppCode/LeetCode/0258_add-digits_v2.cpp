#include <iostream>

class Solution
{
public:
    int addDigits(int num)
    {
        return (num - 1) % 9 + 1;
    }
};

int main()
{
    int num = 38;
    Solution solu;
    std::cout << solu.addDigits(num) << std::endl;

    return 0;
}

/*
T: O(1)
S: O(1)
*/