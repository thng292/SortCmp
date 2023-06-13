#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void QuickSort(int* a, int left, int right)
{
    int i = left, j = right;
    int pivot = a[left + rand() % (right - left)];
    // chia dãy thành 2 phần
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;

        if (i <= j) {
            Swap(&a[i], &a[j]);
            ++i;
            --j;
        }
    }
    // Gọi đệ quy để sắp xếp các nửa
    if (left < j) QuickSort(a, left, j);
    if (i < right) QuickSort(a, i, right);
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

    srand(time(NULL));
    clock_t begin = clock();
    QuickSort(arr, 0, n - 1);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    free(arr);
    return 0;
}
