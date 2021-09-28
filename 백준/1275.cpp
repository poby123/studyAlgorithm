/*
문제
모두 알다시피 동호는 커피숍의 마담이다. (마담이 무엇인지는 본인에게 물어보도록 하자.)

어느 날 커피숍의 손님 A씨가 동호에게 게임을 하자고 했다.

그 게임은 다음과 같은 규칙을 갖는다.

N개의 정수가 있으면, 동호는 다음과 같이 말한다. “3~7번째 수의 합은 무엇이죠?” 그러면 상대방은 “그 답은 000입니다. 그리고 8번째 수를 2로 고치도록 하죠” 그러면 동호는 “네 알겠습니다.”라고 한 뒤에 다시 상대방이 동호가 했던 것처럼 “8~9번째 수의 합은 무엇이죠?”라고 묻게된다. 이 것을 번갈아 가면서 반복하는 게임이다.

당신은 이 게임의 심판 역을 맡았다. 요컨대, 질문에 대한 답들을 미리 알아야 한다는 것이다.

당신의 머리가 출중하다면 10만개 가량 되는 정수와 10만턴 정도 되는 게임을 기억할 수 있을 것이다. 몇판 이 게임을 즐기던 동호는 많은 사람들이 이 게임을 하기를 바라게 되었고, 당신에게 심판 프로그램을 구현해달라고 요청했다.

입력
첫째 줄에 수의 개수 N과 턴의 개수 Q가 주어진다.(1 ≤ N, Q ≤ 100,000) 둘째 줄에는 처음 배열에 들어가 있는 정수 N개가 주어진다. 세 번째 줄에서 Q+2번째 줄까지는 x y a b의 형식으로 x~y까지의 합을 구하여라, a번째 수를 b로 바꾸어라 라는 뜻의 데이터가 주어진다.

입력되는 모든 수는 -231보다 크거나 같고, 231-1보다 작거나 같은 정수이다.

출력
한 턴마다 구한 합을 한 줄마다 한 개씩 출력한다.

예제 입력 1 
5 2
1 2 3 4 5
2 3 3 1
3 5 4 1
예제 출력 1 
5
10

노트
x~y는 당연히 x번째 부터 y번째가 맞다. 하지만, 이 문제에서는 x > y인 경우 y번째 부터 x번째이다.
*/

#include<iostream>
using namespace std;

#define MAX 100001

int N, Q, arr[MAX];
long long tree[4 * MAX];

// 세그먼트 트리 초기화
long long init(int start, int end, int node){
  if(start == end){
    return tree[node] = arr[start];
  }

  int mid = (start + end) / 2;
  return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}


// 구간합 구하기
// start, end : 노드가 담당하는 범위
// left, right : 구해야하는 구간합의 범위
long long sum(int start, int end, int left, int right, int node){
  // left...right...start...end
  // start...end...left...right
  if(right < start || end < left){
    return 0;
  }

  // left...start...end...right
  if(left <= start && end <= right){
    return tree[node];
  }

  // others
  int mid = (start + end) / 2;
  return sum(start, mid, left, right, node*2) + sum(mid+1, end, left, right, node*2+1);
}


// 업데이트 하기
// start, end : 노드가 담당하는 범위
// node : 세그먼트 트리 노드
// index : 수정할 배열 번호
// value : 새로운 값
void update(int start, int end, int node, int index, int value){
  if(index < start || end < index){
    return;
  }

  if(start == end){
    arr[index] = tree[node] = value;
    return;
  }

  int mid = (start + end) / 2;
  update(start, mid, node * 2, index, value);
  update(mid + 1, end, node * 2 + 1, index, value);

  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}


int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> Q;
  for(int i=1;i<=N;i++){
    cin >> arr[i];
  }

  init(1, N, 1);

  for(int i=0;i<Q;i++){
    int a, b, x, y;
    cin >> x >> y >> a >> b;
  
    if(x > y){
      int temp = y;
      y = x;
      x = temp;
    }

    cout << sum(1, N, x, y, 1) << "\n";
    update(1, N, 1, a, b);
  }

  return 0;
}