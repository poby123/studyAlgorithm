/*
문제
그래프가 주어졌을 때, 그 그래프의 최소 스패닝 트리를 구하는 프로그램을 작성하시오.

최소 스패닝 트리는, 주어진 그래프의 모든 정점들을 연결하는 부분 그래프 중에서 그 가중치의 합이 최소인 트리를 말한다.

입력
첫째 줄에 정점의 개수 V(1 ≤ V ≤ 10,000)와 간선의 개수 E(1 ≤ E ≤ 100,000)가 주어진다. 
다음 E개의 줄에는 각 간선에 대한 정보를 나타내는 세 정수 A, B, C가 주어진다. 
이는 A번 정점과 B번 정점이 가중치 C인 간선으로 연결되어 있다는 의미이다. C는 음수일 수도 있으며, 절댓값이 1,000,000을 넘지 않는다.

그래프의 정점은 1번부터 V번까지 번호가 매겨져 있고, 임의의 두 정점 사이에 경로가 있다. 
최소 스패닝 트리의 가중치가 -2,147,483,648보다 크거나 같고, 2,147,483,647보다 작거나 같은 데이터만 입력으로 주어진다.

출력
첫째 줄에 최소 스패닝 트리의 가중치를 출력한다.

예제 입력 1 
3 3
1 2 1
2 3 2
1 3 3
예제 출력 1 
3
*/

/*
    스패닝트리(Spanning Tree) : 
        그래프 내의 모든 정점을 포함하는 트리를 말한다. 신장트리라고도 부른다.
        그래프의 최소 연결 부분 그래프이다. 따라서 간선의 수가 가장 적다.
        그래프에 N개의 정점이 있다면, 스패닝트리는 최소 간선의 수인 N-1개의 간선을 가지고 있다.

    최소 스패닝트리(MST, Minimum Spanning Tree) :  
        스패닝 트리인데, 간선들의 가중치 합이 최소인 트리를 말한다.
        1. 간선의 가중치 합이 최소여야하며,
        2. 정점의 개수보다 하나 적은 간선만을 가지고 있어야한다.
        3. 사이클이 있으면 안된다.

    MST의 구현방법으로는 Kruskal 알고리즘과 Prim 알고리즘이 있다.

    1. Kruskal :
        그리디 알고리즘을 이용해서, 간선들을 가중치를 기준으로 오름차순으로 정렬한다.
        그 후, 가중치 값이 가장 작은 간선을 먼저 사용하면서 그래프를 만들어간다.
        이 때, 사이클이 발생하면 안되므로, Union-Find 알고리즘을 사용해서 사이클 여부를 판단한다.

        * 간선들을 정렬하는 시간복잡도가 전체 시간복잡도를 결정하므로, 크루스칼 알고리즘의 시간복잡도는 O(ElgE)가 된다. [E는 간선의 개수이다]

    2. Prim : 
        시작 정점에서부터 출발해서 단계적으로 확장해나가는 방법이다.
        처음에는 시작 정점만 MST 집합에 포함한다.
        앞 단계에서 만들어진 MST 집합에 인접한 정점들 중 가장 작은 가중치를 가진 간선으로 연결된 정점을 선택하여 트리를 확장한다.
        이 과정을 간선이 N-1개가 될 때까지 반복한다.


    * 그래프안에 간선이 적은 경우(희소 그래프)에는 Kruskal 알고리즘이 적절하고, 간선이 많이 존재하는 경우(밀집 그래프)에는 Prim 알고리즘이 적절하다.

*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int V, E, table[10001], ans;
vector<pair<pair<int, int>, int>> G;

int cri(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b)
{
    return a.second < b.second;
}

int find(int x)
{
    if (table[x] == x)
    {
        return x;
    }
    return table[x] = find(table[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a < b)
    {
        table[b] = a;
    }
    else
    {
        table[a] = b;
    }
}

void kruskal()
{
    for (auto target : G)
    {
        int from = target.first.first;
        int to = target.first.second;
        int cost = target.second;

        if (find(from) != find(to))
        {
            union_(from, to);
            ans += cost;
        }
    }
}

int main()
{

    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> V >> E;

    G.reserve(E);
    for (int i = 1; i <= V; i++)
    {
        table[i] = i;
    }

    for (int i = 0; i < E; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        G.push_back({{A, B}, C});
    }

    sort(G.begin(), G.end(), cri);
    kruskal();
    cout << ans;

    return 0;
}