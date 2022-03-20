// https://www.acmicpc.net/problem/2668

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

const int MAX = 101;

int N, G[MAX], isVisited[MAX];
vector<int> ans;

void dfs(int node, int start)
{
    if(isVisited[node]){
        return;
    }
    isVisited[node] = 1;
    const int next = G[node];
    dfs(next, start);

    // cycle
    if(next == start){
        ans.push_back(start);
    }
}

int main()
{
    fastio;
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> G[i];
    }

    for (int i = 1; i <= N; i++)
    {
        memset(isVisited, 0, sizeof(isVisited));
        dfs(i, i);
    }

    cout << ans.size() << " ";
    for(auto i : ans){
        cout << i << " ";
    }

    return 0;
}
