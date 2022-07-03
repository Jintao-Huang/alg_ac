#include "pre.cpp"

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        // 有a, b数组, 在a, b数组上画一条直线, 使得直线右边的数字大于直线左边的数字. 即当前数字属于左数组.
        // 条件A: 并且使得左边的数字和右边的数字一样多, 或左边比右边多1
        //  e.g. 1 2 3 4. 线在2的左边. 1 2 3. 线在2的前面
        // 所以我们搜索某一条线(满足条件A), 使得右边数字大于左边数字.
        //  即: 数组1的线右边数字 >= 数组2的线左边数字的最小值. (二分语义)
        // 若偶数, 则取左边最大, 右边最小的均值. 若奇数, 则取右边最小(左比右多1).
        // 只需要遍历短的size即可.
        if (nums1.size() > nums2.size())
        {
            swap(nums1, nums2); // 相当于右值的swap, 只改变&*.begin()的地址, O(1).
        }

        int m = nums1.size();
        int n = nums2.size();
        // 其中 m < n
        int lo = 0, hi = m;
        while (lo < hi)
        {
            int mid = (lo + hi) / 2;
            int mid2 = (m + n) / 2 - mid;
            if (mid == m or nums1[mid] > nums2[mid2 - 1])
            {
                hi = mid;
            }
            else
            {
                lo = mid + 1;
            }
        }
        int mid = lo;
        int mid2 = (m + n) / 2 - mid;
        int left_max = min(mid < m ? nums1[mid] : INT32_MAX, mid2 < n ? nums2[mid2] : INT32_MAX);
        if ((m + n) % 2 == 1)
        {
            return left_max;
        }
        else
        {
            int right_min = max(mid - 1 >= 0 ? nums1[mid - 1] : INT32_MIN, mid2 - 1 >= 0 ? nums2[mid2 - 1] : INT32_MIN);
            return (left_max + right_min) * 1. / 2;
        }
    }
};

int main()
{
    {
        vector<int> v = {1, 3};
        vector<int> v2 = {2};
        cout << Solution().findMedianSortedArrays(v, v2) << '\n';
    }
    {
        vector<int> v = {1, 2};
        vector<int> v2 = {3, 4};
        cout << Solution().findMedianSortedArrays(v, v2) << '\n';
    }
}