// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _BINARY_INDEXED_TREE
#define _BINARY_INDEXED_TREE

#include "../load_modules.cpp"
#include "../io.cpp"

#define PLUS1(x) (x) + 1

class BinaryIndexedTree
{
    // 与线段数不同的是, 树状数组只能维护前缀信息
    // 可以通过前缀和信息维护区间和信息. 但不能维护最大最小信息
    // 优点: 更快更memory优的
    ///
private:
    int n;
    vector<int> tree;

public:
    BinaryIndexedTree(vector<int> &nums) : n(nums.size())
    {
        // 只支持diff_style=true;
        /// 以下假设为: 数组从1开始计数. 而在cpp实现是从0开始.
        // 直觉: 每一层末尾的0的个数都是相同的. 即lowbit(ti)相等, 覆盖范围=lowbit(ti)
        // e.g. 第一层: 0001, 0011, 0101, 0111
        //  第二层: 0010, 0110
        //  第三层: 0100
        //  第四层: 1000
        // tree[ti]的父节点为tree[ti+lowbit(x)]
        tree.resize(n);
        _build_tree(nums);
    }
    BinaryIndexedTree(int n) : n(n)
    {
        tree.resize(n);
    }

    inline int lowbit(int x)
    {
        // 返回x在二进制表示下最低位1及其后面0构成的数值
        // e.g. lowbit(44)=lowbit(101100)_2=(100)_2=4
        // 算法: (~x+1) & x; 也可写成: -x & x
        return -x & x; // -x = ~x +1
    }
    // inline int parent(int x)
    // {
    //     return x + lowbit(PLUS1(x))
    // }
    // inline int prev_one(int x){
    //     return x - lowbit(PLUS1(x))
    // }
    void _build_tree(vector<int> &nums)
    {
        // 遍历每个节点. 累加
        for (int i = 0; i < n; ++i)
        {
            tree[i] += nums[i];
            int p = i + lowbit(PLUS1(i));
            if (p < n)
            {
                tree[p] += tree[i];
            }
        }
    }
    int prefix_sum(int hi)
    {
        // 向前遍历.
        assert(hi >= 0 and hi < n);
        int res = 0;
        while (hi >= 0)
        {
            res += tree[hi];
            hi -= lowbit(PLUS1(hi)); // next; parent
        }
        return res;
    }
    int sum_range(int lo, int hi)
    {
        assert(lo >= 0 and lo <= hi and hi < n);
        int res = prefix_sum(hi);
        if (lo == 0)
        {
            return res;
        }
        res -= prefix_sum(lo - 1);
        return res;
    }
    void update(int idx, int diff)
    {
        // 向父节点遍历
        while (idx < n)
        {
            tree[idx] += diff;
            idx += lowbit(PLUS1(idx)); // next; prev_one
        }
    }
};

// int main()
// {
//     vector<int> v = {1, 2, 3, 4};
//     BinaryIndexedTree bit(v);
//     bit.update(0, 1);
//     cout << bit.prefix_sum(3);
//     cout << bit.prefix_sum(0);
// }

#endif