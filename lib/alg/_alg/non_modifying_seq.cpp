
#ifndef _NON_MODIFYING_SEQ
#define _NON_MODIFYING_SEQ

// stl int型简单实现
#include "../../load_modules.cpp"
#include "../../io.cpp"

// InputIterator: 相当于含const, 且只能过一遍, 随后就消失了.
// UnaryPredicate: 返回bool, 单参数. (Function没有此限制).
// BinaryPredicate与Compare的区别: 等于的true和false; 比较的true和false.

// 使用vector<int>

template <class InputIterator, class UnaryPredicate>
bool _all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // 1. 遍历, first不断增加, 知道等于last, 退出循环.
    // 2. 如果遇到pred预测为false, 直接返回false. 如果都为true, 则返回true
    while (first != last)
    {
        if (not pred(*first))
        {
            return false;
        }
        ++first;
    }
    return true;
}

template <class InputIterator, class UnaryPredicate>
bool _any_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // 遍历, 知道first==last
    // 若出现true， 则返回true. 否则, 都是false, 返回false
    while (first != last)
    {
        if (pred(*first))
        {
            return true;
        }
        ++first;
    }
    return false;
}

template <class InputIterator, class UnaryPredicate>
bool _none_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // 若出现true, 则返回false. 否则一直是false, 返回true.
    while (first != last)
    {
        if (pred(*first))
        {
            return false;
        }
        ++first;
    }
    return true;
}

template <class InputIterator, class Function>
Function _for_each(InputIterator first, InputIterator last, Function fn)
{
    // 遍历, 知道first!=last
    // 对每个元素执行fn
    while (first != last)
    {
        fn(*first);
        ++first;
    }
    // 这里的Function返回使用 右值引用. (注意: 要避免引用局部变量).
    return move(fn);
}

template <class InputIterator, class T>
InputIterator _find(InputIterator first, InputIterator last, const T &val)
{
    // 遍历, 若等于val, 则返回地址. 否则直到跳出循环, 返回last
    while (first != last)
    {
        if (*first == val)
        {
            return first;
        }
        ++first;
    }
    return last;
}

template <class InputIterator, class UnaryPredicate>
InputIterator _find_if(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // 遍历, 若pred(*first), 为true, 则找到, 返回first. 否则没找到返回last.
    while (first != last)
    {
        if (pred(*first))
        {
            return first;
        }
        ++first;
    }
    return last;
}

