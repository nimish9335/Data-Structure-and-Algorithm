#include <bits/stdc++.h>
using namespace std;

int largestElement(vector<int>& arr) {
    int largest = arr[0];
    for (int x : arr) {
        if (x > largest) largest = x;
    }
    return largest;
}

int secondLargest(vector<int>& arr) {
    int largest = INT_MIN, secondLargest = INT_MIN;
    for (int x : arr) {
        if (x > largest) {
            secondLargest = largest;
            largest = x;
        } else if (x > secondLargest && x != largest) {
            secondLargest = x;
        }
    }
    return secondLargest;
}

bool isSorted(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

int removeDuplicates(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    int i = 0;
    for (int j = 1; j < n; j++) {
        if (arr[j] != arr[i]) {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}

int main() {
    vector<int> a1 = {2, 5, 1, 3, 0};
    cout << "Largest Element: " << largestElement(a1) << endl;

    vector<int> a2 = {8, 8, 3, 5, 6, 6, 8, 9};
    cout << "Second Largest: " << secondLargest(a2) << endl;

    vector<int> a3 = {1, 2, 2, 3, 4};
    cout << "Is Sorted: " << (isSorted(a3) ? "true" : "false") << endl;

    vector<int> a4 = {1, 1, 2, 2, 2, 3, 3};
    int uniqueCount = removeDuplicates(a4);
    cout << "Unique Count: " << uniqueCount << " -> [";
    for (int i = 0; i < uniqueCount; i++) {
        cout << a4[i];
        if (i != uniqueCount - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
