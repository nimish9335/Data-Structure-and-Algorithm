#include <bits/stdc++.h>
using namespace std;

// ================= Digit Extraction =================
void digitExtraction(int n) {
    while (n != 0) {
        int digit = n % 10;
        cout << digit << " ";
        n = n / 10;
    }
}

// ================= Count Digits =================
int countDigitsLoop(int n) {
    int count = 0;
    while (n != 0) {
        count++;
        n = n / 10;
    }
    return count;
}

int countDigitsLog(int n) {
    if (n == 0) return 1;
    return (int)log10(n) + 1;
}

// ================= Reverse a Number =================
int reverseNumber(int n) {
    int rev = 0;
    while (n != 0) {
        int lastDigit = n % 10;
        rev = (rev * 10) + lastDigit;
        n = n / 10;
    }
    return rev;
}

// ================= Palindrome Check =================
bool isPalindrome(int n) {
    int original = n;
    int rev = reverseNumber(n);
    return original == rev;
}

// ================= Armstrong Numbers =================
bool isArmstrong(int n) {
    int original = n;
    int sum = 0;
    while (n != 0) {
        int digit = n % 10;
        sum += digit * digit * digit;
        n = n / 10;
    }
    return sum == original;
}

// ================= Print All Divisors =================
void printDivisorsBrute(int n) {
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) cout << i << " ";
    }
}

void printDivisorsOptimized(int n) {
    vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    for (int d : divisors) cout << d << " ";
}

// ================= Check for Prime =================
bool isPrime(int n) {
    if (n <= 1) return false;
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i != n / i) cnt++;
        }
    }
    return cnt == 2;
}

// ================= GCD / HCF =================
int gcdBrute(int n1, int n2) {
    int gcd = 1;
    for (int i = 1; i <= min(n1, n2); i++) {
        if (n1 % i == 0 && n2 % i == 0) gcd = i;
    }
    return gcd;
}

int gcdEuclidean(int n1, int n2) {
    while (n1 != 0 && n2 != 0) {
        if (n1 > n2) n1 = n1 % n2;
        else n2 = n2 % n1;
    }
    return n1 == 0 ? n2 : n1;
}
