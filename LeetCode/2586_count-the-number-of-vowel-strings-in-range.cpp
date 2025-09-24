#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Solution
{
public:
    int vowelStrings(std::vector<std::string> &words, int left, int right)
    {
        std::unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'}; // hash set
        int count = 0;
        for (int i = left; i < right + 1; i++)
        {
            std::string word = words[i];
            if (vowels.count(word[0]) && vowels.count(word.back()))
                count++;
        }
        return count;
    }
};

int main()
{
    std::vector<std::string> words = {"hey", "aeo", "mu", "ooo", "artro"};
    int left = 1, right = 4;

    Solution solu;
    std::cout << solu.vowelStrings(words, left, right) << std::endl;

    return 0;
}

/*
T: O(n + 5), for循环，遍历hash set
S: O(5), hash set

时间复杂度：O(n+∣Σ∣)，其中 n 是数组 words 的长度，Σ 是元音的集合，在本题中 ∣Σ∣=5。

空间复杂度：O(∣Σ∣)，即为哈希集合需要使用的空间。

*/