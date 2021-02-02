/*
문제
N×N개의 수가 N×N 크기의 표에 채워져 있다. (x1, y1)부터 (x2, y2)까지 합을 구하는 프로그램을 작성하시오. (x, y)는 x행 y열을 의미한다.

예를 들어, N = 4이고, 표가 아래와 같이 채워져 있는 경우를 살펴보자.

1	2	3	4
2	3	4	5
3	4	5	6
4	5	6	7
여기서 (2, 2)부터 (3, 4)까지 합을 구하면 3+4+5+4+5+6 = 27이고, (4, 4)부터 (4, 4)까지 합을 구하면 7이다.

표에 채워져 있는 수와 합을 구하는 연산이 주어졌을 때, 이를 처리하는 프로그램을 작성하시오.

입력
첫째 줄에 표의 크기 N과 합을 구해야 하는 횟수 M이 주어진다. (1 ≤ N ≤ 1024, 1 ≤ M ≤ 100,000) 둘째 줄부터 N개의 줄에는 표에 채워져 있는 수가 1행부터 차례대로 주어진다. 
다음 M개의 줄에는 네 개의 정수 x1, y1, x2, y2 가 주어지며, (x1, y1)부터 (x2, y2)의 합을 구해 출력해야 한다. 
표에 채워져 있는 수는 1,000보다 작거나 같은 자연수이다. (x1 ≤ x2, y1 ≤ y2)
*/

/*
1	2	3	4
2	3	4	5
3	4	5	6
4	5	6	7

누적합 점화식
=> dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + num; 
=> dp[i-1][j-1] 을 빼는 이유는 dp[i-1][j]와 dp[i][j-1]에 한 번씩 들어가서 총 두 번 들어가므로 한 번을 빼줘야한다.

범위 구하는 점화식
참고 블로그 : https://jaimemin.tistory.com/1144
참고 이미지 : https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile24.uf.tistory.com%2Fimage%2F995C4F475C5C44C1142FDA

*/

#include <iostream>
using namespace std;
#define MAX 1025

int dp[MAX][MAX];
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            int num;
            cin >> num;
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + num;
        }
    }
    for (int i = 0; i < M; i++)
    {
        int y, x, y2, x2;
        cin >> y >> x >> y2 >> x2;
        cout << dp[y2][x2] - dp[y - 1][x2] - dp[y2][x - 1] + dp[y - 1][x - 1] << "\n";
    }
    return 0;
}
