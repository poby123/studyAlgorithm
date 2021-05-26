/*
문제
두 마리의 백조가 호수에서 살고 있었다. 그렇지만 두 마리는 호수를 덮고 있는 빙판으로 만나지 못한다.

호수는 행이 R개, 열이 C개인 직사각형 모양이다. 어떤 칸은 얼음으로 덮여있다.

호수는 차례로 녹는데, 매일 물 공간과 접촉한 모든 빙판 공간은 녹는다. 
두 개의 공간이 접촉하려면 가로나 세로로 닿아 있는 것만 (대각선은 고려하지 않는다) 생각한다.

아래에는 세 가지 예가 있다.

...XXXXXX..XX.XXX ....XXXX.......XX .....XX.......... 
....XXXXXXXXX.XXX .....XXXX..X..... ......X.......... 
...XXXXXXXXXXXX.. ....XXX..XXXX.... .....X.....X..... 
..XXXXX..XXXXXX.. ...XXX....XXXX... ....X......XX.... 
.XXXXXX..XXXXXX.. ..XXXX....XXXX... ...XX......XX.... 
XXXXXXX...XXXX... ..XXXX.....XX.... ....X............ 
..XXXXX...XXX.... ....XX.....X..... ................. 
....XXXXX.XXX.... .....XX....X..... ................. 
      처음               첫째 날             둘째 날
백조는 오직 물 공간에서 세로나 가로로만(대각선은 제외한다) 움직일 수 있다.

며칠이 지나야 백조들이 만날 수 있는 지 계산하는 프로그램을 작성하시오.

입력
입력의 첫째 줄에는 R과 C가 주어진다. 단, 1 ≤ R, C ≤ 1500.

다음 R개의 줄에는 각각 길이 C의 문자열이 하나씩 주어진다. '.'은 물 공간, 'X'는 빙판 공간, 'L'은 백조가 있는 공간으로 나타낸다.

출력
첫째 줄에 문제에서 주어진 걸리는 날을 출력한다.
*/

/*  
    맵의 최대크기가 1500x1500으로 꽤 크기 때문에, 날마다 매번 BFS를 하면 시간초과가 난다. 
    따라서, 한 번 BFS를 할 때 다음날 사용할 큐를 미리 준비해준다. 
    
    이 프로그램에서는 1) 물 큐(waterQ)  2) 다음날 물 큐(nextWaterQ)  3) 백조 큐(swanQ)  4) 다음날 백조 큐(nextSwanQ) 이렇게 4개의 큐를 사용한다. 
    그리고 백조는 물 위에 있으므로, 자연스럽게 백조 큐는 물 큐에도 포함되며, 다음 날 백조 큐 또한 다음날 물 큐에 포함된다. 
    (이렇게 포함되어야 물 큐를 사용하는 bfs를 통해 빙하가 녹을 수 있기 때문이다.)

    이렇게 BFS를 하다가 백조 BFS가 ‘L’을 만나면 성공.

    ※ 많이 헤맨 부분
    다음날 물 큐와 다음 날 백조 큐를 전역으로 선언하는 경우 따로 메모리를 해제하지 않으면 계속해서 데이터가 누적된다. 
    그리고 다음날 큐들은 다음 날 맵을 탐색하는데 사용하므로, 쓸 데 없는 탐색을 하게 되어 결국 시간초과가 난다. 
    지역변수로 선언하거나 반복문을 써서 큐를 해제해줘야한다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 1500

int R, C, mvi[] = {0, 0, -1, 1}, mvj[] = {-1, 1, 0, 0}, swanVisit[MAX][MAX], ans;
char map[MAX][MAX];
queue<pair<int, int>> waterQ, swanQ;

inline bool isIn(const int y, const int x)
{
    return 0 <= y && y < R && 0 <= x && x < C;
}

void waterBfs()
{
    queue<pair<int, int>> nextWaterQ;

    while (!waterQ.empty())
    {
        auto front = waterQ.front();
        waterQ.pop();

        const int y = front.first;
        const int x = front.second;

        for (int d = 0; d < 4; d++)
        {
            const int nextY = y + mvi[d];
            const int nextX = x + mvj[d];

            // 물에 인접한 빙하는 녹이고, 다음날 물 큐에 넣는다.
            if (isIn(nextY, nextX) && map[nextY][nextX] == 'X')
            {
                map[nextY][nextX] = '.';
                nextWaterQ.push({nextY, nextX});
            }
        }
    }
    waterQ = nextWaterQ;
}

bool swanBfs()
{
    // for문 위치상, 맨 처음 빙하를 녹이기 전에도 호출되는데, 이 경우에는 불필요한 연산을 하지 않을 수 있도록 한다.
    if(!ans) return false;

    queue<pair<int, int>> nextSwanQ;

    while (!swanQ.empty())
    {
        auto front = swanQ.front();
        swanQ.pop();

        const int y = front.first;
        const int x = front.second;

        for (int d = 0; d < 4; d++)
        {
            const int nextY = y + mvi[d];
            const int nextX = x + mvj[d];

            if (isIn(nextY, nextX) && !swanVisit[nextY][nextX])
            {
                swanVisit[nextY][nextX] = 1;

                // 백조 발견...!
                if (map[nextY][nextX] == 'L')
                {
                    return true;
                }

                // 물 위는 백조가 이동할 수 있다.
                else if (map[nextY][nextX] == '.')
                {
                    swanQ.push({nextY, nextX});
                }

                // 물(백조는 물 위에 떠있으므로)에 인접한 빙하는 다음 날 녹기 때문에, 다음날 탐색할 수 있도록 넣는다.
                else
                {
                    nextSwanQ.push({nextY, nextX});
                }
            }
        }
    }

    swanQ = nextSwanQ;
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int swanNum = 0;

    // input
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            char& cur = map[i][j];
            cin >> cur;

            // 빙하가 아니면 waterQ에 넣어서 인접한 빙하를 녹일 수 있도록 한다.
            if (cur != 'X')
            {
                waterQ.push({i, j});
            }

            // 처음 나온 백조는 swanQ에 넣는다.
            if (cur == 'L' && !swanNum)
            {
                swanVisit[i][j] = 1;
                swanQ.push({i, j});

                ++swanNum;
            }
        }
    }

    for (; !swanBfs(); waterBfs(), ++ans);
    cout << ans;

    return 0;
}