#include "pre.cpp"

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        // 使用动态规划解决
        // 定义二维数组dp[m][n]. m=len(s)+1, n=len(p)+1
        // aa, a比较. 则如果s[1] == p[0], 则dp[2][1] = dp[1][0]
        // aa, a*比较. 如果p[1]=='*' and s[1]==p[0], 则dp[2][2] = dp[1][2]
        // a, aa*比较. 如果p[2]=='*', 则dp[1][3] = dp[1][1]
        // dp[0][0]是true, dp[1..][0]为false. dp[0][1..]
        // dp[0][0], 0是开区间, 代表""
        int m = s.size() + 1, n = p.size() + 1;
        vector<vector<bool>> dp(m, vector<bool>(n));
        // 初始化
        dp[0][0] = true;
        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = false;
        }
        //
        for (int i = 0; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                int im = i - 1, jm = j - 1; // for s, p
                if (p[jm] == '*')
                {
                    dp[i][j] = (j - 2 >= 0 ? dp[i][j - 2] : 0) or
                               (im >= 0 and jm - 1 >= 0 and (s[im] == p[jm - 1] or p[jm - 1] == '.') ? dp[i - 1][j] : 0);
                }
                else if ((im >= 0 ? s[im] == p[jm] : false) or p[jm] == '.')
                {
                    dp[i][j] = (i - 1 >= 0 ? dp[i - 1][j - 1] : 0);
                }
                else
                {
                    dp[i][j] = false;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};

int main()
{
    {
        string s = "aa";
        string p = "a";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "aa";
        string p = "a*";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "a";
        string p = "aa*";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "aa";
        string p = "a";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "a";
        string p = "ab*";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "ab";
        string p = ".*";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "aaa";
        string p = "ab*a*c*a";
        cout << Solution().isMatch(s, p);
    }
    {
        string s = "ab";
        string p = "a*";
        cout << Solution().isMatch(s, p);
    }
}