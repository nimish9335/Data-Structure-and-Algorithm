#include <bits/stdc++.h>
using namespace std;

void rotateBrute(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;

    vector<int> temp(d);
    for (int i = 0; i < d; i++) {
        temp[i] = arr[i];
    }

    for (int i = d; i < n; i++) {
        arr[i - d] = arr[i];
    }

    for (int i = 0; i < d; i++) {
        arr[n - d + i] = temp[i];
    }
}

void rotateOptimal(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;

    reverse(arr.begin(), arr.begin() + d);
    reverse(arr.begin() + d, arr.end());
    reverse(arr.begin(), arr.end());
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> a1 = {1, 2, 3, 4, 5, 6, 7};
    rotateBrute(a1, 2);
    cout << "Brute Force Result: ";
    printArray(a1);

    vector<int> a2 = {10, 20, 30, 40, 50};
    rotateOptimal(a2, 7);
    cout << "Optimal Result: ";
    printArray(a2);

    return 0;
}
