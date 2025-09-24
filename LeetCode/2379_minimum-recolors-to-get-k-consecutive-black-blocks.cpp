#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    int minimumRecolors(std::string blocks, int k)
    {
        int count_w = 0;
        int ans = INT32_MAX;
        for (int i = 0; i < blocks.size(); i++)
        {
            if (blocks[i] == 'W')
                count_w++;
            if (i < k - 1)
                continue;
            ans = std::min(count_w, ans);
            char ch = blocks[i - k + 1];
            if (ch == 'W')
                count_w--;
        }
        return ans;
    }
};

int main()
{
    std::string blocks = "WBBWWBBWBW";
    int k = 7; // 固定窗口的尺寸是7

    // 计算固定窗口中，W的最小次数
    Solution solu;
    std::cout << solu.minimumRecolors(blocks, k) << std::endl;

    return 0;
}

/*
定长窗口滑动
T: O(n)
S: O(1)
*/