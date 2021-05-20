/*
문제
크기가 N×M인 행렬 A와 M×K인 B를 곱할 때 필요한 곱셈 연산의 수는 총 N×M×K번이다. 
행렬 N개를 곱하는데 필요한 곱셈 연산의 수는 행렬을 곱하는 순서에 따라 달라지게 된다.
예를 들어, A의 크기가 5×3이고, B의 크기가 3×2, C의 크기가 2×6인 경우에 행렬의 곱 ABC를 구하는 경우를 생각해보자.

AB를 먼저 곱하고 C를 곱하는 경우 (AB)C에 필요한 곱셈 연산의 수는 5×3×2 + 5×2×6 = 30 + 60 = 90번이다.
BC를 먼저 곱하고 A를 곱하는 경우 A(BC)에 필요한 곱셈 연산의 수는 3×2×6 + 5×3×6 = 36 + 90 = 126번이다.
같은 곱셈이지만, 곱셈을 하는 순서에 따라서 곱셈 연산의 수가 달라진다.

행렬 N개의 크기가 주어졌을 때, 모든 행렬을 곱하는데 필요한 곱셈 연산 횟수의 최솟값을 구하는 프로그램을 작성하시오. 
입력으로 주어진 행렬의 순서를 바꾸면 안 된다.

입력
첫째 줄에 행렬의 개수 N(1 ≤ N ≤ 500)이 주어진다.
둘째 줄부터 N개 줄에는 행렬의 크기 r과 c가 주어진다. (1 ≤ r, c ≤ 500)
항상 순서대로 곱셈을 할 수 있는 크기만 입력으로 주어진다.

출력
첫째 줄에 입력으로 주어진 행렬을 곱하는데 필요한 곱셈 연산의 최솟값을 출력한다. 정답은 2^31-1 보다 작거나 같은 자연수이다. 
또한, 최악의 순서로 연산해도 연산 횟수가 2^31-1보다 작거나 같다.
*/
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX 500

int N, R[MAX], C[MAX], dp[MAX][MAX];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 입력
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> R[i] >> C[i];
    }

    // basis
    for (int i = 0; i < N - 1; i++)
    {
        dp[i][i + 1] = R[i] * C[i] * C[i + 1];
    }

    // dp
    for (int m = 1; m <= N; m++) // 곱할 행렬의 개수(1 ~ N)
    {
        for (int i = 0; i < N - m; i++) // 시작 위치 = (0 ~ N - 곱할 행렬의 개수)
        {
            int j = i + m; // 종료 위치 = (시작 위치 + 곱할 행렬의 개수)
            for (int k = i; k < j; k++) // 행렬을 쪼갤 중간 위치 (시작위치 ~ 종료위치) 
            {
                // 행렬의 곱셈 계산. i~j에서 연산횟수 = i~k에서 연산횟수 + (k+1)~j에서 연산횟수 + i~k~j에서의 행렬 연산횟수
                int res = dp[i][k] + dp[k + 1][j] + R[i] * C[k] * C[j];
                if (!dp[i][j] || dp[i][j] > res)
                    dp[i][j] = res;
            }
        }
    }

    cout << dp[0][N - 1];

    return 0;
}

/* 재귀함수 이용. 시간은 조금 더 오래 걸림. */
// #include <iostream>
// #include <cstring>
// #include <algorithm>
// using namespace std;

// int N, mat[500][2], dp[500][500];

// int solve(int l, int r)
// {
//     if (l == r)
//         return 0;

//     int &ret = dp[l][r];
//     if (ret != -1)
//         return ret;
        
//     ret = 987654321;

//     for (int i = l; i < r; i++)
//     {
//         ret = min(ret, solve(l, i) + solve(i + 1, r) + mat[l][0] * mat[i][1] * mat[r][1]);
//     }
//     return ret;
// }

// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     memset(dp, -1, sizeof(dp));

//     cin >> N;
//     for (int i = 0; i < N; i++){
//         cin >> mat[i][0] >> mat[i][1];
//     }
//     cout << solve(0, N - 1);

//     return 0;
// }