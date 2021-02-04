/*
문제
어떤 N개의 수가 주어져 있다. 그런데 중간에 수의 변경이 빈번히 일어나고 그 중간에 어떤 부분의 합을 구하려 한다. 
만약에 1,2,3,4,5 라는 수가 있고, 3번째 수를 6으로 바꾸고 2번째부터 5번째까지 합을 구하라고 한다면 17을 출력하면 되는 것이다. 
그리고 그 상태에서 다섯 번째 수를 2로 바꾸고 3번째부터 5번째까지 합을 구하라고 한다면 12가 될 것이다.

입력
첫째 줄에 수의 개수 N(1 ≤ N ≤ 1,000,000)과 M(1 ≤ M ≤ 10,000), K(1 ≤ K ≤ 10,000) 가 주어진다. 
M은 수의 변경이 일어나는 횟수이고, K는 구간의 합을 구하는 횟수이다. 그리고 둘째 줄부터 N+1번째 줄까지 N개의 수가 주어진다. 
그리고 N+2번째 줄부터 N+M+K+1번째 줄까지 세 개의 정수 a, b, c가 주어지는데, 
a가 1인 경우 b(1 ≤ b ≤ N)번째 수를 c로 바꾸고 a가 2인 경우에는 b(1 ≤ b ≤ N)번째 수부터 c(b ≤ c ≤ N)번째 수까지의 합을 구하여 출력하면 된다.

입력으로 주어지는 모든 수는 -2^63보다 크거나 같고, 2^63-1보다 작거나 같은 정수이다.

출력
첫째 줄부터 K줄에 걸쳐 구한 구간의 합을 출력한다. 단, 정답은 -2^63보다 크거나 같고, 2^63-1보다 작거나 같은 정수이다.
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define MAX 1000001

int N, M, K;
long long arr[MAX];
vector<long long> tree;

// node : 세그먼트 트리 노드번호
// start ~ end : node가 담당하는 합의 범위
long long init(int start, int end, int node)
{
    // 노드가 leaf 노드인 경우, 노드는 배열의 그 원소를 가진다.
    if (start == end)
    {
        return tree[node] = arr[start];
    }

    int mid = (start + end) / 2;
    return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

// start ~ end : node가 담당하고 있는 범위
// left ~ right : 구하고자 하는 합의 범위
long long sum(int start, int end, int left, int right, int node)
{
    // [left, right]와 [start, end] 가 겹치지 않는 경우
    // => (start...end...left...right) or (left...right...start...end)
    if (left > end || right < start)
    {
        return 0;
    }

    // [left, right]가 [start, end]를 완전히 포함하는 경우
    // => left...start...end...right
    if (left <= start && end <= right)
    {
        return tree[node];
    }

    // 겹쳐있는 경우
    int mid = (start + end) / 2;
    return sum(start, mid, left, right, node * 2) + sum(mid + 1, end, left, right, node * 2 + 1);
}

// start ~ end : node가 담당하고 있는 범위
// index 번째 수를 val로 변경한다고 할 때,
// dif = val - arr[index]
void update(int start, int end, int node, int index, long long dif)
{
    // [start, end]에 index가 포함되지 않는 경우
    if (index < start || index > end)
    {
        return;
    }

    // [start, end]에 index가 포함되는 경우
    tree[node] += dif;
    if (start != end)
    {
        int mid = (start + end) / 2;
        update(start, mid, node * 2, index, dif);
        update(mid + 1, end, node * 2 + 1, index, dif);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    int h = (int)ceil(log2(N));
    tree.resize(1 << (h + 1));
    
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    init(0, N - 1, 1);

    for (int i = 0; i < M + K; i++)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int b;
            long long c;
            cin >> b >> c;

            long long dif = c - arr[b - 1];
            arr[b - 1] = c;
            update(0, N - 1, 1, b - 1, dif);
        }
        else
        {
            int b, c;
            cin >> b >> c;
            cout << sum(0, N - 1, b - 1, c - 1, 1) << "\n";
        }
    }

    return 0;
}