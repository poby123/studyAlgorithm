// https://www.acmicpc.net/problem/1013
/* 정규표현식 라이브러리를 이용하는 방법 */

// #include<iostream>
// #include<string>
// #include<regex>
// using namespace std;

// int T;
// string str;

// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(0);

//     cin >> T;
//     while(T--){
//         cin >> str;

//         regex pat("(100+1+|01)+");
//         bool result = regex_match(str, pat);
        
//         if(result){
//             cout << "YES\n";
//         }
//         else{
//             cout << "NO\n";
//         }
//     }

//     return 0;
// }

/* DFA를 이용하는 방법 */
#include<cstdio>
#include<cstring>

#define F 9

char s[201];
int T, G[][2]={
    5, 1,
    2, F, 
    3, F,
    3, 4,
    5, 7,
    F, 6,
    5, 1,
    8, 7,
    3, 6,
    F, F
};

int solve(const char* s, int size){
    int state = 0;

    for(int i=0;i<size;++i){
        int cur = s[i]-'0';
        state = G[state][cur];
    }

    return state == 4 || state == 6 || state == 7;
}

int main(){
    scanf("%d ", &T);

    while(T--){
        memset(s, 0, sizeof(s));
        scanf("%s", s);
        
        int result = solve(s, strlen(s));
        const char* msg = result ? "YES" : "NO";
        printf("%s\n", msg);
    }

    return 0;
}
