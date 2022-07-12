#ifndef _IO
#define _IO

#include "load_modules.cpp"

/// vector

template <class InputIterator>
ostream &print(ostream &out, InputIterator first, InputIterator last)
{
    for (auto it = first; it != last; ++it)
    {
        typename iterator_traits<InputIterator>::value_type x = *it;
        if (it != first)
        {
            out << ", ";
        }
        //
        out << x;
    }
    return out;
}

template <class T>
ostream &operator<<(ostream &out, const vector<T> &v)
{
    out << '[';
    print(out, v.begin(), v.end());
    out << ']';
    return out;
}

template <class T, size_t N>
ostream &operator<<(ostream &out, const array<T, N> &arr)
{
    out << '[';
    print(out, arr.begin(), arr.end());
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
ostream &operator<<(ostream &out, const unordered_set<T> &us)
{
    out << '{';
    print(out, us.begin(), us.end());
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
ostream &operator<<(ostream &out, const unordered_map<T1, T2> &um)
{
    out << '{';
    print(out, um.begin(), um.end());
    out << '}';
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