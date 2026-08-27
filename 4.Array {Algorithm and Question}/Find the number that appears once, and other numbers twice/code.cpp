#include <bits/stdc++.h>
using namespace std;

int singleNumberBrute(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) count++;
        }
        if (count == 1) return arr[i];
    }

    return -1;
}

int singleNumberHashing(vector<int>& arr) {
    unordered_map<int, int> freq;

    for (int x : arr) {
        freq[x]++;
    }

    for (auto& it : freq) {
        int key=it.first;
        int count=it.second;
        if (count == 1) return key;
    }

    return -1;
}

int singleNumberXOR(vector<int>& arr) {
    int result = 0;

    for (int x : arr) {
        result ^= x;
    }

    return result;
}

int main() {
    vector<int> arr1 = {4, 1, 2, 1, 2};
    cout << "Brute Force: " << singleNumberBrute(arr1) << endl;
    cout << "Hashing: " << singleNumberHashing(arr1) << endl;
    cout << "XOR: " << singleNumberXOR(arr1) << endl;

    vector<int> arr2 = {2, 2, 1};
    cout << "\nBrute Force: " << singleNumberBrute(arr2) << endl;
    cout << "Hashing: " << singleNumberHashing(arr2) << endl;
    cout << "XOR: " << singleNumberXOR(arr2) << endl;

    return 0;
}
