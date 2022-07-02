// https://www.acmicpc.net/problem/25329

#include<bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)

int N;
map<string, int> table;
vector<pair<int, string>> ans;
string t, name;

int stringTimeToInt(string& time){
    int hh = stoi(time.substr(0, 2));
    int mm = stoi(time.substr(3, 2));
    return hh * 60 + mm;
}

int calcPrice(int t){
    if(t <= 100){
        return 10;
    }

    t -= 100;
    int cost = 10 + 3 * (t / 50);
    return t % 50 == 0 ?  cost : cost + 3;
}

int main(){
    fastio;

    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> t >> name;
      table[name] += stringTimeToInt(t);
    }

    for(const auto it: table){
        ans.push_back({-calcPrice(it.second), it.first});
    }

    sort(ans.begin(), ans.end());
    for(auto it: ans){
        cout << it.second << " " << -it.first << "\n";
    }

}