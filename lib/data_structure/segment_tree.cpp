#ifndef _SEGMENT_TREE
#define _SEGMENT_TREE

#include "../load_modules.cpp"
#include "../io.cpp"
#include "../math.cpp"

class LazySegmentTree
{
private:
    int n;
    bool diff_style;
    vector<int> tree;
    vector<int> lazy_tag;

public:
    inline int LC(int i)
    {
        return (i << 1) + 1;
    }
    inline int RC(int i)
    {
        return (i << 1) + 2;
    }
    LazySegmentTree(vector<int> &nums, bool diff_style = false) : n(nums.size()), diff_style(diff_style)
    {
        // diff_style = true: update中的val代表diff, 对区间进行修改
        // 计算一共需要多少个节点(几层). lazy_tag比tree少一层.
        int h = int(ceil(log2(n) + 1));
        tree.resize(pow2(h) - 1);
        _build_tree(nums, 0, n - 1, 0);
        if (diff_style)
        {
            lazy_tag.resize(pow2(h - 1) - 1);
        }
        else
        {
            lazy_tag.resize(pow2(h - 1) - 1, INT32_NULL);
        }
    }
    LazySegmentTree(int n, bool diff_style = false) : n(n), diff_style(diff_style)
    {
        // 用n个0元素初始化.
        int h = int(ceil(log2(n) + 1));
        tree.resize(pow2(h) - 1); // 无需初始化
        if (diff_style)
        {
            lazy_tag.resize(pow2(h - 1) - 1);
        }
        else
        {
            lazy_tag.resize(pow2(h - 1) - 1, INT32_NULL);
        }
    }

