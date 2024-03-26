#include <iostream>
#include <vector>
class Solution
{
public:
	void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
	{
		int i = m - 1;
		int j = n - 1;
		int k = m + n - 1;

		while (j >= 0)
		{
			if (i >= 0 && nums1[i] > nums2[j]) { nums1[k--] = nums1[i--]; }
			else { nums1[k--] = nums2[j--]; }
		}
	}
};

int main()
{
	std::vector<int> nums1 = { 1, 2, 3, 0, 0, 0 };
	std::vector<int> nums2 = { 2, 5, 6};

	int m = 3;
	int n = 3;

	Solution solu;
	
	solu.merge(nums1, m, nums2, n);

}