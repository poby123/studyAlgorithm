// https://www.acmicpc.net/problem/1931

/*
문제
한 개의 회의실이 있는데 이를 사용하고자 하는 N개의 회의에 대하여 회의실 사용표를 만들려고 한다. 
각 회의 I에 대해 시작시간과 끝나는 시간이 주어져 있고, 
각 회의가 겹치지 않게 하면서 회의실을 사용할 수 있는 회의의 최대 개수를 찾아보자. 
단, 회의는 한번 시작하면 중간에 중단될 수 없으며,
 한 회의가 끝나는 것과 동시에 다음 회의가 시작될 수 있다. 
 회의의 시작시간과 끝나는 시간이 같을 수도 있다. 
 이 경우에는 시작하자마자 끝나는 것으로 생각하면 된다.

입력
첫째 줄에 회의의 수 N(1 ≤ N ≤ 100,000)이 주어진다. 
둘째 줄부터 N+1 줄까지 각 회의의 정보가 주어지는데 이것은 공백을 사이에 두고,
 회의의 시작시간과 끝나는 시간이 주어진다. 
 시작 시간과 끝나는 시간은 2^31-1보다 작거나 같은 자연수 또는 0이다.

출력
첫째 줄에 최대 사용할 수 있는 회의의 최대 개수를 출력한다.


풀이
그리디 알고리즘을 이용한다.
A라는 회의가 진행중이라고 할 때, 가장 많은 회의가 열리기 위해서는 어떤 회의가 다음 회의로 와야할까?
바로 종료시간이 빠른 회의가 와야한다.

추가로 종료시간이 같은 경우를 고려해야하는데, 종료시간이 같은 경우에는 시작시간이 빠른 순서로 정렬한다.
(9, 10), (10, 10)

따라서 시작시간순으로 정렬하고, 그 다음 종료시간 순으로 정렬하면 된다.
*/

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'

int N, last, ans, s, e;
vector<pair<int, int>> v;

int main()
{
    fastio;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> s >> e;
        v.push_back({e, s});
    }

    sort(v.begin(), v.end());

    for (auto cur : v)
    {
        e = cur.first;
        s = cur.second;

        if (last <= s)
        {
            last = e;
            ++ans;
        }
    }

    cout << ans << endl;

    return 0;
}
