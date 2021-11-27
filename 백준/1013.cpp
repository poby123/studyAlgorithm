// https://www.acmicpc.net/problem/1013
/* 정규표현식 라이브러리를 이용하는 방법 */

#include<iostream>
#include<string>
#include<regex>
using namespace std;

int T;
string str;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while(T--){
        cin >> str;

        regex pat("(100+1+|01)+");
        bool result = regex_match(str, pat);
        
        if(result){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}

/* DFA를 이용하는 방법 */