#include <bits/stdc++.h>
using namespace std;

// ---------- 1. Number System Conversion ----------
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

// ---------- 2. Memory Representation ----------
void printBits(int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
        if (i % 4 == 0) cout << " ";
    }
    cout << endl;
}

// ---------- 3. 1's and 2's Complement ----------
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

// ---------- 6. Sign Bit Check ----------
void showSignBit(int n) {
    unsigned int mask = 1u << 31;
    int signBit = (n & mask) ? 1 : 0;
    cout << n << " -> Sign bit: " << signBit
         << (signBit ? " (Negative)" : " (Positive)") << endl;
}

int main() {
    cout << "===== 1. Number System Conversion =====\n";
    cout << "13 in Binary: " << decimalToBinary(13) << endl;
    cout << "1101 in Decimal: " << binaryToDecimal("1101") << endl;

    cout << "\n===== 2. Memory Representation (32-bit) =====\n";
    cout << "13  -> "; printBits(13);
    cout << "-13 -> "; printBits(-13);

    cout << "\n===== 3. 1's and 2's Complement =====\n";
    string bin = "00001101";
    cout << "Original:       " << bin << endl;
    cout << "1's Complement: " << onesComplement(bin) << endl;
    cout << "2's Complement: " << twosComplement(bin) << endl;

    cout << "\n===== 4. Bitwise Operators =====\n";
    int a = 5, b = 3;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "a ^ b = " << (a ^ b) << endl;

    cout << "\n===== 5. Shift Operators =====\n";
    cout << "5 << 1 = " << (5 << 1) << endl;
    cout << "20 >> 1 = " << (20 >> 1) << endl;

    cout << "\n===== 6. Negative Number Representation =====\n";
    showSignBit(13);
    showSignBit(-13);

    cout << "\n===== 7. NOT Operator =====\n";
    int n = 5;
    cout << "~5 = " << (~n) << endl;

    return 0;
}
