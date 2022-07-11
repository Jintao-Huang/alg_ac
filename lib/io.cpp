#ifndef _IO
#define _IO

#include "load_modules.cpp"

/// vector
template <class T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    out << '[';
    int v_len = v.size();
    for (int i = 0; i < v_len; ++i)
    {
        T x = v[i];
        if (i != 0)
        {
            out << ", ";
        }
        //
        out << x;
    }
    out << ']';
    return out;
}

/// pair
template <class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p)
{
    out << "pair(" << p.first << ", " << p.second << ")";
    return out;
}

/// unordered_set
template <class T>
ostream &operator<<(ostream &out, const unordered_set<T> &v)
{
    out << '{';
    int v_len = v.size();
    auto first = v.begin(), last = v.end();
    for (auto p = first; p != last; ++p)
    {
        T x = *p;
        if (p != first)
        {
            out << ", ";
        }
        //
        out << x;
    }
    out << '}';
    return out;
}

/// vector<int>特化, 支持null
template <>
ostream &operator<<(ostream &out, const vector<int> &v)
{
    out << '[';
    int v_len = v.size();
    for (int i = 0; i < v_len; ++i)
    {
        int x = v[i];
        if (i != 0)
        {
            out << ", ";
        }
        //
        if (x == INT32_NULL)
        {
            out << "null";
        }
        else
        {
            out << x;
        }
    }
    out << ']';
    return out;
}

/// unordered_map
template <class T1, class T2>
vector<pair<T1, T2>> &_unordered_map_to_vector(const unordered_map<T1, T2> &um, vector<pair<T1, T2>> &dst)
{
    for (typename unordered_map<T1, T2>::const_iterator it = um.begin(); it != um.end(); ++it)
    {
        dst.emplace_back(*it);
    }
    return dst;
}

template <class T1, class T2>
ostream &operator<<(ostream &out, const unordered_map<T1, T2> &um)
{
    vector<pair<T1, T2>> vp;
    out << _unordered_map_to_vector(um, vp);
    return out;
}

// int main()
// {
//     unordered_map<string, int> um;
//     um["123"] = 1;
//     um["#45"] = 5;
//     cout << um << '\n';
//     //
//     unordered_map<int, int> um2;
//     um2[2] = 1;
//     um2[3] = 5;
//     cout << um2 << '\n';
//     vector<vector<char>> m = {{'X', 'O', 'X'}, {'O', 'X', 'X'}};
//     cout << m << '\n';
//     // [pair(#45, 5), pair(123, 1)]
//     // [pair(3, 5), pair(2, 1)]
//     // [[X, O, X], [O, X, X]]
// }

#endif