#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int low, int high) {

    int pivot = arr[low];

    int i = low;
    int j = high;

    while (i < j) {

        while (arr[i] <= pivot && i <= high - 1)
            i++;

        while (arr[j] > pivot && j >= low + 1)
            j--;

        if (i < j)
            swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);

    return j;
}

void quickSort(vector<int>& arr, int low, int high) {

    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);

    quickSort(arr, low, pivotIndex - 1);

    quickSort(arr, pivotIndex + 1, high);
}

int main() {

    vector<int> arr = {8, 4, 7, 9, 3, 10, 5};

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted Array : ";

    for (int x : arr)
        cout << x << " ";

    return 0;
}