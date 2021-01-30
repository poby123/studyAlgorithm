/*
문제
정렬되어있는 두 배열 A와 B가 주어진다. 두 배열을 합친 다음 정렬해서 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 배열 A의 크기 N, 배열 B의 크기 M이 주어진다. (1 ≤ N, M ≤ 1,000,000)

둘째 줄에는 배열 A의 내용이, 셋째 줄에는 배열 B의 내용이 주어진다. 배열에 들어있는 수는 절댓값이 109보다 작거나 같은 정수이다.

출력
첫째 줄에 두 배열을 합친 후 정렬한 결과를 출력한다.
*/

#include <iostream>
#define MAX 1000000
using namespace std;

int A[MAX], B[MAX], N, M;

void merge()
{
    int a = 0, b = 0;

    while (a < N && b < M)
    {
        if (A[a] < B[b])
        {
            cout << A[a++] << " ";
        }
        else
        {
            cout << B[b++] << " ";
        }
    }
    while (a < N)
    {
        cout << A[a++] << " ";
    }
    while (b < M)
    {
        cout << B[b++] << " ";
    }
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }

    merge();

    return 0;
}
