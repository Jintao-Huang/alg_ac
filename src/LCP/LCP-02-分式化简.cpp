
#include "pre.cpp"
class Solution
{
public:
    pair<int, int> dfs(vector<int> &cont, int idx)
    { 
        // e=c+1/(a/b)=(ac+b)/a=d/a
        // d=ac+b
        int a, b, c, d, e;
        c = cont[idx];
        if (idx == cont.size() - 1)
        {
            return pair(c, 1);
        }
        tie(a, b) = dfs(cont, idx + 1);
        d = a * c + b;
        int gcd_ = gcd(d, a);

        return pair(d / gcd_, a / gcd_);
    }

    vector<int> fraction(vector<int> &cont)
    {
        // 所有系数都大于等于0
        // 返回[n, m], 代表n/m; 最大公约数=1
        ///
        // 可以使用递归的方式, 直到ai
        // b+1/a=(ab+1)/a, 计算gcd, 然后再同除以, 得值
        pair<int, int> p = dfs(cont, 0);
        return vector<int>{p.first, p.second};
    }
};

int main()
{
    {
        vector<int> cont{3, 2, 0, 2};
        cout << Solution().fraction(cont);
    }
    {
        vector<int> cont{0, 0, 3};
        cout << Solution().fraction(cont);
    }
}