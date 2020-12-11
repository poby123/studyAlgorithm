/*
문제
땅 위에 달팽이가 있다. 이 달팽이는 높이가 V미터인 나무 막대를 올라갈 것이다.

달팽이는 낮에 A미터 올라갈 수 있다. 하지만, 밤에 잠을 자는 동안 B미터 미끄러진다. 또, 정상에 올라간 후에는 미끄러지지 않는다.

달팽이가 나무 막대를 모두 올라가려면, 며칠이 걸리는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 세 정수 A, B, V가 공백으로 구분되어서 주어진다. (1 ≤ B < A ≤ V ≤ 1,000,000,000)

출력
첫째 줄에 달팽이가 나무 막대를 모두 올라가는데 며칠이 걸리는지 출력한다.

예제 입력 1 
2 1 5
예제 출력 1 
4

예제 입력 2 
5 1 6
예제 출력 2 
2

예제 입력 3 
100 99 1000000000
예제 출력 3 
999999901
*/
/*
    접근:
    1.
    하루에 올라가는 높이 = A - B
    v <= cost * (하루에 올라가는 높이)
    cost >= v / (하루에 올라가는 높이)
    
    결과 => 오답. 주의의 2번 항목 때문에 이렇게 풀면 안된다. 

    2.
    소요되는 일: cost
    v <= cost * A - ((cost-1) * B);
    v <= cost * A - cost * B + B;
    v - B <= cost(A - B);
    (v - B) / (A - B) <= cost

    주의:
    1. A == B 인 경우?
    A > B 이므로 생기지 않는다.

    2.정상에 올라간 후에는 미끄러지지 않는다.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a, b, v, answer;
    cin >> a >> b >> v;

    answer = (int)ceil((v - b) / (double)(a - b)); //int형끼리의 계산에서 소수점은 버려지므로, 이런식으로 올림 처리를 해줘야 한다.

    cout << answer << "\n";

    return 0;
}