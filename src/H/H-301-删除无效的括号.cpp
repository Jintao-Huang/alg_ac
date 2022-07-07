#include "pre.cpp"

class Solution
// 可优化. 广度+回溯结合
{
public:
    vector<string> res;
    int min_change = INT32_MAX;

    void bktrace(const string &s, string &path, int i, int left, int right, int change)
    {
        int n = s.size();
        if ((right > left) or (n - i + right < left))
        {
            return;
        }
        if (i == n)
        {
            if (left == right)
            {
                // 如果change < min_change: 清空并加入
                // ==: 加入
                // > 忽略
                if (change < min_change)
                {
                    res.clear();
                    min_change = change;
                    res.push_back(path);
                }
                else if (change == min_change)
                {
                    res.push_back(path);
                }
                else // >
                {
                    // ignore
                }
            }
            return;
        }

        if (s[i] == '(')
        {
            // 选择
            path.push_back('(');
            bktrace(s, path, i + 1, left + 1, right, change);
            path.pop_back();
            // 不选择
            bktrace(s, path, i + 1, left, right, change + 1);
        }
        else if (s[i] == ')')
        {
            // 选择
            path.push_back(')');
            bktrace(s, path, i + 1, left, right + 1, change);
            path.pop_back();
            // 不选择
            bktrace(s, path, i + 1, left, right, change + 1);
        }
        else
        { // 其他字符
            path.push_back(s[i]);
            bktrace(s, path, i + 1, left, right, change);
            path.pop_back();
        }
    }

    vector<string> removeInvalidParentheses(string &s)
    {
        // 使用回溯法
        // 所有的符号都有删除和不删除两个选择, 遍历所有的选择, 若某种选择. left==right则符合. 存入开始的索引和长度.
        // 出现更少的 change数, 则clear res, 存入.
        // 需要进行集合去重
        string path;
        bktrace(s, path, 0, 0, 0, 0);
        // 去重
        unordered_set<string> tmp(res.begin(), res.end());
        return vector<string>(tmp.begin(), tmp.end());
    }
};

int main()
{
    // {
    //     string s = "()())()";
    //     cout << Solution().removeInvalidParentheses(s);
    // }
    {
        string s = ")(f";
        cout << Solution().removeInvalidParentheses(s);
    }
}