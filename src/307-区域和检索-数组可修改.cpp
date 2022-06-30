#include "pre.cpp"

class NumArray
{
public:
    SegmentTree st;
    NumArray(vector<int> &nums) : st(nums, false) {}

    void update(int index, int val)
    {
        st.update(index, index, val);
    }

    int sumRange(int left, int right)
    {
        return st.sum_range(left, right);
    }
};

int main()
{
    vector<int> v({1, 3, 5});
    NumArray numArray(v);
    cout << numArray.sumRange(0, 2); // 返回 1 + 3 + 5 = 9
    numArray.update(1, 2);           // nums = [1,2,5]
    cout << numArray.sumRange(0, 2); // 返回 1 + 2 + 5 = 8
}