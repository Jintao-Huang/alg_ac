#ifndef _LIST
#define _LIST
#include "../build_ds.cpp"
#include "../load_modules.cpp"
ListNode *reverse_list(ListNode *lo, ListNode *hi)
{
    // [lo..hi). 不含hi
    // 例如反转1,2. 则先保存t=hi;
    // p=lo
    // 1. _pn=p->next;p->next=t; t=p; p=_pn
    // 一致重复(1), 直到p到达hi. 退出循环, 返回t(即reverse后的头结点)
    ListNode *t = hi, *p = lo;
    //
    while (p != hi)
    {
        ListNode *pn = p->next;
        p->next = t;
        t = p;
        p = pn;
    }
    return t;
}
// int main()
// {
//     ListNode *ln = str_to_list("[1,2,3,4,5]");
//     cout << reverse_list(ln, nullptr);
// }
#endif