    int _build_tree(vector<int> &nums, int lo, int hi, int ti)
    {
        // [lo, hi]
        // 1. 每下建一层, 就将nums分成两个部分, 递归建树. 直到分成叶子节点.
        // 2. 然后累加子树的和
        if (lo == hi)
        {
            tree[ti] = nums[lo];
        }
        else
        {
            int mid = (hi - lo) / 2 + lo;
            int x1 = _build_tree(nums, lo, mid, LC(ti));
            int x2 = _build_tree(nums, mid + 1, hi, RC(ti));
            tree[ti] = x1 + x2;
        }
        return tree[ti];
    }
    int _sum_range(int lo, int hi, int r1, int r2, int ti)
    {
        // range [r1, r2] in [lo, hi].
        // ti是[lo, hi]在树中的索引/节点
        // 1. 对树进行dfs
        // 2. 如果出现 r1==lo, r2==hi, 则返回
        // 3. 如果路途中出现lazy_tag(且不满足2), 则将lazy_tag分配给子节点. 并更新子节点.
        // 如果没发分配(lazy_tag越界), 则不分配. 随后将lazy_tag置None.
        // 4. diff_style时, lazy_tag存的是diff. 反之, 存的是value. lazy-tag代表其子节点都没有更新.
        if (lo == r1 and hi == r2)
        {
            return tree[ti];
        }
        int mid = (hi - lo) / 2 + lo;
        int lc = LC(ti), rc = RC(ti);
        // 处理lazy_tag
        int lazyt = lazy_tag[ti];
        if ((diff_style and lazyt != 0) or (not diff_style and lazyt != INT32_NULL))
        {
            if (lc < lazy_tag.size())
            {
                // rc < 同时成立
                lazy_tag[lc] = lazyt;
                lazy_tag[rc] = lazyt;
            }
            int diff_lc = lazyt * (mid - lo + 1);
            int diff_rc = lazyt * (hi - mid);
            if (diff_style)
            {
                lazy_tag[ti] = 0;
                tree[lc] += diff_lc;
                tree[rc] += diff_rc;
            }
            else
            {
                lazy_tag[ti] = INT32_NULL;
                tree[lc] = diff_lc;
                tree[rc] = diff_rc;
            }
        }

        // 处理sum_range
        int x1 = 0, x2 = 0;
        if (r1 <= mid and r2 <= mid)
        {
            x1 = _sum_range(lo, mid, r1, r2, lc);
        }
        else if (r1 > mid and r2 > mid)
        {
            x2 = _sum_range(mid + 1, hi, r1, r2, rc);
        }
        else
        { // r1 <= mid and r2 > mid
            x1 = _sum_range(lo, mid, r1, mid, lc);
            x2 = _sum_range(mid + 1, hi, mid + 1, r2, rc);
        }
        return x1 + x2;
    }
    int sum_range(int r1, int r2)
    {
        assert(r1 <= r2 and r1 >= 0 and r2 < n);
        return _sum_range(0, n - 1, r1, r2, 0);
    }
    void _update(int lo, int hi, int r1, int r2, int ti, int val)
    {
        // 1. dfs对区间进行切分.
        // 2. 知道lo==r1, hi==r2, 则更新val, 并不再往下更新.
        // 如果diff_style: val是diff; 否则置val.
        // 如果是非叶子节点: 置lazy_tag. 代表其子节点都未更新.
        // 3. 若在不满足2的情况下, 遇到lazy_tag, 则分配到叶节点.
        if (lo == r1 and hi == r2)
        {
            // update val, lazy_tag
            int diff = (hi - lo + 1) * val;
            if (diff_style)
            {
                tree[ti] += diff;
                if (ti < lazy_tag.size())
                {
                    lazy_tag[ti] += val;
                }
            }
            else
            {
                tree[ti] = diff;
                if (ti < lazy_tag.size())
                {
                    lazy_tag[ti] = val;
                }
            }

            return;
        }
        // 不匹配
        int mid = (hi - lo) / 2 + lo;
        int lc = LC(ti), rc = RC(ti);

        // update lazy_tag
        int lazyt = lazy_tag[ti];
        if ((diff_style and lazyt != 0) or (not diff_style and lazyt != INT32_NULL))
        {
            if (lc < lazy_tag.size())
            {
                // rc < 同时成立
                lazy_tag[lc] = lazyt;
                lazy_tag[rc] = lazyt;
            }
            int diff_lc = lazyt * (mid - lo + 1);
            int diff_rc = lazyt * (hi - mid);
            if (diff_style)
            {
                lazy_tag[ti] = 0;
                tree[lc] += diff_lc;
                tree[rc] += diff_rc;
            }
            else
            {
                lazy_tag[ti] = INT32_NULL;
                tree[lc] = diff_lc;
                tree[rc] = diff_rc;
            }
        }

        // dfs
        if (r1 <= mid and r2 <= mid)
        {
            _update(lo, mid, r1, r2, lc, val);
        }
        else if (r1 > mid and r2 > mid)
        {
            _update(mid + 1, hi, r1, r2, rc, val);
        }
        else
        { // r1 <= mid and r2 > mid
            _update(lo, mid, r1, mid, lc, val);
            _update(mid + 1, hi, mid + 1, r2, rc, val);
        }
        tree[ti] = tree[lc] + tree[rc];
    }
    void update(int r1, int r2, int val)
    {
        assert(r1 <= r2 and r1 >= 0 and r2 < n);
        _update(0, n - 1, r1, r2, 0, val);
    }
};

