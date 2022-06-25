
#ifndef _STD_ALG
#define _STD_ALG

#include "../load_modules.cpp"
#include "../io.cpp"
#include "std_alg/non_modifying_seq.cpp"
#include "std_alg/modifying_seq.cpp"
#include "std_alg/other.cpp"

template <class T>
unordered_set<T> &update(unordered_set<T> &s, unordered_set<T> &s2)
{
    // union并将结构放置在first, last后
    auto first2 = s2.begin(), last2 = s2.end();
    for (auto p = first2; p != last2; ++p)
    {
        if (not s.count(*p))
        {
            s.emplace(*p);
        }
    }
    return s;
}

// int main(){
//     unordered_set<int> s = {1, 2, 3};
//     unordered_set<int> s2 = {1, 4, 3};
//     cout << update(s, s2) << '\n';
//     // {4, 3, 2, 1}
// }

#endif
