

#ifndef _MATH
#define _MATH
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
#endif