template <class InputIterator, class UnaryPredicate>
InputIterator _find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // 遍历, 若pred(*first), 为true, 则找到, 返回first. 否则没找到返回last.
    while (first != last)
    {
        if (not pred(*first))
        {
            return first;
        }
        ++first;
    }
    return last;
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 _find_end(ForwardIterator1 first1, ForwardIterator2 last1,
                           ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
{
    // 找[first2, last2)在[first1, last1)最后一次出现位置.
    // 若[first2, last2)为空, 则直接返回last1.
    // 复杂度. O(MN), M=last1-first1, N=last2-first2.
    // 1. 遍历first1->last1. 如果匹配不上, 则移动first1, 重新匹配.
    if (first2 == last2)
        return last1;
    ForwardIterator1 res = last1;
    while (first1 != last1)
    {
        ForwardIterator1 it1 = first1;
        ForwardIterator2 it2 = first2;
        while (pred(*it1, *it2))
        { // *it1 == *it2
            ++it1;
            ++it2;
            // 越界判断
            if (it2 == last2)
            {
                res = first1;
                break;
            }
            if (it1 == last1)
            {
                return res;
            }
        }
        ++first1;
    }
    return res;
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 _search(ForwardIterator1 first1, ForwardIterator2 last1,
                         ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred)
{
    // 找[first2, last2)在[first1, last1)第一次出现位置.
    // 若[first2, last2)为空, 则直接返回last1.
    // 复杂度. O(MN),
    // 1. 遍历first1->last1. 如果匹配不上, 则移动first1, 重新匹配. 匹配上则直接返回
    // 2. 匹配: 设置两个指针, 从first1, first2, 开始匹配. 两种越界情况.
    if (first2 == last2)
        return last1;
    while (first1 != last1)
    {
        ForwardIterator1 it1 = first1;
        ForwardIterator2 it2 = first2;
        while (pred(*it1, *it2))
        { // *it1 == *it2
            ++it1;
            ++it2;
            // 越界判断
            if (it2 == last2)
            {
                return first1;
            }
            if (it1 == last1)
            {
                return last1;
            }
        }
        ++first1;
    }
    return last1;
}

template <class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator _find_first_of(InputIterator first1, InputIterator last1,
                             ForwardIterator first2, ForwardIterator last2, BinaryPredicate pred)
{
    // 找[first2, last2)中任意一元素在[first1, last1)的位置.
    // 1. 遍历first1, 如果包含在X2中, 则返回first1. 遍历完后没有包含, 则返回last1.
    // 2. 包含: 遍历[first2, last2), 是否有等于. 有则直接返回, 无则退出循环.
    while (first1 != last1)
    {
        for (ForwardIterator it = first2; it != last2; ++it)
        {
            if (pred(*it, *first1)) // *it==*first1
            {
                return first1;
            }
        }
        ++first1;
    }
    return last1;
}

template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
_count(InputIterator first, InputIterator last, const T &val)
{
    typename iterator_traits<InputIterator>::difference_type res = 0;
    while (first != last)
    {
        if (*first == val)
        {
            ++res;
        }
        ++first;
    }
    return res;
}

template <class InputIterator, class UnaryPredicate>
typename iterator_traits<InputIterator>::difference_type
_count_if(InputIterator first, InputIterator last, UnaryPredicate pred)
{
    typename iterator_traits<InputIterator>::difference_type res = 0;
    while (first != last)
    {
        if (pred(*first))
        {
            ++res;
        }
        ++first;
    }
    return res;
}

// 容器已经重载了==等比较运算符.

int main()
{
    array<int, 7> arr = {1, 2, 3, 4, 5, 6, 7};

    cout << _all_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 1; });
    cout << _all_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 2; });
    cout << all_of(arr.begin(), arr.end(), [](int x) -> bool
                   { return x >= 1; });
    cout << all_of(arr.begin(), arr.end(), [](int x) -> bool
                   { return x >= 2; })
         << '\n';
    // 1010
    cout << _any_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 7; });
    cout << _any_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 8; });
    cout << any_of(arr.begin(), arr.end(), [](int x) -> bool
                   { return x >= 7; });
    cout << any_of(arr.begin(), arr.end(), [](int x) -> bool
                   { return x >= 8; })
         << '\n';
    // 1010
    cout << _none_of(arr.begin(), arr.end(), [](int x) -> bool
                     { return x >= 7; });
    cout << _none_of(arr.begin(), arr.end(), [](int x) -> bool
                     { return x >= 8; });
    cout << none_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 7; });
    cout << none_of(arr.begin(), arr.end(), [](int x) -> bool
                    { return x >= 8; })
         << '\n';
    // 0101
    vector<int> v;
    auto fn = [&v](int x) -> void
    {
        if (x >= 3)
        {
            v.push_back(2 * x);
        }
    };
    _for_each(arr.begin(), arr.end(), fn);
    cout << v << '\n';
    v.resize(0);
    for_each(arr.begin(), arr.end(), fn);
    cout << v << '\n';
    // [6, 8, 10, 12, 14]
    // [6, 8, 10, 12, 14]
    cout << *_find(arr.begin(), arr.end(), 6);
    cout << (_find(arr.begin(), arr.end(), 10) == arr.end());
    cout << *find(arr.begin(), arr.end(), 6);
    cout << (find(arr.begin(), arr.end(), 10) == arr.end()) << '\n';
    // 6161
    cout << *_find_if(arr.begin(), arr.end(), [](int x) -> bool
                      { return x >= 6; });
    cout << (_find_if(arr.begin(), arr.end(), [](int x) -> bool
                      { return x >= 10; }) == arr.end());
    cout << *find_if(arr.begin(), arr.end(), [](int x) -> bool
                     { return x >= 6; });
    cout << (find_if(arr.begin(), arr.end(), [](int x) -> bool
                     { return x >= 10; }) == arr.end())
         << '\n';
    // 6161
    cout << *_find_if_not(arr.begin(), arr.end(), [](int x) -> bool
                          { return x < 6; });
    cout << (_find_if_not(arr.begin(), arr.end(), [](int x) -> bool
                          { return x < 10; }) == arr.end());
    cout << *find_if_not(arr.begin(), arr.end(), [](int x) -> bool
                         { return x < 6; });
    cout << (find_if_not(arr.begin(), arr.end(), [](int x) -> bool
                         { return x < 10; }) == arr.end())
         << '\n';
    // 6161
    string s = "1234512345";
    string s2 = "345";
    cout << distance(s.begin(), _find_end(s.begin(), s.end(), s2.begin(), s2.end(), [](int x, int y) -> bool
                                          { return x == y; }));
    cout << distance(s.begin(), find_end(s.begin(), s.end(), s2.begin(), s2.end())) << '\n';
    // 77
    cout << distance(s.begin(), _search(s.begin(), s.end(), s2.begin(), s2.end(), [](int x, int y) -> bool
                                        { return x == y; }));
    cout << distance(s.begin(), search(s.begin(), s.end(), s2.begin(), s2.end())) << '\n';
    // 22
    s = "1234512345";
    s2 = "435";
    cout << distance(s.begin(), _find_first_of(s.begin(), s.end(), s2.begin(), s2.end(), [](int x, int y) -> bool
                                               { return x == y; }));
    cout << distance(s.begin(), find_first_of(s.begin(), s.end(), s2.begin(), s2.end())) << '\n';
    // 22
    cout << _count(s.begin(), s.end(), '3');
    cout << count(s.begin(), s.end(), '3') << '\n';
    // 22
    cout << _count_if(s.begin(), s.end(), [](int x) -> bool
                      { return x >= '3'; });
    cout << count_if(s.begin(), s.end(), [](int x) -> bool
                     { return x >= '3'; })
         << '\n';
    // 66
    list<int> l1 = {1, 2, 3};
    list<int> l2 = {1, 2, 3};
    cout << (l1 == l2) << '\n';
    array<int, 8> a1 = {1, 2, 3};
    array<int, 8> a2 = {1, 2, 3};
    cout << (a1 == a2) << '\n';
    // 11
}

#endif