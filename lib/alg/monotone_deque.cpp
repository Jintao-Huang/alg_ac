

//
#ifndef _MONOTONE_DEQUE
#define _MONOTONE_DEQUE

#include "../load_modules.cpp"
#include "../io.cpp"

/// 求下一个比当前元素更大的元素的索引, 若不存在, 则返回-1.
vector<int> &next_gt(const vector<int> &v, vector<int> &dst)
{
    // 由于要求下一个比当前元素更大的元素的索引
    // 所以需要一个单调递减的栈.
    // [^]因为当一个比栈顶元素更大的值出现时, 它具有更近且更大的特征, 所以栈顶元素没有价值, 可以删除.
    // 遍历v的顺序使用倒序遍历
    ///
    // 若改为prev_gt, 则改变迭代方向
    // 若next_ge: 则将while循环的 <= 改为 <, 即为单调不增栈
    // 若next_lt: 则将while循环的 <= 改为 >=, 即为单调递增栈
    int n = v.size();
    dst.resize(n);
    vector<int> st; // stack
    for (int i = n - 1; i >= 0; --i)
    {
        // 如果栈顶小于等于当前值, 则一直弹出栈顶. 直到大于后, 将该值加入栈
        // 当前值的下一个最大元素为栈顶元素(若存在)
        int val = v[i];
        while (not st.empty() and v[st.back()] <= val)
        {
            st.pop_back();
        }
        if (not st.empty())
        {
            dst[i] = st.back();
        }
        else
        {
            dst[i] = -1;
        }
        st.push_back(i);
    }
    return dst;
}

void prev_ge_next_gt(const vector<int> &v, vector<int> &prev_dst, vector<int> &next_dst)
{
    // 由于要求前后一个比当前元素更大的元素的索引,
    // 需要一个单调非递增栈.
    // 优点: 同时确定一个元素的prev_ge, next_gt
    int n = v.size();
    prev_dst.resize(n);
    next_dst.resize(n);
    vector<int> st; // stack
    for (int i = 0; i < n; ++i)
    {
        //
        int val = v[i];
        while (not st.empty() and v[st.back()] < val)
        {
            // 弹出则说明
            int x = st.back();
            st.pop_back();
            next_dst[x] = i;
            if (not st.empty())
            {
                prev_dst[x] = st.back();
            }
            else
            {
                prev_dst[x] = -1;
            }
        }

        st.push_back(i);
    }
    while (not st.empty())
    {
        int x = st.back();
        st.pop_back();
        next_dst[x] = -1;
        if (not st.empty())
        {
            prev_dst[x] = st.back();
        }
        else
        {
            prev_dst[x] = -1;
        }
    }
}

void prev_ge_next_gt2(const vector<int> &v, vector<int> &prev_dst, vector<int> &next_dst)
{
    // 由于要求前后一个比当前元素更大的元素的索引,
    // 需要一个单调非递增栈.
    int n = v.size();
    prev_dst.resize(n);
    next_dst.resize(n);
    vector<int> st; // stack
    for (int i = 0; i < n; ++i)
    {
        //
        int val = v[i];
        while (not st.empty() and v[st.back()] < val)
        {
            // 弹出则说明
            int x = st.back();
            st.pop_back();
            next_dst[x] = i;
        }
        if (not st.empty())
        {
            prev_dst[i] = st.back();
        }
        else
        {
            prev_dst[i] = -1;
        }
        st.push_back(i);
    }
    while (not st.empty())
    {
        int x = st.back();
        st.pop_back();
        next_dst[x] = -1;
    }
}

/// 下一个>=该元素的最小值的索引
vector<int> &next_ge_min(const vector<int> &v, vector<int> &dst)
{
    // 单调栈只能解决下一个 > 该值的最近索引
    // 所以为实现最小值, 可以通过排序后的arg信息, 找下一个arg索引大于当前索引的索引.
    // 排序: 满足下一个元素即为 >= 该值的最小值, 但是不保证在该元素之后
    // 所以需要用单调栈寻找最近的 > arg的值
    int n = v.size();
    dst.resize(n);
    vector<int> arg(n);
    for (int i = 0; i < n; ++i)
    {
        arg[i] = i;
    }

    stable_sort(arg.begin(), arg.end(), [&v](int i, int j) -> bool
                { return v[i] < v[j]; });
    // 对arg做: 下一个>的索引
    vector<int> ngt(arg.size());
    next_gt(arg, ngt);
    // dst的格式转化.
    // 原来存储的是arg中某元素的下一个>其的索引.
    // arg某元素代表索引: arg[i], arg的下一个>其的值代表另一个索引: arg[ngt[i]]
    // 转化为dst[索引] = 索引. 其中arg无重复值.
    for (int i = 0; i < n; ++i)
    {
        dst[arg[i]] = ngt[i] != -1 ? arg[ngt[i]] : -1;
    }
    return dst;
}
// 单调队列

