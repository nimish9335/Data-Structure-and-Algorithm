#include <bits/stdc++.h>
using namespace std;

long long reversePairsBrute(vector<int>& arr) {
    int n = arr.size();
    long long count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((long long)arr[i] > 2LL * arr[j]) count++;
        }
    }

    return count;
}

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

long long countCrossPairs(vector<int>& arr, int low, int mid, int high) {
    long long count = 0;
    int right = mid + 1;

    for (int i = low; i <= mid; i++) {
        while (right <= high && (long long)arr[i] > 2LL * arr[right]) {
            right++;
        }
        count += (right - (mid + 1));
    }

    return count;
}

long long mergeSortAndCount(vector<int>& arr, int low, int high) {
    long long count = 0;

    if (low >= high) return count;

    int mid = (low + high) / 2;

    count += mergeSortAndCount(arr, low, mid);
    count += mergeSortAndCount(arr, mid + 1, high);
    count += countCrossPairs(arr, low, mid, high);

    merge(arr, low, mid, high);

    return count;
}

long long reversePairsOptimal(vector<int> arr) {
    int n = arr.size();
    return mergeSortAndCount(arr, 0, n - 1);
}

int main() {
    vector<int> arr1 = {1, 3, 2, 3, 1};
    cout << "Brute Force: " << reversePairsBrute(arr1) << endl;
    cout << "Optimal (Merge Sort): " << reversePairsOptimal(arr1) << endl;

    vector<int> arr2 = {2, 4, 3, 5, 1};
    cout << "\nBrute Force: " << reversePairsBrute(arr2) << endl;
    cout << "Optimal (Merge Sort): " << reversePairsOptimal(arr2) << endl;

    return 0;
}
