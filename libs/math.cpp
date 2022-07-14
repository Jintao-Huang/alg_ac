

#ifndef _MATH
#define _MATH
#include "load_modules.cpp"
inline int pow2(int x)
{
    // 2 ** x
    return 1 << x;
}

inline int python_mod(long long x, int y)
{
    return (x % y + y) % y;
}

inline int python_mod(int x, int y)
{
    return (x % y + y) % y;
}

class BigInt
{
    // 大的正整数
    // 使用字符串进行存储与运算. 此处不进行优化.
    string s;
    BigInt(string &&s) : s(s) {}
    BigInt(string &s) : s(s) {}
    BigInt() {}
    // 略
};

long long perm(int m, int n)
{
    // m个选n个, 再排序
    // 从m-n乘到m
    long long res = 1;
    for (int i = m - n + 1; i <= m; ++i)
    {
        res *= i;
    }
    return res;
}
long long comb(int m, int n)
{
    // 从m个中选择n个
    long long res = perm(m, n);
    // 再除以n!
    for (int i = 2; i <= n; ++i)
    {
        res /= i;
    }
    return res;
}

int gcd(int x, int y)
{
    // 进行辗转相除, 大的模小的, 直到小的为0
    // 若x < y, 则第一次会交换x,y
    while (y > 0)
    {
        int tmp = x % y;
        x = y;
        y = tmp;
    }
    return x;
}

// int main()
// {

//     // cout << comb(5, 2);
//     cout << gcd(10, 4);
// }

#endif
