/**
 * 2023.07.10
 * https://leetcode.com/problems/coin-change/
 *
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"
class Solution
{
public:
    /**
     * O(coin 종류 * 금액) 114ms
     */
    int coinChange(vector<int> &coins, int amount)
    {
        const int INF = INT_MAX;
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        const int length = coins.size();
        sort(coins.begin(), coins.end());

        for (int coin : coins)
        {
            if (coin > amount)
            {
                break;
            }
            dp[coin] = 1;
        }

        for (int i = 0; i <= amount; i++)
        {
            for (int coin : coins)
            {
                // 현재 금액보다 큰 동전은 고려할 필요가 없다.
                if (coin > i)
                {
                    break;
                }
                if (dp[i - coin] != INF)
                {
                    dp[i] = min(dp[i], dp[i - coin] + dp[coin]);
                }
            }
        }

        return dp[amount];
    }
};

int main()
{
    Solution sol;
    vector<int> v = {2};
    int ans = sol.coinChange(v, 3);
    if (ans == INT_MAX)
    {
        ans = -1;
    }
    cout << "ans : " << ans << endl;

    return 0;
}