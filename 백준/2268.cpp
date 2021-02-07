/*
문제
N개의 수 A[1], A[2], …, A[N] 이 주어졌을 때, 함수 Sum(i, j)는 A[i]+A[i+1]+…+A[j]를 구하는 함수이다. 
(i>j일 경우에는 A[j]+A[j+1]+...+A[i]) A가 주어졌을 때, Sum(i, j)를 구하는 것은 매우 쉬운 문제이다. 
이러한 (i, j)가 여러 개 주어졌을 때도 별로 어려운 문제는 아니다.

Sum함수와 더불어 Modify라는 함수를 정의하자. Modify(i, k)를 수행하면 A[i]=k가 되는 함수이다. 
Sum함수와 Modify 함수의 사용 목록이 주어졌을 때, 이에 해당하는 연산을 하는 프로그램을 작성하시오. 
두 함수를 섞어서 사용할 수도 있다.

입력
첫째 줄에는 N(1≤N≤1,000,000), M(1≤M≤1,000,000)이 주어진다. 
M은 수행한 명령의 개수이며 다음 M개의 줄에는 수행한 순서대로 함수의 목록이 주어진다. 
첫 번째 숫자는 어느 함수를 사용했는지를 나타내며, 0일 경우에는 Sum 함수를, 1일 경우에는 Modify 함수를 나타낸다. 
다음 두 수는 각 함수의 인자 (i, j)나 (i, k)를 나타낸다. 처음에는 A[1]=A[2]=…A[N]=0이다. Modify인 경우에 1 ≤ k ≤ 100,000 이다.

출력
Sum 함수의 개수만큼 각 줄에 Sum 함수의 리턴값을 출력한다.

맥스 : 100,000,000,000
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 1000001

int N, M, A[MAX];
long long tree[4 * MAX];

long long sum(int start, int end, int left, int right, int node)
{
    if (right < start || end < left)
    {
        return 0;
    }

    else if (left <= start && end <= right)
    {
        return tree[node];
    }

    int mid = (start + end) / 2;
    return sum(start, mid, left, right, node * 2) + sum(mid + 1, end, left, right, node * 2 + 1);
}

void modify(int start, int end, int node, int index, int val)
{
    if (start > index || index > end)
    {
        return;
    }

    if (start == end)
    {
        A[index] = tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;
    modify(start, mid, node * 2, index, val);
    modify(mid + 1, end, node * 2 + 1, index, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (!a)
        {
            if (b > c)
            {
                swap(b, c);
            }
            cout << sum(1, N, b, c, 1) << "\n";
        }
        else
        {
            A[b] = c;
            modify(1, N, 1, b, c);
        }
    }

    return 0;
}