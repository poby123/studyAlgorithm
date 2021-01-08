/*
문제
N개의 도시가 있다. 그리고 한 도시에서 출발하여 다른 도시에 도착하는 M개의 버스가 있다. 
우리는 A번째 도시에서 B번째 도시까지 가는데 드는 버스 비용을 최소화 시키려고 한다. 
A번째 도시에서 B번째 도시까지 가는데 드는 최소비용을 출력하여라. 도시의 번호는 1부터 N까지이다.

입력
첫째 줄에 도시의 개수 N(1 ≤ N ≤ 1,000)이 주어지고 둘째 줄에는 버스의 개수 M(1 ≤ M ≤ 100,000)이 주어진다. 
그리고 셋째 줄부터 M+2줄까지 다음과 같은 버스의 정보가 주어진다. 먼저 처음에는 그 버스의 출발 도시의 번호가 주어진다. 그리고 그 다음에는 도착지의 도시 번호가 주어지고 또 그 버스 비용이 주어진다. 버스 비용은 0보다 크거나 같고, 100,000보다 작은 정수이다.

그리고 M+3째 줄에는 우리가 구하고자 하는 구간 출발점의 도시번호와 도착점의 도시번호가 주어진다.
출발점에서 도착점을 갈 수 있는 경우만 입력으로 주어진다.

출력
첫째 줄에 출발 도시에서 도착 도시까지 가는데 드는 최소 비용을 출력한다.

예제 입력 1 
5
8
1 2 2
1 3 3
1 4 1
1 5 10
2 4 2
3 4 1
3 5 1
4 5 3
1 5
예제 출력 1 
4
*/

/*
    헤맨 부분 : 
    1. 출발 노드가 정해져있으므로 플로이드 와샬이 아닌 다익스트라 알고리즘을 사용해야 한다. 제한시간이 0.5초이므로 플로이드 와샬을 쓰면 시간이 초과될 것이다.
    2. INF값을 int형이 오버플로우하지 않게 잡으려고, 아무 생각없이 각 엣지의 비용의 최댓값인 100000으로 잡았던 것이 문제였다.
    다익스트라 알고리즘의 원리상 엣지끼리의 비용끼리 합쳐서, 합치지 않은 비용과 비교하기 때문에
    최대비용을 하나의 엣지 비용으로 잡으면 안된다... 한 정점에서 다른 정점으로 갈 때, 다른 모든 엣지를 지나는 최악의 경우를 생각하면
    적어도 999(N의 최댓값-1) * 1000000(각 엣지의 최대비용) = 999000000 정도로 잡아야할 것이다.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 999000001

using namespace std;

int dist[1001];
vector<pair<int, int>> vec[100001];

void dijkstra(int start)
{
    dist[start] = 0;
    priority_queue<pair<int, int>> pq; //{cost, node} => first을 기준으로, first가 똑같은 경우에는 second로 내림차순 정렬하므로 cost를 first에 넣는다.
    pq.push({0, start});

    while (!pq.empty())
    {
        int cur = pq.top().second;
        int distance = -pq.top().first; //넣을 때 -를 붙여서 넣으므로 꺼낼때도 -를 붙여서 꺼낸다
        pq.pop();

        if (dist[cur] < distance)
        {
            continue;
        }
        for (int i = 0; i < vec[cur].size(); i++)
        {
            int next = vec[cur][i].first;
            int nextDistance = distance + vec[cur][i].second;
            if (dist[next] > nextDistance)
            {
                dist[next] = nextDistance;
                pq.push({-nextDistance, next}); //priority_queue가 내림차순으로 정렬하는데, 비용이 더 적은 순서대로 정렬하기 위해 -를 붙여서 넣는다. (2 1) -> (-1 -2) 이런식으로. 
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int start, end, N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        dist[i] = INF;
    }

    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        vec[u].push_back({v, w});
    }

    cin >> start >> end;
    dijkstra(start);
    cout << dist[end];
    return 0;
}