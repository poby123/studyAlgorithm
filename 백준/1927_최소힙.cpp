/*
문제
널리 잘 알려진 자료구조 중 최소 힙이 있다. 최소 힙을 이용하여 다음과 같은 연산을 지원하는 프로그램을 작성하시오.

배열에 자연수 x를 넣는다.
배열에서 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다.
프로그램은 처음에 비어있는 배열에서 시작하게 된다.

입력
첫째 줄에 연산의 개수 N(1 ≤ N ≤ 100,000)이 주어진다. 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, x가 0이라면 배열에서 가장 작은 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 입력되는 자연수는 231보다 작다.

출력
입력에서 0이 주어진 회수만큼 답을 출력한다. 만약 배열이 비어 있는 경우인데 가장 작은 값을 출력하라고 한 경우에는 0을 출력하면 된다.

예제 입력 1 
9
0
12345678
1
2
0
0
0
0
32

예제 출력 1 
0
1
2
12345678
0
*/

// 방법1. 직접 구현
//arr[k]의 왼쪽 자식: arr[2k+1], 오른쪽 자식 : arr[2k+2], 부모 : arr[(k-1)/2]
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int N; //연산의 개수
int *arr;
int length;

void heapify_down(int k)
{
    while (2 * k + 1 < length || 2 * k + 2 < length) //leaf 노드가 아닐 때까지만 반복한다.
    {
        //자식 노드중에서 최소값을 가진 인덱스를 찾는다.
        int minIndex = -1;
        if (arr[2 * k + 1] > arr[2 * k + 2])
        {
            minIndex = 2 * k + 2;
        }
        else
        {
            minIndex = 2 * k + 1;
        }

        //부모가 자식보다 크다면 바꾼다.
        if (arr[k] > arr[minIndex])
        {
            int temp = arr[k];
            arr[k] = arr[minIndex];
            arr[minIndex] = temp;

            k = minIndex; //자식노드쪽으로 이동해서 계속한다.
        }
        //부모가 자식보다 작으면 그만한다.
        else
        {
            break;
        }
    }
}

int delete_min()
{
    if (length == 0)
    {
        return 0;
    }
    int ret = arr[0];
    arr[0] = arr[length - 1];
    arr[length - 1] = INT_MAX; //heapify_down에서 위로 올라가지 않도록 최댓값을 넣어준다.
    --length;                  //삭제할 노드까지 계산하는 것을 막기 위해 heapify_down을 호출하기 전에 크기를 줄여야한다.
    heapify_down(0);           // heapify_down을 통해 최소힙 성질을 유지할 수 있도록 한다.
    return ret;
}

void heapify_up(int k)
{
    while (k > 0) //루트노드가 아니면 계속한다.
    {
        if (arr[(k - 1) / 2] > arr[k]) //부모가 자신보다 크면 바꾼다.
        {
            int temp = arr[(k - 1) / 2];
            arr[(k - 1) / 2] = arr[k];
            arr[k] = temp;
            k = (k - 1) / 2;
        }
        else //부모가 자신보다 작으면 (최소힙 성질을 만족하면) 그만한다.
        {
            return;
        }
    }
}

void insert(int val)
{
    arr[length] = val;  //맨 끝에 값을 추가한다.
    heapify_up(length); //추가한 값을 힙성질을 만족하는 위치로 올린다.
    ++length;
}

int main()
{
    scanf("%d", &N);
    arr = new int[N];

    for (int i = 0; i < N; ++i)
    {
        int input;
        scanf("%d", &input);
        if (input == 0)
        {
            printf("%d\n", delete_min());
        }
        else
        {
            insert(input);
        }
    }
    delete[] arr;
    arr = nullptr;
    return 0;
}

//방법2 STL 활용
/*
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int> heap; //순서는 있고, 중복 여부는 따지지 않는 STL, 기본은 오름차순 정렬.
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int input;
        scanf("%d", &input);

        if (input == 0)
        {
            if (heap.size() > 0)
            {
                printf("%d\n", -heap.top());
                heap.pop();
            }
            else
            {
                printf("0\n");
            }
        }
        else
        {
            heap.push(-input);
        }
    }
    return 0;
}
*/