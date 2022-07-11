#include "pre.cpp"

class Solution
{
public:
    int maxStudents(vector<vector<char>> &seats)
    {
        // 以列是奇/偶数进行二部图的建立
        // 最大独立集=n-最大匹配/最小点覆盖. 由于学生不能坐在#位置
        // 所以最大学生数=cnt- 最小点覆盖
        int n = seats.size(), m = seats[0].size();
        int s = n * m, t = n * m + 1;
        Dinic d(n * m + 2);
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                char ch = seats[i][j];
                int idx = i * m + j;
                if (ch == '#')
                {
                    continue;
                }
                ++cnt;
                // ch == '.'
                if (j % 2 == 0)
                {
                    d.add_edge(s, idx, 1);
                }
                else
                {
                    d.add_edge(idx, t, 1);
                }
                // 4条边
                if (j - 1 >= 0 and seats[i][j - 1] == '.')
                {
                    int idx2 = idx - 1;
                    if (j % 2 == 0)
                    {
                        d.add_edge(idx, idx2, 1);
                    }
                    else
                    {
                        d.add_edge(idx2, idx, 1);
                    }
                }
                if (j + 1 < m and seats[i][j + 1] == '.')
                {
                    int idx2 = idx + 1;
                    if (j % 2 == 0)
                    {
                        d.add_edge(idx, idx2, 1);
                    }
                    else
                    {
                        d.add_edge(idx2, idx, 1);
                    }
                }
                if (i - 1 >= 0)
                {
                    if (j - 1 >= 0 and seats[i - 1][j - 1] == '.')
                    {
                        int idx2 = idx - m - 1;
                        if (j % 2 == 0)
                        {
                            d.add_edge(idx, idx2, 1);
                        }
                        else
                        {
                            d.add_edge(idx2, idx, 1);
                        }
                    }
                    if (j + 1 < m and seats[i - 1][j + 1] == '.')
                    {
                        int idx2 = idx - m + 1;
                        if (j % 2 == 0)
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
        }
        return cnt - d.dinic(s, t);
    }
};

int main()
{
    vector<vector<char>> seats = {
        {'#', '.', '#', '#', '.', '#'},
        {'.', '#', '#', '#', '#', '.'},
        {'#', '.', '#', '#', '.', '#'},
    };
    cout << Solution().maxStudents(seats);
}