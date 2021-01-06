#include <iostream>
#include <algorithm>
#include <vector>
#include <functional> //less<T>()

using namespace std;

int main()
{
    vector<int> arr = {1,3,2,4}; 
    sort(arr.begin(), arr.end(), less<int>()); // 반드시 오름차순으로 정렬되어 있어야 모든 순열이 출력된다.

    do
    {
        for (auto it : arr)
        {
            cout << it << " ";
        }
        cout << "\n";
    } while (next_permutation(arr.begin(), arr.end()));

    return 0;
}