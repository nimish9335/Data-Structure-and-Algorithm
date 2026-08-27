#include <bits/stdc++.h>
using namespace std;

void mergeBrute(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();

    vector<int> temp;
    for (int x : arr1) temp.push_back(x);
    for (int x : arr2) temp.push_back(x);

    sort(temp.begin(), temp.end());

    for (int i = 0; i < n; i++) arr1[i] = temp[i];
    for (int i = 0; i < m; i++) arr2[i] = temp[n + i];
}

void mergeTwoPointer(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();

    int left = n - 1, right = 0;

    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        } else {
            break;
        }
    }

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

int getElement(vector<int>& arr1, vector<int>& arr2, int idx) {
    int n = arr1.size();
    if (idx < n) return arr1[idx];
    return arr2[idx - n];
}

void setElement(vector<int>& arr1, vector<int>& arr2, int idx, int value) {
    int n = arr1.size();
    if (idx < n) arr1[idx] = value;
    else arr2[idx - n] = value;
}

void mergeGapMethod(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int total = n + m;

    int gap = (total / 2) + (total % 2);

    while (gap > 0) {
        int left = 0, right = gap;

        while (right < total) {
            int leftVal = getElement(arr1, arr2, left);
            int rightVal = getElement(arr1, arr2, right);

            if (leftVal > rightVal) {
                setElement(arr1, arr2, left, rightVal);
                setElement(arr1, arr2, right, leftVal);
            }

            left++;
            right++;
        }

        if (gap == 1) gap = 0;
        else gap = (gap / 2) + (gap % 2);
    }
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> a1 = {1, 4, 8, 10};
    vector<int> a2 = {2, 3, 9};
    mergeTwoPointer(a1, a2);
    cout << "Two-Pointer Result: arr1 = ";
    printArray(a1);
    cout << "                    arr2 = ";
    printArray(a2);

    vector<int> b1 = {1, 3, 5, 7};
    vector<int> b2 = {0, 2, 6, 8, 9};
    mergeGapMethod(b1, b2);
    cout << "\nGap Method Result:  arr1 = ";
    printArray(b1);
    cout << "                    arr2 = ";
    printArray(b2);

    return 0;
}
