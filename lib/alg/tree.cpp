
#ifndef _TREE
#define _TREE
#include "../build_ds.cpp"
#include "../load_modules.cpp"
void bst_to_vector(TreeNode *tn, vector<int> &res)
{
    if (tn == nullptr)
    {
        return;
    }
    bst_to_vector(tn->left, res);
    res.push_back(tn->val);
    bst_to_vector(tn->right, res);
}
// int main()
// {
//     TreeNode *root = str_to_tree("[1,null,2,null,3,null,4,null,5]");
//     vector<int> res;
//     bst_to_vector(root, res);
//     cout << res;
// }
#endif