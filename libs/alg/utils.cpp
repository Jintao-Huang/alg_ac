// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _UTILS
#define _UTILS
#include "../build_ds.cpp"
#include "../load_modules.cpp"
vector<int> &range(int hi, vector<int> &dst)
// step=0. [0..hi)
{
    dst.reserve(hi);
    for (int i = 0; i < hi; ++i)
    {
        dst.push_back(i);
    }
    return dst;
}
template <class T>
vector<T> &prefix_sum(vector<int> &nums, vector<T> &dst)
{
    //
    int n = nums.size();
    dst.resize(n + 1);
    dst[0] = 0;
    for (int i = 0; i < n; ++i)
    {
        int ip = i + 1;
        dst[ip] = dst[i] + nums[i];
    }
    return dst;
}

#endif