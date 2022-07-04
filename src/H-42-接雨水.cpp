#include "pre.cpp"
class Solution
// DP
{
public:
    int trap(vector<int> &height)
    {
        // 要接雨水, =min(右边的最高, 左边的最高)-当前高度
        // 所以只需要求某索引的左右最高地即可.
        int n = height.size();
        vector<int> lv(n), rv(n);
        lv[0] = 0;
        rv[n - 1] = 0;
        for (int i = 1; i < n; ++i)
        {
            lv[i] = max(lv[i - 1], height[i - 1]);
        }
        for (int i = n - 2; i >= 0; --i)
        {
            rv[i] = max(rv[i + 1], height[i + 1]);
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            res += max(min(lv[i], rv[i]) - height[i], 0);
        }
        return res;
    }
};

class Solution2
// 双指针
// 使用双指针代替DP中的两个数组
{
public:
    int trap(vector<int> &height)
    {
        // 移动左右双指针.
        // [0,1,0,2,1,0,1,3,2,1,2,1]
        //  比较左右两个点, 高的那个会停止, 低的那个会继续.
        //  这使得停止的另一边没有任何一个高于此高的点, 即移动的那边, 需要加上自己方向的最高值即可.
        ///
        int lo = 0, hi = height.size() - 1;
        int res = 0;
        int lh_max = 0, rh_max = 0;
        //
        while (lo < hi) // 最高那个(lo==hi): res+=0, 省略;
        {
            // 加了当前值, 才会前进. 所以需要加的范围: [lo..hi]
            if (height[lo] <= height[hi])
            {
                lh_max = max(lh_max, height[lo]);
                res += lh_max - height[lo];
                ++lo;
            }
            else
            {
                rh_max = max(rh_max, height[hi]);
                res += rh_max - height[hi];
                --hi;
            }
        }
        return res;
    }
};

class Solution3
// 单调栈
{
public:
    int trap(vector<int> &height)
    {
        // 找某元素(栈顶元素)前面最近大于等于该元素的元素索引(单调栈的栈顶的前一个元素),
        //  递减栈
        //  后面最近大于该元素的元素索引(弹出时i)
        // 若当前元素大于等于栈顶元素, 则不断弹出栈, 直到无法弹出. 最后更新res, 加入栈
        //
        int n = height.size();
        vector<int> stack; // 存索引
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            int x = height[i];
            while (not stack.empty() and x > height[stack.back()])
            {

                int curr = stack.back();
                stack.pop_back();
                if (not stack.empty())
                {
                    int lo = stack.back();
                    int w = i - lo - 1;
                    int h = min(height[i], height[lo]) - height[curr];
                    res += w * h;
                }
            }
            stack.push_back(i);
        }
        return res;
    }
};
int main()
{
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << Solution().trap(height) << '\n';
    cout << Solution2().trap(height) << '\n';
    cout << Solution3().trap(height) << '\n';
}