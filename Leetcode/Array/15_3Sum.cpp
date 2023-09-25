/**
 * 2023.06.27
 * @author wonju (i2pir@naver.com)
 */

#include "../common.h"
class Solution
{
public:
    /**
     * Fail
     */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
    }
};

int main()
{
    Solution sol;
    vector<int> v = {-1, 0, 1, 2, -1, -4};
    // vector<int> v = {0, 0, 0};
    vector<vector<int>> ans = sol.threeSum(v);
    for (auto &cur : ans)
    {
        for (int i : cur)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}