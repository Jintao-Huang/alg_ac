#include "pre.cpp"

class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        // 若k=1, 则返回head
        // 1,2,3,4,5; k=2; -> 21435
        // 1. 开始时, s在哑节点, p=s; p前进k步(到2), 翻转1,2
        //  p=s->next,s->next=翻转后的头结点.
        // 重复上面的(1), 直到前进时遇到nullptr, 则返回哑节点.next
        if (k == 1)
        {
            return head;
        }
        ListNode *s = new ListNode(0, head);
        ListNode *p, *lo;
        lo = p = s; // (lo..p]
        int step = 1;
        p = p->next;
        while (p != nullptr)
        {
            if (step == k)
            {
                ListNode *pn = p->next;
                p = lo->next;
                lo->next = reverse_list(p, pn);
                lo = p;
                step = 0;
            }
            ++step;
            p = p->next;
        }
        ListNode *res = s->next;
        delete s;
        return res;
    }
};

int main()
{
    ListNode *ln = str_to_list("[1,2,3,4,5]");
    cout << Solution().reverseKGroup(ln, 2);
}