
#include "pre.cpp"
class Solution
{
public:
    int hash(int x, int y)
    {
        // 2 <= command的长度 <= 1000
        // 所以 hash=x*1005+y
        int MAXN = 1005;
        return x * MAXN + y;
    }
    bool robot(string &command, vector<vector<int>> &obstacles, int x, int y)
    {
        // x, y是1e9数量级, 所以计算复杂度要避开x, y
        // 一个command: [0,0] -> [a,b]; 前进(a,b)步. 使用hash_set存储
        // 随后将o, (x,y)减少到(a,b)内. 并判断
        int c_len = command.size(), o_len = obstacles.size();
        int a = 0, b = 0;
        unordered_set<int> visited;
        visited.insert(hash(a, b));
        for (int i = 0; i < c_len; ++i)
        {
            char ch = command[i];
            if (ch == 'R')
            {
                ++a;
                visited.insert(hash(a, b));
            }
            else
            {
                ++b;
                visited.insert(hash(a, b));
            }
        }
        //
        int dxy = min(x / a, y / b);
        int xx = x - dxy * a;
        int yy = y - dxy * b;
        if (not visited.count(hash(xx, yy)))
        {
            return false;
        }
        for (int i = 0; i < o_len; ++i)
        {
            int c = obstacles[i][0], d = obstacles[i][1];
            if (x < c or y < d)
            {
                continue;
            }
            int dcd = min(c / a, d / b);
            c -= dcd * a;
            d -= dcd * b;
            if (visited.count(hash(c, d)))
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    string command = "URRURRR";
    vector<vector<int>> obstacles = {};
    int x = 4915, y = 1966;
    cout << Solution().robot(command, obstacles, x, y);
}
