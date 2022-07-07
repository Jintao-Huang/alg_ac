
#include "pre.cpp"

class Solution
{
public:
    // dfs超时, 试试反向遍历. 出口指向入口. 需修改findLadders函数
    void dfs(vector<vector<int>> &graph, int curr, int end_idx,
             vector<string> &wordList, vector<int> &path, vector<vector<string>> &res)
    {
        // 有向无环图的遍历.
        if (curr == end_idx)
        {
            int n = path.size();
            vector<string> str_path;
            for (int i = n - 1; i >= 0; --i)
            {
                str_path.push_back(wordList[path[i]]);
            }
            res.emplace_back(move(str_path));
        }
        vector<int> &to_list = graph[curr];
        int to_len = to_list.size();
        for (int i = 0; i < to_len; ++i)
        {
            int to = to_list[i];
            path.push_back(to);
            dfs(graph, to, end_idx, wordList, path, res);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        // 同127题, 但需要先建图, 再遍历图. 图中节点需要包含beginWord和endWord
        // wordList是int->string. 我们还需要string->int. 随后我们使用int进行图的存储.
        // 然后我们使用邻接表存储图. vector<vector<int>>, 每一个vector存储 start->end
        // 在一次遍历中, 创建tmp_set, 在结束时, 使用集合减法减去.
        ///
        // 注意. 虽然1->2->3; 1->4->3. graph都需要存, 但是队列中只需要一个3.
        unordered_map<string, int> wm;
        unordered_set<int> ws;
        int wl_len = wordList.size();
        int begin_idx = -1, end_idx = -1;
        // 移动入
        for (int i = 0; i < wl_len; ++i)
        {
            string &s = wordList[i];
            wm[s] = i;
            ws.insert(i);
            if (s == beginWord)
            {
                begin_idx = i;
            }
            if (s == endWord)
            {
                end_idx = i;
            }
        }
        if (begin_idx == -1)
        {
            wordList.push_back(beginWord);
            begin_idx = wl_len;
            ++wl_len;
            wm[beginWord] = begin_idx;
            ws.insert(begin_idx);
        }
        if (end_idx == -1)
        {
            return {};
        }
        //
        vector<vector<int>> graph(wl_len);
        deque<int> dq{begin_idx};
        ws.erase(begin_idx);
        int n = beginWord.size();
        bool found = false;
        while (not dq.empty() and not found)
        {
            int dq_len = dq.size();
            unordered_set<int> tmp_s;
            for (int _ = 0; _ < dq_len; ++_)
            {
                int idx = dq.front();
                dq.pop_front();

                string &w = wordList[idx];
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
                        if (not wm.count(w))
                        {
                            continue;
                        }
                        int w_idx = wm[w];
                        if (not ws.count(w_idx))
                        {
                            continue;
                        }

                        // 注意!
                        if (not tmp_s.count(w_idx))
                        {
                            dq.push_back(w_idx);
                        }
                        tmp_s.insert(w_idx);
                        graph[w_idx].push_back(idx);
                        if (w_idx == end_idx)
                        {
                            found = true;
                        }
                    }
                    w[i] = ch;
                }
            }
            set_difference_update(ws, tmp_s);
        }
        // dfs
        if (not found)
        {
            return {};
        }
        // cout << graph << '\n';
        vector<vector<string>> res;
        vector<int> path{end_idx};
        dfs(graph, end_idx, begin_idx, wordList, path, res);
        return res;
    }
};

