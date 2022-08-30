// https://www.acmicpc.net/problem/1654
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int N, K, x, sum;
vector<int> arr;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> K >> N;
  for (int i = 0; i < K; i++) {
    cin >> x;
    arr.push_back(x);
  }

  // left를 0으로 초기화하면 길이값으로 모두다 1이 들어오는 경우, 27번째 줄에서
  // 0으로 나누는 오류 divisionByZero 오류가 발생한다. 편의상 1로 초기화하고,
  // 출력을 right를 하는 방식으로 하면 된다.
  ll left = 1;
  ll right = *max_element(arr.begin(), arr.end());
  while (left < right) {

    // left와 right의 범위가 int 최대값까지인데, 여기서 오버플로우가
    // 나기 때문에 자료형을 모두 long long 으로 해줘야 문제가 없다.
    ll mid = (left + right) / 2;

    int n = 0;
    for (int i : arr) {
      n += (i / mid);
    }

    if (n >= N) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  cout << right << "\n";

  return 0;
}