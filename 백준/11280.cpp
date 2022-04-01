// https://www.acmicpc.net/problem/11280

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0)
#define endl '\n'
#define MAX 10000

int N, M, a, b, nodeId, sccId, discovered[MAX * 2], done[MAX * 2], SCC[MAX * 2];
vector<int> adj[MAX * 2];
stack<int> s;

// adj의 인덱스를 반환한다.
// n가 음수(not)면 adj에서의 인덱스 값은 2*(-n-1)+1 : 1, 3, 5
// n가 양수면 adj에서의 인덱스 값은 2*(n-1) : 0, 2, 4
int getIndex(int n)
{
    if (n < 0)
    {
        return 2 * (-n - 1) + 1;
    }
    return 2 * (n - 1);
}

// 반대 인덱스를 반환한다.
int getNotIndex(int n)
{
    return (n % 2) ? (n - 1) : (n + 1);
}


// 타잔 알고리즘에서 사용하는 dfs
int dfs(int cur)
{
    int parent = discovered[cur] = ++nodeId;
    s.push(cur);

    for (int next : adj[cur])
    {
        if (!discovered[next])
        {
            parent = min(parent, dfs(next));
        }
        else if (!done[next])
        {
            parent = min(parent, discovered[next]);
        }
    }

    // 부모 노드가 자기 자신
    if (parent == discovered[cur])
    {
        ++sccId;

        while (1)
        {
            int t = s.top();
            s.pop();

            done[t] = 1;
            SCC[t] = sccId;

            if (t == cur)
                break;
        }
    }

    return parent;
}

// 타잔 알고리즘으로 scc를 추출한다.
void targanSCC()
{
    for (int i = 0; i < 2 * N; i++)
    {
        if (!discovered[i])
        {
            dfs(i);
        }
    }
}


// solve
int solve()
{
    targanSCC();

    for (int i = 0; i < N; i++)
    {
        if (SCC[i * 2] == SCC[i * 2 + 1])
        {
            return 0;
        }
    }

    return 1;
}


int main()
{
    fastio;

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;

        a = getIndex(a);
        b = getIndex(b);

        // 두 항중 하나가 거짓일 때, 나머지 하나가 참이되는 명제를 모은다.
        adj[getNotIndex(a)].push_back(b);
        adj[getNotIndex(b)].push_back(a);
    }

    cout << solve() << endl;

    return 0;
}
