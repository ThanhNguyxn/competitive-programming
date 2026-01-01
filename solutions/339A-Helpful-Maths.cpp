// 339A – Helpful Maths.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    vector<char> digits;
    for (char c : s) if (isdigit((unsigned char)c)) digits.push_back(c);

    sort(digits.begin(), digits.end());

    for (int i = 0; i < (int)digits.size(); i++) {
        if (i) cout << '+';
        cout << digits[i];
    }
    cout << "\n";
    return 0;
}
