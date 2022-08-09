// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _GRAPH
#define _GRAPH
#include "../build_ds.cpp"
#include "../load_modules.cpp"
#include "../data_structure/mutable_pq.cpp"
#include "../data_structure/union_find.cpp"

// 有权图的最短路
using WEdge = pair<int, int>; // to, 距离/流大小/val/权重
template <class T>            // T为int或long long
vector<T> &dijkstra(vector<vector<WEdge>> &graph, int s, vector<T> &res, int t = -1)
// s: start_idx, e: end_idx. -1代表完全遍历. 使用邻接表存储
{
    // 从s出发到达所有节点的距离. graph中: to, dist
    // 使用优先级队列计算.
    // 优先拓展距离近的节点.
    // 若节点距离<. 则加入优先级队列. 不适用visited数组
    // 需要两个记录结构, 即: res, visited数组.
    // res: 使得最近的才会建图, 加入队列. visited. 避免对队列中有两个相同的点进行拓展.
    using plli = pair<T, int>;
    int n = graph.size();
    res.resize(n, INT64_MAX);
    priority_queue<plli, vector<plli>, greater<>> pq; // 其实是只比较第一个即可.
    vector<bool> visited(n);
    pq.emplace(pair(0, s));
    res[s] = 0;
    while (not pq.empty())
    {
        auto [_, from] = pq.top(); // s->from的距离, from(v)
        pq.pop();
        if (visited[from])
        {
            continue;
        }
        visited[from] = true;
        //
        vector<WEdge> &edge = graph[from];
        int e_len = edge.size();
        for (int i = 0; i < e_len; ++i)
        {
            auto [to, d_ft] = edge[i]; // from->to的距离
            T d_st = res[from] + d_ft;
            if (d_st < res[to])
            {
                res[to] = d_st;
                if (to == t)
                {
                    break; // 或直接 return res;
                }
                pq.emplace(pair(d_st, to));
            }
        }
    }
    return res;
}

// 使用MutablePQ
template <class T> // T为int或long long
vector<T> &dijkstra2(vector<vector<WEdge>> &graph, int s, vector<T> &res, int t = -1)
// s: start_idx, e: end_idx. -1代表完全遍历. 使用邻接表存储
{
    // 从s出发到达所有节点的距离. graph中: to, dist
    // 使用优先级队列计算.
    // 优先拓展距离近的节点.
    // 若节点距离<. 则加入优先级队列. 不适用visited数组
    // 需要两个记录结构, 即: res, visited数组.
    // res: 使得最近的才会建图, 加入队列. visited. 避免对队列中有两个相同的点进行拓展.
    using plli = pair<T, int>;
    int n = graph.size();
    res.resize(n, INT64_MAX);
    MutablePQ pq(n, [&res](int i, int j)
                 { return res[i] > res[j]; }); // 其实是只比较第一个即可.
    pq.push(s);
    res[s] = 0;
    while (not pq.empty())
    {
        int from = pq.top(); // s->from的距离
        pq.pop();
        //
        vector<WEdge> &edge = graph[from];
        int e_len = edge.size();
        for (int i = 0; i < e_len; ++i)
        {
            auto [to, d_ft] = edge[i]; // from->to的距离
            T d_st = res[from] + d_ft;
            if (d_st < res[to])
            {
                res[to] = d_st;
                if (to == t)
                {
                    break; // 或直接 return res;
                }
                if (pq.contain(to))
                {
                    pq.increase_key(to);
                }
                else
                {
                    pq.push(to);
                }
            }
        }
    }
    return res;
}
// 无权图的最短路
vector<int> &bfs(vector<vector<int>> &graph, int s, vector<int> &res, int t = -1)
// s: start_idx; e: end_idx. 使用邻接表存储
{
    int n = graph.size();
    res.resize(n, INT32_MAX);
    deque<int> dq;
    vector<bool> visited(n);
    dq.emplace_back(s);
    int dist = 0;
    res[s] = dist;
    visited[s] = true;
    // 判断是否到达在加入时判断, 增加found变量
    // 每个节点只允许被扩展一次. 此处与dij不同, 可以直接在加入时判断, 即每个节点只允许被加入dq一次.
    // (dij可能会出现已经加入的节点, 再次出现更短路径. 广搜不会出现这种情况. )
    // res的赋值在加入时赋值(加入时, 别忘了初始化的赋值)
    while (not dq.empty())
    {
        int dq_len = dq.size();
        for (int _ = 0; _ < dq_len; ++_)
        {
            int v = dq.front();
            dq.pop_front();
            vector<int> &edge = graph[v];
            int e_len = edge.size();
            for (int i = 0; i < e_len; ++i)
            {
                int v2 = edge[i];
                if (visited[v2])
                {
                    continue;
                }
                visited[v2] = true;
                res[v2] = dist + 1;
                dq.push_back(v2);
                if (v2 == t)
                {
                    return res;
                }
            }
        }
        ++dist;
    }
    return res;
}

