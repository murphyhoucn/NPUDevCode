#include <iostream>
#include <vector>

class Solution
{
public:
    int countGoodTriplets(std::vector<int> &arr, int a, int b, int c)
    {
        int ans_conut = 0;

        for (int i = 0; i < arr.size() - 2; i++)
        {
            for (int j = i + 1; j < arr.size(); j++)
            {
                for (int k = j + 1; k < arr.size(); k++)
                {
                    if ((abs(arr[i] - arr[j]) <= a) && (abs(arr[j] - arr[k]) <= b) && (abs(arr[i] - arr[k]) <= c))
                        ans_conut++;
                }
            }
        }

        return ans_conut;
    }
};

int main()
{
    std::vector<int> arr = {3, 0, 1, 1, 9, 7};
    int a = 7, b = 2, c = 3;

    Solution solu;
    std::cout << solu.countGoodTriplets(arr, a, b, c) << std::endl;

    return 0;
}

/*
暴力解法，嵌套三个for循环
时间：O(n^3)
空间：O(1)
*/