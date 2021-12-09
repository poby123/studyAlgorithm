/*
문제
    +---+        
    | D |        
+---+---+---+---+
| E | A | B | F |
+---+---+---+---+
    | C |        
    +---+        
	
1개 -> min(a,b,c,d,e,f)
2개 -> min(
		a+d, a+c, a+e, a+b, 
		d+e, d+b, d+f,
		e+c, e+f,
		c+b, c+f,
		b+f,
	)
3개 -> min(
		a+e+d, a+b+d, a+e+c, a+b+c,
		f+e+d, f+b+d, f+e+c, f+b+c
	)

주사위는 위와 같이 생겼다. 주사위의 여섯 면에는 수가 쓰여 있다. 위의 전개도를 수가 밖으로 나오게 접는다.

A, B, C, D, E, F에 쓰여 있는 수가 주어진다.

지민이는 현재 동일한 주사위를 N3개 가지고 있다. 이 주사위를 적절히 회전시키고 쌓아서, 
N×N×N크기의 정육면체를 만들려고 한다. 이 정육면체는 탁자위에 있으므로, 5개의 면만 보인다.

N과 주사위에 쓰여 있는 수가 주어질 때, 보이는 5개의 면에 쓰여 있는 수의 합의 최솟값을 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 N이 주어진다. 둘째 줄에 주사위에 쓰여 있는 수가 주어진다. 
위의 그림에서 A, B, C, D, E, F에 쓰여 있는 수가 차례대로 주어진다. 
N은 1,000,000보다 작거나 같은 자연수이고, 쓰여 있는 수는 50보다 작거나 같은 자연수이다.

출력
첫째 줄에 문제의 정답을 출력한다.

*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

using ll = long long;

vector<int> V(6);
ll N;

int getMin(vector<int> v){
	int ret = v[0];
		
	for(int i: v){
		ret = min(ret, i);
	}
	
	return ret;
}


ll getAns(){
	int &a = V[0], &b = V[1], &c = V[2], &d = V[3], &e = V[4], &f = V[5];
	
	int one = getMin(V);
	int two = getMin({a+d, a+c, a+e, a+b, d+e, d+b, d+f, e+c, e+f, c+b, c+f, b+f});
	int three = getMin({a+e+d, a+b+d, a+e+c, a+b+c, f+e+d, f+b+d, f+e+c, f+b+c});
	
	
	if(N == 1LL){
		sort(V.begin(), V.end());
		return a+b+c+d+e;
	}
	if(N == 2LL){
		return two * 4 + three * 4;
	}
	
	// 면(one), 모서리(two), 코너(three)의 개수에 값을 곱해준다.
	return (one * ((N-2)*(N-1)*4+(N-2)*(N-2))) + (two * ((N-1)*4+(N-2)*4)) + (three * 4);
}


int main(){
	ios::sync_with_stdio(0); 
	cin.tie(0);
	
	cin >> N;
	for(int i=0;i<6;i++){
		cin >> V[i];
	}
	
	cout << getAns() << "\n";
	
	return 0;
}