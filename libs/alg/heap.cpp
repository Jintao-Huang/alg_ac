

#ifndef _HEAP
#define _HEAP

#include "../load_modules.cpp"
#include "../io.cpp"

// 默认: 大根堆
// push_heap()  // 上滤
// pop_heap()  // swap+下滤

void make_heap(vector<int> &heap, function<bool(int, int)> comp = nullptr)
{
    if (comp == nullptr)
    {
        comp = less<int>();
    }
    make_heap(heap.begin(), heap.end(), comp);
}

void push_heap(vector<int> &heap, int x, function<bool(int, int)> comp = nullptr)
{
    if (comp == nullptr)
    {
        comp = less<int>();
    }
    heap.push_back(x);
    push_heap(heap.begin(), heap.end(), comp);
}

void pop_heap(vector<int> &heap, function<bool(int, int)> comp = nullptr)
{
    if (comp == nullptr)
    {
        comp = less<int>();
    }
    pop_heap(heap.begin(), heap.end(), comp);
    heap.pop_back();
}

int replace_heap(vector<int> &heap, int x, function<bool(int, int)> comp = nullptr)
{
    if (comp == nullptr)
    {
        comp = less<int>();
    }
    if (heap.size() > 0)
    {
        heap.push_back(x);
        pop_heap(heap.begin(), heap.end(), comp); // swap+下滤
        x = heap.back();
        heap.pop_back();
    }
    return x;
}

int pushpop_heap(vector<int> &heap, int x, function<bool(int, int)> comp = nullptr)
{
    if (comp == nullptr)
    {
        comp = [](int x, int y) -> bool
        { return x < y; };
    }
    if (heap.size() > 0 and comp(x, heap[0]))
    {
        heap.push_back(x);
        pop_heap(heap.begin(), heap.end(), comp); // swap+下滤
        x = heap.back();
        heap.pop_back();
    }
    return x;
}

/// merge()参见: src/H-23-合并K个升序链表.cpp

// int main()
// {
//     vector<int> heap = {0, 1, 2, 3, 4, 5, 6, 7};
//     make_heap(heap, [](int x, int y)
//               { return x < y; });
//     vector<int> heap2(heap);
//     cout << heap << '\n';
//     push_heap(heap, 8);
//     cout << heap << '\n';
//     cout << heap[0];
//     pop_heap(heap);
//     cout << heap << '\n';
//     // [7, 4, 6, 3, 0, 5, 2, 1]
//     // [8, 7, 6, 4, 0, 5, 2, 1, 3]
//     // 8[7, 4, 6, 3, 0, 5, 2, 1]
//     heap = heap2;
//     cout << replace_heap(heap, 8);
//     cout << heap << '\n';
//     heap = heap2;
//     cout << pushpop_heap(heap, 8);
//     cout << heap << '\n';
//     //
//     heap = heap2;
//     cout << heap[0];
//     pop_heap(heap);
//     push_heap(heap, 8);
//     cout << heap << '\n';
//     heap = heap2;
//     push_heap(heap, 8);
//     cout << heap[0];
//     pop_heap(heap);
//     cout << heap << '\n';
//     // 7[8, 4, 6, 3, 0, 5, 2, 1]
//     // 8[7, 4, 6, 3, 0, 5, 2, 1]
//     // 7[8, 6, 5, 4, 0, 1, 2, 3]
//     // 8[7, 4, 6, 3, 0, 5, 2, 1]
// }

#endif