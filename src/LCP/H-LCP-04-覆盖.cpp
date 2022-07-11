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

int main()
{
    // int n = 8, m = 8;
    // vector<vector<int>> broken = {};
    // cout << Solution2().domino(n, m, broken);
    {
        int n = 3, m = 2;
        vector<vector<int>> broken = {{1, 1}, {2, 1}};
        cout << Solution2().domino(n, m, broken);
    }
}