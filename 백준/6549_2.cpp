/**
 * 고안1. 분할정복 -> 가운데서부터 큰쪽으로 뻗어나가기 (X)
 *
반례
8
8 8 1 2 3 4 5 4
0
 *
 * 답: 16, 출력: 12
 *
 *
 * 고안2. 세그먼트 트리 (일단TLE. (N^2)*(logN))
 * 고안2-2. 분할정복 -> 왼쪽, 오른쪽 반반 x 어떻게 하지?
 * 해답: https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=occidere&logNo=221057769152
 *      높이가 최소인 곳을 기준으로 왼쪽과 오른쪽의 넓이를 구하며 재귀적으로 진행한다.
 *      높이가 최소인 곳을 제외하면 더 큰 넓이가 나올 수 있기 때문이다.

 */

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie()->sync_with_stdio(0);
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;
using ll = long long;

#define MAX 100001
#define INF 1e9

vector<int> tree(MAX << 2);
int N;
vector<ll> H(MAX, 0);

// 구간에서 높이가 최소인 인덱스로 초기화
// node: l ~ r까지 담당
int init(int l, int r, int i)
{
    if (l >= r)
    {
        return tree[i] = l;
    }

    int m = (l + r) / 2;
    int leftMinIndex = init(l, m, i * 2);
    int rightMinIndex = init(m + 1, r, i * 2 + 1);

    return tree[i] = H[leftMinIndex] < H[rightMinIndex] ? leftMinIndex : rightMinIndex;
}

// 구간에서 높이가 최소인 인덱스 반환
int getMin(int l, int r, int s, int e, int i)
{
    // 해당없음
    if (e < l || r < s)
    {
        return 0;
    }

    if (s <= l && r <= e)
    {
        return tree[i];
    }

    int m = (l + r) / 2;
    int leftMinIndex = getMin(l, m, s, e, i * 2);
    int rightMinIndex = getMin(m + 1, r, s, e, i * 2 + 1);

    if (!leftMinIndex || !rightMinIndex)
    {
        return leftMinIndex + rightMinIndex;
    }
    return H[leftMinIndex] < H[rightMinIndex] ? leftMinIndex : rightMinIndex;
}

// 구간에서 최대넓이 반환
// 높이가 최소인 인덱스를 기준으로, 왼쪽과 오른쪽을 나눠서 넓이를 구하고, 최대넓이를 반환.
ll getMaxWidth(int s, int e)
{
    int minIndex = getMin(1, N, s, e, 1);
    ll ans = (e - s + 1) * H[minIndex];

    if (s <= minIndex - 1)
    {
        ll leftSideMaxWidth = getMaxWidth(s, minIndex - 1);
        ans = max(ans, leftSideMaxWidth);
    }
    if (minIndex + 1 <= e)
    {
        ll rightSideMaxWidth = getMaxWidth(minIndex + 1, e);
        ans = max(ans, rightSideMaxWidth);
    }

    return ans;
}

int main()
{
    fastio;

    while (1)
    {
        cin >> N;
        if (N <= 0)
        {
            break;
        }

        for (int i = 1; i <= N; i++)
        {
            int x;
            cin >> x;
            H[i] = x;
        }
        fill(tree.begin(), tree.end(), INF);
        init(1, N, 1);

        ll ans = getMaxWidth(1, N);
        cout << ans << endl;

        H.clear();
        tree.clear();
    }

    return 0;
}