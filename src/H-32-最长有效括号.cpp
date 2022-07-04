#include "pre.cpp"

class Solution
// Ot(N^2)
{
public:
    int longestValidParentheses(const string &s)
    {
        // 暴力法, 两层循环.
        // 使用i, j进行遍历. [i..j), 开区间.
        //  i==j时, dp[i][j] = 0, 代表平衡, 更新res.
        //  ')', 则dp=-1, 代表匹配失败, 则break内层循环.
        //  '(', 则dp=1, 代表缺少一个), 继续匹配.

        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            int count = 0;
            for (int j = i; j < n; ++j)
            {
                if (s[j] == '(')
                {
                    ++count;
                }
                else
                {
                    --count;
                }
                if (count < 0)
                {
                    break;
                }
                if (count == 0)
                {
                    res = max(res, j - i + 1);
                }
            }
        }
        return res;
    }
};

class Solution2
// Ot(N)
{
public:
    int longestValidParentheses(const string &s)
    {
        // 使用栈的方法, 栈中存索引.
        // 当遇到(, 则入栈, 若遇到), 则出栈, 并更新res
        // 并且若)的个数大于(的个数, 即empty, 则不做操作.
        // ()()的情况, 需要一个一维的dp数组.
        int res = 0;
        int n = s.size();
        vector<int> dp(n);
        vector<int> stack; // 存索引
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '(')
            {
                stack.push_back(i);
            }
            else if (not stack.empty())
            {
                int lo = stack.back();
                stack.pop_back();
                dp[i] = (i - lo + 1) + (lo - 1 >= 0 ? dp[lo - 1] : 0);
                res = max(res, dp[i]);
            }
            else
            {
                // 保持代码完整性.
                // s[i] == '(' and stack.empty()
            }
        }
        return res;
    }
};

class Solution3
// Ot(N)
// 去掉dp数组的存储量.
{
public:
    int longestValidParentheses(string &s)
    {
        // 在栈第一位中存放哨兵'(', 代表匹配的开始位置.
        vector<int> stack = {-1};
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '(')
            {
                stack.push_back(i);
            }
            else
            {
                stack.pop_back();
                if (stack.empty())
                {
                    stack.push_back(i);
                }
                else
                {
                    res = max(res, i - stack.back());
                }
            }
        }
        return res;
    }
};

class Solution4
// Ot(N)
// DP
{
public:
    int longestValidParentheses(string &s)
    {
        // 创建一维的dp数组, 代表以某索引结束的括号长度
        //  (...)(); (...)((...))
        //  (: 则为0
        //  ): 找到(与之匹配.
        //   若是(), 则dp[i]=2+dp[i-2]
        //   若)), 且[i-dp[i-1]-1]='(', 则dp[i]=2+dp[i-1]+dp[i-dp[i-1]-2]
        int n = s.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> dp(n);
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '(')
            {
                // 为了代码完整性.
                // dp[i] = 0;
            }
            else if (s[i] == ')')
            {
                if (i - 1 < 0) // i == 0
                {
                    // dp[i] = 0;
                    continue;
                }
                if (s[i - 1] == '(')
                {
                    dp[i] = 2 + (i - 2 >= 0 ? dp[i - 2] : 0);
                }
                else
                { // s[i - 1] == ')'
                    if ((i - dp[i - 1] - 1 >= 0) and (s[i - dp[i - 1] - 1] == '('))
                    {
                        dp[i] = 2 + dp[i - 1] + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
                    }
                    else
                    {
                        // dp[i] = 0;
                    }
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
int main()
{
    {
        string s = "(()";
        cout << Solution().longestValidParentheses(s);
        cout << Solution2().longestValidParentheses(s);
        cout << Solution3().longestValidParentheses(s);
        cout << Solution4().longestValidParentheses(s);
    }
    {
        string s = ")()())";
        cout << Solution().longestValidParentheses(s);
        cout << Solution2().longestValidParentheses(s);
        cout << Solution3().longestValidParentheses(s);
        cout << Solution4().longestValidParentheses(s);
    }
    {
        string s = "(())(";
        cout << Solution().longestValidParentheses(s);
        cout << Solution2().longestValidParentheses(s);
        cout << Solution3().longestValidParentheses(s);
        cout << Solution4().longestValidParentheses(s);
    }
    {
        string s = "()(())";
        cout << Solution().longestValidParentheses(s);
        cout << Solution2().longestValidParentheses(s);
        cout << Solution3().longestValidParentheses(s);
        cout << Solution4().longestValidParentheses(s);
    }
}