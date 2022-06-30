#ifndef _OTHER
#define _OTHER

#include "../../load_modules.cpp"
#include "../../io.cpp"

// partition
template <class BidirectionalIterator, class UnaryPredicate>
BidirectionalIterator _partition(BidirectionalIterator first, BidirectionalIterator last, UnaryPredicate pred)
{
    // pred返回true在前面, 返回false在后面
    // 初始条件: first-1: true, last: false
    // 返回的first, 代表false的第一个.
    // 找到前面为false, 找到后面为true, 然后交换
    while (first != last)
    {
        while (pred(*first))
        {
            // 可以省略, 因为pred(*last)一定是false.
            // if (first == last)
            // {
            //     return first;
            // }
            ++first;
        }
        do
        {
            // first: false, last: false
            if (first == last)
            {
                return first; // false
            }
            --last;
        } while (not pred(*last));
        // first: false, last: true
        swap(*first, *last);
        // first: true, last: false
        ++first;
    }
    return first; // false
}

template <class BidirectionalIterator, class UnaryPredicate>
BidirectionalIterator _stable_partition(BidirectionalIterator first,
                                        BidirectionalIterator last,
                                        UnaryPredicate pred);

// sorting

// sort: 使用operator <或comp. Compare: 二元, 返回bool. 从小到大: <
template <class RandomAccessIterator, class Compare>
void _sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template <class RandomAccessIterator, class Compare>
void _stable_sort(RandomAccessIterator first, RandomAccessIterator last,
                  Compare comp);

// paritial_sort: topK
template <class RandomAccessIterator, class Compare>
void _partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
                   RandomAccessIterator last, Compare comp);
template <class ForwardIterator, class Compare>
bool _is_sorted(ForwardIterator first, ForwardIterator last, Compare comp)
{
    // 检查从first -> last, 是否有序.
    if (first == last)
    {
        return true;
    }

    ForwardIterator next = first;
    while (++next != last)
    {
        // next是first后一个, next未越界
        if (comp(*next, *first)) // *next < *first; 可以等于
        {
            return false;
        }
        ++first;
    }
    return true;
}

// nth_element: 功能: 找中位数等.
// 使用operator <或comp
template <class RandomAccessIterator, class Compare>
void _nth_element(RandomAccessIterator first, RandomAccessIterator nth,
                  RandomAccessIterator last, Compare comp);
// binary search
template <class ForwardIterator, class T, class Compare>
ForwardIterator _lower_bound(ForwardIterator first, ForwardIterator last,
                             const T &val, Compare comp)
{
    // 找 >= val的最小值. 即找 < val的最大值
    ForwardIterator mid; // hi = first + count
    typename iterator_traits<ForwardIterator>::difference_type count, step;
    count = distance(first, last);
    while (count > 0)
    {
        mid = first;
        step = count / 2;
        advance(mid, step);
        if (comp(*mid, val))
        {
            first = ++mid;
            count -= step + 1;
        }
        else
        {                 // 找 res >= val的最小值
            count = step; // !
        }
    }
    return first;
}

template <class ForwardIterator, class T, class Compare>
ForwardIterator _lower_bound2(ForwardIterator first, ForwardIterator last,
                              const T &val, Compare comp)
{
    // 找<val的最大值 +1
    // 范围: [-1, len-1]
    // mid的寻找; lo=mid;
    ForwardIterator mid; // hi = first + count
    typename iterator_traits<ForwardIterator>::difference_type count, step;
    --first;
    --last;
    count = distance(first, last);
    while (count > 0)
    {
        mid = first;
        step = (count + 1) / 2;
        advance(mid, step);
        if (comp(*mid, val))
        {
            first = mid; // !
            count -= step;
        }
        else
        { // 找 res >= val的最小值
            count = step - 1;
        }
    }
    return ++first;
}

