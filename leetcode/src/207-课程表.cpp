#include "pre.cpp"
class Solution
// 拓扑排序
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        // prerequisites[i] = [ai, bi]; ai前必须先学bi. 即bi -> ai
        // 我们首先需要建图(边为 前导课->课), (需要知道这个节点的出边有哪些, 当删除节点时需要使用)
        // 有一个计数器用来计数所有定点的, 计算入边的数量. 不断移除入边为0的边. 直到边为0
        // 直到不能移除为止, 即移除队列为空.

        deque<int> dq;
        int &n = numCourses; // 别名
        vector<int> counter(n);
        vector<vector<int>> graph(n, vector<int>()); // 记录出边
        int m = prerequisites.size();
        for (int i = 0; i < m; ++i)
        {
            vector<int> &p = prerequisites[i];
            int from = p[1], to = p[0];
            counter[to] += 1;
            graph[from].push_back(to);
        }
        // 初始化dq
        for (int i = 0; i < n; ++i)
        {
            if (counter[i] == 0)
            {
                dq.push_back(i);
            }
        }
        int rm_counter = 0;
        while (not dq.empty())
        {
            int x = dq.front();
            dq.pop_front();
            ++rm_counter;
            vector<int> &v = graph[x];
            int n_to = v.size();
            for (int i = 0; i < n_to; ++i)
            {
                int y = v[i];
                --counter[y];
                if (counter[y] == 0)
                {
                    dq.push_back(y);
                }
            }
        }
        return rm_counter == n;
    }
};
int main()
{
    int numCourses = 2;
    vector<vector<int>> prerequisites{{1, 0}};
    cout << Solution().canFinish(numCourses, prerequisites);
}