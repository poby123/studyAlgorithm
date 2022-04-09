#include <iostream>
#include <vector>
using namespace std;

// ret[..i]: N[0..i]에서 접두사도 되고, 접미사도 되는 문자열의 길이를 반환한다.
vector<int> getPartialMatch(const string &N)
{
    int m = N.size();
    int begin = 1, matched = 0;
    vector<int> ret(m, 0);

    while (begin + matched < m)
    {
        if (N[begin + matched] == N[matched])
        {
            ++matched;
            ret[begin + matched - 1] = matched;
        }
        else
        {
            if (matched == 0)
            {
                ++begin;
            }
            else
            {
                begin += matched - ret[matched - 1];
                matched = ret[matched - 1];
            }
        }
    }

    return ret;
}

// 문자열 H에서 N이 나오는 시작위치를 모두 반환한다.
vector<int> KMP(const string &H, const string &N)
{
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);

    int begin = 0, matched = 0;
    int n = H.size(), m = N.size();

    while (begin <= n - m)
    {
        if (matched < m && H[begin + matched] == N[matched])
        {
            ++matched;
            if (matched == m)
            {
                ret.push_back(begin);
            }
        }
        else
        {
            if (matched == 0)
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
}