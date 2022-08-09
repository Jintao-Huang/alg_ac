// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _STRING_HASHER
#define _STRING_HASHER

#include "../load_modules.cpp"
#include "../io.cpp"
#include "../math.cpp"

class StringHasher
{
private:
    vector<int> weight;
    vector<int> prefix_sum;
    char min_char;
    int base;
    int mod;

public:
    // 空代表0, 其他的从1开始计数
    StringHasher() {}
    StringHasher(string &s, char min_char = 'a', int base = 27, int mod = 1e9 + 7)
        : min_char(min_char), base(base), mod(mod)
    {
        // min_char: 1
        // base = 1 + 字符表长度
        // 1. 对字符串s计算前缀和, 空字符为0; 高位在前面
        // 2. 并计算每个差位的权重, s[0]为1: 代表位置之差=0, 权重之商为1

        int s_len = s.size();
        weight.resize(s_len);
        prefix_sum.resize(s_len + 1);
        --min_char;
        //
        prefix_sum[0] = 0;
        prefix_sum[1] = s[0] - min_char;
        weight[0] = 1;
        for (int i = 1; i < s_len; ++i)
        {
            weight[i] = (long long)weight[i - 1] * base % mod;
            prefix_sum[i + 1] = ((long long)prefix_sum[i] * base + (s[i] - min_char)) % mod;
        }
    }
    int get_hash(int lo, int hi)
    {
        // [lo, hi)
        // 1. 如果lo >= hi, 返回0
        // 2. 前缀和相减, 进行python的mod. (xxxyyy - xxx000); 高位在前面
        if (lo >= hi)
        {
            return 0;
        }
        else if (lo == 0)
        { // 避免hi-lo越界
            return prefix_sum[hi];
        }
        return python_mod((prefix_sum[hi] - (long long)prefix_sum[lo] * weight[hi - lo]), mod);
    }
};

// int main()
// {
//     string s = "babab";
//     StringHasher sh(s);
//     cout << sh.get_hash(0, 3) << '\n';
//     cout << sh.get_hash(2, 5) << '\n';
// }
#endif