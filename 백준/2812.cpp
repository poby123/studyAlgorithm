/*
문제
N자리 숫자가 주어졌을 때, 여기서 숫자 K개를 지워서 얻을 수 있는 가장 큰 수를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ K < N ≤ 500,000)

둘째 줄에 N자리 숫자가 주어진다. 이 수는 0으로 시작하지 않는다.

출력
입력으로 주어진 숫자에서 K개를 지웠을 때 얻을 수 있는 가장 큰 수를 출력한다.
*/

/*
	알고리즘
	1. 문자열의 처음부터 순회하면서, 덱에 넣는다.
	2. 덱에 있는 마지막 숫자가 현재 보고 있는 숫자보다 작다면, 그리고 K가 0이 아니라면, 덱에 있는 마지막 숫자가 현재 숫자보다 크거나 같을 때까지 덱에 있는 숫자를 뺀다.
	3. 덱에 현재 숫자를 넣는다.
	4. K가 반드시 0까지 감소하지는 않으므로 dq.size()-K 만큼 출력한다.

	이렇게 하면 덱에 있는 수들은 반드시 내림차순으로 저장된다.
*/

#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int N, K;
deque<char> dq;
string num;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K >> num;

	for(int i=0;i<num.size();i++){
		while(K && !dq.empty() && dq.back() < num[i]){
			dq.pop_back();
			--K;
		}
		dq.push_back(num[i]);
	}

	for(int i=0;i<dq.size()-K;i++){
		cout << dq[i];
	}

	return 0;
}