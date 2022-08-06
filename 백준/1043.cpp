// https://www.acmicpc.net/problem/1043
/*
  1. 파티에 사실을 아는 사람이 있는 경우 거짓말을 할 수 없다.
  2. 또한 어느 파티에서는 거짓말을 하고, 다른 파티에서는 사실을 말했는데 이 두
  파티에 동일한 사람이 참석한 경우 거짓말을 한 것이 들통나게 되므로 안된다.

  따라서 파티마다 집합을 만들되, 진실을 아는 사람을 최상위 부모로 하는 집합을
  만든다. 진실을 아는 사람과 함께 파티에 참석하는 사람은 모두 진실을 아는 사람을
  최상위 부모로 두게 될 것이고, 파티마다 대표로 한 사람씩 find를 통해 최상위
  부모가 진실을 아는 사람인지 확인하면, 이 파티에서 거짓말을 해도 되는지 알 수
  있게 된다.

  Union-find를 사용하는 것이 편리한 이유는 일반 배열로 하는 경우, 탐색하는
  순서에 따라 답이 다르게 나올 수 있기 때문이다. 예를 들어, 1번 사람이 진실을
  알고 있고, A파티에는 2번과 3번이, 그리고 B파티에는 1번과 3번이 참석한다고
  하자. A부터 시작해서 B로 탐색하는 경우, 당장 A파티에는 진실을 아는 사람이
  없으므로 거짓말을 해도 될 것 같지만, B파티에 3번 사람이 있기 때문에 A파티에서
  거짓말을 할 수 없다는 것을 뒤늦게 알게 된다.

  이렇듯 순서에 영향을 받기 때문에 Union-find를 통해 구조화한 후, 나중에 한 번에
  확인하는 것이 깔끔한 해결방법이 된다.
*/

#include<bits/stdc++.h>
using namespace std;

int p[51], N, M, ans;
vector<int> aware, t;

int Find(int x) {
  if (x == p[x]) {
    return p[x];
  }
  return p[x] = Find(p[x]);
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);

  // 진실을 아는 사람이 있다면 그 사람을 부모로 삼는다.
  if (find(aware.begin(), aware.end(), a) != aware.end()) {
    p[b] = a;
  } else if (find(aware.begin(), aware.end(), b) != aware.end()) {
    p[a] = b;
  } else if (a < b) {
    p[b] = a;
  } else {
    p[a] = b;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    p[i] = i;
  }

  int x, n;
  cin >> x;
  for (int i = 0; i < x; i++) {
    cin >> n;
    aware.push_back(n);
  }

  for (int i = 0; i < M; i++) {
    vector<int> temp;
    cin >> n;
    for (int j = 0; j < n; j++) {
      cin >> x;
      temp.push_back(x);
    }

    for (int j = 0; j < n - 1; j++) {
      Union(temp[j], temp[j + 1]);
    }

    // 각 파티에서 대표를 저장한다.
    t.push_back(temp[0]);
  }

  for (int i = 0; i < M; i++) {
    int f = Find(t[i]);
    if (find(aware.begin(), aware.end(), f) == aware.end()) {
      ++ans;
    }
  }

  cout << ans;

  return 0;
}
