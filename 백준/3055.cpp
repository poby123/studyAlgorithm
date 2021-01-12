/*
문제
사악한 암흑의 군주 이민혁은 드디어 마법 구슬을 손에 넣었고, 그 능력을 실험해보기 위해 근처의 티떱숲에 홍수를 일으키려고 한다. 
이 숲에는 고슴도치가 한 마리 살고 있다. 고슴도치는 제일 친한 친구인 비버의 굴로 가능한 빨리 도망가 홍수를 피하려고 한다.

티떱숲의 지도는 R행 C열로 이루어져 있다. 비어있는 곳은 '.'로 표시되어 있고, 물이 차있는 지역은 '*', 돌은 'X'로 표시되어 있다. 
비버의 굴은 'D'로, 고슴도치의 위치는 'S'로 나타내어져 있다.

매 분마다 고슴도치는 현재 있는 칸과 인접한 네 칸 중 하나로 이동할 수 있다. (위, 아래, 오른쪽, 왼쪽) 물도 매 분마다 비어있는 칸으로 확장한다. 
물이 있는 칸과 인접해있는 비어있는 칸(적어도 한 변을 공유)은 물이 차게 된다. 물과 고슴도치는 돌을 통과할 수 없다. 
또, 고슴도치는 물로 차있는 구역으로 이동할 수 없고, 물도 비버의 소굴로 이동할 수 없다.

티떱숲의 지도가 주어졌을 때, 고슴도치가 안전하게 비버의 굴로 이동하기 위해 필요한 최소 시간을 구하는 프로그램을 작성하시오.

고슴도치는 물이 찰 예정인 칸으로 이동할 수 없다. 즉, 다음 시간에 물이 찰 예정인 칸으로 고슴도치는 이동할 수 없다. 이동할 수 있으면 고슴도치가 물에 빠지기 때문이다. 

입력
첫째 줄에 50보다 작거나 같은 자연수 R과 C가 주어진다.

다음 R개 줄에는 티떱숲의 지도가 주어지며, 문제에서 설명한 문자만 주어진다. 'D'와 'S'는 하나씩만 주어진다.

출력
첫째 줄에 고슴도치가 비버의 굴로 이동할 수 있는 가장 빠른 시간을 출력한다. 만약, 안전하게 비버의 굴로 이동할 수 없다면, "KAKTUS"를 출력한다.

예제 입력 1 
3 3
D.*
...
.S.
예제 출력 1 
3
*/
/*
    1. 문제에서 고슴도치는 다음 시간에 물이 찰 예정인 칸으로 움직일 수 없으므로, 물을 먼저 이동시키고, 그 다음 고슴도치를 이동시킨다.
    
    2. 여러 좌표에 있는 물과, 고슴도치가 시간에 맞춰서 움직여야하기 때문에, 
    이동하기 전에 q.size를 이용하여 q의 크기를 구해놓고,(이동하면서 q에 새로운 좌표를 담기 때문에, 반드시 이동하기 전에 q.size를 구해놔야한다.)
    담겨있는 좌표를 그 크기만큼만 꺼내서 새로운 좌표로 이동시킨다. 
*/
#include <iostream>
#include <queue>
using namespace std;

char map[50][51];
int costW[50][50], costG[50][50], R, C, ans;
int mvy[] = {0, 0, 1, -1};
int mvx[] = {-1, 1, 0, 0};

bool isRange(const int &y, const int &x)
{
    return (0 <= x && x < C) && (0 <= y && y < R);
}

int bfs()
{
    queue<pair<int, int>> wq, gq;
    int numW, numG;

    // init
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (map[i][j] == '*')
            {
                wq.push({i, j});
            }
            else if (map[i][j] == 'S')
            {
                gq.push({i, j});
            }
        }
    }

    while (1)
    {
        // Water move
        numW = wq.size();
        for (int i = 0; i < numW; i++)
        {
            auto front = wq.front();
            wq.pop();

            int y = front.first;
            int x = front.second;

            for (int direction = 0; direction < 4; direction++)
            {
                int cost = costW[y][x];
                int nextY = y + mvy[direction];
                int nextX = x + mvx[direction];

                if (isRange(nextY, nextX) && (map[nextY][nextX] == '.' || map[nextY][nextX] == 'S'))
                {
                    costW[nextY][nextX] = cost + 1;
                    map[nextY][nextX] = '*';
                    wq.push({nextY, nextX});
                }
            }
        }

        // 고슴도치 move
        numG = gq.size();
        if (!numG) // 이동한 고슴도치들이 모두 물에 빠져서 죽은 경우 -1을 리턴한다.
            return -1;
        for (int i = 0; i < numG; i++)
        {
            auto front = gq.front();
            gq.pop();

            int y = front.first;
            int x = front.second;

            for (int direction = 0; direction < 4; direction++)
            {
                int cost = costG[y][x];
                int nextY = y + mvy[direction];
                int nextX = x + mvx[direction];

                if (isRange(nextY, nextX) && map[nextY][nextX] != '*' && map[nextY][nextX] != 'X' && !costG[nextY][nextX])
                {
                    costG[nextY][nextX] = cost + 1;
                    if (map[nextY][nextX] == 'D') // 비버 굴에 도착한 경우, 걸린 시간을 리턴한다.
                        return costG[nextY][nextX];
                    map[nextY][nextX] = 'S';
                    gq.push({nextY, nextX});
                }
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> R >> C;

    for (int i = 0; i < R; i++)
    {
        cin >> map[i];
    }

    ans = bfs();

    if (ans < 0)
    {
        cout << "KAKTUS\n";
    }
    else
    {
        cout << ans << "\n";
    }

    return 0;
}