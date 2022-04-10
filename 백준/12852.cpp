#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 9999999
#define MAX 1000001

int N, dp[MAX], root[MAX];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    fill(begin(dp)+2, end(dp), INF);
    
    for(int i=2;i<=N;i++){
        int& cur = dp[i];
        
        if(i % 3 == 0 && cur > dp[i/3]+1){
            cur = dp[i/3]+1;
            root[i] = i/3;
        }
        if(i % 2 == 0 && cur > dp[i/2]+1){
            cur = dp[i/2]+1;
            root[i] = i/2;
        }
        if(cur > dp[i-1]+1){
            cur = dp[i-1]+1;
            root[i] = i-1;
        }
    }
    
    cout << dp[N] << endl;
    for(int i = N;i>=1;i=root[i]){
        cout << i << " ";
    }
    
    return 0;
}