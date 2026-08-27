#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Stack-Based Simulation ----------
string removeOuterParenthesesStack(string s) {
    string result;
    stack<char> st;

    for (char ch : s) {
        if (ch == '(') {
            if (!st.empty()) {
                result += ch;
            }
            st.push(ch);
        } else { // ch == ')'
            st.pop();
            if (!st.empty()) {
                result += ch;
            }
        }
    }

    return result;
}

// ---------- Approach 2: Optimal — Level Counter ----------
string removeOuterParenthesesOptimal(string s) {
    string result;
    int level = 0;

    for (char ch : s) {
        if (ch == '(') {
            if (level > 0) {
                result += ch;
            }
            level++;
        } else { // ch == ')'
            level--;
            if (level > 0) {
                result += ch;
            }
        }
    }

    return result;
}

int main() {
    string s1 = "((()))";
    cout << "Input:  " << s1 << endl;
    cout << "Stack:   " << removeOuterParenthesesStack(s1) << endl;
    cout << "Optimal: " << removeOuterParenthesesOptimal(s1) << endl;

    string s2 = "()(()())(())";
    cout << "\nInput:  " << s2 << endl;
    cout << "Stack:   " << removeOuterParenthesesStack(s2) << endl;
    cout << "Optimal: " << removeOuterParenthesesOptimal(s2) << endl;

    return 0;
}
