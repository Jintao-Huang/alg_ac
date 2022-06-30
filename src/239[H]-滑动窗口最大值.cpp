
#include "pre.cpp"



class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> dst;
        int n = nums.size();
        prev_k_max(nums, k, dst);
        vector<int> res;
        for (int i = k - 1; i < n; ++i)
        {
            res.push_back(nums[dst[i]]);
        }
        cout << dst;
        return res;
    }
};

int main()
{
    // {
    //     vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    //     int k = 3;
    //     cout << Solution().maxSlidingWindow(nums, k) << '\n';
    // }
    {
        vector<int> nums = {1, -1};
        int k = 1;
        cout << Solution().maxSlidingWindow(nums, k) << '\n';
    }
}
