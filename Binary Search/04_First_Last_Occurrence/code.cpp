#include <bits/stdc++.h>
using namespace std;

pair<int,int> firstLastBrute(vector<int>& arr, int target) {
    int n = arr.size();
    int first = -1, last = -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            if (first == -1) first = i;
            last = i;
        }
    }

    return {first, last};
}

pair<int,int> firstLastBounds(vector<int>& arr, int target) {
    int n = arr.size();

    int lb = lower_bound(arr.begin(), arr.end(), target) - arr.begin();

    if (lb == n || arr[lb] != target) {
        return {-1, -1};
    }

    int ub = upper_bound(arr.begin(), arr.end(), target) - arr.begin();

    return {lb, ub - 1};
}

int findFirst(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int first = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            first = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return first;
}

int findLast(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    int last = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            last = mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return last;
}

pair<int,int> firstLastPureBinarySearch(vector<int>& arr, int target) {
    int first = findFirst(arr, target);
    int last = findLast(arr, target);
    return {first, last};
}

int countOccurrences(vector<int>& arr, int target) {
    auto it = firstLastPureBinarySearch(arr, target);
    int first=it.first;
    int last=it.second;
    if (first == -1) return 0;
    return last - first + 1;
}

int main() {
    vector<int> arr1 = {5, 7, 7, 8, 8, 10};
    int target1 = 8;

    auto it = firstLastPureBinarySearch(arr1, target1);
    int f1=it.first;
    int l1=it.second;
    cout << "First = " << f1 << ", Last = " << l1 << ", Count = " << countOccurrences(arr1, target1) << endl;

    vector<int> arr2 = {5, 7, 7, 8, 8, 10};
    int target2 = 6;

    auto it = firstLastPureBinarySearch(arr2, target2);
    int f2=it.first;
    int l2=it.second;
    cout << "First = " << f2 << ", Last = " << l2 << ", Count = " << countOccurrences(arr2, target2) << endl;

    return 0;
}
