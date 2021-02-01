/*
문제
N으로 나누었을 때 나머지와 몫이 같은 모든 자연수의 합을 구하는 프로그램을 작성하시오. 
예를 들어 N=3일 때, 나머지와 몫이 모두 같은 자연수는 4와 8 두 개가 있으므로, 그 합은 12이다.

입력
첫째 줄에 2,000,000 이하의 자연수 N이 주어진다.

출력
첫 줄에 구하고자 하는 수를 출력한다.
*/

/*
    N은 2,000,000 이하지만, 답이 될 수 있는 수는 int의 범위를 넘어갈 수 있으므로 오버플로우에 주의한다.
    ans += N * i + i; 에서 N과 i가 모두 int 라면 우변의 식이 int의 범위를 넘어가서 오버플로우 날 수 있으므로 형변환하거나 더 큰 자료형을 사용한다.
*/

#include <iostream>
using namespace std;

long long N, ans;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (long long i = 1; i < N; i++)
    {
        ans += N * i + i;
    }

    cout << ans;

    return 0;
}