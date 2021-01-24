/*
문제
비어있는 공집합 S가 주어졌을 때, 아래 연산을 수행하는 프로그램을 작성하시오.

add x: S에 x를 추가한다. (1 ≤ x ≤ 20) S에 x가 이미 있는 경우에는 연산을 무시한다.
remove x: S에서 x를 제거한다. (1 ≤ x ≤ 20) S에 x가 없는 경우에는 연산을 무시한다.
check x: S에 x가 있으면 1을, 없으면 0을 출력한다. (1 ≤ x ≤ 20)
toggle x: S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다. (1 ≤ x ≤ 20)
all: S를 {1, 2, ..., 20} 으로 바꾼다.
empty: S를 공집합으로 바꾼다. 
입력
첫째 줄에 수행해야 하는 연산의 수 M (1 ≤ M ≤ 3,000,000)이 주어진다.

둘째 줄부터 M개의 줄에 수행해야 하는 연산이 한 줄에 하나씩 주어진다.

출력
check 연산이 주어질때마다, 결과를 출력한다.
*/

#include <iostream>
using namespace std;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int M, arr = 0, x;
    cin >> M;

    for (int i = 0; i < M; i++)
    {
        string s;
        cin >> s >> x;
        cin.clear();
        --x;

        if (s == "add")
        {
            arr |= (1 << x);
        }
        else if (s == "remove")
        {
            arr &= ~(1 << x);

        }
        else if (s == "check")
        {
            cout << ((arr & (1 << x)) != 0) << "\n";
        }
        else if (s == "toggle")
        {
            arr ^= (1 << x);
        }
        else if (s == "all")
        {
            arr = 0xFFFFFFFF;
        }
        else
        {
            arr = 0;
        }
    }
    return 0;
}