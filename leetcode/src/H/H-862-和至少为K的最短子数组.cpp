
#include "pre.cpp"

class Solution
{
public:
    int shortestSubarray(vector<int> &nums, int k)
    {
        // 找和至少为k的最短非空子数组
        // 返回长度
        ///
        // 先计算前缀和. (n+1)
        // 使用滑动窗口计算. 最短
        // 值i..j: s[j+1] - s[i]. 长度: j-i+1
        // 扩张使得和>=k(计算res). 缩减使得和<k
        vector<long long> ps;
        prefix_sum(nums, ps);
        int lo = 0;
        int res = INT32_MAX;
        int n = nums.size(); // i..j
        // 找每个j的最近的i, 使得i..j>k. 即j越小越好. 所以使用递增队列
        return prev_le_k(ps, k);
    }
};

int main()
{
    // vector<int> nums = {2, -1, 2};
    // cout << Solution().shortestSubarray(nums, 3);
    {
        vector<int> nums = {84, -37, 32, 40, 95};
        cout << Solution().shortestSubarray(nums, 167);
    }
}