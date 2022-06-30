#include "pre.cpp"

class Solution
{
public:
    long long sumScores(string &s)
    {
        // 1. 二分搜索.
        // 2. 遍历i从[0, s_len-1], 表示字符串起点位置, 终点位置为s_len)
        // 3. 对于每个字符串, 进行二分搜索, 判断, [i, ans)与[0, ans-i)的hash是否相同
        // 4. 找到最大的相同字符串
        
        int s_len = s.size();
        StringHasher sh(s);
        long long res = 0;
        for (int i = 0; i < s_len; ++i)
        {

            if (s[i] != s[0])
            {
                continue;
            }
            int lo = i, hi = s_len; // 答案的范围

            // 找最大的等于
            while (lo < hi)
            {
                int mid = (hi - lo + 1) / 2 + lo;
                int hash1 = sh.get_hash(0, mid - i);
                int hash2 = sh.get_hash(i, mid);
                if (hash1 == hash2)
                {
                    lo = mid;
                }
                else
                {
                    hi = mid - 1;
                }
            }
            res += lo - i;
        }
        return res;
    }
};
int main()
{
    string s = "azbazbzaz";
    cout << Solution().sumScores(s);
}