template <class ForwardIterator, class T, class Compare>
ForwardIterator _upper_bound(ForwardIterator first, ForwardIterator last,
                             const T &val, Compare comp)
{
    ForwardIterator mid; // hi = first + count
    typename iterator_traits<ForwardIterator>::difference_type count, step;
    count = distance(first, last);
    while (count > 0)
    {
        mid = first;
        step = count / 2;
        advance(mid, step);
        if (not comp(val, *mid))
        {
            first = ++mid;
            count -= step + 1;
        }
        else
        {                  // 找 res > val的最小值
            count = first; // !
        }
    }
    return first;
}

template <class ForwardIterator, class T, class Compare>
pair<ForwardIterator, ForwardIterator>
_equal_range(ForwardIterator first, ForwardIterator last, const T &val,
             Compare comp)
{
    ForwardIterator it = _lower_bound(first, last, val, comp);
    return pair(it, upper_bound(it, last, val, comp));
}

template <class ForwardIterator, class T, class Compare>
bool binary_search(ForwardIterator first, ForwardIterator last,
                   const T &val, Compare comp)
{
    // first一定 >= val
    first = lower_bound(first, last, val);
    return (first != last and not(comp(val, *first)));
}

// merge
// 必须含result.begin(), 返回为结束时result的iter.
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator _merge(InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      OutputIterator result, Compare comp)
{ // 如果it1结束, 则copy. 同理it2
    // 比较first1, first2, 如果first1 < first2, 则加入first1
    // 相等: 则选first1
    while (true)
    {
        if (first1 == last1)
        {
            return copy(first2, last2, result);
        }
        if (first2 == last2)
        {
            return copy(first1, last1, result);
        }
        *result++ = comp(*first2, *first1) ? *first2++ : *first1++;
    }
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator _set_union(InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, InputIterator2 last2,
                          OutputIterator result, Compare comp)
{
    // merge只有两种比较, union有三种比较
    // 前提: it1, it2内各自没有重复元素.
    while (true)
    {
        if (first1 == last1)
        {
            return copy(first2, last2, result);
        }
        if (first2 == last2)
        {
            return copy(first1, last1, result);
        }
        if (comp(*first2, *first1))
        {
            *result++ = *first2++;
        }
        else if (comp(*first1, *first2))
        {
            *result++ = *first1++;
        }
        else // ==
        {
            *result++ = *first1++;
            ++first2;
        }
    }
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator _set_intersection(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 OutputIterator result, Compare comp)
{
    // 三个判断: 只有==才赋值
    while (true)
    {
        if (first1 == last1)
        {
            return result;
        }
        if (first2 == last2)
        {
            return result;
        }
        if (comp(*first2, *first1))
        {
            ++first2;
        }
        else if (comp(*first1, *first2))
        {
            ++first1;
        }
        else // ==
        {
            *result++ = *first1++;
            ++first2;
        }
    }
}
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator _set_difference(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2,
                               OutputIterator result, Compare comp)
{
    // A-B = A-AB
    // 若first2 > first1, 代表first1符合要求.
    while (true)
    {
        if (first1 == last1)
        {
            return result;
        }
        if (first2 == last2)
        {
            return copy(first1, last1, result);
        }
        if (comp(*first2, *first1))
        {
            ++first2;
        }
        else if (comp(*first1, *first2))
        {
            *result++ = *first1++;
        }
        else // ==
        {
            ++first1;
            ++first2;
        }
    }
}

template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
OutputIterator _set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                                         InputIterator2 first2, InputIterator2 last2,
                                         OutputIterator result, Compare comp)
{
    // 前两个判断语句内与set_union类似.
    while (true)
    {
        if (first1 == last1)
        {
            return copy(first2, last2, result);
        }
        if (first2 == last2)
        {
            return copy(first1, last1, result);
        }
        if (comp(*first2, *first1))
        {
            *result++ = *first2++;
        }
        else if (comp(*first1, *first2))
        {
            *result++ = *first1++;
        }
        else // ==
        {
            ++first1;
            ++first2;
        }
    }
}
// heap

// 默认: 大根堆
template <class RandomAccessIterator, class Compare>
void _make_heap(RandomAccessIterator first, RandomAccessIterator last,
                Compare comp);
// 将最后一位last-1的值加入堆.
template <class RandomAccessIterator, class Compare>
void _push_heap(RandomAccessIterator first, RandomAccessIterator last,
                Compare comp);

// 移除堆的最大值(默认)
template <class RandomAccessIterator, class Compare>
void _pop_heap(RandomAccessIterator first, RandomAccessIterator last,
               Compare comp);

template <class RandomAccessIterator, class Compare>
void _make_heap(RandomAccessIterator first, RandomAccessIterator last,
                Compare comp);

template <class RandomAccessIterator, class Compare>
void _sort_heap(RandomAccessIterator first, RandomAccessIterator last,
                Compare comp);

// min/max
template <class T, class Compare>
const T &_min(const T &a, const T &b, Compare comp)
{ // 等于则a
    return (comp(b, a)) ? b : a;
}

template <class T, class Compare>
const T &_max(const T &a, const T &b, Compare comp)
{ // 等于则a
    return (comp(a, b)) ? b : a;
}

template <class ForwardIterator, class Compare>
ForwardIterator _min_element(ForwardIterator first, ForwardIterator last,
                             Compare comp)
{
    // 如果first==last, 返回last; 否则返回最大值的iter
    if (first == last)
    {
        return last;
    }
    ForwardIterator smallest = first;
    while (++first != last)
    {
        // first != last
        if (comp(*first, *smallest))
        {
            smallest = first;
        }

        // [_first, first]区间的最大值为first
    }
    return smallest;
}

template <class ForwardIterator, class Compare>
ForwardIterator _max_element(ForwardIterator first, ForwardIterator last,
                             Compare comp)
{
    // 如果first==last, 返回last; 否则返回最大值的iter
    // 多个匹配, 则返回第一个
    if (first == last)
    {
        return last;
    }
    ForwardIterator largest = first;
    while (++first != last)
    {
        // first != last
        if (comp(*largest, *first))
        {
            largest = first;
        }

        // [_first, first]区间的最大值为first
    }
    return largest;
}
// other

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << *_partition(v.begin(), v.end(), [](int x) -> bool
                        { return x >= 5; });
    cout << v << '\n';
    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << *partition(v.begin(), v.end(), [](int x) -> bool
                       { return x >= 5; });
    cout << v << '\n';
    // 4[9, 8, 7, 6, 5, 4, 3, 2, 1]
    // 4[9, 8, 7, 6, 5, 4, 3, 2, 1]
    v = {91, 82, 73, 64, 55, 41, 32, 23, 14};
    // BidirectionalIterator
    cout << *stable_partition(v.begin(), v.end(), [](int x) -> bool
                              { return x % 10 >= 3; });
    cout << v << '\n';
    // 91[73, 64, 55, 23, 14, 91, 82, 41, 32]
    // RandomAccessIterator
    sort(v.begin(), v.end(), [](int x, int y) -> bool
         { return x < y; });
    cout << v << '\n';
    v = {91, 82, 73, 64, 55, 41, 32, 23, 14};
    // RandomAccessIterator
    stable_sort(v.begin(), v.end(), [](int x, int y) -> bool
                { return x % 10 < y % 10; });
    cout << v << '\n';
    // [14, 23, 32, 41, 55, 64, 73, 82, 91]
    // [91, 41, 82, 32, 73, 23, 64, 14, 55]
    int K = 4;
    // RandomAccessIterator
    partial_sort(v.begin(), v.begin() + K, v.end(), [](int x, int y) -> bool
                 { return x > y; });
    cout << v << '\n';
    // [91, 82, 73, 64, 32, 23, 41, 14, 55]

    cout << _is_sorted(v.begin(), v.begin() + 4, [](int x, int y) -> bool
                       { return x > y; });
    cout << is_sorted(v.begin(), v.begin() + 4, [](int x, int y) -> bool
                      { return x > y; })
         << '\n';
    // 11
    v = {6, 3, 5, 2, 1, 0, 4};
    nth_element(v.begin(), v.begin() + 4, v.end());
    cout << v << '\n';
    nth_element(v.begin(), v.begin() + 4, v.end(), [](int x, int y) -> bool
                { return x > y; });
    cout << v << '\n';
    // [3, 0, 1, 2, 4, 5, 6]
    // [5, 6, 4, 3, 2, 1, 0]
    //
    v = {1, 2, 2, 2, 3};
    auto temp = _equal_range(v.begin(), v.end(), 2, [](int x, int y) -> bool
                             { return x < y; });
    cout << get<0>(temp) - v.begin() << ", " << get<1>(temp) - v.begin() << '\n';
    cout << _lower_bound2(v.begin(), v.end(), 4, [](int x, int y) -> bool
                          { return x < y; }) -
                v.begin();
    cout << _lower_bound2(v.begin(), v.end(), 2, [](int x, int y) -> bool
                          { return x < y; }) -
                v.begin()
         << '\n';
    // 1, 4
    // 51

    v = {1, 2, 3};
    vector<int> v2 = {1, 2, 4};
    vector<int> v3(6);
    cout << *merge(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
    cout << v3;
    cout << *_merge(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin(), [](int x, int y) -> bool
                    { return x < y; });
    cout << v3 << '\n';
    // 60593[1, 1, 2, 2, 3, 4]60593[1, 1, 2, 2, 3, 4]
    v = {1, 2, 2, 3};
    cout << *set_union(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
    cout << v3;
    cout << *_set_union(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin(), [](int x, int y) -> bool
                        { return x < y; });
    cout << v3 << '\n';

    // 4[1, 2, 2, 3, 4, 4]4[1, 2, 2, 3, 4, 4]
    fill(v3.begin(), v3.end(), 0);
    cout << *set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
    cout << v3;
    cout << *_set_intersection(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin(), [](int x, int y) -> bool
                               { return x < y; });
    cout << v3 << '\n';
    // 0[1, 2, 0, 0, 0, 0]0[1, 2, 0, 0, 0, 0]
    fill(v3.begin(), v3.end(), 0);
    cout << *set_difference(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
    cout << v3;
    cout << *_set_difference(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin(), [](int x, int y) -> bool
                             { return x < y; });
    cout << v3 << '\n';
    // 0[2, 3, 0, 0, 0, 0]0[2, 3, 0, 0, 0, 0]
    fill(v3.begin(), v3.end(), 0);
    cout << *set_symmetric_difference(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
    cout << v3;
    cout << *_set_symmetric_difference(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin(), [](int x, int y) -> bool
                                       { return x < y; });
    cout << v3 << '\n';
    // 0[2, 3, 4, 0, 0, 0]0[2, 3, 4, 0, 0, 0]
    v = {1, 2, 3, 4, 5, 6};
    make_heap(v.begin(), v.end(), [](int x, int y) -> bool
              { return x < y; });
    cout << v << '\n';
    v.push_back(10);
    push_heap(v.begin(), v.end());
    cout << v << '\n';
    pop_heap(v.begin(), v.end());
    v.pop_back();
    cout << v << '\n';
    // [6, 5, 3, 4, 2, 1]
    // [10, 5, 6, 4, 2, 1, 3]
    // [6, 5, 3, 4, 2, 1]

    //
    cout << _min(10, 0, [](int x, int y) -> bool
                 { return x % 10 < y % 10; });
    cout << min(10, 0, [](int x, int y) -> bool
                { return x % 10 < y % 10; });
    cout << _max(10, 0, [](int x, int y) -> bool
                 { return x % 10 < y % 10; });
    cout << max(10, 0, [](int x, int y) -> bool
                { return x % 10 < y % 10; })
         << '\n';
    // 10101010
    v = {20, 10, 0, 30};
    cout << *_max_element(v.begin(), v.end(), [](int x, int y) -> bool
                          { return x % 10 < y % 10; });
    cout << *max_element(v.begin(), v.end(), [](int x, int y) -> bool
                         { return x % 10 < y % 10; });
    cout << *_min_element(v.begin(), v.end(), [](int x, int y) -> bool
                          { return x % 10 < y % 10; });
    cout << *min_element(v.begin(), v.end(), [](int x, int y) -> bool
                         { return x % 10 < y % 10; })
         << '\n';
    // 20202020
}

#endif
