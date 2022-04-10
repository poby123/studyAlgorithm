// https://www.acmicpc.net/problem/10942

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MAX 2001

int N, M, S, E, arr[MAX], dp[MAX][MAX];

int isPallendrom(int s, int e){
    int& memo = dp[s][e];
    
    // cross? -> is pallendrom
    if(s > e) {
        return 1;
    }
    
    // memo is exist
    if(memo != -1){
        return memo;
    }
    
    // a char is pallendrom
    if(s == e){
        return memo=1;
    }
    
    // different
    if(arr[s] != arr[e]){
        return memo=0;
    }
    
    // recursive & memoization
    return memo = isPallendrom(s+1, e-1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    
    for(int i=1;i<=N;i++){
        cin >> arr[i];
    }
    cin >> M;
    
    for(int i=0;i<M;i++){
        cin >> S >> E;
        cout << isPallendrom(S, E) << endl;
    }
    
    return 0;
}