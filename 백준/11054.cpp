/*
문제
수열 S가 어떤 수 Sk를 기준으로 S1 < S2 < ... Sk-1 < Sk > Sk+1 > ... SN-1 > SN을 만족한다면, 그 수열을 바이토닉 수열이라고 한다.

예를 들어, {10, 20, 30, 25, 20}과 {10, 20, 30, 40}, {50, 40, 25, 10} 은 바이토닉 수열이지만,  
{1, 2, 3, 2, 1, 2, 3, 2, 1}과 {10, 20, 30, 40, 20, 30} 은 바이토닉 수열이 아니다.

수열 A가 주어졌을 때, 그 수열의 부분 수열 중 바이토닉 수열이면서 가장 긴 수열의 길이를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 수열 A의 크기 N이 주어지고, 둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. (1 ≤ N ≤ 1,000, 1 ≤ Ai ≤ 1,000)

출력
첫째 줄에 수열 A의 부분 수열 중에서 가장 긴 바이토닉 수열의 길이를 출력한다.

예제 입력 1 
10
1 5 2 1 4 3 4 5 2 1
예제 출력 1 
7
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1001

int A[MAX], DPI[MAX], DPD[MAX], N, ans;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill_n(DPI, MAX, 1);
    fill_n(DPD, MAX, 1);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }

    // DP
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j < i; j++)
        {
            // ->
            if (A[j] < A[i])
            {
                DPI[i] = max(DPI[i], DPI[j] + 1);
            }

            // <-
            if (A[N - j + 1] < A[N - i + 1])
            {
                DPD[N - i + 1] = max(DPD[N - i + 1], DPD[N - j + 1] + 1);
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        ans = max(ans, DPI[i] + DPD[i]);
    }

    cout << ans - 1;

    return 0;
}