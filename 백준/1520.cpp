/*
    DFS와 DP를 이용해 해결한다.
    dp[y][x] = (y, x) 에서 존재하는 경로의 갯수.
    
    방문하지 않은 곳과, DP 값이 정말 0인 경우를 구별하기 위해 -1로 초기화한다.
*/

#include <stdio.h>

int h[501][501], dp[501][501], M, N, mvx[4] = {1, 0, -1, 0}, mvy[4] = {0, 1, 0, -1};

bool isRange(int y, int x)
{
    return x > 0 && x <= M && y > 0 && y <= N;
}

int dfs(int y, int x)
{
    if (y == 1 && x == 1)
        return 1;
    if (dp[y][x] == -1)
    {
        dp[y][x] = 0;
        for (int d = 0; d < 4; d++)
        {
            int nextY = y + mvy[d];
            int nextX = x + mvx[d];
            if (isRange(nextY, nextX) && h[nextY][nextX] > h[y][x])
            {
                dp[y][x] += dfs(nextY, nextX);
            }
        }
    }
    return dp[y][x];
}
int main(void)
{
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            scanf("%d", &h[i][j]);
            dp[i][j] = -1;
        }
    }

    printf("%d\n", dfs(N, M));

    /* //print dp
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            printf("%2d ", dp[i][j]);
        }
        putchar('\n');
    }
    */

    return 0;
}