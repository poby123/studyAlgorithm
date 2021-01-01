#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int start, int end)
{
    int pivot = arr[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        if (pivot > arr[j])
        {
            swap(&arr[i], &arr[j]);
            ++i;
        }
    }
    swap(&arr[i], &arr[end]);
    return i;
}

void quickSort(int *arr, int start, int end)
{
    // 기저사례 : 크기가 1인 경우, 파티션을 나눌 필요가 없다.
    if (start < end)
    {
        int pivot = partition(arr, start, end);
        quickSort(arr, start, pivot-1);
        quickSort(arr, pivot + 1, end);
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
    int arr[] = {5, 8, 2, 9, 1, 10, 41, 56, 78, 99, 21};
    int n = sizeof(arr) / sizeof(int);

    quickSort(arr, 0, n - 1);
    print(arr, n);

    return 0;
}