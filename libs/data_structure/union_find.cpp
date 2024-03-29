// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _UNION_FIND
#define _UNION_FIND
#include "../load_modules.cpp"

class UFSet
{
private:
    int cnt;
    int n;
    vector<int> parent;
    vector<int> sizes;

public:
    // cnt: ufset的个数
    // sizes: 使用每个ufset的size(不使用树高)来作为合并的指标
    UFSet(int n) : n(n), cnt(n), parent(n), sizes(n, 1)
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i; // 代表没有父节点, 自己是根节点
        }
    }
    int find_root(int a)
    {
        // 找根节点
        if (parent[a] != a)
        {
            parent[a] = find_root(parent[a]);
        }
        return parent[a];
    }
    inline int size(int a)
    {
        // 查看某uf_set的大小
        return sizes[find_root(a)];
    }
    inline int size()
    {
        // 返回uf_set的数量
        return cnt;
    }
    bool union_ufset(int a, int b)
    {
        // 返回是否合并成功
        int ra = find_root(a), rb = find_root(b);
        if (ra == rb)
        {
            return false;
        }
        if (sizes[ra] >= sizes[rb])
        {
            sizes[ra] += sizes[rb];
            parent[rb] = ra;
        }
        else
        {
            sizes[rb] += sizes[ra];
            parent[ra] = rb;
        }
        cnt -= 1;
        return true;
        ;
    }
};

int main()
{
    UFSet ufset(10);
    cout << ufset.union_ufset(0, 1) << '\n';
    cout << ufset.union_ufset(0, 1) << '\n';
    cout << ufset.union_ufset(2, 3) << '\n';
    cout << ufset.union_ufset(1, 5) << '\n';
    cout << ufset.union_ufset(1, 2) << '\n';
    cout << ufset.size(1) << '\n';
    cout << ufset.size() << '\n';
}
#endif