/*
문제
LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제이다.

예를 들어, ACAYKP와 CAPCAK의 LCS는 ACAK가 된다.

입력
첫째 줄과 둘째 줄에 두 문자열이 주어진다. 문자열은 알파벳 대문자로만 이루어져 있으며, 최대 1000글자로 이루어져 있다.

출력
첫째 줄에 입력으로 주어진 두 문자열의 LCS의 길이를, 둘째 줄에 LCS를 출력한다.

LCS가 여러 가지인 경우에는 아무거나 출력하고, LCS의 길이가 0인 경우에는 둘째 줄을 출력하지 않는다.
*/

/*
접근:
    if A[i-1] == B[j-1] => dp[i][j] = dp[i-1][j-1] + 1
    else A[i-1] != B[j-1] => max(dp[i-1][j], dp[i][j-1])

    이므로 LCS에 해당하는 문자열을 찾기 위해서는 

    1. dp[i][j] == dp[i-1][j] 또는 dp[i][j] == dp[i][j-1] 인 좌표를 만나면 그 좌표로 이동한다. 똑같은 값은 이전 좌표에서 넘겨받은 것이기 때문이다.
    2. dp[i][j] == dp[i-1][j-1] + 1 이라면 dp[i-1][j-1] 인 좌표에서 1이 커진 것이므로 A[i-1] 문자를 넣고, 그 좌표로 이동한다.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define MAX 1001

string a, b, ans;
int dp[MAX][MAX];

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> a >> b;
    for (int i = 1; i <= a.size(); i++)
    {
        for (int j = 1; j <= b.size(); j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int y = a.size();
    int x = b.size();

    while (dp[y][x])
    {
        if (dp[y][x] == dp[y - 1][x])
        {
            --y;
        }
        else if (dp[y][x] == dp[y][x - 1])
        {
            --x;
        }
        else if (dp[y][x] == dp[y - 1][x - 1] + 1)
        {
            --y;
            --x;
            ans += a[y];
        }
    }

    reverse(ans.begin(), ans.end());

    cout << dp[a.size()][b.size()] << "\n"
         << ans;

    return 0;
}