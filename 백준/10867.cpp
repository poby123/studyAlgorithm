/*
문제
N개의 정수가 주어진다. 이때, N개의 정수를 오름차순으로 정렬하는 프로그램을 작성하시오. 같은 정수는 한 번만 출력한다.

입력
첫째 줄에 수의 개수 N (1 ≤ N ≤ 100,000)이 주어진다. 둘째에는 숫자가 주어진다. 이 수는 절댓값이 1,000보다 작거나 같은 정수이다.

출력
첫째 줄에 수를 오름차순으로 정렬한 결과를 출력한다. 이때, 같은 수는 한 번만 출력한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<int> v;
    cin >> N;
    v.reserve(N);

    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end(), less<>());

    // unique는 중복되는 원소들을 모두 뒤쪽으로 보내고, 뒤로 보낸 원소중 첫번째 원소의 포인터를 반환한다.
    // 여기서 v.erase(start, end) 를 하게 되면, 중복되는 원소의 시작지점부터 끝까지 삭제하므로 중복되는 원소가 사리지게 된다.
    v.erase(unique(v.begin(), v.end()), v.end());

    for(auto i : v){
        cout << i << " ";
    }

    return 0;
}