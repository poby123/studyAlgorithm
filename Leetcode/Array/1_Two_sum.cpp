/**
 * 2023.06.24
 * @author wonju (i2pir@naver.com)
 */

#include "../common.h"

class Solution
{
public:
    /**
     * My solve 1
     * O(N^2) 214ms
     */
    vector<int> twoSum(vector<int> &nums, int target)
    {
        const int length = nums.size();
        vector<int> ans = {};

        for (int i = 0; i < length; i++)
        {
            const int &a = nums[i];
            for (int j = i + 1; j < length; j++)
            {
                const int &b = nums[j];

                int sum = a + b;
                if (sum == target)
                {
                    ans = {i, j};
                    return ans;
                }
            }
        }
        return ans;
    }

    /**
     * My solve 2
     * O(NlogN) 7ms
     */
    vector<int> twoSum2(vector<int> &nums, int target)
    {
        using pp = pair<int, int>;
        vector<int> ans;

        // copy nums with index
        vector<pp> sortedNums;
        for (int i = 0; i < nums.size(); i++)
        {
            sortedNums.push_back({nums[i], i});
        }

        sort(sortedNums.begin(), sortedNums.end());
        const int length = sortedNums.size();
        int l = 0;
        int r = length - 1;

        // binary search
        while (l < length && 0 <= r && l < r)
        {
            auto &[a, ai] = sortedNums[l];
            auto &[b, bi] = sortedNums[r];
            int sum = a + b;

            if (sum == target)
            {
                return ans = {ai, bi};
            }
            else if (sum < target)
            {
                ++l;
            }
            else
            {
                --r;
            }
        }

        return ans;
    }

    /**
     * Other's solve
     * avg. O(N) 12ms
     */
    vector<int> twoSum3(vector<int> &nums, int target)
    {
        const int length = nums.size();
        unordered_map<int, int> mm;

        // O(N)
        for (int i = 0; i < length; i++)
        {
            int newTarget = target - nums[i];

            // avg. O(1), worst. O(N)
            if (mm.find(newTarget) != mm.end())
            {
                return {i, mm[newTarget]};
            }
            mm.insert({nums[i], i});
        }
        return {};
    }
};

int main()
{
    Solution sol;
    vector<int> v = {2, 5, 8};
    vector<int> result = sol.twoSum2(v, 10);

    for (int i : result)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}