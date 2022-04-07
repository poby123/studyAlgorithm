// https://www.acmicpc.net/problem/1701

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'
#define MAX 5000

int ans;

vector<int> getPartialMatch(const string &N)
{
    vector<int> pi(N.size(), 0);
    int begin = 1, matched = 0;

    while (begin + matched < N.size())
    {
        if (N[begin + matched] == N[matched])
        {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else
        {
            if (!matched)
            {
                ++begin;
            }
            else
            {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return pi;
}


int main()
{
    fastio;

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++)
    {
        vector<int> pi = getPartialMatch(s.substr(i, s.size()));
        sort(pi.begin(), pi.end(), greater<int>());

        ans = max(ans, pi[0]);
    }

    cout << ans << endl;

    return 0;
}
