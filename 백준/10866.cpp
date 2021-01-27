/*
문제
정수를 저장하는 덱(Deque)를 구현한 다음, 입력으로 주어지는 명령을 처리하는 프로그램을 작성하시오.

명령은 총 여덟 가지이다.

push_front X: 정수 X를 덱의 앞에 넣는다.
push_back X: 정수 X를 덱의 뒤에 넣는다.
pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 덱에 들어있는 정수의 개수를 출력한다.
empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.

입력
첫째 줄에 주어지는 명령의 수 N (1 ≤ N ≤ 10,000)이 주어진다. 
둘째 줄부터 N개의 줄에는 명령이 하나씩 주어진다. 
주어지는 정수는 1보다 크거나 같고, 100,000보다 작거나 같다. 문제에 나와있지 않은 명령이 주어지는 경우는 없다.

출력
출력해야하는 명령이 주어질 때마다, 한 줄에 하나씩 출력한다.
*/

#include <iostream>
using namespace std;

class Deque
{
private:
    int dqSize, dqFront, dqRear, arr[20100];

public:
    Deque() : dqSize(0), dqFront(10050), dqRear(10051) {}

    void push_front(const int &x)
    {
        ++dqSize;
        arr[dqFront--] = x;
    }

    void push_back(const int &x)
    {
        ++dqSize;
        arr[dqRear++] = x;
    }

    int pop_front()
    {
        if (empty())
        {
            return -1;
        }
        --dqSize;
        return arr[++dqFront];
    }

    int pop_back()
    {
        if (empty())
        {
            return -1;
        }
        --dqSize;
        return arr[--dqRear];
    }

    int size()
    {
        return dqSize;
    }

    int empty()
    {
        return dqSize == 0;
    }

    int front()
    {
        if (empty())
        {
            return -1;
        }
        return arr[dqFront + 1];
    }

    int back()
    {
        if (empty())
        {
            return -1;
        }
        return arr[dqRear - 1];
    }
};

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    Deque dq;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        string cmd;
        int x;

        cin >> cmd;

        if (cmd == "push_front")
        {
            cin >> x;
            dq.push_front(x);
        }
        else if (cmd == "push_back")
        {
            cin >> x;
            dq.push_back(x);
        }
        else if (cmd == "pop_front")
        {
            cout << dq.pop_front() << "\n";
        }
        else if (cmd == "pop_back")
        {
            cout << dq.pop_back() << "\n";
        }
        else if (cmd == "size")
        {
            cout << dq.size() << "\n";
        }
        else if (cmd == "empty")
        {
            cout << dq.empty() << "\n";
        }
        else if (cmd == "front")
        {
            cout << dq.front() << "\n";
        }
        else if (cmd == "back")
        {
            cout << dq.back() << "\n";
        }
    }

    return 0;
}