#include "pre.cpp"

class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        // 使用dp算法来解决. 戳气球的反方向.
        // dp[i][j]: 从[i..j]含j, 的最大数量
        // [3,1,5,8]
        // [1,3,1,5,8,1].
        // 规定: 不能戳最边的两个气球, 即1,1
        // 所以要戳5, 则1*5*1+1,3,1,5的dp值+5,8,1的dp值
        // 1. 先戳8: 1,3,1,5,8; 1,8; 1*8*1
        // 2. 戳3: 1,3; 3,1,5,8; 1*3*8
        // 3. 戳5: 3,1,5; 5,8; 3*5*8
        // 4. 戳1: 3,1; 1,5; 3*1*5
        // 我们使用的dp使用[lo..hi], 闭区间, dp[i][i+1]=0;
        // dp: n*n
        // dp[i][j] = max(dp[i][k]+dp[k][j]+xi*xk*xj)
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));
        // l从2开始, 直到n
        for (int l = 2; l <= n; ++l)
        {
            // 0,1. l=2, i=0, n=2
            for (int i = 0; i <= n - l; ++i)
            {
                int j = i + l - 1;
                if (l == 2)
                {
                    dp[i][j] = 0;
                    continue;
                }
                for (int k = i + 1; k <= j - 1; ++k)
                {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main()
{
    vector<int> nums = {3, 1, 5, 8};
    cout << Solution().maxCoins(nums);
}
