#include <bits/stdc++.h>
using namespace std;

int missingNumberBrute(vector<int>& arr) {
    int n = arr.size() + 1;

    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int x : arr) {
            if (x == i) {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }

    return -1;
}

int missingNumberHashing(vector<int>& arr) {
    int n = arr.size() + 1;
    vector<int> hashArr(n + 1, 0);

    for (int x : arr) {
        hashArr[x] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (hashArr[i] == 0) return i;
    }

    return -1;
}

int missingNumberSum(vector<int>& arr) {
    int n = arr.size() + 1;
    long long expectedSum = (long long)n * (n + 1) / 2;

    long long actualSum = 0;
    for (int x : arr) {
        actualSum += x;
    }

    return (int)(expectedSum - actualSum);
}

int missingNumberXOR(vector<int>& arr) {
    int n = arr.size() + 1;
    int xor1 = 0, xor2 = 0;

    for (int i = 1; i <= n; i++) {
        xor1 ^= i;
    }

    for (int x : arr) {
        xor2 ^= x;
    }

    return xor1 ^ xor2;
}

int main() {
    vector<int> arr1 = {8, 2, 4, 5, 3, 7, 1};
    cout << "Brute Force: " << missingNumberBrute(arr1) << endl;
    cout << "Hashing: " << missingNumberHashing(arr1) << endl;
    cout << "Sum Formula: " << missingNumberSum(arr1) << endl;
    cout << "XOR: " << missingNumberXOR(arr1) << endl;

    vector<int> arr2 = {1, 2, 3, 5};
    cout << "\nBrute Force: " << missingNumberBrute(arr2) << endl;
    cout << "Hashing: " << missingNumberHashing(arr2) << endl;
    cout << "Sum Formula: " << missingNumberSum(arr2) << endl;
    cout << "XOR: " << missingNumberXOR(arr2) << endl;

    return 0;
}
