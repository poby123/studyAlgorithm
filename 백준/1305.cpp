// https://www.acmicpc.net/problem/1305

/*
    전광판의 크기: L
    현재 보이는 광고판: s
    구해야하는 것: 가능한 광고의 길이 중 가장 짧은 것의 길이. 이것을 N이라 하자.

    pi[i] = s[..i]에서 접두사도 되고, 접미사도 되는 문자열의 길이
    
    ex) 5 babba -> 3
    L - pi[L-1] = 5 - pi[5 - 1] = 5 - 2 = 3

    문자열의 마지막이 접두사와 중복된 채로 끝났다면, 
    그 길이 만큼 광고 문자열을 감소시킴으로써, 가장 짧은 길이를 구할 수가 있다.
    다음 광고가 중복되는 부분부터 시작한다고 가정할 수 있기 때문이다!
*/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int L;
string s;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> L >> s;

    int m = s.size();
    vector<int> pi(m, 0);

    for (int i = 1, matched = 0; i < m; i++)
    {
        while (matched > 0 && s[i] != s[matched])
            matched = pi[matched - 1];

        if (s[i] == s[matched])
        {
            pi[i] = ++matched;
        }
    }

    cout << L - pi[L - 1] << endl;

    return 0;
}
