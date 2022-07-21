
#include "pre.cpp"
class Solution
{
public:
    void _board_to_res(vector<int> &board, vector<string> &res)
    {
        int n = board.size();
        for (int i = 0; i < n; ++i)
        {
            string &s = res[i];
            for (int j = 0; j < n; ++j)
            {
                if (board[i] == j)
                {
                    s.push_back('Q');
                }
                else
                {
                    s.push_back('.');
                }
            }
        }
    }
    // 回溯的优化. 不需要一个个格子遍历, 因为一行只可能选一个位置, 所以选后, 可以直接调到下一行. (以行为回溯单位, 而不是格子)
    void _backtrace(int i, vector<int> &board, // board: 每行放置的位置
                    vector<bool> &cols, vector<bool> &rd, vector<bool> &ld,
                    vector<vector<string>> &res)
    {
        // 遍历每个格子, 并判断是否能设置皇后
        // 如果可以则下一个, 如果不行则回溯
        int n = cols.size();
        if (i == n)
        {
            // 满足
            vector<string> tmp(n);
            _board_to_res(board, tmp);
            res.emplace_back(move(tmp));
            return;
        }
        // 放
        for (int j = 0; j < n; ++j)
        {
            int rd_idx = i - j + n - 1, ld_idx = i + j;
            if (not(cols[j] or rd[rd_idx] or ld[ld_idx]))
            {
                board[i] = j;
                cols[j] = true;
                rd[rd_idx] = true;
                ld[ld_idx] = true;
                _backtrace(i + 1, board, cols, rd, ld, res);
                cols[j] = false;
                rd[rd_idx] = false;
                ld[ld_idx] = false;
            }
        }
        // 失败
        return;
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<int> board(n);
        vector<bool> cols(n);       // 代表一列中是否有皇后
        vector<bool> rd(2 * n + 1); // i-j+n-1. i-j in [-(n-1)..n-1]
        vector<bool> ld(2 * n + 1); // i + j
        vector<vector<string>> res;
        _backtrace(0, board, cols, rd, ld, res);
        return res;
    }
};

int main()
{
    int n = 4;
    cout << Solution().solveNQueens(4);
}