// 某元素的后面的k个位置, 含当前位置的最大数的索引
vector<int> &next_k_max(const vector<int> &v, int k, vector<int> &dst)
{
    // 从后往前遍历, 使用非递增栈, 即最大值在栈顶.
    // 判断栈顶的索引, 如果距离>k, 则丢弃.
    ///
    // 若不含当前位置, 则求max的操作(操作3)需要在加入当前元素之前(操作1前); 记得判断empty()
    int n = v.size();
    dst.resize(n);
    deque<int> dq;
    for (int i = n - 1; i >= 0; --i)
    {

        // 1. 加入当前元素. 递减栈(相等, 返回靠近的索引), 存索引
        // 若是非递增栈, 则返回远离的索引
        int val = v[i];
        while (not dq.empty() and val >= v[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        // 距离.
        while (dq.front() - i + 1 > k) // dq.empty()一定不成立(因为有当前元素加入)
        {
            dq.pop_front();
        }
        // 3.
        dst[i] = dq.front(); // dq.empty()一定不成立
    }
    return dst;
}

/// 某元素的前面的k个位置, 含当前位置的最大数的索引
// 1. 循环顺序: 正向
// 2. dq弹出前面的判断语句 i - dq.front()+ 1 > k
/// 若要改为prev_k_min()
// 1. >= 变为 <=. 即递减栈变为递增栈
vector<int> &prev_k_max(const vector<int> &v, int k, vector<int> &dst)
{
    int n = v.size();
    dst.resize(n);
    deque<int> dq;
    for (int i = 0; i < n; ++i)
    {

        int val = v[i];
        while (not dq.empty() and val >= v[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        // 距离.
        while (i - dq.front() + 1 > k) // dq.empty()一定不成立
        {
            dq.pop_front();
        }
        // 3.
        dst[i] = dq.front(); // dq.empty()一定不成立
    }
    return dst;
}

// [862]
template <class T>
int prev_le_k(const vector<T> &v, int k)
{
    // 找前面最近的 小于等于(当前元素-k)的索引. 即: v[j] <= v[k] - k.
    // 所以若k>0; 则为单调递增栈.
    // 返回max(hi-lo). 所以可以使用单调队列. 若找到dq.front()满足, 则可以弹出, 因为这是单调递增栈.
    // dq=[1,2,3,4], 5
    int n = v.size();
    deque<int> dq;
    int res = INT32_MAX;
    for (int i = 0; i < n; ++i)
    {
        T val = v[i];
        while (not dq.empty() and v[dq.back()] >= val)
        {
            dq.pop_back();
        }
        dq.push_back(i);
        int lo;
        while (not dq.empty() and v[lo = dq.front()] <= val - k)
        {
            // front满足
            res = min(res, i - lo);
            dq.pop_front();
        }
    }
    return res != INT32_MAX ? res : -1;
}

// int main()
// {
//     {
//         vector<int> nums = {3, 4, 2, 2, 5, 4};
//         vector<int> dst(nums.size());
//         cout << next_gt(nums, dst) << '\n';
//         // [1, 4, 4, 4, -1, -1]
//     }
//     {
//         vector<int> nums = {3, 4, 2, 2, 5, 4};
//         vector<int> prev_dst(nums.size());
//         vector<int> next_dst(nums.size());
//         prev_ge_next_gt(nums, prev_dst, next_dst);
//         cout << prev_dst << next_dst << '\n';
//         // [-1, -1, 1, 2, -1, 4][1, 4, 4, 4, -1, -1]
//     }
//     {
//         vector<int> nums = {3, 4, 2, 2, 5, 4};
//         vector<int> prev_dst(nums.size());
//         vector<int> next_dst(nums.size());
//         prev_ge_next_gt2(nums, prev_dst, next_dst);
//         cout << prev_dst << next_dst << '\n';
//         // [-1, -1, 1, 2, -1, 4][1, 4, 4, 4, -1, -1]
//     }
//     {
//         vector<int> nums = {3, 4, 2, 2, 5, 4};
//         vector<int> dst(nums.size());
//         cout << next_ge_min(nums, dst) << '\n';
//         // [1, 5, 3, 5, -1, -1]
//     }

//     {
//         vector<int> nums = {3, 4, 2, 2, 5, 4};
//         vector<int> dst(nums.size());
//         cout << next_k_max(nums, 2, dst) << '\n';
//         // [1, 1, 2, 4, 4, 5]
//     }
// }

#endif
