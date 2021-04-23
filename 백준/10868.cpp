/*
문제
N(1 ≤ N ≤ 100,000)개의 정수들이 있을 때, a번째 정수부터 b번째 정수까지 중에서 제일 작은 정수를 찾는 것은 어려운 일이 아니다. 
하지만 이와 같은 a, b의 쌍이 M(1 ≤ M ≤ 100,000)개 주어졌을 때는 어려운 문제가 된다. 이 문제를 해결해 보자.

여기서 a번째라는 것은 입력되는 순서로 a번째라는 이야기이다. 예를 들어 a=1, b=3이라면 입력된 순서대로 1번, 2번, 3번 정수 중에서 최솟값을 찾아야 한다. 
각각의 정수들은 1이상 1,000,000,000이하의 값을 갖는다.

입력
첫째 줄에 N, M이 주어진다. 다음 N개의 줄에는 N개의 정수가 주어진다. 다음 M개의 줄에는 a, b의 쌍이 주어진다.

출력
M개의 줄에 입력받은 순서대로 각 a, b에 대한 답을 출력한다.
*/

#include <iostream>
#include <algorithm>
#include <climits>
#define MAX 100001
using namespace std;

int N, M, arr[MAX], tree[4 * MAX];

// 노드 범위 : start ~ end
void init(int start, int end, int node)
{
    if (start == end)
    {
        tree[node] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    init(start, mid, node * 2);
    init(mid + 1, end, node * 2 + 1);

    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

// 탐색 범위 : left ~ right
// 노드 범위 : start ~ end
int find(int left, int right, int start, int end, int node)
{
    // 탐색범위와 노드 범위가 겹치지 않는 경우
    if (right < start || end < left)
    {
        return INT_MAX;
    }

    // 탐색범위가 해당 노드범위에 완전히 포함되는 경우
    if (left <= start && end <= right)
    {
        return tree[node];
    }

    // 탐색범위가 해당 노드 범위에 걸친 경우
    int mid = (start + end) / 2;
    int c1 = find(left, right, start, mid, node * 2);
    int c2 = find(left, right, mid + 1, end, node * 2 + 1);

    return min(c1, c2);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }

    init(1, N, 1);

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << find(a, b, 1, N, 1) << "\n";
    }

    return 0;
}