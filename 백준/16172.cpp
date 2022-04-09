// https://www.acmicpc.net/problem/16172

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)
#define endl '\n'

vector<int> getPartialMatch(const string &);
vector<int> KMP(const string &, const string &);

string H, S, K;

int main()
{
    fastio;

    cin >> S >> K;
    for(char c : S){
        if(!isdigit(c)){
            H.push_back(c);
        }
    }

    cout << (KMP(H, K).size() != 0) << endl;

    return 0;
}

vector<int> getPartialMatch(const string &N)
{
    int m = N.size();
    vector<int> pi(m, 0);

    for (int i = 1, j = 0; i < m; i++)
    {   
        while (j > 0 && N[i] != N[j])
        {
            j = pi[j - 1];
        }

        if (N[i] == N[j])
        {
            pi[i] = ++j;
        }
    }

    return pi;
}

vector<int> KMP(const string &H, const string &N)
{
    int n = H.size(), m = N.size();
    vector<int> pi = getPartialMatch(N);
    vector<int> ret;

    for (int i = 0, j = 0; i < n; i++)
    {
        while (j > 0 && H[i] != N[j])
        {
            j = pi[j - 1];
        }

        if (H[i] == N[j])
        {
            ++j;
            if (j == m)
            {
                ret.push_back(i - m + 1);
            }
        }
    }

    return ret;
}