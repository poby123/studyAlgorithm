#include <iostream>
#include <algorithm>
using namespace std;

int arr[2];

void get(const string &s)
{
    ++arr[s[0] - '0'];
    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] != s[i - 1])
        {
            ++arr[s[i] - '0'];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    get(s);
    cout << min(arr[0], arr[1]);

    return 0;
}