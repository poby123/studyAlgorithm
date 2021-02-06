/*
문제
세계적인 도둑 상덕이는 보석점을 털기로 결심했다.

상덕이가 털 보석점에는 보석이 총 N개 있다. 각 보석은 무게 Mi와 가격 Vi를 가지고 있다. 
상덕이는 가방을 K개 가지고 있고, 각 가방에 담을 수 있는 최대 무게는 Ci이다. 
가방에는 최대 한 개의 보석만 넣을 수 있다.

상덕이가 훔칠 수 있는 보석의 최대 가격을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N, K ≤ 300,000)

다음 N개 줄에는 각 보석의 정보 Mi와 Vi가 주어진다. (0 ≤ Mi, Vi ≤ 1,000,000)

다음 K개 줄에는 가방에 담을 수 있는 최대 무게 Ci가 주어진다. (1 ≤ Ci ≤ 100,000,000)

모든 숫자는 양의 정수이다.

출력
첫째 줄에 상덕이가 훔칠 수 있는 보석 가격의 합의 최댓값을 출력한다.
*/

/*
    헤맨 부분:
    보석을 기준으로 가방을 고를 때, 가방을 vector로 표현해서 O(N) 시간에 탐색하려고 하니깐 시간초과가 떴다.
    질문 게시판에 보니, 가방을 multiset(중복이 허용되는 set) 에 있는 lower_bound를 이용해야한다고 했고, 이것을 이용하니 시간초과 없이 풀 수 있었다.
    lower_bound를 이용하기 위해서는 정렬이 되어있어야 하므로 multiset 을 이용한 것이다. 굳이 multiset 안쓰고, vector에 sort해도 괜찮지 않을까 싶다.

    * 처음보는 함수들 *
    lower_bound(key)는 이진 탐색 기반의 탐색방법으로, key보다 "작지 않은(즉, 크거나 같은)" 첫번째 원소를 찾는다.
    upper_bound(key)는 key값보다 "큰" 첫번째 원소를 찾는다. 
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
using namespace std;

typedef struct
{
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        if (a.second != b.second)
        {
            return a.second < b.second;
        }
        return a.first > b.first;
    }
} cri;

int N, K;
unsigned long long ans;
priority_queue<pair<int, int>, vector<pair<int, int>>, cri> pq; // 무게, 가격
multiset<int> bag;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int m, v;
        cin >> m >> v;

        pq.push({m, v});
    }
    for (int i = 0; i < K; i++)
    {
        int x;
        cin >> x;
        bag.insert(x);
    }

    while (!pq.empty())
    {
        int w = pq.top().first;
        int p = pq.top().second;
        pq.pop();

        auto it = bag.lower_bound(w);
        if (it != bag.end())
        {
            ans += p;
            bag.erase(it);
        }
        if (bag.empty())
        {
            break;
        }
    }

    cout << ans << "\n";

    return 0;
}