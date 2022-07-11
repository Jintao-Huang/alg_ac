
#ifndef _MODIFYING_SEQ
#define _MODIFYING_SEQ

#include "../../load_modules.cpp"
#include "../../io.cpp"

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);

template <class T>
void swap(T &a, T &b);

template <class InputIterator, class OutputIterator>
OutputIterator move(InputIterator first, InputIterator last, OutputIterator result);

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last,
             const T &old_value, const T &new_value);

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T &val);

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last,
                       BinaryPredicate pred);
#endif
