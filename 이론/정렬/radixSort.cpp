#include <iostream>
#include <cmath>
#include <queue>
#include <climits>
using namespace std;

int getMaxDigit(int *arr, int n)
{
    int max = INT_MIN;
    int max_digit = 0;

    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    while (max)
    {
        max /= 10;
        ++max_digit;
    }

    return max_digit;
}

void radixSort(int *arr, int n)
{
    queue<int> bucket[10];
    int max_digit = getMaxDigit(arr, n); //가장 큰 값의 자릿수
    int max_pivot = pow(10, max_digit);

    for (int pivot = 1; pivot < max_pivot; pivot *= 10)
    {
        // 각 숫자의 자릿수를 기준으로 queue에 넣기
        for (int i = 0; i < n; i++)
        {
            int index = 0;
            if (pivot <= arr[i])
            {
                index = (arr[i] / pivot) % 10;
            }
            bucket[index].push(arr[i]);
        }

        // queue에 들어간 순서를 유지하면서 배열에 넣기
        int arr_i = 0;
        for (int i = 0; i < 10; i++)
        {
            while (!bucket[i].empty())
            {
                arr[arr_i] = bucket[i].front();
                bucket[i].pop();
                ++arr_i;
            }
        }
    }
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main()
{
    int arr[] = {10001, 408, 5, 100, 2, 10000, 123456, 999, 239, 1, 10, 41, 56, 78, 99, 21, 101};
    int n = sizeof(arr) / sizeof(int);

    radixSort(arr, n);
    print(arr, n);

    return 0;
}