#include <iostream>
#include <vector>
using namespace std;

// 조합 경우의 수 구하기 : (n_C_r) = (n-1_C_r-1) + (n-1_C_r)
int combination(int n, int r)
{
    if (n == r || r == 0)
    {
        return 1;
    }
    else
    {
        return combination(n - 1, r - 1) + combination(n - 1, r);
    }
}

//조합
void Combination(vector<char> arr, vector<char> picked, int r, int depth)
{
    /* r이 0인 경우, 즉 다 뽑은 경우 */
    if (r == 0)
    {
        for (auto it : picked)
        {
            cout << it << " ";
        }
        cout << "\n";
    }

    /* r이 0이 아니면서, arr은 다 돈 경우 => 남은 요소는 없는데, 원하는 만큼 뽑지 않았기 때문에 그냥 종료.*/
    else if (depth == arr.size())
    {
        return;
    }

    /* r이 0이 아니고, arr도 남은 경우 */
    else
    {
        //뽑지 않는 경우
        Combination(arr, picked, r, depth + 1);

        // 뽑는 경우
        picked.push_back(arr[depth]);
        Combination(arr, picked, r - 1, depth + 1);
    }
}

int main()
{
    vector<char> arr = {'a', 'b', 'c', 'd', 'e'};
    const int r = 4;
    vector<char> picked;
    picked.reserve(r);

    Combination(arr, picked, r, 0);
    cout << "Combination's number of cases : " << combination(arr.size(), r);

    return 0;
}