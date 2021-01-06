#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void permutation(vector<int> &arr, int start, int end)
{
    // 기저사례1 : start와 end가 같은 경우, 더 이상 permutation 할 게 없다.
    if (start == end)
    {
        for (auto it : arr)
        {
            cout << it << " ";
        }
        cout << "\n";
    }
    else
    {
        // i가 start+1이 아니라 start부터 시작해야한다.
        for (int i = start; i <= end; i++)
        {
            swap(arr[start], arr[i]);
            permutation(arr, start + 1, end);
            swap(arr[start], arr[i]);
        }
    }
}

int main()
{
    vector<int> arr = {1, 2, 3};
    permutation(arr, 0, arr.size() - 1);
    return 0;
}