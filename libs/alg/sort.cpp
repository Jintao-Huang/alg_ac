// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _SORT
#define _SORT
#include "../build_ds.cpp"
#include "../load_modules.cpp"

int partition(vector<int> &v, int lo, int hi)
{
    // [lo..hi]
    // 按nums[lo]进行划分.
    //  先备份nums[lo]为x, 然后找hi(未测), 若hi小于x, 则放到前面来.
    //  那么后面多了个空位. lo已测, ++lo, 找lo(未测), 若lo大于x, 则放到后面去.
    int x = v[lo];
    while (lo < hi)
    {
        // hi未测, lo为空位
        while (lo < hi)
        {
            if (x > v[hi])
            {
                v[lo++] = v[hi];
                break;
            }
            --hi;
        }
        // lo未测, hi为空位
        while (lo < hi)
        {
            if (x < v[lo])
            {
                v[hi--] = v[lo];
                break;
            }
            ++lo;
        }
    }
    v[lo] = x;
    return lo;
}

void quick_sort(vector<int> &v, int lo, int hi)
{
    // [lo..hi]
    // 对v进行切分, 取左右数组继续划分
    if (lo >= hi)
    {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    swap(v[lo], v[mid]);
    int idx = partition(v, lo, hi);
    quick_sort(v, lo, idx - 1);
    quick_sort(v, idx + 1, hi);
}

void merge(vector<int> &v, int lo, int mid, int hi)
{
    // [lo..mid], [mid+1..hi].
    // 两个有序数组
    //  先复制前面到一个新数组, 防止覆盖
    //  进行循环, 每次循环都将两个数组较小的数放在v上
    //  直到有一个有序数组为空, 则将后面进行复制.
    vector<int> v2(v.begin() + lo, v.begin() + mid + 1); // 长度: mid+1
    int v2_len = mid - lo + 1;
    int i = 0, j = mid + 1, k = lo;
    while (i < v2_len and j <= hi)
    {
        if (v2[i] <= v[j])
        {
            v[k++] = v2[i++];
        }
        else
        {
            v[k++] = v[j++];
        }
    }
    while (i < v2_len)
    {
        v[k++] = v2[i++];
    }
}

void merge_sort(vector<int> &v, int lo, int hi)
{
    // 将数组进行不断中分, 直到只有一个元素
    // 随后不断合并
    if (lo >= hi)
    {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    merge_sort(v, lo, mid);
    merge_sort(v, mid + 1, hi);
    merge(v, lo, mid, hi);
}

void heap_sort(vector<int> &v, int lo, int hi)
{
    //
    make_heap(v.begin() + lo, v.begin() + hi + 1);
    // 对大根堆, 不断取最后一个元素换到最后
    // 然后做下滤, 恢复堆特性
    for (int i = hi; i >= lo; --i)
    {
        //
        pop_heap(v.begin() + lo, v.begin() + i + 1);
    }
}

int main()
{
    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        quick_sort(v, 0, v.size() - 1);
        cout << v << '\n';
    }
    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        merge_sort(v, 0, v.size() - 1);

        cout << v << '\n';
    }
    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        heap_sort(v, 0, v.size() - 1);

        cout << v << '\n';
    }

    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        quick_sort(v, 1, v.size() - 2);
        cout << v << '\n';
    }
    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        merge_sort(v, 1, v.size() - 2);
        cout << v << '\n';
    }
    {
        vector<int> v = {5, 2, 7, 3, 4, 6};
        heap_sort(v, 1, v.size() - 2);
        cout << v << '\n';
    }
}

#endif
