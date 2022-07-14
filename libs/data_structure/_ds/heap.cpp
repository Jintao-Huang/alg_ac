

#ifndef _HEAP
#define _HEAP
#include "../../load_modules.cpp"
#include "../../io.cpp"

class Heap
// 大根堆
{
private:
    vector<int> heap;

public:
    Heap() {}
    Heap(vector<int> &nums) : heap(nums) {}
    Heap(vector<int> &&nums) : heap(nums) {}
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
        int x = heap[idx];
        while (idx > 0)
        { // 即父节点存在
            int p = PARENT(idx);
            int vp = heap[p];
            if (vp >= x)
            {
                break;
            }
            heap[idx] = vp;
            idx = p;
        }
        heap[idx] = x;
    }
    void _siftdown(int idx, int n)
    {
        // 堆的长度是n, 将idx进行下滤
        // idx不符合堆性质的.
        ///
        // 比较左右孩子, 将大的那个与当前节点比较. 如果子大, 则子覆盖父
        // 如果当前大, 则退出. 并赋值当前
        int x = heap[idx];
        int c = LC(idx);
        while (c < n)
        {
            int rc = RC(idx);
            if (rc < n and heap[rc] > heap[c])
            {
                c = rc;
            }
            int vc = heap[c];
            if (x >= vc)
            {
                break;
            }
            heap[idx] = vc;
            idx = c;
            c = LC(idx);
        }
        heap[idx] = x;
    }
    void heapify()
    {
        // 对heap进行建队
        int n = heap.size();
        int p = PARENT(n - 1);
        for (int i = p; i >= 0; --i)
        {
            _siftdown(i, n);
        }
    }
    void heappush(int x)
    {
        heap.push_back(x);
        _siftup(heap.size() - 1);
    }
    void heappop()
    {
        int n = heap.size();
        if (n > 1)
        {
            swap(heap[0], heap[n - 1]);
            _siftdown(0, n - 1);
        }
        heap.pop_back();
    }
    inline int front()
    {
        return heap[0];
    }
    // heapreplace 不等于 poppush
    // heappushpop
    ///
    // merge
    // nlarget
    // nsmallest
};

// int main()
// {
//     vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
//     Heap h(move(v));
//     h.heapify();
//     cout << h.heap;
//     h.heappush(8);
//     cout << h.heap;
//     h.heappop();
//     cout << h.heap;
//     {
//         vector<int> v;
//         Heap h(move(v));
//         h.heapify();
//         cout << h.heap;
//         h.heappush(8);
//         cout << h.heap;
//         h.heappop();
//         cout << h.heap;
//     }
// }

#endif