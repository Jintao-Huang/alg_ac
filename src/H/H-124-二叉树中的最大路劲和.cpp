#include "pre.cpp"

class Solution
{
public:
    int res = INT32_MIN;
    int _maxPathSum(TreeNode *root)
    {
        // 最大路劲和, 本质某节点的两个子树的: 到达子树根的最大值. res = max1+max2+当前节点, max1>0
        //  维护max信息(到达当前子树的根节点的最大值): max=((max1, max2)+当前节点, 0). 0: 当前子树<0
        //  后序遍历树
        if (root == nullptr)
        {
            return 0;
        }
        int max1 = _maxPathSum(root->left);
        int max2 = _maxPathSum(root->right);
        res = max(res, max1 + max2 + root->val);
        return max(max(max1, max2) + root->val, 0);
    }
    int maxPathSum(TreeNode *root)
    {
        _maxPathSum(root);
        return res;
    }
};

int main()
{
    TreeNode *root = str_to_tree("[1,2,3]");
    cout << Solution().maxPathSum(root);
}