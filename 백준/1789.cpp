/*
문제
서로 다른 N개의 자연수의 합이 S라고 한다. S를 알 때, 자연수 N의 최댓값은 얼마일까?

입력
첫째 줄에 자연수 S(1 ≤ S ≤ 4,294,967,295)가 주어진다.

출력
첫째 줄에 자연수 N의 최댓값을 출력한다.

예제 입력 1 
200
예제 출력 1 
19
*/

/*
    1부터 차례대로 더해야, N이 최대가 될 것이므로 1부터 숫자를 키워가면서 더한다.
    마지막 N+1 번째를 더한 값이 S 보다 큰 경우, N번째 숫자를 바꾸면 되므로 그냥 탈출한다.
    예를 들어, 
        S = 20 이라고 하자.
        1+2+...+18+19 = 190, 
        만약 여기에 20을 더하면 210으로 S를 초과하게 되므로, 초과한 경우 20번째는 무시하고 탈출한다.
        따라서 마지막으로 19번째 더한 19를 29로 바꾸고 그러면 합이 S가 되므로, 답은 19 이다.
*/

#include <iostream>
using namespace std;

long long ans, S, sum, cur = 1LL;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> S;
    while (1)
    {
        sum += cur;

        if (sum > S)
        {
            break;
        }
        ++ans;
        ++cur;
    }

    cout << ans;

    return 0;
}