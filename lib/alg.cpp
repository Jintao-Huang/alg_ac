#ifndef _ALG
#define _ALG
// #include "alg/_std_alg.cpp"
#include "alg/tree.cpp"
#include "alg/graph.cpp"
#include "alg/binary_search.cpp"
#include "alg/knapsack.cpp"
#include "alg/monotone_deque.cpp"
#include "alg/heap.cpp"
#include "alg/set.cpp"
#include "alg/list.cpp"

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

#endif