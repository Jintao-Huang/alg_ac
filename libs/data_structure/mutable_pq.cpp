// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _MUTABLE_PQ
#define _MUTABLE_PQ

#include "../load_modules.cpp"
#include "../io.cpp"

class MutablePQ
// 用于dijkstra算法
{
public:
    // 可以通过vector: 值->索
    // 这里的值是另一个v2的索引, 那个表示优先级
    vector<int> mapper; // 如果没有对应则: -1
    vector<int> heap;
    function<bool(int, int)> comp;
    int max_id; // n代表最大的heap中的id or val;
    // 这里的heap是id. mapper[id] -> position in heap.
    // 可以通过id, 直接increase key. (heap[pos] -> id)
    MutablePQ(int max_id, function<bool(int, int)> comp) : max_id(max_id), comp(comp)
    {
        mapper.resize(max_id, -1);
    }
    //
    inline int PARENT(int i)
    {
        return (i - 1) >> 1;
    }
    inline int LC(int i)
    {
        return (i << 1) + 1;
    }
    inline int RC(int i)
    {
        return (i << 1) + 2;
    }
    //
    void _siftup(int idx)
    {
        // 将idx进行上滤. 默认idx < n
        // idx不符合堆性质的.
        ///
        // 保存idx, 然后比较父节点, 如果父节点更小, 则父节点覆盖子节点
        // 直到父节点 >= 当前节点. 则停止上滤, 并赋值
        int id = heap[idx];
        while (idx > 0)
        { // 即父节点存在
            int p = PARENT(idx);
            int p_id = heap[p];
            if (not comp(p_id, id)) // p_id >= id
            {
                break;
            }
            heap[idx] = p_id;
            mapper[p_id] = idx;
            idx = p;
        }
        heap[idx] = id;
        mapper[id] = idx;
    }
    void _siftdown(int idx, int n)
    {
        // 堆的长度是n, 将idx进行下滤
        // idx不符合堆性质的.
        ///
        // 比较左右孩子, 将大的那个与当前节点比较. 如果子大, 则子覆盖父
        // 如果当前大, 则退出. 并赋值当前
        int id = heap[idx];
        int c = LC(idx);
        while (c < n)
        {
            int rc = RC(idx);
            if (rc < n and comp(heap[c], heap[rc])) // heap[rc] > heap[c]
            {
                c = rc;
            }
            int c_id = heap[c];
            if (not comp(id, c_id)) // id >= c_id
            {
                break;
            }
            heap[idx] = c_id;
            mapper[c_id] = idx;
            idx = c;
            c = LC(idx);
        }
        heap[idx] = id;
        mapper[id] = idx;
    }

    inline void push(int id)
    {
        // 判断id是否已经在了
        assert(mapper[id] == -1);
        //
        int idx = heap.size();
        heap.push_back(id);
        mapper[id] = idx;
        if (idx >= 1)
        {
            _siftup(idx);
        }
    }
    inline void pop()
    {
        int n = heap.size();
        mapper[heap[0]] = -1;
        if (n > 1)
        {
            swap(heap[0], heap[n - 1]);
            _siftdown(0, n - 1);
        }
        heap.pop_back();
    }
    inline int top()
    {
        return heap[0];
    }
    inline void increase_key(int id)
    // 前提是已经对该位置进行了增加优先级的操作. 只能增加
    {
        _siftup(mapper[id]);
    }
    inline void decrease_key(int id)
    {
        _siftdown(mapper[id], heap.size());
    }
    inline bool contain(int id)
    {
        return mapper[id] != -1;
    }
    inline int size()
    {
        return heap.size();
    }
    inline bool empty()
    {
        return heap.empty();
    }
};

// int main()
// {
//     vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     MutablePQ mpq(8, [&v](int i, int j)
//                   { return v[i] < v[j]; });
//     mpq.push(0);
//     mpq.push(1);
//     mpq.push(2);
//     mpq.push(3);
//     mpq.push(4);
//     mpq.push(5);
//     mpq.push(6);
//     mpq.push(7);
//     cout << mpq.heap;
//     cout << mpq.mapper;
//     mpq.pop();
//     cout << mpq.heap;
//     cout << mpq.mapper;
//     v[0] = 10;
//     mpq.increase_key(0);
//     cout << mpq.heap;
//     cout << mpq.mapper;
//     v[0] = 1;
//     mpq.decrease_key(0);
//     cout << mpq.heap;
//     cout << mpq.mapper;

// }

#endif