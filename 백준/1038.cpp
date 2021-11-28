/*
문제
음이 아닌 정수 X의 자릿수가 가장 큰 자릿수부터 작은 자릿수까지 감소한다면, 그 수를 감소하는 수라고 한다. 
예를 들어, 321과 950은 감소하는 수지만, 322와 958은 아니다. 
N번째 감소하는 수를 출력하는 프로그램을 작성하시오. 
0은 0번째 감소하는 수이고, 1은 1번째 감소하는 수이다. 만약 N번째 감소하는 수가 없다면 -1을 출력한다.

입력
첫째 줄에 N이 주어진다. N은 1,000,000보다 작거나 같은 자연수 또는 0이다.

출력
첫째 줄에 N번째 감소하는 수를 출력한다.

예제 입력 1 
18
예제 출력 1 
42

예제 입력 2 
0
예제 출력 2 
0

예제 입력 3 
500000
예제 출력 3 
-1

1021
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<long long> v;
int N, arr[] = {9,8,7,6,5,4,3,2,1,0};

void solve(int before, int toPick, long long acc){
    if(!toPick){
        v.push_back(acc);
        return;
    }
    for(int i=before+1;i<10;i++){
        solve(i, toPick-1, acc * 10LL + arr[i]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    v.reserve(1024);

    cin >> N;
    for(int i=1;i<=10;i++){
        solve(-1, i, 0LL);
    }

    sort(v.begin(), v.end());

    if(v.size() <= N){
        cout << "-1\n";
    }
    else{
        cout << v[N] << "\n";
    }
    
    return 0;
}