// https://www.acmicpc.net/problem/1786

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000001

string H, N;
int n, m, i, matched;
vector<int> pi(MAX, 0), ans;

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    getline(cin, H);
    getline(cin, N);

    n = H.size(), m = N.size();

    // getParitalMatch
    for (i = 1, matched = 0; i < m; i++)
    {
        while (matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];

        if (N[i] == N[matched])
        {
            pi[i] = ++matched;
        }
    }

    // KMP
    for (i = 0, matched = 0; i < n; i++)
    {
        while (matched > 0 && H[i] != N[matched])
            matched = pi[matched - 1];

        if (H[i] == N[matched])
        {
            ++matched;
            if (matched == m)
            {
                ans.push_back(i + 1 - m);
            }
        }
    }

    // print
    cout << ans.size() << endl;
    for (int i : ans)
    {
        cout << i + 1 << " ";
    }

    return 0;
}