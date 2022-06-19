#include "load-modules.cpp"
#include "io.cpp"

/* List */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int _get_number(const string &s, int &p)
{
    int flag = 1; // 1: 正; -1: 负
    if (p > 0 and s[p - 1] == '-')
    {
        flag = -1;
    }
    // 默认第一位是isdigit
    int res = s[p++] - '0';
    while (isdigit(s[p]))
    {
        res *= 10;
        res += s[p++] - '0';
    }
    return res * flag;
}

vector<int> &str_to_vector(const string &s, vector<int> &dst)
{
    int s_len = s.size();
    for (int i = 0; i < s_len; i++)
    {
        char c = s[i];
        if (isdigit(c))
        {
            dst.push_back(_get_number(s, i));
        }
    }
    return dst;
}

// 未进行垃圾回收
ListNode *str_to_list(const string &s)
{
    vector<int> v;
    str_to_vector(s, v);
    int v_len = v.size();
    if (v_len == 0)
    {
        return nullptr;
    }
    ListNode *head, *p;
    // 直接赋第一个
    head = p = new ListNode(v[0]);
    for (int i = 1; i < v_len; i++)
    {
        int x = v[i];
        p->next = new ListNode(x);
        p = p->next;
    }
    return head;
}

vector<int> &_list_to_vector(ListNode *head, vector<int> &dst)
{
    while (head != nullptr)
    {
        dst.push_back(head->val);
        head = head->next;
    }
    return dst;
}

ostream &operator<<(ostream &out, ListNode *head)
{
    vector<int> v;
    out << _list_to_vector(head, v);
    return out;
}

/* Tree */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool _is_null(const string &s, int &p)
{
    int null_len = 4;
    char null_str[null_len + 1] = "null";
    for (int i = 0; i < null_len; i++)
    {
        if (s[p + i] != null_str[i])
        {
            return false;
        }
    }
    p += null_len;
    return true;
}

vector<TreeNode *> &_str_to_tn_vector(const string &s, vector<TreeNode *> &dst)
{
    int s_len = s.size();
    for (int i = 0; i < s_len; i++)
    {
        char c = s[i];
        if (isdigit(c))
        {
            int x = _get_number(s, i);
            dst.push_back(new TreeNode(x));
        }
        else if (_is_null(s, i))
        {
            dst.push_back(nullptr);
        }
    }
    return dst;
}

// 未进行垃圾回收
TreeNode *str_to_tree(const string &s)
{
    vector<TreeNode *> v;
    _str_to_tn_vector(s, v);
    int v_len = v.size();
    if (v_len == 0)
    {
        return nullptr;
    }
    TreeNode *root = v[0];
    deque<TreeNode *> dq{root};
    int i = 1;
    while (i < v_len)
    {
        // 两个为一个单位
        TreeNode *p = dq.front();
        dq.pop_front();
        TreeNode *tn = v[i++];
        dq.push_back(tn);
        p->left = tn;
        //
        if (i < v_len)
        {
            tn = v[i++];
            dq.push_back(tn);
            p->right = tn;
        }
    }
    return root;
}

vector<int> &_remove_last_null(vector<int> &v)
{
    int v_len = v.size();
    for (int i = v_len - 1; i >= 0; i--)
    {
        if (v[i] != INT32_NULL)
        {
            return v;
        }
        v.pop_back();
    }
    return v;
}

vector<int> &_tree_to_vector(TreeNode *root, vector<int> &v)
{
    deque<TreeNode *> dq{root};
    while (not dq.empty())
    {
        TreeNode *tn = dq.front();
        dq.pop_front();
        v.push_back(tn ? tn->val : INT32_NULL);
        if (tn == nullptr)
        {
            continue;
        }
        dq.push_back(tn->left);
        dq.push_back(tn->right);
    }
    return _remove_last_null(v);
}
ostream &operator<<(ostream &out, TreeNode *root)
{
    vector<int> tv;
    out << _tree_to_vector(root, tv);
    return out;
}

// int main()
// {
//     vector<int> v;
//     str_to_vector("[12, 23, 45]", v);
//     cout << v << '\n';
//     //
//     ListNode *head = str_to_list("[12, 23, 45]");
//     cout << head << '\n';
//     //
//     TreeNode *root = str_to_tree("[-10, 9, 20, null, null, 15, 7]");
//     cout << root << '\n';
// }
