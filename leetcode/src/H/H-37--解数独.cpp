
#include "pre.cpp"

class Solution
{
public:
    bool _backtrace(int i, int j, vector<vector<char>> &board,
                    vector<vector<bool>> &boxes, vector<vector<bool>> &rows, vector<vector<bool>> &cols)
    {
        // 返回: True/False. 表示finished
        // 从左上往右下遍历
        // 每个格子试1-9, 如果不满足, 则试下一个数字. 都不满足则回溯. 如果满足则试下一个格子
        // 9*9的格子

        if (j == 9)
        {
            ++i;
            j = 0;
        }
        if (i == 9)
        {
            return true;
        }
        if (board[i][j] != '.')
        {
            if (_backtrace(i, j + 1, board, boxes, rows, cols))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        //
        for (int k = 1; k <= 9; ++k)
        {
            int box_idx = i / 3 * 3 + j / 3;
            int km = k - 1;
            if (boxes[box_idx][km] or rows[i][km] or cols[j][km])
            {
                continue;
            }
            boxes[box_idx][km] = true;
            rows[i][km] = true;
            cols[j][km] = true;
            board[i][j] = k + '0';
            //
            if (_backtrace(i, j + 1, board, boxes, rows, cols))
            {
                return true;
            }

            //
            boxes[box_idx][km] = false;
            rows[i][km] = false;
            cols[j][km] = false;
            board[i][j] = '.';
        }
        return false;
    }

    void _preprocess(vector<vector<char>> &board,
                     vector<vector<bool>> &boxes,
                     vector<vector<bool>> &rows,
                     vector<vector<bool>> &cols)
    {

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                {
                    continue;
                }
                int km = board[i][j] - '0' - 1;
                int box_idx = i / 3 * 3 + j / 3;
                boxes[box_idx][km] = true;
                rows[i][km] = true;
                cols[j][km] = true;
            }
        }
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        // 代表每个格子, 1-9的visited情况
        vector<vector<bool>> boxes(9, vector<bool>(9)), rows(9, vector<bool>(9)), cols(9, vector<bool>(9));
        _preprocess(board, boxes, rows, cols);
        _backtrace(0, 0, board, boxes, rows, cols);
    }
};

int main()
{
    vector<vector<char>> board(9, vector<char>(9, '.'));
    Solution().solveSudoku(board);
    cout << board;
}