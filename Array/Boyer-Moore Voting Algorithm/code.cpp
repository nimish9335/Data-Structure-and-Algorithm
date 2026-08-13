#include <bits/stdc++.h>
using namespace std;

int majorityElementBrute(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) count++;
        }
        if (count > n / 2) return arr[i];
    }

    return -1;
}

int majorityElementHashing(vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, int> freq;

    for (int x : arr) {
        freq[x]++;
    }

    for (auto& it : freq) {
        int key=it.first;
        int count=it.second;
        if (count > n / 2) return key;
    }

    return -1;
}

int majorityElementMoore(vector<int>& arr) {
    int n = arr.size();
    int count = 0;
    int candidate = -1;

    for (int x : arr) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }

    int actualCount = 0;
    for (int x : arr) {
        if (x == candidate) actualCount++;
    }

    if (actualCount > n / 2) return candidate;
    return -1;
}

int main() {
    vector<int> arr1 = {2, 2, 1, 1, 1, 2, 2};
    cout << "Brute Force: " << majorityElementBrute(arr1) << endl;
    cout << "Hashing: " << majorityElementHashing(arr1) << endl;
    cout << "Moore's Voting: " << majorityElementMoore(arr1) << endl;

    vector<int> arr2 = {3, 3, 4};
    cout << "\nBrute Force: " << majorityElementBrute(arr2) << endl;
    cout << "Hashing: " << majorityElementHashing(arr2) << endl;
    cout << "Moore's Voting: " << majorityElementMoore(arr2) << endl;

    return 0;
}
