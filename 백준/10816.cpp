// 이분탐색
#include<bits/stdc++.h>
using namespace std;

vector<int> G;
int N, M, v;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for(int i=0;i<N;i++){
        cin >> v;
        G.push_back(v);
    }

    sort(G.begin(), G.end());

    cin >> M;
    for(int i=0;i<M;i++){
        cin >> v;
        cout << upper_bound(G.begin(), G.end(), v) - lower_bound(G.begin(), G.end(), v) << " "; // https://chanhuiseok.github.io/posts/algo-55/
    }

    return 0;
}

// 단순 map 활용
// #include<bits/stdc++.h>
// using namespace std;

// map<int, int> G;
// int N, M, v;

// int main(){
//     cin.tie(0)->sync_with_stdio(0);

//     cin >> N;
//     for(int i=0;i<N;i++){
//         cin >> v;
//         ++G[v];
//     }

//     cin >> M;
//     for(int i=0;i<M;i++){
//         cin >> v;
//         cout << G[v] << " ";
//     }

//     return 0;
// }
