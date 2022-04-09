// https://www.acmicpc.net/problem/4354

/*
    문자열에서 반복되는 패턴의 길이를, 문자열의 길이로 나누면 된다.
    
    반복되는 패턴의 길이는, 
    전체 문자열에서 접두사와 접미사가 일치하는 부분 문자열의 길이를 뺀것이다.
    예를 들어, 
    ababab 에서 abab를 제외한 문자열인 ab를 패턴으로 이용할 수 있다.
    abcabc 에서는 abc를 제외한 문자열인 abc를 패턴으로 이용할 수 있다.
    
    $주의할 점
    abcdabc의 경우, abc를 제외한 abcd를 패턴으로 이용할 수 없다.
    따라서 m / (m - pi[m-1])가 나머지 없이 떨어지는 경우에만 성립한다.
    
*/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

string N;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    while(1){
        cin >> N;
        int m = N.size();
        
        if(N == "."){
            break;
        }
        
        // kmp
        vector<int> pi(m, 0);
        for(int i=1, matched=0;i<m;i++){
            while(matched > 0 && N[i] != N[matched])
                matched = pi[matched - 1];
                
            if(N[i] == N[matched]){
                pi[i] = ++matched;
            }
        }
        
        // print
        if(m % (m - pi[m-1]) == 0){
            cout << m / (m - pi[m-1]) << endl;
        }
        else{
            cout << 1 << endl;
        }
    }

    return 0;
}
