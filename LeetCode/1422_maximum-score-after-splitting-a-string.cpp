#include <iostream>
#include <string>

class Solution
{
public:
    int maxScore(std::string s)
    {
        int max_score = 0;
        std::string left;
        std::string right;

        for (int i = 1; i < s.length(); i++)
        {
            left = s.substr(0, i); // [0, i）前闭后开
            right = s.substr(i);   // [i, end）

            // std::cout << "left string:  " << left << std::endl;
            // std::cout << "right string: " << right << std::endl;
            int count_score = 0;
            for (char ch : left)
            {
                if (ch == '0')
                    count_score++;
            }
            for (char ch : right)
            {
                if (ch == '1')
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
S: O(n)

效率不好！
*/