#include "pre.cpp"

string &vector_to_str(const vector<int> &v, string &s)
{
    int n = v.size();
    s += '[';
    for (int i = 0; i < n; ++i)
    {
        if (i != 0)
        {
            s += ',';
        }
        s += v[i] != INT32_NULL ? to_string(v[i]) : "null";
    }
    s += ']';
    return s;
}

class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string s;
        vector<int> v;
        return vector_to_str(_tree_to_vector(root, v), s);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        return str_to_tree(data);
    }
};

int main()
{
    TreeNode *tree = Codec().deserialize("[1,2,3]");
    cout << Codec().serialize(tree) << '\n';
}
