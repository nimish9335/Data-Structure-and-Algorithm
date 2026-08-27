#include <bits/stdc++.h>
using namespace std;

long long countInversionsBrute(vector<int>& arr) {
    int n = arr.size();
    long long count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) count++;
        }
    }

    return count;
}

long long merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;
    long long count = 0;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            count += (mid - left + 1);
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

    return count;
}

long long mergeSortAndCount(vector<int>& arr, int low, int high) {
    long long count = 0;

    if (low >= high) return count;

    int mid = (low + high) / 2;

    count += mergeSortAndCount(arr, low, mid);
    count += mergeSortAndCount(arr, mid + 1, high);
    count += merge(arr, low, mid, high);

    return count;
}

long long countInversionsOptimal(vector<int> arr) {
    int n = arr.size();
    return mergeSortAndCount(arr, 0, n - 1);
}

int main() {
    vector<int> arr1 = {2, 4, 1, 3, 5};
    cout << "Brute Force: " << countInversionsBrute(arr1) << endl;
    cout << "Optimal (Merge Sort): " << countInversionsOptimal(arr1) << endl;

    vector<int> arr2 = {5, 4, 3, 2, 1};
    cout << "\nBrute Force: " << countInversionsBrute(arr2) << endl;
    cout << "Optimal (Merge Sort): " << countInversionsOptimal(arr2) << endl;

    return 0;
}
