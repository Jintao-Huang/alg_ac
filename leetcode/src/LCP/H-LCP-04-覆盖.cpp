#include "pre.cpp"
class Solution
// 超时
{
public:
    int res = 0;
    void bktrace(int n, int m, int i, int j, vector<vector<bool>> &visited, int count)
    {
        if (m == j)
        {
            j = 0;
            i += 1;
        }
        if (n == i)
        {
            res = max(res, count);
            return;
        }
        // 不放
        bktrace(n, m, i, j + 1, visited, count);
        // 横着放
        if (not visited[i][j] and (j + 1 < m and not visited[i][j + 1]))
        {
            visited[i][j] = true;
            visited[i][j + 1] = true;
            bktrace(n, m, i, j + 1, visited, count + 1);
            visited[i][j] = false;
            visited[i][j + 1] = false;
        }

        // 竖着放
        if (not visited[i][j] and (i + 1 < n and not visited[i + 1][j]))
        {
            visited[i][j] = true;
            visited[i + 1][j] = true;
            bktrace(n, m, i, j + 1, visited, count + 1);
            visited[i][j] = false;
            visited[i + 1][j] = false;
        }
    }
    int domino(int n, int m, vector<vector<int>> &broken)
    {
        // 1<=n, m<=8, 所以可以考虑回溯法
        // 每个格子有3种方案: 不放, 横着放, 竖着放
        // 将所有的情况进行遍历, 找到最大的放的个数
        int b_len = broken.size();
        vector<vector<bool>> visited(n, vector<bool>(m));
        for (int i = 0; i < b_len; ++i)
        {
            vector<int> &b = broken[i];
            visited[b[0]][b[1]] = true;
        }

        bktrace(n, m, 0, 0, visited, 0);
        return res;
    }
};

class Solution2
// 二分图最大匹配
{
public:
    inline int hash(int x, int y)
    {
        // m <= 8
        return (x << 4) + y;
    }
    int domino(int n, int m, vector<vector<int>> &broken)
    {
        int s = n * m, t = n * m + 1;
        Dinic d(n * m + 2);
        unordered_set<int> broken_s;
        int b_len = broken.size();
        for (int i = 0; i < b_len; ++i)
        {
            vector<int> &b = broken[i];
            broken_s.insert(hash(b[0], b[1]));
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {

                if (broken_s.count(hash(i, j)))
                {
                    continue;
                }
                //
                int k = (i + j) % 2;
                int idx = i * m + j;
                if (k == 0)
                {
                    d.add_edge(s, idx, 1);
                }
                else
                {
                    d.add_edge(idx, t, 1);
                }
                // 因为对称性, 所以只需要判断右边和下面即可.

                if (i + 1 < n and not broken_s.count(hash(i + 1, j)))
                {
                    int idx2 = idx + m;
                    if (k == 0)
                    {
                        d.add_edge(idx, idx2, 1);
                    }
                    else
                    {
                        d.add_edge(idx2, idx, 1);
                    }
                }

                if (j + 1 < m and not broken_s.count(hash(i, j + 1)))
                {
                    int idx2 = idx + 1;
                    if (k == 0)
                    {
                        d.add_edge(idx, idx2, 1);
                    }
                    else
                    {
                        d.add_edge(idx2, idx, 1);
                    }
                }
            }
        }
        return d.dinic(s, t);
    }
};

class Solution3
// 轮廓线dp
// 时间复杂度: O(nm 2^m)
// 空间复杂度: O(2^m)
{
public:
    int hash(int i, int j)
    {
        // i = broken[0], j = broken[1];
        // 1 <= j <= 8
        return (i << 4) + j;
    }
    int domino(int n, int m, vector<vector<int>> &broken)
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
        unordered_set<int> broken_s;
        int n_broken = broken.size();
        for (int i = 0; i < n_broken; ++i)
        {
            vector<int> &b = broken[i];
            broken_s.emplace(hash(b[0], b[1]));
        }
        // if (n < m)
        // {
        //     swap(n, m);
        // }
        int _2m = 1 << m, _2m_m = _2m - 1;
        // dp[pos][s]: 代表以pos为结束的轮廓线(pos+1的轮廓线)的最多块数
        vector<vector<int>> dp(2, vector<int>(_2m, INT32_MIN));
        bool idx = false;
        dp[idx][_2m_m] = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                idx ^= 1;
                fill(dp[idx].begin(), dp[idx].end(), INT32_MIN);
                int h = hash(i, j);
                // 遍历上一格子的轮廓线
                for (int k = 0; k < _2m; ++k)
                {
                    int p = dp[!idx][k];
                    if (p == INT32_MIN)
                    {
                        continue;
                    }
                    if (broken_s.count(h))
                    {

                        // 不能放
                        int &x = dp[idx][((k << 1) + 1) & _2m_m];
                        x = max(x, p);
                        continue;
                    }

                    // 不在第0行, 且轮廓线首位位0, 只能竖着放
                    if (i > 0 and (k >> (m - 1) & 1) == 0)
                    {
                        // 竖放. idx: 当前的轮廓线. !idx: 上一格的轮廓线
                        int &x = dp[idx][((k << 1) + 1) & _2m_m];
                        x = max(x, p + 1);
                    }
                    if (j > 0 and (k >> (m - 1) & 1) == 1 and (k & 1) == 0)
                    {
                        int &x = dp[idx][((k << 1) + 3) & _2m_m];
                        x = max(x, p + 1); // 横放
                    }
                    // 不放
                    int &x = dp[idx][(k << 1) & _2m_m];
                    x = max(x, p);
                }
            }
        }
        return *max_element(dp[idx].begin(), dp[idx].end()); // 最后一格的后一格的轮廓线全1
    }
};

int main()
{
    // int n = 8, m = 8;
    // vector<vector<int>> broken = {};
    // cout << Solution2().domino(n, m, broken);
    // cout << Solution3().domino(n, m, broken);
    // {
    //     int n = 3, m = 2;
    //     vector<vector<int>> broken = {{1, 1}, {2, 1}};
    //     cout << Solution2().domino(n, m, broken);
    //     cout << Solution3().domino(n, m, broken);
    // }
    {
        int n = 2, m = 3;
        // int n = 3, m = 2;
        vector<vector<int>> broken = {{0, 0}, {0, 1}};
        cout << Solution2().domino(n, m, broken);
        cout << Solution3().domino(n, m, broken);
    }
}