#include "pre.cpp"

class Solution
{
public:
    inline int DIST(int x1, int y1, int x2, int y2)
    {
        return abs(x2 - x1) + abs(y2 - y1);
    }
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        vector<WEdge2> edges;
        int p_len = points.size();
        for (int i = 0; i < p_len; ++i)
        {
            vector<int> &pi = points[i];
            int x1 = pi[0], y1 = pi[1];
            for (int j = i + 1; j < p_len; ++j)
            {
                vector<int> &pj = points[j];
                int x2 = pj[0], y2 = pj[1];
                int d = DIST(x1, y1, x2, y2);
                edges.emplace_back(tuple(i, j, d));
            }
        }
        return kruskal(p_len, edges);
    }
};

class Solution2
{
public:
    inline int DIST(int x1, int y1, int x2, int y2)
    {
        return abs(x2 - x1) + abs(y2 - y1);
    }
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int p_len = points.size();
        vector<vector<int>> graph(p_len, vector<int>(p_len));
        for (int i = 0; i < p_len; ++i)
        {
            vector<int> &pi = points[i];
            int x1 = pi[0], y1 = pi[1];
            for (int j = i + 1; j < p_len; ++j)
            {
                vector<int> &pj = points[j];
                int x2 = pj[0], y2 = pj[1];
                int d = DIST(x1, y1, x2, y2);
                graph[i][j] = d;
                graph[j][i] = d;
            }
        }
        return prim(graph);
    }
};

int main()
{
    vector<vector<int>> v;
    str_to_matrix("[[0,0],[2,2],[3,10],[5,2],[7,0]]", v);
    cout << Solution().minCostConnectPoints(v);
    cout << Solution2().minCostConnectPoints(v);
}