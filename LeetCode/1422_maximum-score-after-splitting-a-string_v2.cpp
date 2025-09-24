#include <iostream>
#include <string>

class Solution
{
public:
    int maxScore(std::string s)
    {
        int max_score = 0;

        for (int i = 0; i < s.length() - 1; i++)
        {
            int count_score = 0;
            for (int j = 0; j < s.length(); j++)
            {
                if (j <= i && s[j] == '0')
                    count_score++;
                else if (j > i && s[j] == '1')
                    count_score++;
            }
            max_score = count_score > max_score ? count_score : max_score;
        }

        return max_score;
    }
};

int main()
{
    std::string s = "011101";
    Solution solu;

    std::cout << solu.maxScore(s) << std::endl;

    return 0;
}

/*
T: O(n^2)
S: O(1)

效率不好！
*/