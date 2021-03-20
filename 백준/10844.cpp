/*
문제
45656이란 수를 보자.

이 수는 인접한 모든 자리수의 차이가 1이 난다. 이런 수를 계단 수라고 한다.

세준이는 수의 길이가 N인 계단 수가 몇 개 있는지 궁금해졌다.

N이 주어질 때, 길이가 N인 계단 수가 총 몇 개 있는지 구하는 프로그램을 작성하시오. (0으로 시작하는 수는 없다.)

입력
첫째 줄에 N이 주어진다. N은 1보다 크거나 같고, 100보다 작거나 같은 자연수이다.

출력
첫째 줄에 정답을 1,000,000,000으로 나눈 나머지를 출력한다.
*/
#include <iostream>
using namespace std;

int N, dp[101][10];
long long ans;
const int MOD = 1000000000;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i <= 9; i++)
    {
        dp[1][i] = 1;
    }

    cin >> N;
    for (int i = 2; i <= N; i++)
    {
        dp[i][0] = dp[i-1][1];
        dp[i][9] = dp[i-1][8];
        for (int j = 1; j <= 8; j++)
        {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % MOD;
        }
    }

    for (int j = 0; j <= 9; j++)
    {
        ans += dp[N][j];
    }

    cout << ans % MOD;

    return 0;
}

/*
풀이

0 이나 9 같은 경우, 어디 오느냐에 따라 주변에 올 수 있는 수가 달라지므로, 자릿수에 맞춰서 생각해보자

1. N = 1 인 경우를 생각해보자.
끝에 오는 숫자가
0 1 2 3 4 5 6 7 8 9 일 때, 각각의 수마다 가능한 계단 수를 생각해보면
0 1 1 1 1 1 1 1 1 1 이 된다.

2. N = 2 인 경우를 생각해보자.
끝에 오는 숫자가 
0 1 2 3 4 5 6 7 8 9 일 때, 각각의 수마다 가능한 계단 수를 생각해보면
1 1 2 2 2 2 2 2 2 1 이 된다.(10, 21, 12, 32 ...)

3. N = 3 인 경우를 생각해보자.
끝에 오는 숫자가 
0 1 2 3 4 5 6 7 8 9 일 때, 각각의 수마다 가능한 계단 수를 생각해보면
1 3 3 4 4 4 4 4 3 2 이 된다.(210, 321, 101, 121 ... )

위 경우를 모두 이어붙이면
0 1 2 3 4 5 6 7 8 9 <- idx
0 1 1 1 1 1 1 1 1 1 <- N : 1
1 1 2 2 2 2 2 2 2 1 <- N : 2
1 3 3 4 4 4 4 4 3 2 <- N : 3

점화식 : 따라서 dp[i][j] 일 때 가능한 계단 수는 dp[i-1][j-1] + dp[i-1][j+1] 이 된다.
=> 길이가 i이고, i번째 수가 j일 때 가능한 계단수 = 길이가 i-1이고, i-1번째 숫자가 j-1 이나 j+1 일 때 가능한 계단수의 합이다.
ex) 길이가 3이고, 3번째 수가 3일 때 가능한 계단수 = 길이가 2이고, 2번째 숫자가 2이나 4일 때 가능한 계단수의 합
*/