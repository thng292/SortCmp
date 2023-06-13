#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SelectionSort(int* arr, int length)
{
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        Swap(&arr[i], &arr[min]);
    }
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
    SelectionSort(arr, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%lf", time_spent);

    free(arr);
    return 0;
}
