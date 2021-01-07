/**
 * 문제
 'Dummy' 라는 도스게임이 있다. 이 게임에는 뱀이 나와서 기어다니는데, 사과를 먹으면 뱀 길이가 늘어난다. 뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.

게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다. 보드의 상하좌우 끝에 벽이 있다. 게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다. 뱀은 처음에 오른쪽을 향한다.

뱀은 매 초마다 이동을 하는데 다음과 같은 규칙을 따른다.

먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉, 몸길이는 변하지 않는다.
사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초에 끝나는지 계산하라.

입력
첫째 줄에 보드의 크기 N이 주어진다. (2 ≤ N ≤ 100) 다음 줄에 사과의 개수 K가 주어진다. (0 ≤ K ≤ 100)

다음 K개의 줄에는 사과의 위치가 주어지는데, 첫 번째 정수는 행, 두 번째 정수는 열 위치를 의미한다. 사과의 위치는 모두 다르며, 맨 위 맨 좌측 (1행 1열) 에는 사과가 없다.

다음 줄에는 뱀의 방향 변환 횟수 L 이 주어진다. (1 ≤ L ≤ 100)

다음 L개의 줄에는 뱀의 방향 변환 정보가 주어지는데,  정수 X와 문자 C로 이루어져 있으며. 게임 시작 시간으로부터 X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻이다. X는 10,000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.

출력
첫째 줄에 게임이 몇 초에 끝나는지 출력한다.

예제 입력 1 
6
3
3 4
2 5
5 3
3
3 D
15 L
17 D
예제 출력 1 
9
 * */

#include <iostream>
#include <queue>
#include <deque>
using namespace std;

#define SPACE 0
#define APPLE 1
#define SNAKE 2

int N, K, L, direction, ans, board[100][100];

int mvy[] = {0, -1, 0, 1};
int mvx[] = {1, 0, -1, 0};

bool isRange(const int &y, const int &x)
{
    return (0 <= y && y < N) && (0 <= x && x < N);
}

void updateBoard(deque<pair<int, int>> &snake, int next_y, int next_x, bool isApple)
{
    snake.push_front({next_y, next_x});
    board[next_y][next_x] = SNAKE;

    if (!isApple)
    {
        auto back = snake.back();
        snake.pop_back();

        board[back.first][back.second] = SPACE;
    }
}

int forward(deque<pair<int, int>> &snake, queue<pair<int, char>> &move)
{
    int time = 0;
    while (1)
    {
        // update direction
        int change_direction = 0;
        if (!move.empty())
        {
            pair<int, char> front = move.front();
            int reservedTime = front.first;
            if (time == reservedTime)
            {
                move.pop();
                char second = front.second;
                change_direction = (second == 'L') ? 1 : -1;
            }
        }
        direction += change_direction;
        if (direction > 3)
        {
            direction = 0;
        }
        else if (direction < 0)
        {
            direction = 3;
        }

        // move
        pair<int, int> front = snake.front();
        int head_y = front.first;
        int head_x = front.second;

        int next_y = head_y + mvy[direction];
        int next_x = head_x + mvx[direction];

        if (isRange(next_y, next_x))
        {
            switch (board[next_y][next_x])
            {
            case SPACE:
                updateBoard(snake, next_y, next_x, false);
                break;
            case APPLE:
                updateBoard(snake, next_y, next_x, true);
                break;
            case SNAKE:
                return time + 1; /* 여기서 break하면 switch 문을 나가게 되며, while문을 나간다고 착각해서는 안된다.*/
            }
        }
        else
        {
            break;
        }
        ++time;
    }
    return time + 1;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    queue<pair<int, char>> move;
    deque<pair<int, int>> snake;

    cin >> N >> K;

    for (int i = 0; i < K; i++)
    {
        int y, x;
        cin >> y >> x;
        board[y - 1][x - 1] = APPLE;
    }

    snake.push_back({0, 0});
    board[0][0] = SNAKE;

    cin >> L;
    for (int i = 0; i < L; i++)
    {
        int time;
        char direction;
        cin >> time >> direction;
        move.push({time, direction});
    }
    ans = forward(snake, move);
    cout << ans << "\n";

    return 0;
}