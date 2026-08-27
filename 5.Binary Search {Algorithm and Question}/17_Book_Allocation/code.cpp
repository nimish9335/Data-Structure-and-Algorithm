#include <bits/stdc++.h>
using namespace std;

// Number of students needed to allocate books contiguously without exceeding `barrier` pages each.
int countStudents(vector<int>& books, int barrier) {
    int students = 1;
    long long pages = 0;

    for (int b : books) {
        if (pages + b > barrier) {
            students++;
            pages = 0;
        }
        pages += b;
    }

    return students;
}

int allocateBooksBrute(vector<int>& books, int m) {
    int n = books.size();
    if (m > n) return -1;

    int low = *max_element(books.begin(), books.end());
    long long high = accumulate(books.begin(), books.end(), 0LL);

    for (long long b = low; b <= high; b++) {
        if (countStudents(books, (int)b) <= m) {
            return (int)b;
        }
    }

    return (int)high;
}

int allocateBooksBinarySearch(vector<int>& books, int m) {
    int n = books.size();
    if (m > n) return -1;

    int low = *max_element(books.begin(), books.end());
    long long high = accumulate(books.begin(), books.end(), 0LL);
    int ans = (int)high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (countStudents(books, (int)mid) <= m) {
            ans = (int)mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    vector<int> books1 = {12, 34, 67, 90};
    int m1 = 2;
    cout << "Brute Force: " << allocateBooksBrute(books1, m1) << endl;
    cout << "Binary Search: " << allocateBooksBinarySearch(books1, m1) << endl;

    vector<int> books2 = {10, 20, 30, 40};
    int m2 = 2;
    cout << "\nBrute Force: " << allocateBooksBrute(books2, m2) << endl;
    cout << "Binary Search: " << allocateBooksBinarySearch(books2, m2) << endl;

    return 0;
}
