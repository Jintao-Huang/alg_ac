

#include "pre.cpp"
class Solution
{
public:
    long long minimumWeight(int n, vector<vector<int>> &edges, int src1, int src2, int dest)
    {
        // 子图边权和最小. src1->dst, src2->dst.
        // 即最小边: min{t}(src1->t+src2->t+t->dst).
        // dijkstra计算三次.
        // 随后遍历t
        ///
        // 先建图, 使用邻接表, 存储pair<to, dist>
        vector<vector<pair<int, int>>> graph(n);
        vector<vector<pair<int, int>>> graph_r(n);
        int e_len = edges.size();
        for (int i = 0; i < e_len; ++i)
        {
            vector<int> &e = edges[i];
            int from = e[0], to = e[1], dist = e[2];
            graph[from].emplace_back(pair(to, dist));
            graph_r[to].emplace_back(pair(from, dist));
        }
        vector<long long> res1, res2, resd;
        dijkstra(graph, src1, res1);
        dijkstra(graph, src2, res2);
        dijkstra(graph_r, dest, resd);
        long long res = INT64_MAX;
        for (int i = 0; i < n; ++i)
        {
            res = min(res, (res1[i] != INT64_MAX and res2[i] != INT64_MAX and resd[i] != INT64_MAX) ? (res1[i] + res2[i] + resd[i]) : INT64_MAX);
        }
        return res != INT64_MAX ? res : -1;
    }
};

class Solution2
// 使用dijkstra2
{
public:
    long long minimumWeight(int n, vector<vector<int>> &edges, int src1, int src2, int dest)
    {
        // 子图边权和最小. src1->dst, src2->dst.
        // 即最小边: min{t}(src1->t+src2->t+t->dst).
        // dijkstra计算三次.
        // 随后遍历t
        ///
        // 先建图, 使用邻接表, 存储pair<to, dist>
        vector<vector<pair<int, int>>> graph(n);
        vector<vector<pair<int, int>>> graph_r(n);
        int e_len = edges.size();
        for (int i = 0; i < e_len; ++i)
        {
            vector<int> &e = edges[i];
            int from = e[0], to = e[1], dist = e[2];
            graph[from].emplace_back(pair(to, dist));
            graph_r[to].emplace_back(pair(from, dist));
        }
        vector<long long> res1, res2, resd;
        dijkstra2(graph, src1, res1);
        dijkstra2(graph, src2, res2);
        dijkstra2(graph_r, dest, resd);
        long long res = INT64_MAX;
        for (int i = 0; i < n; ++i)
        {
            res = min(res, (res1[i] != INT64_MAX and res2[i] != INT64_MAX and resd[i] != INT64_MAX) ? (res1[i] + res2[i] + resd[i]) : INT64_MAX);
        }
        return res != INT64_MAX ? res : -1;
    }
};

int main()
{
    int n = 6;
    vector<vector<int>> edges;
    str_to_matrix("[[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]]", edges);
    int src1 = 0, src2 = 1, dest = 5;
    cout << Solution().minimumWeight(n, edges, src1, src2, dest);
    cout << Solution2().minimumWeight(n, edges, src1, src2, dest);
}