/// 最小生成树
// 无向图, 因为是无向图, 所以用v1, v2表示
// 这不是邻接表, 所以每条无向边不需要存两条边
using WEdge2 = tuple<int, int, int>; // v1, v2, 距离/流大小/val/权重

int kruskal(int n, vector<WEdge2> &edges)
{
    // 返回最小生成树的路径长度
    ///
    // 输入为点, 使用并查集.
    // 每次从edges取一条边, 判断两个定点是否在一个集合中
    // 如果不在, 则union, 更新res
    // 直到只有1个集合.
    UFSet ufset(n);
    sort(edges.begin(), edges.end(), [](WEdge2 &x, WEdge2 &y)
         { return get<2>(x) < get<2>(y); });
    int e_len = edges.size();
    int res = 0;
    for (int i = 0; i < e_len; ++i)
    {

        auto [from, to, w] = edges[i];
        if (ufset.union_ufset(from, to))
        {
            res += w;
        }
        if (ufset.size() == 1)
        {
            break;
        }
    }
    return res;
}

// 类似于dijkstra算法, 只不是dij中的res是s->v的距离, prim是S集合->V集合
/// 使用邻接矩阵存储, 无向图. 是对称矩阵. 因为用prim算法的情景一般是稠密图. 稀疏图用kruskal计算.
int prim(vector<vector<int>> &graph)
{
    // graph中存权重, 无边则INF, 自边不进行操作(随意)
    int s = 0; // 默认
    int n = graph.size();
    vector<int> min_cost(n, INT32_MAX);
    vector<bool> visited(n); // dij可以不用visited数组. prim必须使用
    min_cost[s] = 0;
    MutablePQ mpq(n, [&min_cost](int i, int j)
                  { return min_cost[i] > min_cost[j]; });
    int cnt = 0;
    int res = 0;
    mpq.push(s);
    while (not mpq.empty() and cnt != n)
    {
        int v = mpq.top();

        visited[v] = true;
        mpq.pop();
        ++cnt;
        res += min_cost[v];
        vector<int> &edges = graph[v];
        for (int i = 0; i < n; ++i)
        {
            if (visited[i])
            {
                continue;
            }
            int w = edges[i];
            if (w >= min_cost[i])
            {
                continue;
            }
            min_cost[i] = w;
            if (mpq.contain(i))
            {
                mpq.increase_key(i);
            }
            else
            {
                mpq.push(i);
            }
        }
    }
    return res;
}

/// dinic
// 可以解决最大流/最小流问题; 以及二部图的无权图匹配问题.
class Dinic
{
private:
    // 如此存储的优势: 找反向边方便
    // 取相反边: edges[i ^ 1]
    // e.g. 10^1=11; 11^1=10;
    vector<WEdge> edges;    // 类似于hashmap, int -> edge
    vector<vector<int>> rg; // 边为在edges的索引
    vector<int> cur;        // 当前弧优化. 类似于边的visited, 避免回溯的指数级复杂度
    vector<int> level;      // level graph
    int n;                  // 顶点数
public:
    Dinic(int n) : n(n)
    {
        rg.resize(n);
        cur.resize(n);
        level.resize(n);
    }
    void add_edge(int from, int to, int cap)
    {
        int idx = edges.size();
        edges.emplace_back(pair(to, cap));
        rg[from].push_back(idx);
        //
        edges.emplace_back(pair(from, 0));
        rg[to].push_back(idx + 1);
    }

