

#include "pre.cpp"
class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        // 对每个位置+1, 设计一个ufset. +1为外层位置.
        // 遍历每个点, 进行合并.
        // 如果与外层位置在同一集合中, 则不需变换. 否则进行变换
        int r_len = board.size();
        int c_len = board[0].size();
        int n = r_len * c_len;
        UFSet ufset(n + 1);
        // i==0, j==0的两种情况
        for (int i = 0; i < r_len; ++i)
        {
            if (board[i][0] == 'O')
            {
                int p0 = i * c_len;
                ufset.union_ufset(n, p0);
            }
        }
        for (int j = 0; j < c_len; ++j)
        {
            if (board[0][j] == 'O')
            {
                int p0 = j;
                ufset.union_ufset(n, p0);
            }
        }

        for (int i = 0; i < r_len; ++i)
        {
            for (int j = 0; j < c_len; ++j)
            {
                if (board[i][j] == 'O')
                {
                    int p0 = i * c_len + j;
                    //
                    if (j + 1 < c_len)
                    {
                        if (board[i][j + 1] == 'O')
                        {
                            int p1 = p0 + 1;
                            ufset.union_ufset(p0, p1);
                        }
                    }
                    else
                    {
                        ufset.union_ufset(p0, n);
                    }

                    //
                    if (i + 1 < r_len)
                    {
                        if (board[i + 1][j] == 'O')
                        {
                            int p2 = p0 + c_len;
                            ufset.union_ufset(p0, p2);
                        }
                    }
                    else
                    {
                        ufset.union_ufset(p0, n);
                    }
                }
            }
        }
        int p = ufset.find_root(n);
        for (int i = 0; i < r_len; ++i)
        {
            for (int j = 0; j < c_len; ++j)
            {
                int p0 = i * c_len + j;
                if (board[i][j] == 'O' and ufset.find_root(p0) != p)
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

int main()
{
    vector<vector<char>> m = {{'X', 'X', 'X', 'X'},
                              {'X', 'O', 'O', 'X'},
                              {'X', 'X', 'O', 'X'},
                              {'X', 'O', 'X', 'X'}};
    Solution().solve(m);
    cout << m << '\n';
    m = {{'X', 'O', 'X'},
         {'O', 'X', 'O'},
         {'X', 'O', 'X'}};
    Solution().solve(m);
    cout << m << '\n';
}