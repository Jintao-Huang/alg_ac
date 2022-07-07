
#include "pre.cpp"

class Solution
// 这里的广搜的判断放在加入时. 
// 若beginWord==endWord则会发生错误. 
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        // beginword不需要在wordList中.
        // 不存在转换返回0
        ///
        // 将wordList转化为unordered_map, 并除去beginWord
        // 使用广度优先搜索.
        // dq; 每次弹出w. 改变w的每个位置以及26个字母.
        // 如果单词在wordList中, 则删除该单词, 然后将改单词加入dq.
        // 直到dq为空或w==endWord
        unordered_set<string> ws(wordList.begin(), wordList.end());
        ws.erase(beginWord); // 如果不存在返回0
        deque<string> dq{beginWord};
        int n = beginWord.size();
        int step = 1;
        while (not dq.empty())
        {
            int dq_len = dq.size();
            for (int _ = 0; _ < dq_len; ++_)
            {
                string &w = dq.front();
                for (int i = 0; i < n; ++i)
                {
                    char ch = w[i]; // 备份
                    for (char j = 'a'; j <= 'z'; ++j)
                    {
                        if (w[i] == j)
                        {
                            continue;
                        }
                        w[i] = j;
                        if (not ws.count(w))
                        {
                            continue;
                        }
                        // res判断
                        if (w == endWord)
                        {
                            return step + 1;
                        }
                        ws.erase(w);
                        dq.push_back(w); // copy
                    }
                    w[i] = ch;
                }
                dq.pop_front(); // 避免w引用的访问free地址
            }

            ++step;
        }
        return 0;
    }
};

int main()
{
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        cout << Solution().ladderLength(beginWord, endWord, wordList);
    }
    {
        // string beginWord = "a";
        // string endWord = "c";
        // vector<string> wordList = {"a", "b", "c"};
        // cout << Solution().ladderLength(beginWord, endWord, wordList);
    }
}