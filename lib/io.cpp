#ifndef _IO
#define _IO

#include "load_modules.cpp"

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

// template <class T1, class T2>
// ostream &operator<<(ostream &out, const pair<T1, T2> &p)
// {
//     out << '<' << p.first << ", " << p.second << '>';
//     return out;
// }

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

template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &m)
{
    out << '[';
    int r_len = m.size();
    for (int i = 0; i < r_len; ++i)
    {
        if (i != 0)
        {
            out << ", ";
        }
        //
        cout << m[i];
    }
    out << ']';
    return out;
}

template <class T>
using pTi = pair<T, int>;

template <class T>
ostream &operator<<(ostream &out, const vector<pTi<T>> &vp)
{
    out << '{';
    bool is_first = true;
    for (const pair<T, int> &p : vp)
    {
        if (is_first)
        {
            is_first = false;
        }
        else
        {
            out << ", ";
        }
        out << p.first << ": " << p.second;
    }
    out << '}';
    return out;
}

template <class T>
vector<pTi<T>> &_unordered_map_to_vector(const unordered_map<T, int> &um, vector<pTi<T>> &dst)
{
    for (typename unordered_map<T, int>::const_iterator it = um.begin(); it != um.end(); ++it)
    {
        dst.emplace_back(*it);
    }
    return dst;
}

template <class T>
ostream &operator<<(ostream &out, const unordered_map<T, int> &um)
{
    vector<pTi<T>> vpTi;
    out << _unordered_map_to_vector(um, vpTi);
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
// }

#endif