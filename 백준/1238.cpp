/*
문제
N개의 숫자로 구분된 각각의 마을에 한 명의 학생이 살고 있다.
어느 날 이 N명의 학생이 X (1 ≤ X ≤ N)번 마을에 모여서 파티를 벌이기로 했다. 
이 마을 사이에는 총 M개의 단방향 도로들이 있고 i번째 길을 지나는데 Ti(1 ≤ Ti ≤ 100)의 시간을 소비한다.
각각의 학생들은 파티에 참석하기 위해 걸어가서 다시 그들의 마을로 돌아와야 한다. 하지만 이 학생들은 워낙 게을러서 최단 시간에 오고 가기를 원한다.
이 도로들은 단방향이기 때문에 아마 그들이 오고 가는 길이 다를지도 모른다. N명의 학생들 중 오고 가는데 가장 많은 시간을 소비하는 학생은 누구일지 구하여라.

입력
첫째 줄에 N(1 ≤ N ≤ 1,000), M(1 ≤ M ≤ 10,000), X가 공백으로 구분되어 입력된다. 
두 번째 줄부터 M+1번째 줄까지 i번째 도로의 시작점, 끝점, 그리고 이 도로를 지나는데 필요한 소요시간 Ti가 들어온다. 
시작점과 끝점이 같은 도로는 없으며, 시작점과 한 도시 A에서 다른 도시 B로 가는 도로의 개수는 최대 1개이다.

모든 학생들은 집에서 X에 갈수 있고, X에서 집으로 돌아올 수 있는 데이터만 입력으로 주어진다.

출력
첫 번째 줄에 N명의 학생들 중 오고 가는데 가장 오래 걸리는 학생의 소요시간을 출력한다.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX 1001
#define INF 1000000000

int N, M, X;

vector<pair<int, int>> G[MAX];
int dp[MAX][MAX], ans;

void dik(int start)
{
    dp[start][start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto top = pq.top();

        int cur = top.second;
        int cost = -top.first;
        pq.pop();

        if (dp[start][cur] < cost)
        {
            continue;
        }
        for (int i = 0; i < G[cur].size(); i++)
        {
            int next = G[cur][i].first;
            int nextCost = cost + G[cur][i].second;
            if (dp[start][next] > nextCost)
            {
                dp[start][next] = nextCost;
                pq.push({-nextCost, next});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> X;
    fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), INF);

    for (int i = 0; i < M; i++)
    {
        int s, e, t;
        cin >> s >> e >> t;
        G[s].push_back({e, t});
    }

    for (int i = 1; i <= N; i++)
    {
        dik(i);
    }

    for (int i = 1; i <= N; i++)
    {
        ans = max(ans, dp[i][X] + dp[X][i]);
    }

    cout << ans << "\n";

    return 0;
}