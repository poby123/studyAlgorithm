/**
 * 2023.07.10
 * https://leetcode.com/problems/climbing-stairs/
 *
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"
class Solution
{
public:
    /**
     * O(n) 4ms
     * n번째 계단을 올라가는 경우의 수 = (n-1번째 계단을 올라가는 경우의 수) + (n-2번째 계단을 올라가는 경우의 수)
     */
    int climbStairs(int n)
    {
        vector<int> dp(n + 1, 0);

        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

int main()
{
    Solution sol;
    sol.climbStairs(19);

    return 0;
}