#include <iostream>

class Solution
{
public:
    int addDigits(int num)
    {
        while (num / 10)
        {
            int sum = 0;
            while (num > 0)
            {
                sum += num % 10;
                num /= 10;
            }
            num = sum;
        }

        return num;
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
T: O(log num)
S: O(1)
*/