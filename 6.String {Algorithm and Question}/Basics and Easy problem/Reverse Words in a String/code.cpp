#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
string reverseWordsBrute(string s) {
    vector<string> words;
    string word = "";

    for (char ch : s) {
        if (ch != ' ') {
            word += ch;
        } else if (!word.empty()) {
            words.push_back(word);
            word = "";
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    reverse(words.begin(), words.end());

    string result = "";
    for (int i = 0; i < (int)words.size(); i++) {
        result += words[i];
        if (i != (int)words.size() - 1) {
            result += " ";
        }
    }

    return result;
}

// ---------- Optimal — Right-to-Left Scan ----------
string reverseWordsOptimal(string s) {
    string result = "";
    int i = (int)s.size() - 1;

    while (i >= 0) {
        // skip trailing/extra spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        if (i < 0) break;

        int end = i;

        // move left until a space or start of string
        while (i >= 0 && s[i] != ' ') {
            i--;
        }

        string word = s.substr(i + 1, end - i);

        if (!result.empty()) {
            result += " ";
        }
        result += word;
    }

    return result;
}

int main() {
    string s1 = "welcome to the jungle";
    cout << "Input:  \"" << s1 << "\"" << endl;
    cout << "Brute Force: \"" << reverseWordsBrute(s1) << "\"" << endl;
    cout << "Optimal:     \"" << reverseWordsOptimal(s1) << "\"" << endl;

    string s2 = "  amazing coding skills  ";
    cout << "\nInput:  \"" << s2 << "\"" << endl;
    cout << "Brute Force: \"" << reverseWordsBrute(s2) << "\"" << endl;
    cout << "Optimal:     \"" << reverseWordsOptimal(s2) << "\"" << endl;

    return 0;
}
