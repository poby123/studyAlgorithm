/**
 * MEDIUM
 * https://leetcode.com/problems/product-of-array-except-self/
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * Follow up: Can you solve the problem in O(1) extra space complexity?
 * (The output array does not count as extra space for space complexity analysis.)
 *
 * 2023.06.24
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"

class Solution
{
public:
    /**
     * O(n) - 32ms
     *
     *  1  2  3  4   - nums
     *  1  2  6 24   - LtoR product
     *   \  \  \
     * 24 12  8  6   - answer
     *   \  \  \
     * 24 24 12  4   - RtoL product
     */
    vector<int> productExceptSelf(vector<int> &nums)
    {
        const int length = nums.size();
        vector<int> LtoR(length, nums[0]);
        vector<int> RtoL(length, nums[length - 1]);
        vector<int> ans(length, 0);

        for (int i = 1; i < length; i++)
        {
            LtoR[i] = LtoR[i - 1] * nums[i];
            RtoL[length - i - 1] = RtoL[length - i] * nums[length - i - 1];
        }

        ans[0] = RtoL[1];
        ans[length - 1] = LtoR[length - 2];
        for (int i = 1; i < length - 1; i++)
        {
            ans[i] = LtoR[i - 1] * RtoL[i + 1];
        }

        return ans;
    }

    /**
     * O(n) - 32ms
     */
    vector<int> productExceptSelf2(vector<int> &nums)
    {
        const int length = nums.size();
        int LtoR = nums[0];
        int RtoL = nums[length - 1];
        vector<int> ans(length, 1);

        for (int i = 1; i < length; i++)
        {
            ans[i] *= LtoR;
            LtoR *= nums[i];
        }

        for (int i = length - 2; i >= 0; i--)
        {
            ans[i] *= RtoL;
            RtoL *= nums[i];
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> v = {1, 2, 3, 4};
    vector<int> ans = sol.productExceptSelf2(v);

    for (int i : ans)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}