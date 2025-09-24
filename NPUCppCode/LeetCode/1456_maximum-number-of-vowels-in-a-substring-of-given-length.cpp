#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    int maxVowels(std::string s, int k)
    {
        int ans = 0, vowels = 0;
        for (int i = 0; i < s.length(); i++)
        {
            // 1. 进入窗口
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
                vowels++;

            // 不够k的长
            if (i < k - 1)
                continue;

            // 2. 更新
            ans = std::max(ans, vowels);

            // 3. 离开窗口
            char out = s[i - k + 1];
            if (out == 'a' || out == 'e' || out == 'i' || out == 'o' || out == 'u')
                vowels--;
        }

        return ans;
    }
};

int main()
{
    std::string s = "abciiidef";
    int k = 3;
    Solution solu;
    std::cout << solu.maxVowels(s, k) << std::endl;

    return 0;
}

/*
定长窗口滑动
T: O(n)
S: O(1)
*/