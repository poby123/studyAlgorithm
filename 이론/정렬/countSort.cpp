#include <stdio.h>
#include <string.h>

int k = 1001; //k보다 작은 수에 대하여 정렬

void countSort(int *arr, int *sorted, int n)
{
    int *count = new int[k];
    memset(count, 0, k * sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        ++count[arr[i]];
    }

    for (int i = 1; i < k; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        sorted[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    delete[] count;
    count = nullptr;
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
    int arr[] = {5, 8, 2, 9, 1, 1000, 10, 41, 56, 78, 99, 21};
    const int n = sizeof(arr) / sizeof(int);
    int *sorted = new int[n];

    countSort(arr, sorted, n);
    print(sorted, n);

    delete[] sorted;
    sorted = nullptr;

    return 0;
}