#include "pre.cpp"

void prev_lt(vector<int> &v, vector<int> &dst)
{
    // 递增栈
    //
    int n = v.size();
    assert(dst.size() == n);
    vector<int> st;
    for (int i = 0; i < n; ++i)
    {
        int x = v[i];
        while (not st.empty() and v[st.back()] >= x)
        {
            st.pop_back();
        }
        if (not st.empty())
        {
            dst[i] = st.back();
        }
        else
        {
            dst[i] = -1;
        }
        st.push_back(i);
    }
}

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        // 即找到当前元素的最近小于当前元素的索引, 和最近小于当前元素的索引. (需要两次遍历)
        // 2 1 5 6 2 3
        // 例如: 5的最近最小分别为: 1, 2; 索引为: 1, 4.
        // 所以5对应高度的面积: (4-1-1)*5
        vector<int> prev_dst(heights.size());
        prev_lt(heights, prev_dst);
        int res = 0;
        // next_lt + 计算
        vector<int> &v = heights; // 别名, 后面的函数是复制的.
        int n = v.size();
        vector<int> st;
        for (int i = n - 1; i >= 0; --i)
        {
            int x = v[i];
            while (not st.empty() and v[st.back()] >= x)
            {
                st.pop_back();
            }
            int w, h = v[i];
            if (not st.empty())
            {
                w = (st.back() - prev_dst[i] - 1);
            }
            else
            {
                w = (n - prev_dst[i] - 1);
            }
            res = max(res, h * w);
            st.push_back(i);
        }
        return res;
    }
};

int main()
{
    vector<int> v = {2, 1, 5, 6, 2, 3};
    cout << Solution().largestRectangleArea(v);
}