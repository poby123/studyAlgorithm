#include<bits/stdc++.h>
#define MAX 1001
using namespace std;

int T, N, K, W, i, x, y, inDegree[MAX], dp[MAX], D[MAX];
vector<int> G[MAX];

int bfs(){
    queue<int> q;
    
    for(i=1;i<=N;i++){
        if(!inDegree[i]){
            q.push(i);
            dp[i] = D[i];
        }
    }
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
    
        for(int i : G[cur]){
            dp[i] = max(dp[i], D[i] + dp[cur]);
            if(!--inDegree[i]){
                q.push(i);
            }
        }
    }
    
    return dp[W];
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> T;
    
    while(T--){
        // init
        memset(D, 0, sizeof(D));
        memset(inDegree, 0, sizeof(inDegree));
        memset(dp, 0, sizeof(dp));
        for(i=0;i<MAX;++i){
            G[i].clear();
        }
        
        // inputs
        cin >> N >> K;
        for(i=1;i<=N;i++){
            cin >> D[i];
        }
        for(i=0;i<K;i++){
            cin >> x >> y;
            G[x].push_back(y);
            ++inDegree[y];
        }
        cin >> W;
        cout << bfs() << "\n";
    }
    
    return 0;
}