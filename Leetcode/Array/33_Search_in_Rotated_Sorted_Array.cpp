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
     * O(logN) - 7ms
     *
     * 이분탐색을 할 때 경계부분에 대해 조금 더 생각해봐야겠다.
     */
    int search(vector<int> &nums, int target)
    {
        int length = nums.size();
        if (length <= 1)
        {
            return nums[0] == target ? 0 : -1;
        }
        if (length <= 2)
        {
            return nums[0] == target ? 0 : (nums[1] == target ? 1 : -1);
        }

        int l = 0;
        int r = length - 1;

        while (l <= r)
        {
            int m = (l + r) >> 1;

            // check find
            if (nums[l] == target)
            {
                return l;
            }
            if (nums[r] == target)
            {
                return r;
            }
            if (nums[m] == target)
            {
                return m;
            }

            // left side is ASC
            if (nums[l] < nums[m])
            {
                // left side contains target scope
                if (nums[l] < target && target < nums[m])
                {
                    r = m;
                }
                else
                {
                    l = m;
                }
            }
            // right side is ASC
            else
            {
                // right side contains target scope
                if (nums[m] < target && target < nums[r])
                {
                    l = m;
                }
                else
                {
                    r = m;
                }
            }
        }

        return -1;
    }

    /**
     * O(logN) - 3ms
     */
    int search2(vector<int> &nums, int target)
    {
        int length = nums.size();
        int l = 0;
        int r = length - 1;

        while (l <= r)
        {
            int m = (l + r) >> 1;
            if (nums[m] == target)
            {
                return m;
            }

            // left side is ASC
            if (nums[l] <= nums[m])
            {
                // left side contains target scope
                if (nums[l] <= target && target <= nums[m])
                {
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }
            // right side is ASC
            else
            {
                // right side contains target scope
                if (nums[m] <= target && target <= nums[r])
                {
                    l = m + 1;
                }
                else
                {
                    r = m - 1;
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    vector<int> v = {3, 1};
    int ans = sol.search2(v, 1);
    cout << ans << endl;

    return 0;
}