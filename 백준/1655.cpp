/*
문제
수빈이는 동생에게 "가운데를 말해요" 게임을 가르쳐주고 있다. 
수빈이가 정수를 하나씩 외칠때마다 동생은 지금까지 수빈이가 말한 수 중에서 중간값을 말해야 한다. 
만약, 그동안 수빈이가 외친 수의 개수가 짝수개라면 중간에 있는 두 수 중에서 작은 수를 말해야 한다.

예를 들어 수빈이가 동생에게 1, 5, 2, 10, -99, 7, 5를 순서대로 외쳤다고 하면, 동생은 1, 1, 2, 2, 2, 2, 5를 차례대로 말해야 한다. 
수빈이가 외치는 수가 주어졌을 때, 동생이 말해야 하는 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에는 수빈이가 외치는 정수의 개수 N이 주어진다. N은 1보다 크거나 같고, 100,000보다 작거나 같은 자연수이다. 
그 다음 N줄에 걸쳐서 수빈이가 외치는 정수가 차례대로 주어진다. 정수는 -10,000보다 크거나 같고, 10,000보다 작거나 같다.

출력
한 줄에 하나씩 N줄에 걸쳐 수빈이의 동생이 말해야하는 수를 순서대로 출력한다.
*/

/*
    시간제한이 0.1초이기 때문에 수를 하나 외칠 때마다 O(logN) 시간 정도로 중간값을 구할 수 있어야한다.
    이를 위해 최소힙과 최대힙을 이용한다. 힙 구조는 삽입시간은 O(logN), top에 접근하는 시간은 O(1)이기 때문이다.

    최대힙은 가장 큰 수가 top에 오는 힙구조이고, 최소힙은 가장 작은 수가 top에 오는 구조이다.
    이를 이용해서, 최대힙 < 최소힙의 구조를 가지도록 하면, 최대힙의 top 또는 최소힙의 top을 가지고 중간값을 구할 수 있게 된다. 이것이 이 문제를 푸는 핵심 아이디어이다.
    단, 최대힙이나 최소힙 둘 중 하나에 값이 몰리면 중간값을 가지지 않으므로, 두 힙의 크기 차이가 1이하가 되도록 한다.
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

priority_queue<int, vector<int>, greater<>> gpq; // 최소힙
priority_queue<int, vector<int>, less<>> lpq;    // 최대힙
int N, mid, x;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> x;

        // push
        if (mid < x)
        {
            gpq.push(x);
        }
        else
        {
            lpq.push(x);
        }

        // balance
        if (lpq.size() > gpq.size() + 1)
        {
            gpq.push(lpq.top());
            lpq.pop();
        }
        else if (gpq.size() > lpq.size() + 1)
        {
            lpq.push(gpq.top());
            gpq.pop();
        }

        // odd
        if (i % 2)
        {
            mid = gpq.size() > lpq.size() ? gpq.top() : lpq.top();
        }

        // even
        else
        {
            mid = min(gpq.top(), lpq.top());
        }

        cout << mid << "\n";
    }

    return 0;
}