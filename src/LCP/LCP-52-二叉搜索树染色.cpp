
#include "pre.cpp"

class Solution
{
public:
    int getNumber(TreeNode *root, vector<vector<int>> &ops)
    {
        // 1. 先将搜索树变为数组, 建立ST
        // 2. st使用0: 蓝色, 1: 红色.
        // 3 使用mapper, 将数字 -> 索引.
        // 4. 按ops的顺序进行update
        vector<int> v;
        bst_to_vector(root, v);
        int ops_len = ops.size();
        unordered_map<int, int> mapper;
        int v_len = v.size();
        vector<int> res(v_len);
        // mapper
        for (int i = 0; i < v_len; ++i)
        {
            mapper[v[i]] = i;
        }

        // st
        SegmentTree st(res, false);
        for (int i = 0; i < ops_len; ++i)
        {
            vector<int> &o = ops[i];
            int val = o[0], r1 = mapper[o[1]], r2 = mapper[o[2]];
            st.update(r1, r2, val);
        }
        return st.sum_range(0, v_len - 1);
    }
};

int main()

{
    TreeNode *root = str_to_tree("[2,1,3]");
    vector<vector<int>> ops;
    str_to_matrix("[[0,1,2],[1,2,3]]", ops);
    cout << Solution().getNumber(root, ops) << '\n';
    // 
    root = str_to_tree("[1,null,2,null,3,null,4,null,5]");
    str_to_matrix("[[1,2,4],[1,1,3],[0,3,5]]", ops);
    cout << Solution().getNumber(root, ops) << '\n';
}