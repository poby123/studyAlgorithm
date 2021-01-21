/*
문제
스도쿠는 18세기 스위스 수학자가 만든 '라틴 사각형'이랑 퍼즐에서 유래한 것으로 현재 많은 인기를 누리고 있다. 
이 게임은 아래 그림과 같이 가로, 세로 각각 9개씩 총 81개의 작은 칸으로 이루어진 정사각형 판 위에서 이뤄지는데, 게임 시작 전 일부 칸에는 1부터 9까지의 숫자 중 하나가 쓰여 있다.

나머지 빈 칸을 채우는 방식은 다음과 같다.

각각의 가로줄과 세로줄에는 1부터 9까지의 숫자가 한 번씩만 나타나야 한다.
굵은 선으로 구분되어 있는 3x3 정사각형 안에도 1부터 9까지의 숫자가 한 번씩만 나타나야 한다.
위의 예의 경우, 첫째 줄에는 1을 제외한 나머지 2부터 9까지의 숫자들이 이미 나타나 있으므로 첫째 줄 빈칸에는 1이 들어가야 한다.

또한 위쪽 가운데 위치한 3x3 정사각형의 경우에는 3을 제외한 나머지 숫자들이 이미 쓰여있으므로 가운데 빈 칸에는 3이 들어가야 한다.

이와 같이 빈 칸을 차례로 채워 가면 다음과 같은 최종 결과를 얻을 수 있다.


게임 시작 전 스도쿠 판에 쓰여 있는 숫자들의 정보가 주어질 때 모든 빈 칸이 채워진 최종 모습을 출력하는 프로그램을 작성하시오.

입력
아홉 줄에 걸쳐 한 줄에 9개씩 게임 시작 전 스도쿠판 각 줄에 쓰여 있는 숫자가 한 칸씩 띄워서 차례로 주어진다. 스도쿠 판의 빈 칸의 경우에는 0이 주어진다. 스도쿠 판을 규칙대로 채울 수 없는 경우의 입력은 주어지지 않는다.

출력
모든 빈 칸이 채워진 스도쿠 판의 최종 모습을 아홉 줄에 걸쳐 한 줄에 9개씩 한 칸씩 띄워서 출력한다.

스도쿠 판을 채우는 방법이 여럿인 경우는 그 중 하나만을 출력한다.

제한
baekjoon의 백트래킹 알고리즘으로 풀 수 있는 입력만 주어진다. 다음은 그 알고리즘의 수행 시간이다.
C++14: 80ms
Java: 292ms
PyPy3: 1172ms
*/
/*
    정리: 
    1. 한 칸에 들어갈 수 있는 숫자를 정하지 않고, 그냥 1부터 9까지 넣어보면 시간초과가 난다.
    따라서 한 칸에 들어갈 수 있는 숫자를 정해서 재귀적으로 푼다.
    2. 1부터 9까지의 합은 45이므로 메모제이션을 통해 확인한다.
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int map[10][10], empty_size;

bool check()
{
    // check row and column
    for (int i = 0; i < 9; i++)
    {
        if (map[i][9] != 45 || map[9][i] != 45)
        {
            return false;
        }
    }

    // check square
    for (int i = 0; i <= 6; i += 3)
    {
        for (int j = 0; j <= 6; j += 3)
        {
            int sum = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sum += map[i + k][j + l];
                }
            }
            if (sum != 45)
            {
                return false;
            }
        }
    }
    return true;
}

void getCandidate(vector<int> &candidate, int y, int x)
{
    int visit[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 9; i++)
    {
        if (map[y][i])
        {
            visit[map[y][i] - 1] = 1;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (map[i][x])
        {
            visit[map[i][x] - 1] = 1;
        }
    }

    int startY = y / 3 * 3;
    int startX = x / 3 * 3;

    for (int i = startY; i < startY + 3; i++)
    {
        for (int j = startX; j < startX + 3; j++)
        {
            if (map[i][j])
            {
                visit[map[i][j] - 1] = 1;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (!visit[i])
        {
            candidate.push_back(i + 1);
        }
    }
}

bool solve(vector<pair<int, int>> &s, int idx)
{
    if (idx == empty_size)
    {
        return check();
    }
    int y = s[idx].first;
    int x = s[idx].second;

    vector<int> candidate;
    candidate.reserve(9);
    getCandidate(candidate, y, x);

    for (auto v : candidate)
    {
        map[y][x] = v;
        map[y][9] += v;
        map[9][x] += v;

        bool result = solve(s, idx + 1);
        if (result)
        {
            return true;
        }

        map[y][x] = 0;
        map[y][9] -= v;
        map[9][x] -= v;
    }

    return false;
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<pair<int, int>> s;
    s.reserve(81);

    // input
    for (int i = 0; i < 9; i++)
    {
        int sum = 0;
        for (int j = 0; j < 9; j++)
        {
            cin >> map[i][j];
            sum += map[i][j];

            if (!map[i][j])
            {
                s.push_back({i, j});
            }
        }
        map[i][9] = sum;
    }

    // check sum
    for (int j = 0; j < 9; j++)
    {
        int sum = 0;
        for (int i = 0; i < 9; i++)
        {
            sum += map[i][j];
        }
        map[9][j] = sum;
    }

    empty_size = s.size();
    solve(s, 0);

    // output
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}