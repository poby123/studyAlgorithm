#include<bits/stdc++.h>
#define MAX 1001
using namespace std;
using ll = long long;

int T, N, K, W, i, x, y;
vector<int> G[MAX];
ll D[MAX], dp[MAX];

ll dfs(int cur){
    ll& curDp = dp[cur];
    if(curDp != -1){
        return curDp;
    }
    
    curDp = D[cur];
    for(int next : G[cur]){
        curDp = max(curDp, dfs(next) + D[cur]);
    }
    
    return curDp;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> T;
    
    while(T--){
        // init
        memset(D, 0, sizeof(D));
        memset(dp, -1, sizeof(dp)); // 시간이 0인 것과 구분하기 위해 -1로 초기화해야한다.
        for(i=0;i<MAX;++i){
            G[i].resize(0);
            G[i].reserve(MAX);
        }
        
        // inputs
        cin >> N >> K;
        for(i=1;i<=N;i++){
            cin >> D[i];
        }
        for(i=0;i<K;i++){
            cin >> x >> y;
            G[y].push_back(x);
        }
        cin >> W;
        cout << dfs(W) << "\n";
    }
    
    return 0;
}