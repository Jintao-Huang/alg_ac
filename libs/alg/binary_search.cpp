// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _BINARY_SEARCH
#define _BINARY_SEARCH

#include "../load_modules.cpp"
#include "../io.cpp"

int lower_bound(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    // 找 v[i] >= val的最小值
    // [lo, hi)
    if (hi == -1)
    {
        hi = v.size();
    }
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] >= val)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return lo;
}

int lower_bound2(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    // 找 v[i] < val的最大值+1
    // [lo, hi)
    if (hi == -1)
    {
        hi = v.size();
    }
    --lo;
    --hi;
    while (lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if (v[mid] < val)
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return lo + 1;
}

int upper_bound(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    // 找 v[i] > val的最小值
    // [lo, hi)
    if (hi == -1)
    {
        hi = v.size();
    }
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] > val)
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return lo;
}

int upper_bound2(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    // 找 v[i] <= val的最大值 + 1
    // [lo, hi)
    if (hi == -1)
    {
        hi = v.size();
    }
    --lo;
    --hi;
    while (lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if (v[mid] <= val)
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return lo + 1;
}

pair<int, int> equal_range(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    int i = lower_bound(v, val, lo, hi);
    return pair(i, upper_bound(v, val, i, hi));
}

bool binary_search(vector<int> &v, int val, int lo = 0, int hi = -1)
{
    // first一定 >= val
    int i = lower_bound(v, val);
    return (i != v.size() and val == v[i]);
}

// int main()
// {
//     vector<int> v = {0, 0};
//     cout << lower_bound(v, 0);
//     cout << lower_bound(v, -1);
//     cout << lower_bound(v, 1);
//     //
//     cout << lower_bound2(v, 0);
//     cout << lower_bound2(v, -1);
//     cout << lower_bound2(v, 1);
//     //
//     cout << upper_bound(v, 0);
//     cout << upper_bound(v, -1);
//     cout << upper_bound(v, 1);
//     //
//     cout << upper_bound2(v, 0);
//     cout << upper_bound2(v, -1);
//     cout << upper_bound2(v, 1);
//     //
//     cout << '\n';
//     cout << equal_range(v, 0);
//     cout << equal_range(v, -1);
//     cout << equal_range(v, 1);
//     cout << '\n';
//     //
//     cout << binary_search(v, 0);
//     cout << binary_search(v, -1);
//     cout << binary_search(v, 1);
//     // 002002202202
//     // pair(0, 2)pair(0, 0)pair(2, 2)
//     // 100
// }

#endif