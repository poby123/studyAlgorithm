/*
문제
N(1 ≤ N ≤ 100,000)개의 정수들이 있을 때, a번째 정수부터 b번째 정수까지 중에서 제일 작은 정수, 또는 제일 큰 정수를 찾는 것은 어려운 일이 아니다. 
하지만 이와 같은 a, b의 쌍이 M(1 ≤ M ≤ 100,000)개 주어졌을 때는 어려운 문제가 된다. 이 문제를 해결해 보자.

여기서 a번째라는 것은 입력되는 순서로 a번째라는 이야기이다. 
예를 들어 a=1, b=3이라면 입력된 순서대로 1번, 2번, 3번 정수 중에서 최소, 최댓값을 찾아야 한다. 
각각의 정수들은 1이상 1,000,000,000 이하의 값을 갖는다.

입력
첫째 줄에 N, M이 주어진다. 다음 N개의 줄에는 N개의 정수가 주어진다. 다음 M개의 줄에는 a, b의 쌍이 주어진다.

출력
M개의 줄에 입력받은 순서대로 각 a, b에 대한 답을 최솟값, 최댓값 순서로 출력한다.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int N, M;
vector<pair<int, int>> tree; // max, min
vector<int> arr;

// start ~ end : 노드가 담당하는 arr 범위
void init(int start, int end, int node)
{
    if (start == end)
    {
        tree[node].first = arr[start];
        tree[node].second = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    init(start, mid, node * 2);
    init(mid + 1, end, node * 2 + 1);

    tree[node].first = max(tree[node * 2].first, tree[node * 2 + 1].first);
    tree[node].second = min(tree[node * 2].second, tree[node * 2 + 1].second);
}

// start ~ end : 노드가 담당하는 arr 범위, left ~ right : 검색 범위
pair<int, int> find(int left, int right, int start, int end, int node)
{
    // 범위를 벗어나는 경우
    if (end < left || right < start)
    {
        return {INT_MIN, INT_MAX};
    }

    // 범위에 있는 경우
    if (left <= start && end <= right)
    {
        return tree[node];
    }

    // 겹쳐있는 경우
    int mid = (start + end) / 2;
    auto cand1 = find(left, right, start, mid, node * 2);
    auto cand2 = find(left, right, mid + 1, end, node * 2 + 1);

    /*
        실수한 부분 : find에서 tree를 업데이트하면 안된다ㅜ
        아래처럼 그냥 값을 리턴해야한다.
    */
    return {max(cand1.first, cand2.first), min(cand1.second, cand2.second)};
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    arr.resize(N + 1);
    tree.resize(4 * N); // 세그먼트 트리는 4 * N 의 크기로 잡아줘야 충분하다.

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    // 세그먼트 트리 초기화
    init(0, N - 1, 1);

    for (int i = 0; i < M; i++)
    {
        int left, right;
        cin >> left >> right;
        
        auto ans = find(left - 1, right - 1, 0, N - 1, 1);
        cout << ans.second << " " << ans.first << "\n";
    }

    return 0;
}