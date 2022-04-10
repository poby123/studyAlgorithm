// https://www.acmicpc.net/problem/1647

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MAX 100001

int N, M, ans, parent[MAX], maxCost, a, b, c;
vector<tuple<int, int, int>> G;


int findParent(int x){
    if(x == parent[x]){
        return x;
    }
    return parent[x] = findParent(parent[x]);
}


void unionParent(int a, int b){
    a = findParent(a);
    b = findParent(b);
    
    if(a < b){
        parent[b] = a;
    }
    else{
        parent[a] = b;
    }
}


void kruskal(){
    for(const auto& cur : G){
        tie(c, a, b) = cur;
        
        if(findParent(a) != findParent(b)){
            ans += c;
            maxCost = max(maxCost, c);
            unionParent(a, b);
        }
    }
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for(int i=1;i<MAX;i++){
        parent[i] = i;
    }
    
    cin >> N >> M;
    G.reserve(M);
    
    for(int i=0;i<M;i++){
        cin >> a >> b >> c;
        G.push_back({c, a, b});
    }
    
    sort(G.begin(), G.end());
    kruskal();
    
    cout << ans - maxCost << endl;
    
    return 0;
}