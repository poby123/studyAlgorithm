/*
문제
오민식은 자기가 좋아하는 여자 N명 중에 한 명과 함께 데이트하러 나가고 싶어한다.

하지만 N명 모두를 사랑하는 오민식에게는 한 명을 선택하고 나머지 여자를 버리는 것은 슬픈 결정이기 때문에 누구를 선택해야 할지 고민에 빠졌다.

마침 오민식은 사랑계산기를 얻었다. 사랑계산기는 두 사람의 이름을 이용해서 두 사람이 성공할 확률을 계산해 준다. 사랑계산기는 다음과 같이 작동한다.

L = 두 사람 이름에서 등장하는 L의 개수
O = 두 사람 이름에서 등장하는 O의 개수
V = 두 사람 이름에서 등장하는 V의 개수
E = 두 사람 이름에서 등장하는 E의 개수
위의 개수를 모두 계산 한 후에 확률 계산은 다음과 같이 한다.

((L+O)*(L+V)*(L+E)*(O+V)*(O+E)*(V+E)) mod 100

오민식의 영어 이름과 나머지 여자들의 이름이 주어졌을 때, 오민식과 성공할 확률이 가장 높은 여자의 이름을 출력하는 프로그램을 작성하시오. 
여러명일 때에는 알파벳으로 가장 앞서는 이름을 출력하면 된다.

입력
첫째 줄에 오민식의 영어 이름이 주어진다. 둘째 줄에는 좋아하는 여자가 몇 명인지 N이 주어지고, 셋째 줄부터 N개의 줄에 여자의 이름이 하나 씩 주어진다. 
N은 50보다 작거나 같고, 모든 이름은 알파벳 대문자로만 구성되어 있고 모두 길어야 20글자이다.

출력
오민식이 선택한 여자의 이름을 출력한다.
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, c[26];
string arr[50], myName;
vector<pair<int, string>> v;

bool cri(const pair<int, string> &a, const pair<int, string> &b)
{
    if (a.first != b.first)
    {
        return a.first > b.first;
    }
    return a.second < b.second;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> myName;
    cin >> N;
    v.reserve(N);
    for (auto it : myName)
    {
        ++c[it - 'A'];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        int temp[26], P, L, O, V, E;
        memcpy(temp, c, sizeof(temp));
        for (auto it : arr[i])
        {
            ++temp[it - 'A'];
        }
        L = temp['L' - 'A'];
        O = temp['O' - 'A'];
        V = temp['V' - 'A'];
        E = temp['E' - 'A'];
        P = ((L + O) * (L + V) * (L + E) * (O + V) * (O + E) * (V + E)) % 100;
        v.push_back({P, arr[i]});
    }

    sort(v.begin(), v.end(), cri);
    cout << v[0].second;

    return 0;
}