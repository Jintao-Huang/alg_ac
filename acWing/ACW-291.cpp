
#include "pre.cpp"
#include <bits/stdc++.h>
using namespace std;

class Solution
// 状态压缩dp. 求放的种类数
// 时间复杂度: O(n 2^m 2^m)
// 空间复杂度: O(2^m)
// 其中m=min(n,m); n=max(n,m)
{
public:
    long long domino(int n, int m)
    {
        // 横着放: 00; 竖着放: 1;0.
        // 就是说1的下面必须有行, 且为0
        // 下一行的状态由上一行决定.
        // 每一行的状态一共有2**m次个状态
        // 结束状态: dp[n-1][0]. 因为最后一行不能有1. dp表示: 放的种类数.
        if (n < m)
        {
            swap(n, m);
        }
        long long _2m = 1 << m; // 2 ** m
        vector<long long> dp(_2m);
        // 初始化第0行: 遍历所有的可能性. 判断是否合法. 合法则为1, 不合法为0.
        // 不合法情况: 101. 所以1的中间要有偶数个0
        for (long long i = 0; i < _2m; ++i)
        {
            // 遍历每个位置, 如果该位置是1, 判断并重置odd. 如果是0, 则异或odd.
            //  判断: 若出现11中间奇数个0, 则dp置为0. 若遍历到最后都满足, 则置1
            bool odd = true; // 偶数
            for (long long j = 0; j < m; ++j)
            {
                if ((i >> j) & 1)
                { // 这里相当于倒着遍历位置.
                    // 该位置为1
                    if (not odd)
                    { // 奇数
                        dp[i] = 0;
                        break;
                    }
                }
                else
                {
                    odd ^= 1;
                }
            }
            dp[i] = odd;
        }
        // 遍历每一行, 并遍历状态, 并遍历上一行的状态, 如果符合则+1.
        //  符合: 1下必0. 0下随意. 类似于&操作, 若&为1, 则不可
        // 行内规则符合dp[0]的规则. 但多了一些情况. 例如上1下0是可行的. 所以这种情况要当成1
        vector<vector<long long>> dp2(2, vector<long long>(_2m));
        dp2[0] = dp;
        bool idx = false;
        for (int i = 1; i < n; ++i)
        {
            idx ^= 1;
            // 遍历当前行状态
            fill(dp2[idx].begin(), dp2[idx].end(), 0);
            for (long long j = 0; j < _2m; ++j)
            {
                // 遍历上一行状态
                for (long long k = 0; k < _2m; ++k)
                {
                    if ((j & k) or dp[j | k] == 0)
                    {
                        continue;
                    }
                    else
                    {
                        dp2[idx][j] += dp2[!idx][k];
                    }
                }
            }
        }
        return dp2[idx][0]; // 最后一行只能是全0
    }
};

class Solution2
// 轮廓线dp
// 时间复杂度: O(nm 2^m)
// 空间复杂度: O(2^m)
{
public:
    long long domino(int n, int m)
    {
        // 轮廓线: 一个格子的上面的所有右边格子+这个格子的所有左边格子
        // 使用滚动数组优化.
        // dp[pos, s]: 当前位置为pos的状态为s的方案数. s=2^m(代表轮廓线). pos=n*m
        //  这里dp使用状态压缩. 2行交替更新.
        // s: 0: 没放. 1: 放了. 而不是横放竖放. 第一排相当于上一排放满了
        // 如果第一行, 则只能横着放
        ///
        // 随后, 若轮廓线的首位为1, 则可以不放. 若首位为1, 末尾为0: 也可以横放
        // 若轮廓线首位为0, 只能竖着放
        // 然后转移: +=
        if (n < m)
        {
            swap(n, m);
        }
        long long _2m = 1 << m, _2m_m = _2m - 1;
        vector<vector<long long>> dp(2, vector<long long>(_2m));
        bool idx = false;
        dp[idx][_2m_m] = 1;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                idx ^= 1;
                fill(dp[idx].begin(), dp[idx].end(), 0);
                // 遍历上一格子的轮廓线
                for (long long k = 0; k < _2m; ++k)
                {
                    // 不在第0行, 且轮廓线首位位0, 只能竖着放
                    if (i > 0 and (k >> (m - 1) & 1) == 0)
                    {
                        // 竖放. idx: 当前的轮廓线. !idx: 上一格的轮廓线
                        dp[idx][((k << 1) + 1) & _2m_m] += dp[!idx][k];
                    }
                    if (j > 0 and (k >> (m - 1) & 1) == 1 and (k & 1) == 0)
                    {
                        dp[idx][((k << 1) + 3) & _2m_m] += dp[!idx][k]; // 横放
                    }
                    if ((k >> (m - 1) & 1) == 1)
                    {
                        dp[idx][(k << 1) & _2m_m] += dp[!idx][k];
                    }
                }
            }
        }
        return dp[idx][_2m_m]; // 最后一格的后一格的轮廓线全1
    }
};

int main()
{

    freopen("in", "r", stdin);
    int n, m;
    while (cin >> n >> m and n and m)
    {

        cout << Solution().domino(n, m) << '\n';
        cout << Solution2().domino(n, m) << '\n';
    }

    return 0;
}