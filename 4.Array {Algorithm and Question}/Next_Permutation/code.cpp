#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& arr) {
    int n = arr.size();
    int breakpoint = -1;

    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            breakpoint = i;
            break;
        }
    }

    if (breakpoint == -1) {
        reverse(arr.begin(), arr.end());
        return;
    }

    for (int i = n - 1; i > breakpoint; i--) {
        if (arr[i] > arr[breakpoint]) {
            swap(arr[i], arr[breakpoint]);
            break;
        }
    }

    reverse(arr.begin() + breakpoint + 1, arr.end());
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr1 = {1, 2, 3};
    nextPermutation(arr1);
    cout << "Next Permutation: ";
    printArray(arr1);

    vector<int> arr2 = {3, 2, 1};
    nextPermutation(arr2);
    cout << "Next Permutation: ";
    printArray(arr2);

    return 0;
}
