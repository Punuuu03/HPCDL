HPC 4: Write a program to implement Parallel Merge Sort using OpenMP. Use existing algorithms and measure the performance of sequential and parallel algorithms.

#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void parallelMergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);
        #pragma omp section
        parallelMergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
}

int main() {
    int arr[] = {8, 4, 5, 7, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int arr_parallel[n];
    for (int i = 0; i < n; i++)
        arr_parallel[i] = arr[i];

    double start_time = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    double end_time = omp_get_wtime();
    cout << "Simple Merge Sort Time: " << (end_time - start_time) * 1000 << " milliseconds" << endl;
    
    cout << "Sorted array (Simple Merge Sort): ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    start_time = omp_get_wtime();
    parallelMergeSort(arr_parallel, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    cout << "Sorted array (Parallel Merge Sort): ";
    for (int i = 0; i < n; i++)
        cout << arr_parallel[i] << " ";
    cout << endl;

    return 0;
}
