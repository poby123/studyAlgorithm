#include<iostream>
#include<vector>
using namespace std;


// ret[..i]: N[0..i]에서 접두사도 되고, 접미사도 되는 문자열의 길이를 반환한다.
// 다른 KMP 알고리즘을 이용한 구현
vector<int> getPartialMatch2(const string &N)
{
    int m = N.size();
    int matched = 0;
    vector<int> ret(m, 0);

    for (int i = 1; i < m; i++)
    {
        while (matched > 0 && N[i] != N[matched])
        {
            matched = ret[matched - 1];
        }

        if (N[i] == N[matched])
        {
            ++matched;
            ret[i] = matched;
        }
    }

    return ret;
}


// 문자열 H에서 N이 나오는 시작위치를 모두 반환한다.
// KMP 알고리즘의 또 다른 구현.
vector<int> KMP2(const string &H, const string &N)
{
    int n = H.size(), m = N.size();
    int matched = 0;

    vector<int> pi = getPartialMatch2(N);
    vector<int> ret;

    // 짚더미 문자열 H의 각 글자를 순회한다.
    for (int i = 0; i < n; i++)
    {
        // 불일치하는 경우, 현재 대응된 글자 수를 pi[matched-1]로 줄인다.
        while (matched > 0 && H[i] != N[matched])
        {
            matched = pi[matched - 1];
        }

        // 일치하는 경우
        if (H[i] == N[matched])
        {
            ++matched;
            if (matched == m)
            {
                ret.push_back(i - m + 1);
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}