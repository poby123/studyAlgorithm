/*
문제
수열 A가 주어졌을 때, 가장 긴 증가하는 부분 수열을 구하는 프로그램을 작성하시오.

예를 들어, 수열 A = {10, 20, 10, 30, 20, 50} 인 경우에 가장 긴 증가하는 부분 수열은 A = {10, 20, 10, 30, 20, 50} 이고, 길이는 4이다.

입력
첫째 줄에 수열 A의 크기 N (1 ≤ N ≤ 1,000)이 주어진다.

둘째 줄에는 수열 A를 이루고 있는 Ai가 주어진다. (1 ≤ Ai ≤ 1,000)

출력
첫째 줄에 수열 A의 가장 긴 증가하는 부분 수열의 길이를 출력한다.

둘째 줄에는 가장 긴 증가하는 부분 수열을 출력한다. 그러한 수열이 여러가지인 경우 아무거나 출력한다.

예제 입력 1 
6
10 20 10 30 20 50
예제 출력 1 
4
10 20 30 50
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1001

// 헤맨 부분 : 프로그램에 모든 인덱스를 1부터 시작하는 상태에서 ans 를 0으로 초기화하면 길이가 1일 때 부분수열이 출력되지 않는다.
int N, A[MAX], dp[MAX], before[MAX], ans = 1;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 입력
    cin >> N;
    fill_n(dp, N + 1, 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }

    // A 순회
    for (int i = 1; i <= N; i++)
    {
        int cur = A[i];
        int targetJ = 0;
        int targetDP = 0;

        // A[i]보다는 작으면서, DP[j]는 최대인 값을 찾는다.
        for (int j = 1; j < i; j++)
        {
            if (A[j] < cur && dp[j] > targetDP)
            {
                targetDP = dp[j];
                targetJ = j;
            }
        }

        // 나중에 부분수열을 출력하기 위해 dp[i]가 영향을 받은 이전 인덱스 j를 기억한다.
        before[i] = targetJ;
        
        // dp[i]는 이전 최대 길이 + 1
        dp[i] = targetDP + 1;

        // ans 업데이트
        if (dp[i] > dp[ans])
        {
            ans = i;
        }
    }

    // 답
    vector<int> v;
    int len = dp[ans];
    int cur = ans;

    cout << len << "\n";
    v.reserve(len);

    // ans 인덱스로부터, before 배열을 이용해서 거슬러 올라간다.
    // 초기 before은 모두 0으로 초기화되어있으므로, before[부분 수열의 시작 인덱스]는 0일 것이다. 
    // 따라서 0이 아닐 때까지 반복한다.
    while (cur)
    {
        v.push_back(A[cur]);
        cur = before[cur];
    }

    // 거꾸로 출력한다.
    for (int i = v.size() - 1; i >= 0; --i)
    {
        cout << v[i] << " ";
    }
    
    return 0;
}