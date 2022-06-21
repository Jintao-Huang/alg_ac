#ifndef _PRIORITY_QUEUE
#define _PRIORITY_QUEUE

#include "../load_modules.cpp"
#include "../io.cpp"

template <class T>
class PriorityQueue
{
private:
    vector<T> heap;

public:
    //
    PriorityQueue() {}
    PriorityQueue(initializer_list<T> &&il) : heap(il)
    {

        make_heap(heap.begin(), heap.end());
    }
    void add(T elem)
    {
        heap.push_back(elem);
        push_heap(heap.begin(), heap.end()); // 上滤
    }
    void pop()
    {
        pop_heap(heap.begin(), heap.end()); // 下滤
        heap.pop_back();
    }
    T peek()
    {
        return heap[0];
    }

    friend ostream &operator<<(ostream &out, const PriorityQueue &pq)
    {
        out << pq.heap;
        return out;
    }

    int size()
    {
        return heap.size();
    }
};

// int main()
// {
//     PriorityQueue<float> pq{1.2, 6, 3, 4, 8, 2, 5, 7};
//     cout << pq << '\n';
//     pq.pop();
//     cout << pq << '\n';
//     pq.add(100);
//     cout << pq << '\n';
// }

#endif