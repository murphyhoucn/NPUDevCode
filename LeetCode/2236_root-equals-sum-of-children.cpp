#include <iostream>

// struct TreeNode {
//     int val; // 节点中存储的数据
//     TreeNode *left; // 指向左子树的指针
//     TreeNode *right; // 指向右子树的指针

//     // 构造函数
//     TreeNode() : val(0), left(nullptr), right(nullptr) {} //这是一个默认构造函数，它将节点的值初始化为0，左子树和右子树指针初始化为nullptr（表示空指针）。
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} //这是一个带参数的构造函数，它将节点的值初始化为x，左子树和右子树指针初始化为nullptr。
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {} //这是一个带参数的构造函数，它将节点的值初始化为x，左子树指针初始化为left，右子树指针初始化为right。
// };

struct TreeNode
{
    int val;
    TreeNode *left, *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {};
};

class Solution
{
public:
    bool checkTree(TreeNode *root)
    {
        return root->val == root->left->val + root->right->val ? true : false;
    }
};

int main()
{
    TreeNode *root = new TreeNode(10, new TreeNode(4), new TreeNode(6));

    Solution solu;
    std::cout << solu.checkTree(root) << std::endl;

    delete root->left;
    delete root->right;
    delete root;

    return 0;
}

/*
时间复杂度：O(1)。
空间复杂度：O(1)。
*/