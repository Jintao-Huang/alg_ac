

//
#ifndef _KNAPSACK
#define _KNAPSACK

#include "../load_modules.cpp"
#include "../io.cpp"

// 背包问题:
// C: 背包容量
// W: 每个物品的重量, 或说成本
// V: 每个物品的价值
// 目标: 返回价值最大的价值数

// 01背包: 物品的个数只有一个.
// 可以不装满, 价值尽可能大的01背包, 一定>=0
int k01(vector<int> &W, vector<int> &V, int C)
{
    // dp[0]=0: 容量为0的背包的最大价值数为0
    // 当出现一个物品时, 可以选择是否加入.
    // 若某物品w=4, v=2
    // 当C=5, dp[5] = max(dp[5], dp[1] + 2)
    // 所以遍历所有的物品, 并且倒着遍历所有的C
    vector<int> dp(C + 1, 0); // 价值至少为0. 可以不装V[i]<0的物品.
    int n = W.size();
    assert(n == V.size());
    for (int i = 0; i < n; ++i)
    {
        // 每个商品只能选一次, 所以需要倒着遍历C
        for (int j = C; j >= 0; --j)
        {
            dp[j] = j - W[i] >= 0 ? max(dp[j], dp[j - W[i]] + V[i]) : dp[j];
        }
    }
    return dp[C];
}
// 必须装满, 价值尽可能大的01背包, 可以为负数.
// 1. dp的初始值为-INF(INT32_MIN), 会选择负数价值的物品. dp[0] = 0
// 2. dp判断语句中, 需要判断dp[j-W[i]]不是-INF, 因为这是没装满的标志, 此条可能性路径依旧为-INF
// 3. 若dp[C]为-INF, 则代表没有可能装满.
///
// 若改为k01_F_min:
// 1. dp初始值: INF(INT32_MAX)
// 2. dp判断语句
// 3. max变min
int k01_F_max(vector<int> &W, vector<int> &V, int C)
{

    vector<int> dp(C + 1, INT32_MIN);
    dp[0] = 0;
    int n = W.size();
    assert(n == V.size());
    for (int i = 0; i < n; ++i)
    {
        for (int j = C; j >= 0; --j)
        {
            dp[j] = (j - W[i] >= 0 and dp[j - W[i]] != INT32_MIN) ? max(dp[j], dp[j - W[i]] + V[i]) : dp[j];
        }
    }
    return dp[C];
}

int k01_F_min(vector<int> &W, vector<int> &V, int C)
{
    vector<int> dp(C + 1, INT32_MAX);
    dp[0] = 0;
    int n = W.size();
    assert(n == V.size());
    for (int i = 0; i < n; ++i)
    {
        for (int j = C; j >= 0; --j)
        {
            dp[j] = (j - W[i] >= 0 and dp[j - W[i]] != INT32_MAX) ? min(dp[j], dp[j - W[i]] + V[i]) : dp[j];
        }
    }
    return dp[C];
}

/// 完全背包: 物品的个数有无数个
// 1. 将C遍历变为正向.
// 完全背包的循环顺序可以先C后n.
int kC(vector<int> &W, vector<int> &V, int C)
{
    vector<int> dp(C + 1, 0);
    int n = W.size();
    assert(n == V.size());

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= C; ++j)
        {
            dp[j] = j - W[i] >= 0 ? max(dp[j], dp[j - W[i]] + V[i]) : dp[j];
        }
    }
    return dp[C];
}

// int main()
// {
//     {
//         vector<int> W{1, 2, 3, 4};
//         vector<int> V{-1, -2, -4, -6};
//         int C = 5;
//         cout << k01(W, V, C) << '\n';
//         cout << k01_F_max(W, V, C) << '\n';
//         cout << k01_F_min(W, V, C) << '\n';
//         cout << kC(W, V, C) << '\n';
//     }
//     {
//         vector<int> W{1, 2, 3, 4};
//         vector<int> V{1, 2, 4, 6};
//         int C = 11;
//         cout << k01(W, V, C) << '\n';
//         cout << k01_F_max(W, V, C) << '\n';
//         cout << k01_F_min(W, V, C) << '\n';
//         cout << kC(W, V, C) << '\n';
//     }
//     // 0
//     // -6
//     // -7
//     // 0
//     // 13
//     // -2147483648
//     // 2147483647
//     // 16
// }

#endif
