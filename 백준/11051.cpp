/*
문제
자연수 N과 정수 K가 주어졌을 때 이항 계수 nCk 를 10,007로 나눈 나머지를 구하는 프로그램을 작성하시오.

입력
첫째 줄에 N과 K가 주어진다. (1 ≤ N ≤ 1,000, 0 ≤ K ≤ N)

출력
이항계수 nCk 를 10,007로 나눈 나머지를 출력한다.
*/

#include<iostream>
#include<cstring>
using namespace std;

#define MAX 1001
#define MOD 10007

int N, K, dp[MAX][MAX];

int C(int n, int k){
    if(n == k || !k)
        return dp[n][k] = 1;
    if(dp[n][k] != -1)
        return dp[n][k];
    else
        return dp[n][k] = (C(n-1, k) + C(n-1, k-1)) % MOD;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    cin >> N >> K;

    cout << C(N, K);

    return 0;
}

/*
풀이:
n_C_k = n-1_C_k-1 + n-1_C_k 임을 이용한다.
재귀함수를 이용하되, 메모이제이션을 통해 반복되는 계산을 줄인다. 
*/