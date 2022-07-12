#include "pre.cpp"

class Solution
{
public:
    // 曼哈顿距离
    int cal_dist(int x, int y, int x2, int y2)
    {
        return abs(x2 - x) + abs(y2 - y);
    }

    int getMaximumNumber(vector<vector<int>> &moles)
    {
        // moles[i] = [t,x,y]
        // 第0秒, 锤子在1,1点
        ///
        // moles插入标尺(0,1,1). moles没有按时间排序
        // 先对moles进行排序
        // dp[0]=0
        // dp[i], 代表以moles[i]结束总共敲钟最多数.
        // 从0,0到2,2需要4秒, 所以当delta_t>=4, 则一定能敲到
        // dp[i]=max(max(t大于4前的最大),max(判断能否移动到的最大))
        /// 注意
        // 注意, t=0时的x,y导致的问题. (0,1,0) dp=-1. dp[0,1,1]=1. 
        sort(moles.begin(), moles.end(), [](vector<int> &x, vector<int> &y)
             { return x[0] < y[0]; });
        moles.emplace(moles.begin(), vector<int>{0, 1, 1});
        int n = moles.size();
        vector<int> dp(n, -1);
        vector<int> dp_max(n);
        // 初始化
        dp[0] = 0;
        // dp_max[0] = 0;

        for (int i = 1; i < n; ++i)
        {
            vector<int> &m = moles[i];
            int t1 = m[0], x1 = m[1], y1 = m[2];
            for (int j = i - 1; j >= 0; --j)
            {
                vector<int> &m2 = moles[j];
                int t2 = m2[0], x2 = m2[1], y2 = m2[2];
                int dt = t1 - t2;
                if (dt >= 4)
                {
                    dp[i] = max(dp[i], dp_max[j] + 1);
                    break;
                }
                int d = cal_dist(x1, y1, x2, y2);
                if (d <= dt)
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            dp_max[i] = max(dp_max[i - 1], dp[i]);
        }
        return dp_max[n - 1];
    }
};

int main()
{
    vector<vector<int>> v;
    str_to_matrix("[[0,1,0],[0,0,1],[0,2,1],[0,1,2],[0,0,2],[1,2,2],[1,0,0],[1,0,2],[2,0,2],[2,2,2],[2,0,1],[2,0,0],[2,2,0],[3,1,2],[3,0,0],[3,2,0],[3,0,2],[3,2,2],[3,1,0],[4,0,1],[4,1,2],[4,1,1],[4,0,2],[4,1,0],[5,0,1],[5,0,0],[5,2,0],[5,0,2],[6,1,2],[6,0,0],[6,0,2],[6,1,0],[6,2,1],[7,0,0],[7,2,0],[7,1,1],[7,1,2],[7,2,1],[8,2,2],[8,0,1],[8,2,1],[8,1,2],[8,1,1],[8,2,0],[9,1,1],[9,0,2],[9,2,2],[9,1,0],[9,2,1],[9,0,0],[9,2,0],[10,1,1],[10,0,2],[10,1,0],[10,2,2],[10,2,1],[10,1,2],[10,0,0]]", v);
    cout << Solution().getMaximumNumber(v);
    {
        vector<vector<int>> v;
        str_to_matrix("[ [ 4, 2, 1 ], [ 1, 1, 2 ], [ 2, 1, 0 ], [ 3, 2, 1 ], [ 4, 0, 0 ], [ 0, 1, 1 ] ]", v);
        cout << Solution().getMaximumNumber(v);
    }
    {
        vector<vector<int>> v;
        str_to_matrix("[[1,1,0],[2,0,1],[4,2,2]]", v);
        cout << Solution().getMaximumNumber(v);
    }
}