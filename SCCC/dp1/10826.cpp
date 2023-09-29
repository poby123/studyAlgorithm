// https://www.acmicpc.net/problem/10826

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

class BigInteger
{
private:
    string value;

public:
    BigInteger(const int value) : value(to_string(value)) {}
    BigInteger(const string &value) : value(value) {}
    friend BigInteger operator+(const BigInteger &abi, const BigInteger &bbi)
    {
        string ret = "";

        const string &av = abi.value;
        const string &bv = bbi.value;

        size_t aLength = av.size();
        size_t bLength = bv.size();
        size_t length = max(aLength, bLength);

        int carry = 0;
        for (size_t i = 0; i < length; i++)
        {
            int a = 0, b = 0;
            if (i < aLength)
            {
                a = av.at(aLength - i - 1) - '0';
            }
            if (i < bLength)
            {
                b = bv.at(bLength - i - 1) - '0';
            }

            const int result = a + b + carry;
            carry = (result) / 10;
            const int mod = result % 10;

            ret += to_string(mod);
        }
        if (carry)
        {
            ret += to_string(carry);
        }

        reverse(ret.begin(), ret.end());
        return BigInteger(ret);
    }
    friend ostream &operator<<(ostream &os, const BigInteger &a)
    {
        os << a.value;
        return os;
    }
};

int N;
BigInteger a(0), b(1), c(0);

BigInteger solve()
{
    if (N == 0)
    {
        return a;
    }
    if (N == 1)
    {
        return b;
    }

    for (int i = 2; i <= N; i++)
    {
        c = a + b;
        if (i % 2 == 0)
        {
            a = c;
        }
        else
        {
            b = c;
        }
    }

    return c;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    cout << solve() << endl;

    return 0;
}