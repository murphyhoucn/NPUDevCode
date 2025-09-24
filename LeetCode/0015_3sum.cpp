#include <iostream>
#include <vector>
#include <algorithm>

class Solution{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums){
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        int n = nums.size();
        
        for (int i = 0; i < n - 2; i++)
        {
            int x = nums[i];

            if (i > 0 && x == nums[i - 1]) continue; // 处理相邻的两个x的值是一样的情况
            if (x + nums[i + 1] + nums[i + 2] > 0) break; // 特殊情况优化
            if (x + nums[n - 1] + nums[n - 2] < 0) continue;// 特殊情况优化
                
            int j = i + 1, k = n - 1;

            while (j < k)
            {
                int s = x + nums[j] + nums[k];
                if (s > 0)  k--;
                else if (s < 0) j++;
                else
                {
                    ans.push_back({x, nums[j], nums[k]});

                    j++;
                    while (j < k && nums[j] == nums[j-1]) j ++;// 使用while跳过多个重复的元素
        
                    k--;
                    while (j < k && nums[k] == nums[k+1]) k--;
                }
                
            }
        }

        return ans;
    }
};

int main(){
    Solution solu;
    std::vector<int> numbers = {-1, 1, 2, -1, -4};
    std::vector<std::vector<int>> ans = solu.threeSum(numbers);

    // // 打印矩阵
    // for (size_t i = 0; i < ans.size(); ++i) { // 遍历每一行
    //     for (size_t j = 0; j < ans[i].size(); ++j) { // 遍历行中的每一个元素
    //         std::cout << ans[i][j] << ' '; // 打印元素，后跟一个空格
    //     }
    //     std::cout << std::endl; // 每打印完一行后换行
    // }

    // 打印矩阵
    for (const auto& row : ans)
    {
        for (int val : row)
        {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
    
    return 0;
}

/*
时间复杂度：O(n^2)
空间复杂度：O(1)
*/