    bool _bfs(int s, int t)
    {
        // 若无法建立路径, 则返回false. 否则返回true. 并建立level graph
        // bfs只要找到t, 立即退出
        ///
        deque<int> dq;
        vector<bool> visited(n);
        //
        fill(level.begin(), level.end(), -1); // 一定不满足下边的条件.
        //
        dq.push_back(s);
        visited[s] = true;
        level[s] = 0;
        int step = 0;
        //
        while (not dq.empty())
        {
            int dq_len = dq.size();
            for (int _ = 0; _ < dq_len; ++_)
            {
                int v = dq.front();
                dq.pop_front();
                //
                const vector<int> &es = rg[v];
                int e_len = es.size();
                for (int i = 0; i < e_len; ++i)
                {
                    auto [v2, w] = edges[es[i]];
                    if (visited[v2] or w == 0)
                    {
                        continue;
                    }
                    visited[v2] = true;
                    level[v2] = step + 1;
                    if (v2 == t)
                    {
                        return true;
                    }
                    dq.push_back(v2);
                }
            }
            ++step;
        }
        return false;
    }

    int _dfs(int v, int t, int flow)
    {
        // 返回流的大小, 即后面流的大小; flow为前面流的大小
        ///
        // 使用后序遍历
        // dfs在所有边中的下边中, 随便找一条.
        // 更新流; 更新rg; 更新反向边
        if (v == t or flow == 0)
        {
            return flow;
        }
        int res = 0; // 后面流的大小的总和.
        vector<int> &es = rg[v];
        int e_len = es.size();
        for (int &i = cur[v]; i < e_len; ++i)
        {
            int idx = es[i];
            // v为from
            auto &[to, w] = edges[idx];
            if (level[to] < level[v] + 1)
            {
                continue; // 不是下边
            }
            // level[to] == level[from] + 1
            int f = _dfs(to, t, min(w, flow));
            if (f == 0)
            {
                continue;
            }
            // f > 0
            auto &[_, w2] = edges[idx ^ 1];
            w -= f;
            w2 += f;
            res += f;
            flow -= f;
            if (flow == 0)
            {
                break;
            }
        }
        return res;
    }

    int dinic(int s, int t)
    {
        // 相对于Edmonds-Karp的两点优化: 多路增广+当前弧优化. dfs是算法核心
        ///
        // 1. 建立RG(假设已建立)
        // 2. 建立level graph(BFS)
        // 3. dfs寻找多路最短路径流; 并更新rg, 反向边等.
        // 4. 更新res
        int flow = 0;
        while (_bfs(s, t))
        {
            fill(cur.begin(), cur.end(), 0);
            flow += _dfs(s, t, INT32_MAX);
        }
        return flow;
    }
};

//

class Hungarian
{
    // 匈牙利算法(解决有权二部图的最小匹配)
    //  最大匹配/最小匹配可以相互转化.
    // 因为匈牙利算法只适用于in=out=n的情况, 所以需要对少的一部分点进行加点
    // 匈牙利算法在邻接矩阵中操作. 将不存在的边设置为0
    ///
    // 略
};

// int main()
// {
//     Dinic dinic(6);
//     dinic.add_edge(0, 1, 10);
//     dinic.add_edge(0, 2, 10);
//     dinic.add_edge(1, 2, 2);
//     dinic.add_edge(1, 3, 4);
//     dinic.add_edge(1, 4, 8);
//     dinic.add_edge(2, 4, 9);
//     dinic.add_edge(3, 5, 10);
//     dinic.add_edge(4, 3, 6);
//     dinic.add_edge(4, 5, 10);
//     cout << dinic.dinic(0, 5);
//     cout << dinic.level;
//     cout << dinic.rg;
//     cout << dinic.edges;
// }

#endif