
#include "pre.cpp"

class Solution
{
public:
    string minWindow(string &s, string &t)
    {
        // 设置滑动窗口. require, windows的字典, need_sati: 含需要满足条件的个数
        // 遍历t, 初始化require字典
        // 进行hi的for循环, 每次前进以此for[0..len(s)-1];
        //  先扩, 调整windows, need_sati
        //  后缩, 调整need_sati, windows, 直到不满足包含条件
        //  所以每次满足缩的条件, 需要更新res
        int res_lo = 0, res_len = INT32_MAX; // [lo..hi]
        int s_len = s.size(), t_len = t.size();
        unordered_map<char, int> require, windows;
        for (int i = 0; i < t_len; ++i)
        {
            require[t[i]] += 1;
        }
        int need_sati = require.size();
        int lo = 0;
        for (int hi = 0; hi < s_len; ++hi)
        {
            char ch = s[hi];
            windows[ch] += 1;
            if (windows[ch] == require[ch])
            {
                need_sati -= 1;
            }
            while (need_sati == 0)
            {
                // 满足条件
                if (res_len > hi - lo + 1)
                {
                    res_len = hi - lo + 1;
                    res_lo = lo;
                }
                //
                char ch2 = s[lo];
                if (windows[ch2] == require[ch2])
                {
                    need_sati += 1;
                }
                windows[ch2] -= 1;
                ++lo;
            }
        }
        return res_len != INT32_MAX ? s.substr(res_lo, res_len) : "";
    }
};

int main()
{
    string s = "ADOBECODEBANC", t = "ABC";
    cout << Solution().minWindow(s, t);
}