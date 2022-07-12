#include "pre.cpp"

class NumArray
{
public:
    SegmentTree st;
    NumArray(vector<int> &nums) : st(nums, false) {}

    void update(int index, int val)
    {
        st.update(index, val);
    }

    int sumRange(int left, int right)
    {
        return st.sum_range(left, right);
    }
};

class NumArray2
{
public:
    BinaryIndexedTree bit;
    vector<int> nums;
    NumArray2(vector<int> &nums) : bit(nums), nums(nums) {}

    void update(int index, int val)
    {

        int diff = val - nums[index];
        nums[index] = val;
        bit.update(index, diff);
    }

    int sumRange(int left, int right)
    {
        return bit.sum_range(left, right);
    }
};

int main()
{
    vector<int> v({5, 18, 13});
    NumArray arr(v);
    cout << arr.sumRange(0, 2);
    arr.update(1, -1);
    cout << arr.sumRange(0, 2);
    arr.update(2, 3);
    cout << arr.sumRange(0, 2);
    arr.update(0, 5);
    cout << arr.sumRange(0, 2);
    arr.update(0, -4);
    cout << arr.sumRange(0, 2);
    cout << '\n';

    {
        vector<int> v({5, 18, 13});
        NumArray2 arr(v);
        cout << arr.sumRange(0, 2);
        arr.update(1, -1);
        cout << arr.sumRange(0, 2);
        arr.update(2, 3);
        cout << arr.sumRange(0, 2);
        arr.update(0, 5);
        cout << arr.sumRange(0, 2);
        arr.update(0, -4);
        cout << arr.sumRange(0, 2);
    }
}