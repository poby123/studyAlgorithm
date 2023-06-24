/**
 * 2023.06.24
 * @author wonju (i2pir@naver.com)
 */
#include "../common.h"
#include <unordered_set>

class Solution
{
public:
    /**
     * O(n) - 169ms
     * make unique using set
     */
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> mm(nums.begin(), nums.end());
        return nums.size() != mm.size();
    }

    /**
     * O(n) - 163ms
     * count
     */
    bool containsDuplicate2(vector<int> &nums)
    {
        unordered_map<int, int> mm;
        for (int cur : nums)
        {
            if (mm[cur])
            {
                return true;
            }
            ++mm[cur];
        }

        return false;
    }

    /**
     * O(n) - 123ms
     * make unique using vector
     */
    bool containsDuplicate3(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> uniqueVector(nums.begin(), unique(nums.begin(), nums.end()));

        return nums.size() != uniqueVector.size();
    }
};

int main()
{
    Solution sol;
    vector<int> v = {1, 2, 3};
    bool ans = sol.containsDuplicate3(v);
    cout << "ans: " << ans << endl;

    return 0;
}