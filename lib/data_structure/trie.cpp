

#ifndef _TRIE
#define _TRIE

#include "../load_modules.cpp"
#include "../io.cpp"
#include "../build_ds.cpp"

struct TrieTreeNode
{
    unordered_map<char, TrieTreeNode *> children; // 可以用vector代替
    char val;
    bool finish;
    TrieTreeNode(char val = '\0') : val(val), finish(false) {}
};
MPool<TrieTreeNode> _mpool_ttn;

class Trie
{
public:
    TrieTreeNode *root;
    Trie()
    {
        // 相当于一个多叉树. 根节点为空
        root = _mpool_ttn.create();
    }
    void insert(const string &word)
    {
        // 遍历word. 将树往下遍历.
        // 若某字母没有, 则建立节点. 若存在, 则不建立
        // 直到最后一个节点, 将当前节点的finish=true.
        int n = word.size();
        TrieTreeNode *p = root;
        for (int i = 0; i < n; ++i)
        {
            char ch = word[i];
            if (not p->children.count(ch))
            {
                p->children[ch] = _mpool_ttn.create(ch);
            }
            else
            {
                // 算法完整性
            }
            p = p->children[ch];
        }
        p->finish = true;
    }
    bool search(const string &word)
    {
        // 按这word的顺序, 不断往下遍历.
        // 直到word遍历完/无法走下去
        // 若word遍历完: 判断当前节点是否是finish节点. 若是: 则返回true. 否则false
        // 无法走下去, 则返回false
        int n = word.size();
        TrieTreeNode *p = root;
        for (int i = 0; i < n; ++i)
        {
            char ch = word[i];
            if (not p->children.count(ch))
            {
                return false;
            }
            p = p->children[ch];
        }
        return p->finish;
    }
    bool starts_with(const string &prefix)
    {
        const string &word = prefix; // 别名
        // 只改变search的return语句
        int n = word.size();
        TrieTreeNode *p = root;
        for (int i = 0; i < n; ++i)
        {
            char ch = word[i];
            if (not p->children.count(ch))
            {
                return false;
            }
            p = p->children[ch];
        }
        return true;
    }
};

#endif
