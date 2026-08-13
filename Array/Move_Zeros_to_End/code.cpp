#include <bits/stdc++.h>
using namespace std;

void moveZerosBrute(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp;

    for (int x : arr) {
        if (x != 0) temp.push_back(x);
    }

    int idx = 0;
    for (int x : temp) {
        arr[idx++] = x;
    }

    while (idx < n) {
        arr[idx++] = 0;
    }
}

void moveZerosOptimal(vector<int>& arr) {
    int n = arr.size();
    int j = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            j = i;
            break;
        }
    }

    if (j == -1) return;

    for (int i = j + 1; i < n; i++) {
        if (arr[i] != 0) {
            swap(arr[i], arr[j]);
            j++;
        }
    }
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> a1 = {1, 0, 2, 3, 0, 4, 0, 1};
    moveZerosBrute(a1);
    cout << "Brute Force Result: ";
    printArray(a1);

    vector<int> a2 = {1, 2, 0, 1, 0, 4, 0};
    moveZerosOptimal(a2);
    cout << "Optimal Result: ";
    printArray(a2);

    return 0;
}
