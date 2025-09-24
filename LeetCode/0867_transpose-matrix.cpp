#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> &matrix)
    {
        // matrix.size(): 行数
        // matrix[0].size(): 列数
        std::vector<std::vector<int>> ans(matrix[0].size(), std::vector<int>(matrix.size()));

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                ans[j][i] = matrix[i][j];
            }
        }
        return ans;
    }
};

int main()
{
    Solution solu;

    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    for (auto row : matrix)
    {
        for (auto element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    for (auto row : solu.transpose(matrix))
    {
        for (auto element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

/*
C++中居然没有直接转置矩阵的API？！

T: O(mn)
S: O(mn)

*/