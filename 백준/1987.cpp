/*
문제
세로 R칸, 가로 C칸으로 된 표 모양의 보드가 있다. 보드의 각 칸에는 대문자 알파벳이 하나씩 적혀 있고, 좌측 상단 칸 (1행 1열) 에는 말이 놓여 있다.

말은 상하좌우로 인접한 네 칸 중의 한 칸으로 이동할 수 있는데, 새로 이동한 칸에 적혀 있는 알파벳은 지금까지 지나온 모든 칸에 적혀 있는 알파벳과는 달라야 한다. 
즉, 같은 알파벳이 적힌 칸을 두 번 지날 수 없다.

좌측 상단에서 시작해서, 말이 최대한 몇 칸을 지날 수 있는지를 구하는 프로그램을 작성하시오. 말이 지나는 칸은 좌측 상단의 칸도 포함된다.

입력
첫째 줄에 R과 C가 빈칸을 사이에 두고 주어진다. (1 ≤ R,C ≤ 20) 둘째 줄부터 R개의 줄에 걸쳐서 보드에 적혀 있는 C개의 대문자 알파벳들이 빈칸 없이 주어진다.

출력
첫째 줄에 말이 지날 수 있는 최대의 칸 수를 출력한다.

예제 입력 1 
2 4
CAAB
ADCB
예제 출력 1 
3
*/
#include <iostream>
#include <algorithm>
using namespace std;

int R, C, ans, visit[26], mvy[] = {0, 0, -1, 1}, mvx[] = {-1, 1, 0, 0};
char map[20][21];

bool isRange(int y, int x)
{
    return 0 <= y && y < R && 0 <= x && x < C;
}

void dfs(int y, int x, int count)
{
    if (!isRange(y, x))
        return;
    if (visit[map[y][x] - 'A'])
        return;

    visit[map[y][x] - 'A'] = count;
    ans = max(ans, count);

    for (int i = 0; i < 4; i++)
    {
        int nextY = y + mvy[i];
        int nextX = x + mvx[i];
        dfs(nextY, nextX, count + 1);
    }
    visit[map[y][x] - 'A'] = 0;
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

    dfs(0, 0, 1);
    cout << ans;

    return 0;
}