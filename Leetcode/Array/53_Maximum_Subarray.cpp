/**
 * MEDIUM
 * https://leetcode.com/problems/maximum-subarray/
 *
 * 2023.06.24
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"

class Solution
{
public:
    /**
     * O(2n) - 136ms
     * Prefix Sum Array
     *
     * sum[i] = nums[0]~nums[i]까지의 합
     *
     * ans = max(0~i까지의 합, k~i까지의 합 [k|k<i])
     *     = max(sum[i], sum[i] - sum[k-1])
     *      위에서 우항인 (sum[i] - sum[k-1])을 큰 값으로 만들기 위해, k-1은 sum[k-1]을 최소로 만드는 수가 되어야한다.
     */
    int maxSubArray(vector<int> &nums)
    {
        const int length = nums.size();
        vector<int> prefixSum(length, 0);
        int ans = prefixSum[0] = nums[0];
        int minValue = prefixSum[0];

        for (int i = 1; i < length; i++)
        {
            prefixSum[i] = nums[i] + prefixSum[i - 1];
        }

        for (int i = 1; i < length; i++)
        {
            ans = max(ans, max(prefixSum[i], prefixSum[i] - minValue));
            minValue = min(minValue, prefixSum[i]);
        }

        return ans;
    }

    /**
     * O(n) - 119ms
     * Prefix Sum
     *
     * 위에서 굳이 누적합을 배열로 나타낼 필요가 없기 때문에 간소화한 것이다.
     * 공간복잡도를 O(1)로 줄일 수 있다.
     */
    int maxSubArray2(vector<int> &nums)
    {
        const int length = nums.size();
        int ans = nums[0];
        int prefixSum = nums[0];
        int minValue = nums[0];

        for (int i = 1; i < length; i++)
        {
            prefixSum += nums[i];

            ans = max(ans, max(prefixSum, prefixSum - minValue));
            minValue = min(minValue, prefixSum);
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> v = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int ans = sol.maxSubArray2(v);
    cout << ans << endl;

    return 0;
}