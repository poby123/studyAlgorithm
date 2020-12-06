/*
문제
LCS(Longest Common Subsequence, 최장 공통 부분 수열)문제는 두 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것을 찾는 문제이다.

예를 들어, ACAYKP와 CAPCAK의 LCS는 ACAK가 된다.

입력
첫째 줄과 둘째 줄에 두 문자열이 주어진다. 문자열은 알파벳 대문자로만 이루어져 있으며, 최대 1000글자로 이루어져 있다.

출력
첫째 줄에 입력으로 주어진 두 문자열의 LCS의 길이를 출력한다.

예제 입력 1 
ACAYKP
CAPCAK

예제 출력 1 
4
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 방법1 : 재귀함수를 이용하는 방법 -> 시간초과
// 원리
// LCS(a[k], b[k]) 를 a의 0번째 인덱스부터 k번째까지의 문자열과 와 b 0번째 인덱스부터 k번째까지의 문자열의 최장 공통 부분 수열이라고 하면
// a[k] == b[k] 일 때 : LCS(a[k-1], b[k-1]) + 1 이다. 이런식으로 큰 문제가 작은 문제로 쪼개진다.
// a[k] != b[k] 이면 max(LCS(a[k-1], b[k]), LCS(a[k], b[k-1])) 로 바꿀 수 있다.
// int LCS(string a, string b)
// {
//     if (a.length() == 0 || b.length() == 0)
//     {
//         return 0;
//     }
//     else if (a[a.length() - 1] == b[b.length() - 1])
//     {
//         return LCS(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1)) + 1;
//     }
//     else
//     {
//         return max(LCS(a.substr(0, a.length() - 1), b.substr(0, b.length())), LCS(a.substr(0, a.length()), b.substr(0, b.length() - 1)));
//     }
// }

// 방법2 : DP를 이용하는 방법
// 원리 : 방법1의 원리의 응용이다.
// DP테이블을 순회하면서, a[i-1] == b[j-1] 이면 dp[i][j] = dp[i-1][j-1] + 1 이 된다.
// a[i-1] != b[j-1] 이면 dp[i][j] = max(dp[i-1][j], dp[i][j-1]) 이 된다.
int LCS(string a, string b)
{
    int dp[1001][1001] = {0};
    for (int i = 1; i <= a.length(); ++i)
    {
        for (int j = 1; j <= b.length(); ++j)
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
    return dp[a.length()][b.length()];
}

int main()
{
    string a, b;
    cin >> a >> b;
    printf("%d", LCS(a, b));
    return 0;
}