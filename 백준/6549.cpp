/**
 * 고안3. 스택
 * 해답: https://cocoon1787.tistory.com/315
 * 막대의 인덱스를 순서대로 스택에 push 할 때 push 하려는 막대의 높이가 스택의 top 인덱스의 막대 높이보다 크거나 같다면 계속해서 스택을 쌓습니다.
 * 그러다가 push 하려는 막대의 높이가 스택의 top 인덱스의 막대 높이보다 작을 경우,
 * 스택의 top 인덱스의 막대 높이가 push 하려는 막대의 높이보다 작아질 때까지 while문을 도는데,
 * while문 안에서는 스택을 하나씩 pop 하면서 구할 수 있는 직사각형의 최대 넓이를 구하게 됩니다.
 *
 * -> 스택 내부를 오름차순으로 관리하기.


8 1 2 3 4 5 4 1 8 0

8 1 2 3 4 5 4 1 8 0

8 1 2 3 4 5 6 7 8 0

10 2 3 4 5 0 7 6 5 4 3 0
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

stack<int> st;
int N;

ll solve(const vector<int> &H)
{
    ll ans = 0LL;

    for (int i = 0; i < N; i++)
    {
        int curH = H[i];
        while (!st.empty() && curH < H[st.top()])
        {
            int topIndex = st.top();
            st.pop();

            int startIndex = -1;
            if (!st.empty())
            {
                startIndex = st.top();
            }
            int w = (i - startIndex - 1);
            ans = max(ans, w * (ll)H[topIndex]);
        }

        st.push(i);
    }

    while (!st.empty())
    {
        int topIndex = st.top();
        st.pop();

        int startIndex = -1;
        if (!st.empty())
        {
            startIndex = st.top();
        }
        int w = (N - startIndex - 1);
        ans = max(ans, w * (ll)H[topIndex]);
    }

    return ans;
}

int main()
{
    fastio;

    while (1)
    {
        cin >> N;
        vector<int> H(N, 0);
        if (N <= 0)
        {
            break;
        }

        for (int i = 0; i < N; i++)
        {
            int x;
            cin >> x;
            H[i] = x;
        }

        ll ans = solve(H);
        cout << ans << endl;
    }

    return 0;
}