// Author: Jintao Huang
// Email: hjt_study@qq.com
// Date:

#ifndef _SET
#define _SET
#include "../build_ds.cpp"
#include "../load_modules.cpp"

template <class T>
unordered_set<T> &set_union(unordered_set<T> &s, unordered_set<T> &s2, unordered_set<T> &dst)
{
    // 将s, s2的值插入dst中即可
    dst = s;
    for (auto &e : s2)
    {
        dst.insert(e);
    }
    return dst;
}
template <class T>
unordered_set<T> &set_union_update(unordered_set<T> &s, unordered_set<T> &s2)
{
    // 将s, s2的值插入dst中即可
    for (auto &e : s2)
    {
        s.insert(e);
    }
    return s;
}

template <class T>
unordered_set<T> &set_intersection(unordered_set<T> &s, unordered_set<T> &s2, unordered_set<T> &dst)
{
    for (auto &e : s2)
    {
        if (s.count(e))
        {
            dst.insert(e);
        }
    }
    return dst;
}

template <class T>
unordered_set<T> &set_difference(unordered_set<T> &s, unordered_set<T> &s2, unordered_set<T> &dst)
{
    dst = s;
    for (auto &e : s2)
    {
        dst.erase(e);
    }
    return dst;
}

template <class T>
unordered_set<T> &set_difference_update(unordered_set<T> &s, unordered_set<T> &s2)
{
    for (auto &e : s2)
    {
        s.erase(e);
    }
    return s;
}

template <class T>
unordered_set<T> &set_symmetric_difference(unordered_set<T> &s, unordered_set<T> &s2, unordered_set<T> &dst)
{
    for (auto &e : s)
    {
        if (not s2.count(e))
        {
            dst.insert(e);
        }
    }
    for (auto &e : s2)
    {
        if (not s.count(e))
        {
            dst.insert(e);
        }
    }
    return dst;
}

template <class T>
bool issuperset(unordered_set<T> &s, unordered_set<T> &s2)
{
    // s是s2的超集, 即为s >= s2
    for (auto &e : s2)
    {
        if (not s.count(e))
        {
            return false;
        }
    }
    return true;
}
template <class T>
bool operator>(unordered_set<T> &s, unordered_set<T> &s2)
{
    return issuperset(s, s2) and s.size() > s2.size();
}

template <class T>
bool operator>=(unordered_set<T> &s, unordered_set<T> &s2)
{
    return issuperset(s, s2);
}

template <class T>
bool issubset(unordered_set<T> &s, unordered_set<T> &s2)
{
    // s <= s2
    for (auto &e : s)
    {
        if (not s2.count(e))
        {
            return false;
        }
    }
    return true;
}

template <class T>
bool operator<(unordered_set<T> &s, unordered_set<T> &s2)
{
    return issubset(s, s2) and s.size() < s2.size();
}

template <class T>
bool operator<=(unordered_set<T> &s, unordered_set<T> &s2)
{
    return issubset(s, s2);
}

template <class T>
bool isdisjoint(unordered_set<T> &s, unordered_set<T> &s2)
{
    // 不相交的, 即: s & s2 为空集
    for (auto &e : s)
    {
        if (s2.count(e))
        {
            return false;
        }
    }
    return true;
}

// int main()
// {
//     unordered_set<int> s = {1, 2, 3};
//     unordered_set<int> s2 = {1, 4, 3};
//     unordered_set<int> s3;
//     cout << set_union(s, s2, s3) << '\n';
//     cout << set_union_update(s, s2) << '\n';
//     s3.clear();
//     cout << set_intersection(s, s2, s3) << '\n';
//     s3.clear();
//     cout << set_difference(s, s2, s3) << '\n';
//     cout << set_difference_update(s, s2) << '\n';
//     s3.clear();
//     cout << set_symmetric_difference(s, s2, s3) << '\n';
//     s3.clear();
//     //
//     s = {1, 2, 3};
//     s2 = {1, 2};
//     cout << (s < s2);
//     cout << (s <= s);
//     cout << (s > s2);
//     cout << (s >= s);
//     s2 = {4};
//     cout << isdisjoint(s, s2);
// }

#endif