class SegmentTree
{
private:
    int n;
    bool diff_style;
    vector<int> tree;

public:
    inline int LC(int i)
    {
        return (i << 1) + 1;
    }
    inline int RC(int i)
    {
        return (i << 1) + 2;
    }
    SegmentTree(vector<int> &nums, bool diff_style = false) : n(nums.size()), diff_style(diff_style)
    {
        // diff_style = true: update中的val代表diff, 对区间进行修改
        int h = int(ceil(log2(n) + 1));
        tree.resize(pow2(h) - 1);
        _build_tree(nums, 0, n - 1, 0);
    }
    SegmentTree(int n, bool diff_style = false) : n(n), diff_style(diff_style)
    {
        int h = int(ceil(log2(n) + 1));
        tree.resize(pow2(h) - 1);
    }
    int _build_tree(vector<int> &nums, int lo, int hi, int ti)
    {
        // [lo, hi]
        // 1. 每下建一层, 就将nums分成两个部分, 递归建树. 直到分成叶子节点.
        // 2. 然后累加子树的和
        if (lo == hi)
        {
            tree[ti] = nums[lo];
        }
        else
        {
            int mid = (hi - lo) / 2 + lo;
            int x1 = _build_tree(nums, lo, mid, LC(ti));
            int x2 = _build_tree(nums, mid + 1, hi, RC(ti));
            tree[ti] = x1 + x2;
        }
        return tree[ti];
    }
    int _sum_range(int lo, int hi, int r1, int r2, int ti)
    {
        // range [r1..r2] in [lo..hi].
        // ti是[lo, hi]在树中的索引/节点
        // 1. 对树进行dfs
        // 2. 如果出现 r1==lo, r2==hi, 则返回
        if (lo == r1 and hi == r2)
        {
            return tree[ti];
        }
        int mid = (hi - lo) / 2 + lo;
        int lc = LC(ti), rc = RC(ti);

        // 处理sum_range
        int x1 = 0, x2 = 0;
        if (r1 <= mid and r2 <= mid)
        {
            x1 = _sum_range(lo, mid, r1, r2, lc);
        }
        else if (r1 > mid and r2 > mid)
        {
            x2 = _sum_range(mid + 1, hi, r1, r2, rc);
        }
        else
        { // r1 <= mid and r2 > mid
            x1 = _sum_range(lo, mid, r1, mid, lc);
            x2 = _sum_range(mid + 1, hi, mid + 1, r2, rc);
        }
        return x1 + x2;
    }
    int sum_range(int r1, int r2)
    {
        assert(r1 <= r2 and r1 >= 0 and r2 < n);
        return _sum_range(0, n - 1, r1, r2, 0);
    }
    void _update(int lo, int hi, int idx, int ti, int val)
    {
        // [lo..hi]
        // 使用后序遍历.
        // 1. dfs对区间进行切分.
        // 2. 知道lo==idx==hi, 则更新val, 并不再往下更新.
        // 如果diff_style: val是diff; 否则置val.
        if (lo == hi)
        {
            // update val
            int diff = (hi - lo + 1) * val;
            if (diff_style)
            {
                tree[ti] += diff;
            }
            else
            {
                tree[ti] = diff;
            }
            return;
        }
        // 不匹配
        int mid = (hi - lo) / 2 + lo;
        int lc = LC(ti), rc = RC(ti);

        // dfs
        if (idx <= mid)
        {
            _update(lo, mid, idx, lc, val);
        }
        else
        {
            _update(mid + 1, hi, idx, rc, val);
        }
        tree[ti] = tree[lc] + tree[rc];
    }
    void update(int idx, int val)
    {
        assert(idx >= 0 and idx < n);
        _update(0, n - 1, idx, 0, val);
    }
};

// int main()
// {
//     vector<int> x = {0, 1, 2, 3, 4, 5};
//     LazySegmentTree lst(x, true);
//     lst.update(0, 5, -100);
//     cout << lst.sum_range(0, 5) << '\n';
//     cout << lst.sum_range(0, 1) << '\n';
//     cout << lst.sum_range(2, 3) << '\n';
//     cout << '\n';
//     SegmentTree st(x, true);
//     st.update(0, -100);
//     st.update(1, -100);
//     st.update(2, -100);
//     st.update(3, -100);
//     st.update(4, -100);
//     st.update(5, -100);
//     cout << st.sum_range(0, 5) << '\n';
//     cout << st.sum_range(0, 1) << '\n';
//     cout << st.sum_range(2, 3) << '\n';
// }

#endif
