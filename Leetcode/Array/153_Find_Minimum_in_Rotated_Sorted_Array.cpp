/**
 * 2023.06.25
 * @author wonju (i2pir@naver.com)
 */

#include "../common.h"

class Solution
{
public:
    /**
     * My Solve
     * O(logN) - 0ms
     */
    int findMin(vector<int> &nums)
    {
        const int length = nums.size();

        // base case
        if (length == 1)
        {
            return nums[0];
        }

        // binary search
        int l = 0;
        int r = length - 1;
        int m = (l + r) / 2;
        int ans = min(nums[l], nums[r]);

        while (l + 1 < r)
        {
            int m = (l + r) / 2;
            ans = min(ans, min(nums[l], nums[r]));
            ans = min(ans, nums[m]);

            if (nums[l] > nums[m] && nums[r] > nums[m])
            {
                r = m;
            }
            else
            {
                l = m;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> v = {5, 6, 7, 0, 1, 2, 4};
    int ans = sol.findMin(v);
    cout << ans << endl;

    return 0;
}