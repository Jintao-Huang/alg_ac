#include "std_pre.cpp"

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mapper;
        int n_len = nums.size();
        for (int i = 0; i < n_len; i++)
        {
            int x = nums[i];
            if (mapper.count(target - x))
            {
                return {i, mapper[target - x]};
            }
            else
            {
                mapper[x] = i;
            }
        }
        return {};
    }
};

int main()
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    cout << Solution().twoSum(nums, target) << endl;
    return 0;
}