class Solution2
// 进行预处理. 空间换时间.
{
public:
    // dfs超时, 试试反向遍历. 出口指向入口. 需修改findLadders函数
    void dfs(vector<vector<int>> &graph, int curr, int end_idx,
             vector<string> &wordList, vector<int> &path, vector<vector<string>> &res)
    {
        // 有向无环图的遍历.
        if (curr == end_idx)
        {
            int n = path.size();
            vector<string> str_path;
            for (int i = n - 1; i >= 0; --i)
            {
                str_path.push_back(wordList[path[i]]);
            }
            res.emplace_back(move(str_path));
        }
        vector<int> &to_list = graph[curr];
        int to_len = to_list.size();
        for (int i = 0; i < to_len; ++i)
        {
            int to = to_list[i];
            path.push_back(to);
            dfs(graph, to, end_idx, wordList, path, res);
            path.pop_back();
        }
    }
    unordered_map<string, vector<int>> &processing(vector<string> &wordList,
                                                   unordered_map<string, vector<int>> &choices)
    {
        // string processing. *通配符 choices
        int wl_len = wordList.size();
        for (int i = 0; i < wl_len; ++i)
        {
            string &w = wordList[i];
            int n = w.size();
            for (int j = 0; j < n; ++j)
            {
                char ch = w[j];
                w[j] = '*';
                choices[w].push_back(i);
                w[j] = ch;
            }
        }
        return choices;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
    {
        // 同127题, 但需要先建图, 再遍历图. 图中节点需要包含beginWord和endWord
        // wordList是int->string. 我们还需要string->int. 随后我们使用int进行图的存储.
        // 然后我们使用邻接表存储图. vector<vector<int>>, 每一个vector存储 start->end
        // 在一次遍历中, 创建tmp_set, 在结束时, 使用集合减法减去.
        ///
        // 注意. 虽然1->2->3; 1->4->3. graph都需要存, 但是队列中只需要一个3.
        unordered_map<string, int> wm;
        unordered_set<int> ws;
        unordered_map<string, vector<int>> choices;
        processing(wordList, choices);
        int wl_len = wordList.size();
        int begin_idx = -1, end_idx = -1;
        // 移动入
        for (int i = 0; i < wl_len; ++i)
        {
            string &s = wordList[i];
            wm[s] = i;
            ws.insert(i);
            if (s == beginWord)
            {
                begin_idx = i;
            }
            if (s == endWord)
            {
                end_idx = i;
            }
        }
        if (begin_idx == -1)
        {
            wordList.push_back(beginWord);
            begin_idx = wl_len;
            ++wl_len;
            wm[beginWord] = begin_idx;
            ws.insert(begin_idx);
        }
        if (end_idx == -1)
        {
            return {};
        }
        //
        vector<vector<int>> graph(wl_len);
        deque<int> dq{begin_idx};
        ws.erase(begin_idx);
        int n = beginWord.size();
        bool found = false;
        while (not dq.empty() and not found)
        {
            int dq_len = dq.size();
            unordered_set<int> tmp_s;
            for (int _ = 0; _ < dq_len; ++_)
            {
                int idx = dq.front();
                dq.pop_front();

                string &w = wordList[idx];
                for (int i = 0; i < n; ++i)
                {
                    char ch = w[i]; // 备份
                    w[i] = '*';
                    if (not choices.count(w))
                    {
                        w[i] = ch;
                        continue;
                    }
                    vector<int> &choice = choices[w];
                    for (int w_idx : choice)
                    {
                        if (not ws.count(w_idx))
                        {
                            continue;
                        }

                        // 注意!
                        if (not tmp_s.count(w_idx))
                        {
                            dq.push_back(w_idx);
                        }
                        tmp_s.insert(w_idx);
                        graph[w_idx].push_back(idx);
                        if (w_idx == end_idx)
                        {
                            found = true;
                        }
                    }
                    w[i] = ch;
                }
            }
            set_difference_update(ws, tmp_s);
        }
        // dfs
        if (not found)
        {
            return {};
        }
        // cout << graph << '\n';
        vector<vector<string>> res;
        vector<int> path{end_idx};
        dfs(graph, end_idx, begin_idx, wordList, path, res);
        return res;
    }
};

int main()
{
    {
        string beginWord = "hit";
        string endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        cout << Solution().findLadders(beginWord, endWord, wordList);
        cout << Solution2().findLadders(beginWord, endWord, wordList);
    }
    // {
    //     string beginWord = "a";
    //     string endWord = "c";
    //     vector<string> wordList = {"a", "b", "c"};
    //     cout << Solution().findLadders(beginWord, endWord, wordList);
    // }

    // {
    //     string beginWord = "red";
    //     string endWord = "tax";
    //     vector<string> wordList = {"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
    //     cout << Solution().findLadders(beginWord, endWord, wordList);
    // }
    // {
    //     string beginWord = "aaaaa";
    //     string endWord = "ggggg";
    //     vector<string> wordList = {"aaaaa", "caaaa", "cbaaa", "daaaa", "dbaaa", "eaaaa", "ebaaa", "faaaa", "fbaaa", "gaaaa", "gbaaa", "haaaa", "hbaaa", "iaaaa", "ibaaa", "jaaaa", "jbaaa", "kaaaa", "kbaaa", "laaaa", "lbaaa", "maaaa", "mbaaa", "naaaa", "nbaaa", "oaaaa", "obaaa", "paaaa", "pbaaa", "bbaaa", "bbcaa", "bbcba", "bbdaa", "bbdba", "bbeaa", "bbeba", "bbfaa", "bbfba", "bbgaa", "bbgba", "bbhaa", "bbhba", "bbiaa", "bbiba", "bbjaa", "bbjba", "bbkaa", "bbkba", "bblaa", "bblba", "bbmaa", "bbmba", "bbnaa", "bbnba", "bboaa", "bboba", "bbpaa", "bbpba", "bbbba", "abbba", "acbba", "dbbba", "dcbba", "ebbba", "ecbba", "fbbba", "fcbba", "gbbba", "gcbba", "hbbba", "hcbba", "ibbba", "icbba", "jbbba", "jcbba", "kbbba", "kcbba", "lbbba", "lcbba", "mbbba", "mcbba", "nbbba", "ncbba", "obbba", "ocbba", "pbbba", "pcbba", "ccbba", "ccaba", "ccaca", "ccdba", "ccdca", "cceba", "cceca", "ccfba", "ccfca", "ccgba", "ccgca", "cchba", "cchca", "cciba", "ccica", "ccjba", "ccjca", "cckba", "cckca", "cclba", "cclca", "ccmba", "ccmca", "ccnba", "ccnca", "ccoba", "ccoca", "ccpba", "ccpca", "cccca", "accca", "adcca", "bccca", "bdcca", "eccca", "edcca", "fccca", "fdcca", "gccca", "gdcca", "hccca", "hdcca", "iccca", "idcca", "jccca", "jdcca", "kccca", "kdcca", "lccca", "ldcca", "mccca", "mdcca", "nccca", "ndcca", "occca", "odcca", "pccca", "pdcca", "ddcca", "ddaca", "ddada", "ddbca", "ddbda", "ddeca", "ddeda", "ddfca", "ddfda", "ddgca", "ddgda", "ddhca", "ddhda", "ddica", "ddida", "ddjca", "ddjda", "ddkca", "ddkda", "ddlca", "ddlda", "ddmca", "ddmda", "ddnca", "ddnda", "ddoca", "ddoda", "ddpca", "ddpda", "dddda", "addda", "aedda", "bddda", "bedda", "cddda", "cedda", "fddda", "fedda", "gddda", "gedda", "hddda", "hedda", "iddda", "iedda", "jddda", "jedda", "kddda", "kedda", "lddda", "ledda", "mddda", "medda", "nddda", "nedda", "oddda", "oedda", "pddda", "pedda", "eedda", "eeada", "eeaea", "eebda", "eebea", "eecda", "eecea", "eefda", "eefea", "eegda", "eegea", "eehda", "eehea", "eeida", "eeiea", "eejda", "eejea", "eekda", "eekea", "eelda", "eelea", "eemda", "eemea", "eenda", "eenea", "eeoda", "eeoea", "eepda", "eepea", "eeeea", "ggggg", "agggg", "ahggg", "bgggg", "bhggg", "cgggg", "chggg", "dgggg", "dhggg", "egggg", "ehggg", "fgggg", "fhggg", "igggg", "ihggg", "jgggg", "jhggg", "kgggg", "khggg", "lgggg", "lhggg", "mgggg", "mhggg", "ngggg", "nhggg", "ogggg", "ohggg", "pgggg", "phggg", "hhggg", "hhagg", "hhahg", "hhbgg", "hhbhg", "hhcgg", "hhchg", "hhdgg", "hhdhg", "hhegg", "hhehg", "hhfgg", "hhfhg", "hhigg", "hhihg", "hhjgg", "hhjhg", "hhkgg", "hhkhg", "hhlgg", "hhlhg", "hhmgg", "hhmhg", "hhngg", "hhnhg", "hhogg", "hhohg", "hhpgg", "hhphg", "hhhhg", "ahhhg", "aihhg", "bhhhg", "bihhg", "chhhg", "cihhg", "dhhhg", "dihhg", "ehhhg", "eihhg", "fhhhg", "fihhg", "ghhhg", "gihhg", "jhhhg", "jihhg", "khhhg", "kihhg", "lhhhg", "lihhg", "mhhhg", "mihhg", "nhhhg", "nihhg", "ohhhg", "oihhg", "phhhg", "pihhg", "iihhg", "iiahg", "iiaig", "iibhg", "iibig", "iichg", "iicig", "iidhg", "iidig", "iiehg", "iieig", "iifhg", "iifig", "iighg", "iigig", "iijhg", "iijig", "iikhg", "iikig", "iilhg", "iilig", "iimhg", "iimig", "iinhg", "iinig", "iiohg", "iioig", "iiphg", "iipig", "iiiig", "aiiig", "ajiig", "biiig", "bjiig", "ciiig", "cjiig", "diiig", "djiig", "eiiig", "ejiig", "fiiig", "fjiig", "giiig", "gjiig", "hiiig", "hjiig", "kiiig", "kjiig", "liiig", "ljiig", "miiig", "mjiig", "niiig", "njiig", "oiiig", "ojiig", "piiig", "pjiig", "jjiig", "jjaig", "jjajg", "jjbig", "jjbjg", "jjcig", "jjcjg", "jjdig", "jjdjg", "jjeig", "jjejg", "jjfig", "jjfjg", "jjgig", "jjgjg", "jjhig", "jjhjg", "jjkig", "jjkjg", "jjlig", "jjljg", "jjmig", "jjmjg", "jjnig", "jjnjg", "jjoig", "jjojg", "jjpig", "jjpjg", "jjjjg", "ajjjg", "akjjg", "bjjjg", "bkjjg", "cjjjg", "ckjjg", "djjjg", "dkjjg", "ejjjg", "ekjjg", "fjjjg", "fkjjg", "gjjjg", "gkjjg", "hjjjg", "hkjjg", "ijjjg", "ikjjg", "ljjjg", "lkjjg", "mjjjg", "mkjjg", "njjjg", "nkjjg", "ojjjg", "okjjg", "pjjjg", "pkjjg", "kkjjg", "kkajg", "kkakg", "kkbjg", "kkbkg", "kkcjg", "kkckg", "kkdjg", "kkdkg", "kkejg", "kkekg", "kkfjg", "kkfkg", "kkgjg", "kkgkg", "kkhjg", "kkhkg", "kkijg", "kkikg", "kkljg", "kklkg", "kkmjg", "kkmkg", "kknjg", "kknkg", "kkojg", "kkokg", "kkpjg", "kkpkg", "kkkkg", "ggggx", "gggxx", "ggxxx", "gxxxx", "xxxxx", "xxxxy", "xxxyy", "xxyyy", "xyyyy", "yyyyy", "yyyyw", "yyyww", "yywww", "ywwww", "wwwww", "wwvww", "wvvww", "vvvww", "vvvwz", "avvwz", "aavwz", "aaawz", "aaaaz"};
    //     cout << Solution().findLadders(beginWord, endWord, wordList);
    // }
}