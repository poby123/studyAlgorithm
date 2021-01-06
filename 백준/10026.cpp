/*
문제
적록색약은 빨간색과 초록색의 차이를 거의 느끼지 못한다. 따라서, 적록색약인 사람이 보는 그림은 아닌 사람이 보는 그림과는 좀 다를 수 있다.

크기가 N×N인 그리드의 각 칸에 R(빨강), G(초록), B(파랑) 중 하나를 색칠한 그림이 있다. 그림은 몇 개의 구역으로 나뉘어져 있는데, 구역은 같은 색으로 이루어져 있다. 또, 같은 색상이 상하좌우로 인접해 있는 경우에 두 글자는 같은 구역에 속한다. (색상의 차이를 거의 느끼지 못하는 경우도 같은 색상이라 한다)

예를 들어, 그림이 아래와 같은 경우에

RRRBB
GGBBB
BBBRR
BBRRR
RRRRR
적록색약이 아닌 사람이 봤을 때 구역의 수는 총 4개이다. (빨강 2, 파랑 1, 초록 1) 하지만, 적록색약인 사람은 구역을 3개 볼 수 있다. (빨강-초록 2, 파랑 1)

그림이 입력으로 주어졌을 때, 적록색약인 사람이 봤을 때와 아닌 사람이 봤을 때 구역의 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. (1 ≤ N ≤ 100)

둘째 줄부터 N개 줄에는 그림이 주어진다.

출력
적록색약이 아닌 사람이 봤을 때의 구역의 개수와 적록색약인 사람이 봤을 때의 구역의 수를 공백으로 구분해 출력한다.

예제 입력 1 
5
RRRBB
GGBBB
BBBRR
BBRRR
RRRRR
예제 출력 1 
4 3
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, ans1, ans2;
char map[100][101];
bool visit[100][100];
int mvy[] = {0, 0, 1, -1};
int mvx[] = {1, -1, 0, 0};

bool isRange(int y, int x)
{
    return (0 <= y && y < N) && (0 <= x && x < N);
}

int bfs(int y, int x)
{
    queue<pair<int, int>> q;
    char type = map[y][x];

    q.push({y, x});
    visit[y][x] = true;

    while (!q.empty())
    {
        pair<int, int> front = q.front();
        int y = front.first;
        int x = front.second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextY = y + mvy[i];
            int nextX = x + mvx[i];

            if (isRange(nextY, nextX) && !visit[nextY][nextX] && map[nextY][nextX] == type)
            {
                visit[nextY][nextX] = true;
                q.push({nextY, nextX});
            }
        }
    }
    return 1;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> map[i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!visit[i][j])
            {
                ans1 += bfs(i, j);
            }
        }
    }

    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] == 'G')
            {
                map[i][j] = 'R';
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!visit[i][j])
            {
                ans2 += bfs(i, j);
            }
        }
    }

    cout << ans1 << " " << ans2 << "\n";

    return 0;
}