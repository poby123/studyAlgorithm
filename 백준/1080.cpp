/*
문제
0과 1로만 이루어진 행렬 A와 행렬 B가 있다. 이때, 행렬 A를 행렬 B로 바꾸는데 필요한 연산의 횟수의 최솟값을 구하는 프로그램을 작성하시오.

행렬을 변환하는 연산은 어떤 3*3크기의 부분 행렬에 있는 모든 원소를 뒤집는 것이다. (0 -> 1, 1 -> 0)

입력
첫째 줄에 행렬의 크기 N M이 주어진다. N과 M은 50보다 작거나 같은 자연수이다. 둘째 줄부터 N개의 줄에는 행렬 A가 주어지고, 그 다음줄부터 N개의 줄에는 행렬 B가 주어진다.

출력
첫째 줄에 문제의 정답을 출력한다. 만약 A를 B로 바꿀 수 없다면 -1을 출력한다.

예제 입력 1 
3 4
0000
0010
0000
1001
1011
1001

예제 출력 1 
2
*/

#include <iostream>
using namespace std;

char a[50][50], b[50][50];
int n, m, answer;

bool checkDone()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (a[i][j] != b[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    /* input */
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
    }

    /* solve */
    /* 행이나 열이 3보다 작으면 뒤집을 수 없으므로 이에 대한 처리가 필요하다. */
    if (n >= 3 && m >= 3)
    {
        for (int i = 0; i <= n - 3; ++i)
        {
            for (int j = 0; j <= m - 3; ++j)
            {
                /* 시작 지점이 다른 경우에만 뒤집으면 된다. */
                if (a[i][j] != b[i][j])
                {
                    ++answer;
                    for (int k = 0; k < 3; ++k)
                    {
                        for (int l = 0; l < 3; ++l)
                        {
                            b[i + k][j + l] = !(b[i + k][j + l] - '0') + '0';
                        }
                    }
                }
            }
        }
    }

    /* 행이나 열이 3보다 작은 경우에 대한 처리이다. */
    else
    {
        /* 비교 후, 다르면 출력 후 종료 */
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (a[i][j] != b[i][j])
                {
                    cout << -1 << "\n";
                    return 0;
                }
            }
        }
    }

    if (!checkDone())
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << answer << "\n";
    }

    return 0;
}