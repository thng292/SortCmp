#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int Partition(int* arr, int start, int end)
{
    int pivot = arr[end];
    int j = start;
    for (int i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            Swap(&arr[i], &arr[j]);
            j++;
        }
    }
    Swap(&arr[j], &arr[end]);
    return j;
}

void QuickSort(int* arr, int start, int end)
{
    if (end <= start) {
        return;
    }

    int tmp = Partition(arr, start, end);

    QuickSort(arr, start, tmp - 1);
    QuickSort(arr, tmp + 1, end);
}

int main(int args, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    int n;
    fscanf(file, "%d", &n);
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    clock_t begin = clock();
    QuickSort(arr, 0, n - 1);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    free(arr);
    return 0;
}
