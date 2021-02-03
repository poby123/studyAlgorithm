# 기본 알고리즘 이론 & 코드 정리

## 목차

- [투 포인터](#투-포인터)
- [구간 합](#구간-합)
- [이분 그래프](#이분-그래프)
- [사이클 찾기](#사이클-찾기)

<hr/>

### 투 포인터

#### 1. 예시 문제

-   N개의 자연수로 구성된 수열이 있다.
-   합이 M인 부분 연속 수열의 개수를 O(N) 시간 내에 구해라.
[백준 1806](./백준/1806.cpp)

#### 2. 문제 해결 방법

-   리스트에 순차적으로 접근해야할 때 두 개의 점을 이용해, 위치를 기록하면서 처리한다.

1. 시작점(start)과, 끝점(end)이 첫번째 원소의 인덱스를 가리키도록 한다.
2. 현재 부분합이 M과 같다면, 카운트하고, end를 1 증가시킨다.
3. 현재 부분합이 M보다 작으면, end를 1 증가시킨다.
4. 현재 부분합이 M보다 크다면, start를 1 증가시킨다.
5. 모든 경우에 대해 2~4 과정을 반복한다.

#### 3. 예시 코드

```c++
#include <iostream>
using namespace std;

int arr[] = {1, 2, 3, 2, 5};
int N, S, sum, l, r, ans;

int main()
{
    // 데이터의 개수
    N = sizeof(arr) / sizeof(int);
    
    // 원하는 부분 연속 수열의 합
    S = 5;

    // * 초기 합 초기화 *
    sum = arr[0];
    
    while (l <= r && r < N)
    {
        // 합이 원하는 합보다 작다면, 오른쪽 포인터를 이동시킨 후 더한다.
        if (sum < S)
        {
            sum += arr[++r];
        }

        // 합이 원하는 합과 같다면, 카운트하고, 오른쪽 포인터를 이동시킨 후 더한다.
        else if (sum == S)
        {
            ++ans;
            sum += arr[++r];
        }

        // 합이 원하는 합보다 크다면, 왼쪽 포인터가 가리키는 값을 뺀 뒤 이동시킨다.
        else if (sum > S)
        {
            sum -= arr[l++];
        }
    }

    cout << ans;

    return 0;
}
```
<hr/>

### 구간 합

#### 1. 예시 문제
-   [백준 11659번](./백준/11659.cpp)
-   N개의 정수로 구성된 수열이 있다.
-   M개의 쿼리 정보가 주어진다.
    -   각 쿼리는 L과 R로 구성된다.
    -   [L, R] 구간에 해당하는 데이터들의 합을 모두 구하여라.
-   시간 제한 : O(N + M)

#### 2. 문제 해결방법

-   접두사 합 (Prefix Sum)

##### Prefix Sum을 이용한 해결방법

1. Prefix Sum을 계산해 배열 P에 저장한다.
2. M개의 쿼리 정보를 확인할 때, 구간 합은 P[R] - P[L-1] 이 된다.

-   ex) {    10, 20, 30, 40,   50 }
    P : { 0, 10, 30, 60, 100, 150 }

##### Prefix Sum 예제 코드
```c++
#include <iostream>

int main()
{
    int data[] = {10, 20, 30, 40, 50};
    int N = sizeof(data) / sizeof(int);
    int *prefix = new int[N + 1];
    prefix[0] = 0;

    for (int i = 1; i <= N; i++)
    {
        prefix[i] = prefix[i - 1] + data[i - 1];
    }

    // 구간 합 계산
    int left = 3, right = 4;
    std::cout << prefix[right] - prefix[left - 1];

    delete[] prefix;
    return 0;
}
```
<hr/>

### 세그먼트 트리
#### 세그먼트 트리란?
배열 A가 있을 때, A의 부분 합을 트리구조로 저장함으로써 O(logN) 이라는 빠른 속도로 부분합을 구할 수 있다.

#### 세그먼트 트리 만들기
세그먼트 트리를 사용하기 위해, 다음과 같은 규칙대로 배열을 이진 트리 구조로 만든다.
1. 부모노드의 값은 양 쪽 자식 노드의 합이다.
2. 배열의 요소들은 leaf 노드에 위치한다.

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2F2fQXV%2FbtqyDDzhnQD%2FkzrqxxCbj1AT1YYa1f8xx1%2Fimg.png" width="700">

<p>
트리는 1차원 배열을 통해 구현할 수 있으며, <strong>트리의 각 노드 별 배열의 인덱스</strong>는 아래 그림과 같다. 아래 그림과 같이, 세그먼트 트리에서 첫번째 인덱스는 0이 아닌 1을 사용한다.
</p>

<img src="https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FJyU75%2FbtqyGwrsP2Z%2FKfjafFJhL0x2JRosP4vrF0%2Fimg.png" width="700"> 

<p>
기존 배열의 크기를 N이라고 하면, 리프노드의 개수는 N이고, 따라서 트리의 높이(H)는 LogN, 배열의 크기는 2^(H+1) 이 된다. 따라서 세그먼트 트리 배열을 만들 때, 배열의 크기는,  <strong>2^k > N</strong>인 k중 가장 작은 값을 취하면 된다. <br/> 이렇게 계산하는 게 귀찮다면, 크기를 4 * N으로 잡으면 모든 범위를 커버할 수 있다.
</p>

#### 트리 만드는 예제 코드
```c++
// start : 시작 인덱스, end : 끝 인덱스
int init(int start, int end, int node){
    if(start == end) {
        return tree[node] = a[start];
    }
    int mid = (start + end) / 2;

    // 재귀적으로 왼쪽과 오른쪽 부분으로 나눈 뒤, 그 합을 자기 노드의 값으로 취한다.
    return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}
```
<br/>

#### 구간합 구하는 예제 코드
구간의 합은 <span style="color:red">범위 안에 있는 경우</span> 에 한해서만 더하면 된다. 그 밖의 경우는 고려하지 않는다.

```c++
// start: 시작 인덱스, end: 끝 인덱스
// left, right : 구간 합 범위
int sum(int start, int end, int left, int right, int node){
    // 범위 밖
    if(left > end || right < start){
        return 0;
    }

    // 범위 안
    if(left <= start && end <= right){
        return tree[node];
    }

    // left나 rigt 중 하나만 범위에 속하는 경우, 두 부분으로 나누어 합을 구한다.
    int mid = (start + end) / 2;
    return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}
```

<br/>

#### 특정 원소의 값을 수정하는 코드
해당 원소를 포함하고 있는 모든 구간 합 노드들을 갱신하면 된다. 수정할 노드도 <span style="color:red">범위안에 있는 경우</span> 에 한해서 수정하면 된다.

```c++
// start: 시작 인덱스, end: 끝 인덱스
// index: 구간 합을 수정하고자 하는 노드
// dif: 변경하고자 하는 값 - a[index]
void update(int start, int end, int node, int index, int dif) {
    // 범위 밖
    if(index < left || index > end){
        return;
    }

    // 범위 안
    tree[node] += dif;
    if(start == end){
        return;
    }
    int mid = (start + end) / 2;
    update(start, mide, node * 2, index, dif);
    update(mid + 1, end, node * 2 + 1, index, dif);
}
```

#### 참조
[코드 출처](https://blog.naver.com/ndb796/221282210534)

<hr/>

### 이분 그래프

##### 이분 그래프란?

<img src="https://gmlwjd9405.github.io/images/data-structure-graph/bipartite-graph1.gif"/>
<p>2가지 색깔이 있을 때 모든 정점에 대해, 인접한 정점을 서로 다른 색으로 칠할 수 있는 그래프를 말한다.</p>

##### 이분 그래프인지 확인하는 방법

-   BFS 또는 DFS 탐색을 하면서 노드을 방문한다.
-   노드를 방문할 때마다 두 가지 색 중, 한 가지 색으로 칠한다. 단, 현재 노드와 인접한 노드는 다른 색깔로 칠한다.
-   만약, 현재 노드와 인접한 노드가 같은 색이라면, 이분 그래프가 아니다.
-   노드 방문을 마치고, 모든 노드에 대해 인접한 노드의 색과 같은 경우가 없다면, 이분 그래프다.

<span>※ 비연결 그래프인 경우도 고려해야한다.</span>

=> [이분 그래프 확인하는 코드](./백준/1707.cpp)

<hr/>

### 사이클 찾기
#### 사이클이란?
<img src="https://blog.kakaocdn.net/dn/tVNdo/btqw7bDujcb/UWt6YsgLzjQHhDKldCoLT1/img.png"/>
<p>위와 같은 그래프가 있을 때 1 -> 2 -> 4 -> 3 -> 1 과 같이 순환이 발생하는 부분을 사이클이라고 한다.</p>

#### 1. 단방향 그래프에서 찾기
##### 예시 문제
- [백준 9466 텀프로젝트](./백준/9466.cpp)
##### 기본 아이디어
- 모든 정점에 대해 DFS를 해서 자기 자신이 나온다면, 사이클이 존재하는 것이다.

##### 알고리즘
1. 노드에 방문했다는 표시를 해준다. `visit[node] = true`
2. 현재 노드가 가리키고 있는 다음 노드에 대해
    - 방문하지 않았다면, 재귀적으로 DFS 탐색한다.
    - 방문했지만, 종료되지 않은 노드라면 사이클이 존재하는 것이다.
3. 노드가 종료됐다는 표시를 해준다. `finished[node] = true`

##### 예시코드
```c++
vector<vector<int>> adj;
vector<bool> visit, finished;
bool hasCycle;

void dfs(int node)
{
    visit[node] = 1;
    for (int i = 0; i < adj[node].size(); ++i) {
        int next = adj[node][i];

        // 방문하지 않은 경우 
        if (!visit[next]){
            dfs(next);
        }

        //  방문했지만, 종료되지 않은 경우
        else if (!finished[next]) {
            hasCycle = 1;
        }
    }
    finished[node] = 1;
}
```
#### 2. 무향 그래프에서 찾기
##### 기본 아이디어
- 부모가 같은 노드가 있다면 사이클이 발생한 것이다.

##### 예시 문제 & 코드
- [백준 1197 최소 스패닝 트리 - 크루스칼 부분](./백준/1197.cpp)