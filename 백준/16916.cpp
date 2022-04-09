// https://www.acmicpc.net/problem/16916

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'

// N[..i]에서 접두사도 되고 접미사도 되는 문자열의 길이 pi[..i]를 반환한다.
vector<int> getPartialMatch(const string &N)
{
    int m = N.size();
    int matched = 0;
    vector<int> ret(m, 0);

    // iterate N
    for (int i = 1; i < m; i++)
    {
        while (matched > 0 && N[i] != N[matched])
        {
            matched = ret[matched - 1];
        }

        if (N[i] == N[matched])
        {
            ret[i] = ++matched;
        }
    }

    return ret;
}


// 짚더미 문자열 H에서, 바늘 문자열 N를 찾아서 시작위치를 반환한다.
vector<int> KMP(const string &H, const string &N)
{
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    int n = H.size(), m = N.size();
    int matched = 0;

    for (int i = 0; i < n; i++)
    {
        while (matched > 0 && H[i] != N[matched])
        {
            matched = pi[matched - 1];
        }

        if (H[i] == N[matched])
        {
            ++matched;
            if (matched == m)
            {
                ret.push_back(i - m + 1); // 시작위치 넣기
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}


int main()
{
    fastio;

    string S, P;
    cin >> S >> P;

    cout << (KMP(S, P).size() != 0) << endl;

    return 0;
}