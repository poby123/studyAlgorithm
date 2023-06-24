/**
 * 2023.06.24
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"

class Solution
{
public:
    /**
     * O(n^2) - TLE
     */
    int maxProfit(vector<int> &prices)
    {
        const int length = prices.size();
        int l = 0;
        int r = length - 1;
        int ans = 0;

        for (int i = 0; i < length; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                int s = prices[j] - prices[i];
                ans = max(ans, s);
            }
        }

        return ans;
    }

    /**
     * O(3n) - 178ms
     */
    int maxProfit2(vector<int> &prices)
    {
        const int length = prices.size();
        int ans = 0;
        vector<int> mins(length, prices[0]);
        vector<int> maxes(length, prices[length - 1]);

        for (int i = 1; i < length; i++)
        {
            const int curPrice = prices[i];
            mins[i] = min(mins[i - 1], curPrice);
        }

        for (int i = length - 2; i >= 0; i--)
        {
            const int curPrice = prices[i];
            maxes[i] = max(maxes[i + 1], curPrice);
        }

        for (int i = 0; i < length; i++)
        {
            ans = max(ans, maxes[i] - mins[i]);
        }

        return ans;
    }

    /**
     * Others
     * O(n) - 137ms
     *
     * 현재값 - 과거의 최솟값 => 최대이익
     */
    int maxProfit3(vector<int> &prices)
    {
        const int length = prices.size();
        int ans = 0;
        int minPrice = prices[0];

        for (int i = 1; i < length; i++)
        {
            int curPrice = prices[i];
            int profit = curPrice - minPrice;
            ans = max(ans, profit);
            minPrice = min(minPrice, curPrice);
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> v = {7, 1, 5, 3, 6, 4};
    int ans = sol.maxProfit3(v);
    cout << ans << endl;

    return 0;
}