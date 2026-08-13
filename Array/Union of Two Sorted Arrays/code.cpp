#include <bits/stdc++.h>
using namespace std;

vector<int> unionUsingMap(vector<int>& arr1, vector<int>& arr2) {
    map<int, bool> mp;

    for (int x : arr1) mp[x] = true;
    for (int x : arr2) mp[x] = true;

    vector<int> result;
    for (auto& it : mp) {
        int key=it.first;
        int val=it.second;
        result.push_back(key);
    }

    return result;
}

vector<int> unionUsingSet(vector<int>& arr1, vector<int>& arr2) {
    set<int> s;

    for (int x : arr1) s.insert(x);
    for (int x : arr2) s.insert(x);

    vector<int> result(s.begin(), s.end());
    return result;
}

vector<int> unionUsingTwoPointers(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int i = 0, j = 0;
    vector<int> result;

    while (i < n && j < m) {
        if (arr1[i] < arr2[j]) {
            if (result.empty() || result.back() != arr1[i]) {
                result.push_back(arr1[i]);
            }
            i++;
        } else if (arr1[i] > arr2[j]) {
            if (result.empty() || result.back() != arr2[j]) {
                result.push_back(arr2[j]);
            }
            j++;
        } else {
            if (result.empty() || result.back() != arr1[i]) {
                result.push_back(arr1[i]);
            }
            i++;
            j++;
        }
    }

    while (i < n) {
        if (result.empty() || result.back() != arr1[i]) {
            result.push_back(arr1[i]);
        }
        i++;
    }

    while (j < m) {
        if (result.empty() || result.back() != arr2[j]) {
            result.push_back(arr2[j]);
        }
        j++;
    }

    return result;
}

void printArray(vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> arr2 = {2, 3, 4, 4, 5, 11, 12};

    vector<int> res1 = unionUsingMap(arr1, arr2);
    cout << "Using Map: ";
    printArray(res1);

    vector<int> res2 = unionUsingSet(arr1, arr2);
    cout << "Using Set: ";
    printArray(res2);

    vector<int> res3 = unionUsingTwoPointers(arr1, arr2);
    cout << "Using Two Pointers: ";
    printArray(res3);

    return 0;
}
