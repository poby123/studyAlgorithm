/*
문제(https://www.acmicpc.net/problem/2206)
N×M의 행렬로 표현되는 맵이 있다. 맵에서 0은 이동할 수 있는 곳을 나타내고, 1은 이동할 수 없는 벽이 있는 곳을 나타낸다. 
당신은 (1, 1)에서 (N, M)의 위치까지 이동하려 하는데, 이때 최단 경로로 이동하려 한다. 
최단경로는 맵에서 가장 적은 개수의 칸을 지나는 경로를 말하는데, 이때 시작하는 칸과 끝나는 칸도 포함해서 센다.

만약에 이동하는 도중에 한 개의 벽을 부수고 이동하는 것이 좀 더 경로가 짧아진다면, 벽을 한 개 까지 부수고 이동하여도 된다.

맵이 주어졌을 때, 최단 경로를 구해 내는 프로그램을 작성하시오.

입력
첫째 줄에 N(1 ≤ N ≤ 1,000), M(1 ≤ M ≤ 1,000)이 주어진다. 다음 N개의 줄에 M개의 숫자로 맵이 주어진다. (1, 1)과 (N, M)은 항상 0이라고 가정하자.

출력
첫째 줄에 최단 거리를 출력한다. 불가능할 때는 -1을 출력한다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

char map[1001][1001];
int visit[1001][1001][2]; //3차원 배열을 이용한다. 1번 벽을 넘을 수 있으므로, 2개의 층이 있다고 생각하자.
int mvx[] = {0, 0, -1, 1};
int mvy[] = {1, -1, 0, 0};
int N, M;

int bfs()
{
    queue<pair<pair<int, int>, int>> q; // {{y,x}, 벽을 뿌순 횟수}
    visit[1][1][0] = 1;
    q.push({{1, 1}, 0});

    while (!q.empty())
    {
        pair<pair<int, int>, int> p = q.front();
        q.pop();

        int current_y = p.first.first;
        int current_x = p.first.second;
        int crush = p.second;

        // 도착지에 도착한 경우 경로의 길이를 반환한다.
        if (current_y == N && current_x == M)
        {
            return visit[N][M][crush];
        }

        // 상하좌우 이동
        for (int direction = 0; direction < 4; ++direction)
        {
            int next_y = current_y + mvy[direction];
            int next_x = current_x + mvx[direction];

            // 다음 위치가 범위안인지 확인
            if (1 <= next_x && next_x <= M && 1 <= next_y && next_y <= N)
            {
                // 벽 뿌수기(위치가 벽이고, 벽을 뿌순 적이 없으면)
                if (crush < 1 && map[next_y][next_x] == '1')
                {
                    visit[next_y][next_x][crush + 1] = visit[current_y][current_x][crush] + 1;
                    q.push({{next_y, next_x}, crush + 1});
                }

                // 이동 (위치가 빈 공간이고, 방문한 적이 없으면)
                else if (map[next_y][next_x] == '0' && visit[next_y][next_x][crush] == 0)
                {
                    visit[next_y][next_x][crush] = visit[current_y][current_x][crush] + 1;
                    q.push({{next_y, next_x}, crush});
                }
            }
        }
    }
    // 도착지에 도착하지 못한 경우, -1을 반환한다.
    return -1;
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i)
    {
        //문자열 입력을 통해 scanf의 호출시간을 줄일 수 있고, 결과적으로 60ms 정도의 시간을 단축시킬 수 있다.
        scanf("%s", &map[i][1]);
    }

    printf("%d\n", bfs());

    return 0;
}