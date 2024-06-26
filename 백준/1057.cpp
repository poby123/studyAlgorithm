/**
 * 김지민은 N명이 참가하는 스타 토너먼트에 진출했다.
 * 토너먼트는 다음과 같이 진행된다.
 * 일단 N명의 참가자는 번호가 1번부터 N번까지 배정받는다.
 * 그러고 난 후에 서로 인접한 번호끼리 스타를 한다.
 * 이긴 사람은 다음 라운드에 진출하고, 진 사람은 그 라운드에서 떨어진다.
 * 만약 그 라운드의 참가자가 홀수명이라면, 마지막 번호를 가진 참가자는 다음 라운드로 자동 진출한다.
 * 다음 라운드에선 다시 참가자의 번호를 1번부터 매긴다.
 * 이때, 번호를 매기는 순서는 처음 번호의 순서를 유지하면서 1번부터 매긴다.
 * 이 말은 1번과 2번이 스타를 해서 1번이 진출하고, 3번과 4번이 스타를 해서 4번이 진출했다면, 4번은 다음 라운드에서 번호 2번을 배정받는다.
 * 번호를 다시 배정받은 후에 한 명만 남을 때까지 라운드를 계속 한다.
 * 마침 이 스타 대회에 임한수도 참가했다. 김지민은 갑자기 스타 대회에서 우승하는 욕심은 없어지고,
 * 몇 라운드에서 임한수와 대결하는지 궁금해졌다. 일단 김지민과 임한수는 서로 대결하기 전까지 항상 이긴다고 가정한다.
 * 1 라운드에서 김지민의 번호와 임한수의 번호가 주어질 때, 과연 김지민과 임한수가 몇 라운드에서 대결하는지 출력하는 프로그램을 작성하시오.
 *
 *
 * 1 2 3 4 5 6 7 8
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
 *
 *
 *
 * 1'      2'
 * 1       2'       3'          4
 * 1   2   3   4'   5'    6     7     8
 * 1 2 3 4 5 6 7 8' 9' 10 11 12 13 14 15 16
 */

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using pp = pair<int, int>;
using tp = tuple<int, int, int>;

int N, a, b;

int solve()
{

    cin >> N >> a >> b;

    for (int i = 0; N >= 2; i++)
    {
        if ((a == b + 1 && b % 2 == 1) || (a % 2 == 1 && b == a + 1))
        {
            return i + 1;
        }

        if (N % 2 != 0)
        {
            N = (N - 1) / 2 + 1;
        }
        else
        {
            N /= 2;
        }

        a = (a + 1) / 2;
        b = (b + 1) / 2;
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << solve();

    return 0;
}