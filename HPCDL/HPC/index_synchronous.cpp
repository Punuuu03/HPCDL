#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int a[100], n, i;
    cout << "Enter the number of elements in array: ";
    cin >> n;
    cout << "\nEnter array elements: ";
    for (i = 0; i < n; i++) cin >> a[i];

    int min_val = a[0], max_val = a[0];
    float sum = 0;

    #pragma omp parallel for reduction(min: min_val) reduction(max: max_val) reduction(+: sum)
    for (i = 0; i < n; i++) {
        int id = omp_get_thread_num(); // Get the thread ID
        sum += a[i];
        min_val = (a[i] < min_val) ? a[i] : min_val;
        max_val = (a[i] > max_val) ? a[i] : max_val;
        #pragma omp critical
        // cout << "\nFor i = " << i << ", thread " << id << " is executing." << endl;
    }

    float avg = sum / n;

    cout << "\nMinimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;

    return 0;
}
