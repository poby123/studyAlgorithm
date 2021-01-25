/*
문제
한수는 지금 (x, y)에 있다. 직사각형의 왼쪽 아래 꼭짓점은 (0, 0)에 있고, 오른쪽 위 꼭짓점은 (w, h)에 있다. 직사각형의 경계선까지 가는 거리의 최솟값을 구하는 프로그램을 작성하시오.

입력
첫째 줄에 x, y, w, h가 주어진다.

출력
첫째 줄에 문제의 정답을 출력한다.

제한
1 ≤ w, h ≤ 1,000
1 ≤ x ≤ w-1
1 ≤ y ≤ h-1
x, y, w, h는 정수
예제 입력 1 
6 2 10 3
예제 출력 1 
1
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int x, y, w, h, ans = INT_MAX;

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> x >> y >> w >> h;

    ans = min(ans, x);
    ans = min(ans, y);
    ans = min(ans, w - x);
    ans = min(ans, h - y);

    cout << ans;

    return 0;
}