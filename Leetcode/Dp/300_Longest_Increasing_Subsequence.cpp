/**
 * 2023.07.10
 * https://leetcode.com/problems/longest-increasing-subsequence/
 *
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"
class Solution
{
public:
    /**
     *  Failed
     */
    int lengthOfLIS(vector<int> &nums)
    {
        const int length = nums.size();
        vector<vector<int>> dp(2, vector<int>(length, 0));
        int ans = 1;

        for (int i = 0; i < length; i++)
        {
            dp[0][i] = 1;
            dp[1][i] = i;
        }

        for (int i = 1; i < length; i++)
        {
            int cur = nums[i];
            int before = nums[i - 1];
            int lastIndex = dp[1][i - 1];

            if (before < cur)
            {
                dp[0][i] = dp[0][i - 1] + 1;
                dp[1][i] = i;
            }
            else if (nums[lastIndex] < cur)
            {
                dp[0][i] = max(dp[0][i], dp[0][lastIndex] + 1);
                dp[1][i] = lastIndex;
            }
            else
            {
                dp[0][i] = dp[0][i - 1];
                dp[1][i] = lastIndex;
            }
        }

        for (int j = 0; j < 2; j++)
        {
            for (int i = 0; i < length; i++)
            {
                cout << dp[j][i] << " ";
            }
            cout << endl;
        }

        return dp[0][length - 1];
    }
};

int main()
{
    Solution sol;
    vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
    int ans = sol.lengthOfLIS(v);
    cout << "ans : " << ans << endl;

    return 0;
}