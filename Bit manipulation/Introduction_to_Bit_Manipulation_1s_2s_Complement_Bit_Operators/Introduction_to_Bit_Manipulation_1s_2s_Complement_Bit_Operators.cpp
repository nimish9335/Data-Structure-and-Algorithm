#include <bits/stdc++.h>
using namespace std;

string decimalToBinary(int n) {
    if (n == 0) return "0";
    string binary = "";
    while (n > 0) {
        binary += (char)('0' + (n % 2));
        n /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

int binaryToDecimal(string binary) {
    int decimal = 0, power = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') decimal += pow(2, power);
        power++;
    }
    return decimal;
}

string printBits(int n) {
    string result = "";
    for (int i = 31; i >= 0; i--) {
        result += ((n >> i) & 1) ? '1' : '0';
        if (i % 4 == 0) result += ' ';
    }
    return result;
}

string onesComplement(string binary) {
    string result = "";
    for (char b : binary) result += (b == '0') ? '1' : '0';
    return result;
}

string twosComplement(string binary) {
    string ones = onesComplement(binary);
    int carry = 1;
    for (int i = ones.size() - 1; i >= 0 && carry; i--) {
        if (ones[i] == '1') ones[i] = '0';
        else { ones[i] = '1'; carry = 0; }
    }
    return ones;
}

int bitwiseAND(int a, int b) {
    return a & b;
}

int bitwiseOR(int a, int b) {
    return a | b;
}

int bitwiseXOR(int a, int b) {
    return a ^ b;
}

pair<int, int> xorSwap(int a, int b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    return {a, b};
}

bool isOdd(int n) {
    return n & 1;
}

int leftShift(int n, int k) {
    return n << k;
}

int rightShift(int n, int k) {
    return n >> k;
}

int getSignBit(int n) {
    unsigned int mask = 1u << 31;
    return (n & mask) ? 1 : 0;
}

int bitwiseNOT(int n) {
    return ~n;
}
