// https://www.acmicpc.net/problem/1260

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
#define MAX_N 1001

int N, M, V, a, b;
vector<vector<int>> G(MAX_N);
vector<int> visited(MAX_N, 0);

void dfs(int x) {
  if (visited[x]) {
    return;
  }

  visited[x] = 1;
  cout << x << " ";

  for (int next : G[x]) {
    dfs(next);
  }
}

void bfs(int x) {
  queue<int> q;

  visited[x] = 1;
  q.push(x);

  while (!q.empty()) {
    int cur = q.front();
    cout << cur << " ";
    q.pop();

    for (int next : G[cur]) {
      if (!visited[next]) {
        visited[next] = 1;
        q.push(next);
      }
    }
  }
}

int main() {
  fastio;

  cin >> N >> M >> V;

  for (int i = 0; i < M; i++) {
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  for (int i = 1; i <= N; i++) {
    sort(G[i].begin(), G[i].end());
  }

  dfs(V);
  visited.assign(MAX_N, 0);
  cout << "\n";
  bfs(V);

  return 0;
}