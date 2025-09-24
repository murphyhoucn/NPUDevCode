#include <iostream>
#include <vector>

class Solution
{
public:
    bool isUgly(int n)
    {
        if (n <= 0)
            return false;

        std::vector<int> factors = {2, 3, 5};
        for (int factor : factors)
        {
            while (n % factor == 0)
            {
                n /= factor;
            }
        }
        return n == 1;
    }
};

int main()
{
    int num = 45;
    Solution solu;
    std::cout << solu.isUgly(num) << std::endl;

    return 0;
}

/*
T: O(logn)
S: O(1)
*/
