/*
문제
n×m의 0, 1로 된 배열이 있다. 이 배열에서 1로 된 가장 큰 정사각형의 크기를 구하는 프로그램을 작성하시오.

0	1	0	0
0	1	1	1
1	1	1	0
0	0	1	0

위와 같은 예제에서는 가운데의 2×2 배열이 가장 큰 정사각형이다. 

입력
첫째 줄에 n, m(1 ≤ n, m ≤ 1,000)이 주어진다. 다음 n개의 줄에는 m개의 숫자로 배열이 주어진다.

출력
첫째 줄에 가장 큰 정사각형의 넓이를 출력한다.

예제 입력 1 
4 4
0100
0111
1110
0010
예제 출력 1 
4
*/

#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, map[1000][1000], ans;

int checkSquare(const int &y, const int &x)
{
    if (!map[y][x])
    {
        return -1;
    }
    else if ((map[y][x] == map[y][x + 1]) && (map[y][x + 1] == map[y + 1][x]) && (map[y + 1][x] == map[y + 1][x + 1]))
    {
        return map[y][x];
    }
    else
    {
        return -1;
    }
}

void solve()
{
    while (1)
    {
        int temp_ans = ans;
        --N;
        --M;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                map[i][j] = checkSquare(i, j) + 1;
                ans = max(ans, map[i][j]);
            }
        }
        if (temp_ans == ans)
            break;
    }
}

int main()
{

    scanf("%d %d", &N, &M);
    getchar();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%1d", &map[i][j]);
            if(map[i][j]) ans = 1;
        }
    }

    solve();
    printf("%d", ans * ans);
}