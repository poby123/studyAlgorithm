#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int T, N;
string f, arr;
deque<int> v;

void parse(string &s)
{
    s = s.substr(1, s.size() - 2);

    if (s.empty())
    {
        return;
    }

    istringstream ss(s);
    string buffer;

    while (getline(ss, buffer, ','))
    {
        v.push_back(stoi(buffer));
    }
}

void print(bool reverse)
{
    int start = 0;
    int end = v.size();

    cout << "[";
    if (reverse)
    {
        for (int i = v.size() - 1; i >= 0; --i)
        {
            cout << v[i];

            if (i != 0)
            {
                cout << ",";
            }
        }
    }
    else
    {
        for (int i = 0; i < v.size(); ++i)
        {
            cout << v[i];

            if (i != v.size() - 1)
            {
                cout << ",";
            }
        }
    }
    cout << "]\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while (T--)
    {
        bool end = false;
        bool reverse = false;
        v.clear();

        cin >> f >> N >> arr;

        parse(arr);

        for (int i = 0; i < f.size(); i++)
        {
            char cur = f[i];

            if (cur == 'R')
            {
                reverse = !reverse;
            }

            if (cur == 'D')
            {
                if (v.empty())
                {
                    cout << "error\n";
                    end = true;
                    break;
                }
                if (reverse)
                {
                    v.pop_back();
                }
                else
                {
                    v.pop_front();
                }
            }
        }

        if (end)
        {
            continue;
        }

        print(reverse);
    }

    return 0;
}