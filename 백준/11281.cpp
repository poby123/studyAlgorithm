// https://www.acmicpc.net/problem/11281

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0)
#define endl '\n'
#define MAX 10000

int N, M, a, b, nodeId, sccId, discovered[MAX * 2], done[MAX * 2], SCC[MAX * 2], var[MAX];
vector<int> adj[MAX * 2];
stack<int> s;

// adj의 인덱스를 반환한다.
// n가 음수면 adj에서의 인덱스 값은 2*(-n-1)+1 : 1, 3, 5
// n가 양수면 adj에서의 인덱스 값은 2*(n-1) : 0, 2, 4
int getIndex(int n)
{
    if (n < 0)
    {
        return 2 * (-n - 1) + 1;
    }
    return 2 * (n - 1);
}

// 반대(Not) index를 반환한다.
inline int getNotIndex(int n)
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
vector<int> solve()
{
    targanSCC();

    // P와 ~P가 같은 SCC에 있는 경우, 모순이므로 f는 거짓이 된다.
    for (int i = 0; i < N; i++)
    {
        if (SCC[i * 2] == SCC[i * 2 + 1])
        {
            return vector<int>();
        }
    }

    // f가 참인 경우의 변수의 값을 구하기 위해 각 정점을 정렬한다.
    // SCC 방문한 순서를 뒤집으면 위상정렬이 되는 점을 이용하자.
    vector<pair<int, int>> satOrder;
    for (int i = 0; i < 2 * N; i++)
    {
        satOrder.push_back({-SCC[i], i}); // reverse
    }
    sort(satOrder.begin(), satOrder.end());


    // f를 참으로 만드는 x_i 배열인 var을 채워보자.
    vector<int> var(N, -1);
    for (const auto &cur : satOrder)
    {
        int i = cur.second;

        // i가 홀수면 ~P를, 짝수면 P를 방문한 것이었다. 
        // ~P를 먼저 방문한 경우에는 ~P를 거짓으로 만들어야하므로, P는 참이된다. P=1 (i가 홀수)
        // P를 먼저 방문한 경우에는 P를 거짓으로 만들어야하므로, ~P는 참이 된다. P=0 (i가 짝수)
        if (var[i / 2] == -1)
        {
            var[i / 2] = !(i % 2 == 0);
        }
    }

    return var;
}

int main()
{
    fastio;
    memset(var, -1, sizeof(var));

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


    vector<int> ans = solve();
    if (ans.size())
    {
        cout << 1 << endl;
        for (int i : ans)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    else
    {
        cout << 0 << endl;
    }

    return 0;
}
