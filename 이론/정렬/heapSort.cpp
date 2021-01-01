#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(int *arr, int i, int n)
{
    while (i < n)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
        {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest])
        {
            largest = right;
        }
        if (i != largest)
        {
            swap(&arr[i], &arr[largest]);
            i = largest;
        }
        else
        {
            break;
        }
    }
}

void buildHeap(int *arr, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        heapifyDown(arr, i, n);
    }
}

void heapSort(int *arr, int n)
{
    buildHeap(arr, n);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapifyDown(arr, 0, i);
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
    int arr[] = {1, 5, 8, 2, 9, 10, 41, 56, 78, 99, 21};
    int n = sizeof(arr) / sizeof(int);
    heapSort(arr, n);
    print(arr, n);
    return 0;
}