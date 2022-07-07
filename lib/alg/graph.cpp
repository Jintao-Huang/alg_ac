
#ifndef _GRAPH
#define _GRAPH
#include "../build_ds.cpp"
#include "../load_modules.cpp"

vector<long long> &dijkstra(vector<vector<pair<int, int>>> &graph, int s, vector<long long> &res)
// s: start_idx
{
    // 从s出发到达所有节点的距离.
    // 使用优先级队列计算.
    // 优先拓展距离近的节点.
    // 若节点距离i < res[i]. 则加入优先级队列. 不适用visited数组
    int n = graph.size();
    res.resize(n, INT64_MAX);
    res[s] = 0;
    auto comp = [](pair<int, long long> &x, pair<int, long long> &y) -> bool
    { return x.second > y.second; };
    using pill = pair<int, long long>;
    priority_queue<pill, vector<pill>, decltype(comp)> pq(comp);
    pq.emplace(pair(s, 0));
    while (not pq.empty())
    {
        auto [from, d_sf] = pq.top(); // s->from的距离
        pq.pop();
        if (d_sf > res[from])
        {
            continue;
        } // 否则为==
        vector<pair<int, int>> &edge = graph[from];
        int e_len = edge.size();
        for (int i = 0; i < e_len; ++i)
        {
            auto [to, d_ft] = edge[i]; // from->to的距离
            long long d_st = d_sf + d_ft;
            if (d_st < res[to])
            {
                res[to] = d_st;
                pq.emplace(pair(to, d_st));
            }
        }
    }
    return res;
}
#endif