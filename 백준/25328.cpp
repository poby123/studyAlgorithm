// https://www.acmicpc.net/problem/25328

#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0)

string s, acc;
vector<string> inputs, ans;
map<string, int> freq;
int k;

void get_subsets(string &s, int cur) {
    if (acc.size() >= k) {
        ++freq[acc];
        return;
    }

    for (int i = cur; i < s.size(); i++) {
        acc.push_back(s[i]);
        get_subsets(s, i + 1);
        acc.pop_back();
    }
}

int main() {
    fastio;

    for (int i = 0; i < 3; i++) {
        cin >> s;
        inputs.push_back(s);
    }
    cin >> k;

    for (int i = 0; i < 3; i++) {
        get_subsets(inputs[i], 0);
    }

    for (auto it : freq) {
        if (it.second >= 2) {
            ans.push_back(it.first);
        }
    }

    if (ans.empty()) {
        cout << "-1" << "\n";
    } 
    else {
        sort(ans.begin(), ans.end());
        for (string s : ans) {
            cout << s << "\n";
        }
    }
}