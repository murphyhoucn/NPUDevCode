#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<double> convertTemperature(double celsius) {
        return {celsius + 273.15, celsius * 1.80 + 32.00};
    }
};

int main()
{
    double c = 36.50;
    Solution solu;
    std::cout << solu.convertTemperature(c)[0] << ' ' << solu.convertTemperature(c)[1] << std::endl;
    return 0;
}

/*
时间复杂度：O(1)。
空间复杂度：O(1)。
*/