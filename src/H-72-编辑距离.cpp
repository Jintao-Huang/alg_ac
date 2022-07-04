
#include "pre.cpp"

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        // 插入w1一个字符等价于删除w2一个字符
        // 有dp[m+1][n+1], m=len(w1), n=len(w2)
        //  dp[0][j]=j; dp[i][0]=i;
        //  若w1[i]==w2[j]: dp[i][j] = dp[i-1][j-1]
        //  若不等, dp[i][j]=min(删w2: dp[i][j-1], 删w1: dp[i-1][j], 替换: dp[i-1][j-1]) +1
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; ++i)
        {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j)
        {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                int im = i - 1, jm = j - 1;
                if (word1[im] == word2[jm])
                {
                    dp[i][j] = dp[im][jm];
                }
                else
                {
                    dp[i][j] = min(min(dp[i][jm], dp[im][j]), dp[im][jm]) + 1;
                }
            }
        }
        return dp[m][n];
    }
};

int main()
{
    string word1 = "horse", word2 = "ros";
    cout << Solution().minDistance(word1, word2);
}