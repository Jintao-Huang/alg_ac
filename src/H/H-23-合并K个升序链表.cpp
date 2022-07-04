#include "pre.cpp"


/// 此函数可以改为ForwardIterator
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        // 用堆来保存vector中链表的头元素. 每次弹出最小值
        ///
        // [1,4,5], [1,3,4], [2,6]
        int n = lists.size();
        ListNode head(0, nullptr);
        ListNode *curr = &head;
        if (n == 0)
        {
            return nullptr;
        }
        else if (n == 1)
        {
            return lists[0];
        }
        //
        // 1. 初始化堆heap, 使用索引建堆, [0,1,2]
        vector<int> heap;
        for (int i = 0; i < n; ++i)
        {
            // 判断链表不是null
            ListNode *p = lists[i];
            if (p != nullptr)
            {
                heap.push_back(i);
            }
        }
        function<bool(int, int)> comp = [&lists](int i, int j) -> bool
        { return lists[i]->val > lists[j]->val; };
        make_heap(heap.begin(), heap.end(), comp);
        // 2. 从堆中不断去除最小元素, 并将其对应的vector取出元素加入.
        //  若vector为空, 则不加入.
        while (heap.size() > 1)
        {
            // 分支: 是否p->next为空, 非空则replace, 空则pop
            int i = heap[0];
            ListNode *p = lists[i];
            ListNode *pnext = p->next;
            if (pnext != nullptr)
            {
                // 改curr， lists[i]
                // 维护堆(堆使用的是索引, 所以需要线改变lists[i], 再维护堆)
                lists[i] = pnext;
                replace_heap(heap, i, comp);
                curr->next = p;
                curr = curr->next;
            }
            else
            {
                lists[i] = nullptr; // 为了代码统一性
                pop_heap(heap, comp);
                curr->next = p;
                curr = curr->next;
            }
        }
        // 3. 直到vector的size==1, 直接将链表拼接
        if (heap.size() == 1)
        {
            curr->next = lists[heap[0]];
            lists[heap[0]] = nullptr; // 为了代码统一性
        }
        return head.next;
    }
};

int main()
{
    // {
    //     vector<ListNode *> lists = {str_to_list("[1,4,5]"),
    //                                 str_to_list("[1,3,4]"),
    //                                 str_to_list("[2,6]")};
    //     cout << lists;
    //     cout << Solution().mergeKLists(lists) << '\n';
    //     cout << lists << '\n';
    // }
    {
        vector<ListNode *> lists = {str_to_list("[]"),
                                    str_to_list("[]"),
                                    str_to_list("[]")};
        cout << lists;
        cout << Solution().mergeKLists(lists) << '\n';
        cout << lists << '\n';
    }
}