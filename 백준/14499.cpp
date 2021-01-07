/*
문제
크기가 N×M인 지도가 존재한다. 지도의 오른쪽은 동쪽, 위쪽은 북쪽이다. 이 지도의 위에 주사위가 하나 놓여져 있으며, 주사위의 전개도는 아래와 같다. 지도의 좌표는 (r, c)로 나타내며, r는 북쪽으로부터 떨어진 칸의 개수, c는 서쪽으로부터 떨어진 칸의 개수이다. 

  2
4 1 3
  5
  6
주사위는 지도 위에 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며, 놓여져 있는 곳의 좌표는 (x, y) 이다. 가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.

지도의 각 칸에는 정수가 하나씩 쓰여져 있다. 주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.

주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때, 주사위가 이동했을 때 마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성하시오.

주사위는 지도의 바깥으로 이동시킬 수 없다. 만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

입력
첫째 줄에 지도의 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 20), 주사위를 놓은 곳의 좌표 x y(0 ≤ x ≤ N-1, 0 ≤ y ≤ M-1), 그리고 명령의 개수 K (1 ≤ K ≤ 1,000)가 주어진다.

둘째 줄부터 N개의 줄에 지도에 쓰여 있는 수가 북쪽부터 남쪽으로, 각 줄은 서쪽부터 동쪽 순서대로 주어진다. 주사위를 놓은 칸에 쓰여 있는 수는 항상 0이다. 지도의 각 칸에 쓰여 있는 수는 10을 넘지 않는 자연수 또는 0이다.

마지막 줄에는 이동하는 명령이 순서대로 주어진다. 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4로 주어진다.

출력
이동할 때마다 주사위의 윗 면에 쓰여 있는 수를 출력한다. 만약 바깥으로 이동시키려고 하는 경우에는 해당 명령을 무시해야 하며, 출력도 하면 안 된다.

예제 입력 1 
4 2 0 0 8
0 2
3 4
5 6
7 8
4 4 4 1 3 3 3 2
예제 출력 1 
0
0
3
0
0
8
6
3
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3
#define TOP 4
#define BOTTOM 5

int dice[6]; // 동 서 남 북 위 아래
int map[20][20], command[1000];
int N, M, K, dicePos_y, dicePos_x;

void copy()
{
    if (map[dicePos_y][dicePos_x])
    {
        dice[BOTTOM] = map[dicePos_y][dicePos_x];
        map[dicePos_y][dicePos_x] = 0;
    }
    else
    {
        map[dicePos_y][dicePos_x] = dice[BOTTOM];
    }
}

void moveEast()
{
    // 동->아래, 아래->서, 서->위, 위->동
    int temp = dice[EAST];
    dice[EAST] = dice[TOP];
    dice[TOP] = dice[WEST];
    dice[WEST] = dice[BOTTOM];
    dice[BOTTOM] = temp;
}

void moveWest()
{
    // 서->아래, 아래->동, 동->위, 위->서
    int temp = dice[WEST];
    dice[WEST] = dice[TOP];
    dice[TOP] = dice[EAST];
    dice[EAST] = dice[BOTTOM];
    dice[BOTTOM] = temp;
}

void moveNorth()
{
    // 북->아래, 아래->남, 남->위, 위->북
    int temp = dice[NORTH];
    dice[NORTH] = dice[TOP];
    dice[TOP] = dice[SOUTH];
    dice[SOUTH] = dice[BOTTOM];
    dice[BOTTOM] = temp;
}

void moveSouth()
{
    // 남->아래, 아래->북, 북->위, 위->남
    int temp = dice[SOUTH];
    dice[SOUTH] = dice[TOP];
    dice[TOP] = dice[NORTH];
    dice[NORTH] = dice[BOTTOM];
    dice[BOTTOM] = temp;
}

void doCommand()
{
    for (int i = 0; i < K; i++)
    {
        int current_command = command[i];
        bool flag = false;
        switch (current_command)
        {
        case 1:
            if (dicePos_x + 1 < M)
            {
                moveEast();
                ++dicePos_x;
                flag = true;
            }
            break;
        case 2:
            if (dicePos_x - 1 >= 0)
            {
                moveWest();
                --dicePos_x;
                flag = true;
            }
            break;
        case 3:
            if (dicePos_y - 1 >= 0)
            {
                moveNorth();
                --dicePos_y;
                flag = true;
            }
            break;
        case 4:
            if (dicePos_y + 1 < N)
            {
                moveSouth();
                ++dicePos_y;
                flag = true;
            }
            break;
        }
        if (flag)
        {
            copy();
            cout << dice[TOP] << "\n";
        }
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M >> dicePos_y >> dicePos_x >> K;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < K; i++)
    {
        cin >> command[i];
    }

    doCommand();
    return 0;
}